

#include "Stdafx.h"
#include "Registry.h"

#define SD_SIZE (65536 + SECURITY_DESCRIPTOR_MIN_LENGTH)

BOOL CRegistry::OpenKey(enum Keys hKey, LPCTSTR szKey)
{	
   if(RegOpenKeyEx((HKEY)hKey,(LPCTSTR)szKey, 0, KEY_ALL_ACCESS, &m_hKey) == ERROR_SUCCESS)
   {
      return TRUE;
   }
   else
   {
      m_hKey = NULL;
      return FALSE;
   }
}

BOOL CRegistry::CreateKey(enum Keys hKey, LPCTSTR szKey)
{	
   if(RegCreateKeyEx((HKEY)hKey,(LPCTSTR)szKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hKey, NULL) == ERROR_SUCCESS)
   {
      return TRUE;
   }
   else
   {
      m_hKey = NULL;
      return FALSE;
   }
}

BOOL CRegistry::SetValue(LPCTSTR lpValueName, LPCTSTR lpData)
{
   ASSERT(m_hKey != NULL);

   DWORD dwType = REG_SZ;

   if(::RegSetValueEx(m_hKey, (LPCTSTR)lpValueName, 0, dwType, (LPBYTE)(LPCTSTR)lpData, (_tcslen(lpData)+1)*sizeof(WCHAR)) == ERROR_SUCCESS)
   {
      ::RegFlushKey(m_hKey);
      return TRUE;
   }

   return FALSE;
}

BOOL CRegistry::SetValue(LPCTSTR lpValueName, DWORD dwValue)
{
   ASSERT(m_hKey != NULL);

   DWORD dwType = REG_DWORD;

   if(::RegSetValueEx(m_hKey, (LPCTSTR)lpValueName, 0, dwType, (LPBYTE)&dwValue, sizeof(DWORD)) == ERROR_SUCCESS)
   {
      ::RegFlushKey(m_hKey);
      return TRUE;
   }
   return FALSE;
}

BOOL CRegistry::GetValue(LPCTSTR lpValueName, CString& strValue)
{
   BOOL bRet = FALSE;
   LPSTR lpstrValue;
   DWORD dwType = REG_SZ;
   DWORD lpcbData;

   bRet = FALSE;	
   lpstrValue = (LPSTR)malloc(sizeof(char) * 1024);
   memset(lpstrValue, 0, sizeof(char) * 1024);
   lpcbData = 1024;

   if(::RegQueryValueEx(m_hKey,
      lpValueName,
      NULL,
      &dwType, 
      (BYTE*)(LPCTSTR)lpstrValue,
      &lpcbData) == ERROR_SUCCESS)
   {
      bRet = TRUE;
      strValue = (LPCTSTR)lpstrValue;
   }
   else
   {
      strValue.Empty();
   }

   free(lpstrValue);

   return bRet;
}	

BOOL CRegistry::GetValue(LPCTSTR lpValueName, DWORD& dwValue)
{
   BOOL bRet = FALSE;
   DWORD dwType = REG_DWORD;
   DWORD lpcbData = sizeof(DWORD);
   dwValue = 0;	


   if(RegQueryValueEx(m_hKey,
      lpValueName,
      NULL,
      &dwType, 
      (BYTE*)(DWORD)&dwValue,
      &lpcbData) == ERROR_SUCCESS)
      bRet = TRUE;

   return bRet;
}

BOOL CRegistry::DeleteKey(enum Keys hKey, LPCTSTR szKey)
{	
   return ::RegDeleteKey((HKEY)hKey,(LPCTSTR)szKey) == ERROR_SUCCESS;
}

BOOL CRegistry::DeleteValue(LPCTSTR lpValueName)
{	
   if(::RegDeleteValue(m_hKey,(LPCTSTR)lpValueName) == ERROR_SUCCESS)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }

}

void CRegistry::CloseKey()
{
   ::RegCloseKey(m_hKey);
   m_hKey = NULL;
}

