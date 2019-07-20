#ifndef __REGISTRY_H
#define __REGISTRY_H

//注册表相关操作类   add anjie by 2019/1/7
class CRegistry
{
public:
   enum cregRestoreEnum
   {
      regVolatile = REG_WHOLE_HIVE_VOLATILE,
      regRefresh = REG_REFRESH_HIVE,
      regNoLazy = REG_NO_LAZY_FLUSH
   };

   enum Keys
   {
      classesRoot = (DWORD)HKEY_CLASSES_ROOT,
      currentUser = (DWORD)HKEY_CURRENT_USER,
      localMachine = (DWORD)HKEY_LOCAL_MACHINE,
      currentConfig = (DWORD)HKEY_CURRENT_CONFIG,
      users = (DWORD)HKEY_USERS,
      performanceData = (DWORD)HKEY_PERFORMANCE_DATA,	//Windows NT/2000
      dynData = (DWORD)HKEY_DYN_DATA					//Windows 95/98
   };

   CRegistry()
   {
      m_hKey = NULL;
   };

   ~CRegistry()
   {
      CloseKey();
      m_hKey = NULL;
   };

   BOOL OpenKey(enum Keys hKey, LPCTSTR szKey);
   BOOL CreateKey(enum Keys hKey, LPCTSTR szKey);
   BOOL DeleteKey(enum Keys hKey, LPCTSTR szKey);
   BOOL DeleteValue(LPCTSTR lpValueName);
   BOOL GetValue(LPCTSTR lpValueName, CString& strValue);
   BOOL GetValue(LPCTSTR lpValueName, DWORD& dwValue);
   BOOL SetValue(LPCTSTR lpValueName, LPCTSTR lpData);
   BOOL SetValue(LPCTSTR lpValueName, DWORD dwValue);
   BOOL SaveKey(LPCTSTR lpszFileName);
   BOOL RestoreKey(LPCTSTR lpszFileName, DWORD dwFlag);
   BOOL LoadKey(enum Keys hKey, LPCTSTR lpszSubKey, LPCTSTR lpszFileName);
   BOOL SetKeySecurity();
   void CloseKey();	

protected:
   HKEY m_hKey;

private:
   SECURITY_DESCRIPTOR GetWorldSD();
   DWORD GetRegKeySecurity(HKEY hRegKey, PSECURITY_DESCRIPTOR* ppRegKeySD);
   DWORD AddToRegKeySD(PSECURITY_DESCRIPTOR pRelSD, PSID pGroupSID, DWORD dwAccessMask, HKEY hSecurityRegKey);
   DWORD RegSetHiveSecurity(HKEY hKey, PSID psid, SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd);
   BOOL AddAccessRights(HKEY hKey, PSID pSID, DWORD dwAcessMask);
};

#endif