BOOL CRegistry::SaveKey(LPCTSTR lpszFileName)
{
   ASSERT(m_hKey != NULL);
   return ::RegSaveKey(m_hKey, lpszFileName, NULL) == ERROR_SUCCESS;
}

BOOL CRegistry::RestoreKey(LPCTSTR lpszFileName, DWORD dwFlags)
{
   ASSERT(m_hKey != NULL);
   return ::RegRestoreKey(m_hKey, lpszFileName, dwFlags) == ERROR_SUCCESS;
}

BOOL CRegistry::LoadKey(enum Keys hKey, LPCTSTR lpszSubKey, LPCTSTR lpszFileName)
{
   return ::RegLoadKey((HKEY)hKey, lpszSubKey, lpszFileName) == ERROR_SUCCESS;
}

BOOL CRegistry::SetKeySecurity()
{
   SECURITY_DESCRIPTOR         sd;
   PSID                        psidWorldSid;
   SID_IDENTIFIER_AUTHORITY    siaWorldSidAuthority = SECURITY_WORLD_SID_AUTHORITY;

   psidWorldSid = (PSID)LocalAlloc(LPTR, GetSidLengthRequired(1));

   InitializeSid(psidWorldSid, &siaWorldSidAuthority, 1);

   *(GetSidSubAuthority(psidWorldSid, 0)) = SECURITY_WORLD_RID;

   DWORD dwResult = RegSetHiveSecurity(m_hKey,
      psidWorldSid,
      OWNER_SECURITY_INFORMATION,
      &sd);

   return (dwResult == 0);
}

DWORD CRegistry::RegSetHiveSecurity(HKEY hKey, PSID psid, SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd)
{
   int     nIdx    =   0;
   HKEY    hSubKey;
   TCHAR    acSubKey    [   MAX_PATH    +   1];
   DWORD   dwRes   =   ERROR_SUCCESS;

   if(!AddAccessRights(hKey, psid, GENERIC_ALL))
      return GetLastError();

   for(;;)
   {
      dwRes = RegEnumKey(hKey,
         nIdx,
         acSubKey,
         MAX_PATH + 1);

      if(ERROR_NO_MORE_ITEMS == dwRes)
      {
         dwRes = 0;
         break;
      }

      if(ERROR_SUCCESS != dwRes)
         break;

      nIdx++;
      //printf("found '%s'\n", acSubKey);

      dwRes = RegOpenKeyEx(hKey,
         acSubKey,
         0,
         KEY_ALL_ACCESS,
         &hSubKey);

      if(ERROR_SUCCESS != dwRes)
      {
         //printf("ERROR opening '%s', reason == %d\n", acSubKey, dwRes);
         continue;
      }

      dwRes = RegSetHiveSecurity(hSubKey,
         psid,
         si,
         psd);

      RegCloseKey(hSubKey);

      if(ERROR_NO_MORE_ITEMS != dwRes)
         break;

      //printf("SUCCEEDED for '%s'\n", acSubKey);
   }

   return dwRes;
}

DWORD CRegistry::AddToRegKeySD(PSECURITY_DESCRIPTOR pRelSD, PSID pGroupSID, DWORD dwAccessMask, HKEY hSecurityRegKey)
{
   PSECURITY_DESCRIPTOR	pAbsSD = NULL;
   PACL					pDACL = NULL;
   DWORD					dwSDLength = 0;
   DWORD					dwSDRevision;
   DWORD					dwDACLLength = 0;
   SECURITY_DESCRIPTOR_CONTROL sdcSDControl;
   PACL					pNewDACL  = NULL;
   DWORD					dwAddDACLLength = 0;
   BOOL					fAceFound = 0;
   BOOL					fHasDACL  = FALSE;
   BOOL					fDACLDefaulted = FALSE; 
   ACCESS_ALLOWED_ACE*		pDACLAce;
   DWORD					dwError = 0;
   DWORD					i;

   // get SD control bits
   if(!GetSecurityDescriptorControl(
      pRelSD, 
      (PSECURITY_DESCRIPTOR_CONTROL)&sdcSDControl, 
      (LPDWORD)&dwSDRevision))
      return GetLastError();

   //check if DACL is present
   if(SE_DACL_PRESENT & sdcSDControl)
   {
      //get dacl 
      if(!GetSecurityDescriptorDacl(pRelSD, (LPBOOL)&fHasDACL, (PACL*)&pDACL, (LPBOOL)&fDACLDefaulted))
         return GetLastError();

      //get dacl length
      dwDACLLength = pDACL->AclSize;

      //now check if SID's ACE is there
      for(i = 0; i < pDACL->AceCount; i++)
      {
         if(!GetAce(pDACL, i, (LPVOID*) &pDACLAce))
            return GetLastError();

         //check if group sid is already there
         if(EqualSid((PSID)&(pDACLAce->SidStart), pGroupSID))
            break;
      }

      //exit if found (means already has been set)
      if(i < pDACL->AceCount)
      {
         dwError = ERROR_GROUP_EXISTS;
         return dwError;
      }

      //get length of new DACL
      dwAddDACLLength = sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(pGroupSID);
   }
   else
      //get length of new DACL
      dwAddDACLLength = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(pGroupSID);

   //get memory needed for new DACL
   if(!(pNewDACL = (PACL)malloc(dwDACLLength + dwAddDACLLength)))
      return GetLastError();

   //get the sd length
   dwSDLength = GetSecurityDescriptorLength(pRelSD);

   //get memory for new SD
   if(!(pAbsSD = (PSECURITY_DESCRIPTOR)malloc(dwSDLength + dwAddDACLLength)))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //change self-relative SD to absolute by making new SD
   if(!InitializeSecurityDescriptor(pAbsSD, SECURITY_DESCRIPTOR_REVISION))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //init new DACL
   if(!InitializeAcl(pNewDACL, dwDACLLength + dwAddDACLLength, ACL_REVISION))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //now add in all of the ACEs into the new DACL (if org DACL is there)
   if(SE_DACL_PRESENT & sdcSDControl)
   { 
      for(i = 0; i < pDACL->AceCount; i++)
      {
         //get ace from original dacl
         if(!GetAce(pDACL, i, (LPVOID *)&pDACLAce))
         {
            dwError = GetLastError();
            goto ErrorExit;
         }

         //now add ace to new dacl
         if(!AddAccessAllowedAce(pNewDACL, 
            ACL_REVISION, 
            pDACLAce->Mask,
            (PSID)&(pDACLAce->SidStart)))
         {
            dwError = GetLastError();
            goto ErrorExit;
         }
      }
   }

   //now add new ACE to new DACL
   if(!AddAccessAllowedAce(pNewDACL, 
      ACL_REVISION, 
      dwAccessMask,
      pGroupSID))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //check if everything went ok
   if(!IsValidAcl(pNewDACL))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //now set security descriptor DACL
   if(!SetSecurityDescriptorDacl(pAbsSD, 
      TRUE, 
      pNewDACL, 
      fDACLDefaulted))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }

   //check if everything went ok
   if(!IsValidSecurityDescriptor(pAbsSD))
   {
      dwError = GetLastError();
      goto ErrorExit;
   }


   //now set the reg key security (this will overwrite any existing security)
   dwError = RegSetKeySecurity(hSecurityRegKey, 
      (SECURITY_INFORMATION)( DACL_SECURITY_INFORMATION),
      pAbsSD);

ErrorExit:

   //free memory
   if(pAbsSD)
      free((VOID *)pAbsSD);
   if(pNewDACL)
      free((VOID *)pNewDACL);

   return dwError;
}

DWORD CRegistry::GetRegKeySecurity(HKEY hRegKey, PSECURITY_DESCRIPTOR* ppRegKeySD)
{
   LONG		lError = 0L;  // reg errors 
   TCHAR		szClassName[MAX_PATH] = _T(""); // Buffer for class name.
   DWORD		dwcSubKeys;     // Number of sub keys.
   DWORD		dwcMaxSubKey;    // Longest sub key size.
   DWORD		dwcMaxClass;    // Longest class string.
   DWORD		dwcValues;     // Number of values for this key.
   DWORD		dwcMaxValueName;   // Longest Value name.
   DWORD		dwcMaxValueData;   // Longest Value data.
   DWORD		dwcSDLength;    // Security descriptor length
   DWORD		dwcClassLen;
   FILETIME	ftLastWriteTime;   // Last write time. 

   if((lError = RegQueryInfoKey(hRegKey, 
      szClassName, 
      &dwcClassLen, 
      NULL, 
      &dwcSubKeys, 
      &dwcMaxSubKey, 
      &dwcMaxClass, 
      &dwcValues,
      &dwcMaxValueName,
      &dwcMaxValueData,
      &dwcSDLength, 
      &ftLastWriteTime))) 
   {
      //PERR ( "RegQueryInfoKey", lError);		
   }
   else
   {
      *ppRegKeySD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, (UINT)dwcSDLength);
      //now get SD 
      if((lError = RegGetKeySecurity(hRegKey, 
         (SECURITY_INFORMATION)(OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION),
         *ppRegKeySD,
         &dwcSDLength)))
      {		
         if(!IsValidSecurityDescriptor(*ppRegKeySD))
         {
            lError = GetLastError();
            //PERR ( "IsValidSecurityDescriptor", lError); 
         }
      }
   }

   return lError;
}

SECURITY_DESCRIPTOR CRegistry::GetWorldSD()
{
   SID_IDENTIFIER_AUTHORITY	siaWorld = SECURITY_WORLD_SID_AUTHORITY;
   PSID						psidEveryone = NULL; 
   int							nSidSize; 
   int							nAclSize;
   PACL						paclNewDacl = NULL; 
   SECURITY_DESCRIPTOR			sd ;

   __try{
      // Create the everyone sid
      if (!AllocateAndInitializeSid(&siaWorld, 1, SECURITY_WORLD_RID, 0,
         0, 0, 0, 0, 0, 0, &psidEveryone))
      {            
         psidEveryone = NULL ; 
         __leave;
      }

      nSidSize = GetLengthSid(psidEveryone) ;
      nAclSize = nSidSize * 2 + sizeof(ACCESS_ALLOWED_ACE) + sizeof(ACCESS_DENIED_ACE) + sizeof(ACL) ;
      paclNewDacl = (PACL) LocalAlloc( LPTR, nAclSize ) ;
      if( !paclNewDacl )
         __leave ; 
      if(!InitializeAcl( paclNewDacl, nAclSize, ACL_REVISION ))
         __leave ; 
      if(!AddAccessDeniedAce( paclNewDacl, ACL_REVISION, WRITE_DAC | WRITE_OWNER, psidEveryone ))
         __leave ; 
      // I am using GENERIC_ALL here so that this very code can be applied to 
      // other objects.  Specific access should be applied when possible.
      if(!AddAccessAllowedAce( paclNewDacl, ACL_REVISION, GENERIC_ALL, psidEveryone ))
         __leave ; 
      if(!InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION ))
         __leave ; 
      if(!SetSecurityDescriptorDacl( &sd, TRUE, paclNewDacl, FALSE ))
         __leave ; 
   }__finally{

      if( !paclNewDacl )
         LocalFree( paclNewDacl );
      if( !psidEveryone )
         FreeSid( psidEveryone );

   }

   return sd; 
}

BOOL CRegistry::AddAccessRights(HKEY hKey, PSID pSID, DWORD dwAcessMask)
{

   //  SD variables.

   UCHAR          ucSDbuf[SD_SIZE];
   PSECURITY_DESCRIPTOR pSD=(PSECURITY_DESCRIPTOR)ucSDbuf;
   DWORD          dwSDLengthNeeded   =   SD_SIZE;

   // ACL variables.

   PACL           pACL;
   BOOL           bDaclPresent;
   BOOL           bDaclDefaulted;
   ACL_SIZE_INFORMATION AclInfo;

   // New ACL variables.

   PACL           pNewACL;
   DWORD          dwNewACLSize;

   // New SD variables.

   UCHAR                NewSD[SECURITY_DESCRIPTOR_MIN_LENGTH];
   PSECURITY_DESCRIPTOR psdNewSD=(PSECURITY_DESCRIPTOR)NewSD;

   // Temporary ACE.

   PVOID          pTempAce;
   UINT           CurrentAceIndex;

   // STEP 2: Get SID (parameter).

   // STEP 3: Get security descriptor (SD) for key.

   if(ERROR_SUCCESS!=RegGetKeySecurity(hKey,
      (SECURITY_INFORMATION)(DACL_SECURITY_INFORMATION),
      pSD,
      &dwSDLengthNeeded))
   {
      printf("Error %d:RegGetKeySecurity\n",GetLastError());
      return(FALSE);
   }

   // STEP 4: Initialize new SD.

   if(!InitializeSecurityDescriptor
      (psdNewSD,SECURITY_DESCRIPTOR_REVISION))
   {
      printf("Error %d:InitializeSecurityDescriptor\n",GetLastError());
      return(FALSE);
   }

   // STEP 5: Get DACL from SD.

   if (!GetSecurityDescriptorDacl(pSD,
      &bDaclPresent,
      &pACL,
      &bDaclDefaulted))
   {
      printf("Error %d:GetSecurityDescriptorDacl\n",GetLastError());
      return(FALSE);
   }

   // STEP 6: Get key ACL size information.

   if(!GetAclInformation(pACL,&AclInfo,sizeof(ACL_SIZE_INFORMATION),
      AclSizeInformation))
   {
      printf("Error %d:GetAclInformation\n",GetLastError());
      return(FALSE);
   }

   // STEP 7: Compute size needed for the new ACL.

   dwNewACLSize = AclInfo.AclBytesInUse +
      sizeof(ACCESS_ALLOWED_ACE) +
      GetLengthSid(pSID) - sizeof(DWORD);

   // STEP 8: Allocate memory for new ACL.

   pNewACL = (PACL)LocalAlloc(LPTR, dwNewACLSize);

   // STEP 9: Initialize the new ACL.

   if(!InitializeAcl(pNewACL, dwNewACLSize, ACL_REVISION2))
   {
      printf("Error %d:InitializeAcl\n",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 10: If DACL is present, copy it to a new DACL.

   if(bDaclPresent)  // Only copy if DACL was present.
   {
      // STEP 11: Copy the file's ACEs to our new ACL.

      if(AclInfo.AceCount)
      {

         for(CurrentAceIndex = 0; CurrentAceIndex < AclInfo.AceCount;
            CurrentAceIndex++)
         {
            // STEP 12: Get an ACE.

            if(!GetAce(pACL,CurrentAceIndex,&pTempAce))
            {
               printf("Error %d: GetAce\n",GetLastError());
               LocalFree((HLOCAL) pNewACL);
               return(FALSE);
            }

            // STEP 13: Add the ACE to the new ACL.

            if(!AddAce(pNewACL, ACL_REVISION, MAXDWORD, pTempAce,
               ((PACE_HEADER)pTempAce)->AceSize))
            {
               printf("Error %d:AddAce\n",GetLastError());
               LocalFree((HLOCAL) pNewACL);
               return(FALSE);
            }

         }
      }
   }

   // STEP 14: Add the access-allowed ACE to the new DACL.

   if(!AddAccessAllowedAce(pNewACL,ACL_REVISION,dwAcessMask, pSID))
   {
      printf("Error %d:AddAccessAllowedAce",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 15: Set our new DACL to the file SD.

   if (!SetSecurityDescriptorDacl(psdNewSD,
      TRUE,
      pNewACL,
      FALSE))
   {
      printf("Error %d:SetSecurityDescriptorDacl",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 16: Set the SD to the key.

   if (ERROR_SUCCESS!=RegSetKeySecurity(hKey, DACL_SECURITY_INFORMATION,psdNewSD))
   {
      printf("Error %d:RegSetKeySecurity\n",GetLastError());
      LocalFree((HLOCAL) pNewACL);
      return(FALSE);
   }

   // STEP 17: Free the memory allocated for the new ACL.

   LocalFree((HLOCAL) pNewACL);

   return(TRUE);
} 