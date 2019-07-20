#include "stdafx.h"
#include "TabStopManager.h"

#include <list>
#include <vector>
#include "..\tinyxml\tinyxml.h"

using namespace std;

const char *STR_DELIM = "::";
static BOOL AnalyzeXMLControl(TiXmlElement *pControl, const deque<int> &deqSubDialogues,
   std::pair<CTabStopManager::CtrlID, CTabStopManager::CCtrlInfo> *pIDPair);

std::vector<CStringW> CTabStopManager::SplitStrW(const CStringW &strOrg, const WCHAR *delim)
{
   std::vector<WCHAR> vecProcessTCHAR(strOrg.GetLength() + 1);

   memcpy(vecProcessTCHAR.data(), (LPCWSTR)strOrg, strOrg.GetLength() * sizeof(WCHAR));
   WCHAR *pTUploadChar = ::wcstok(vecProcessTCHAR.data(), delim);

   std::vector<CStringW> setResultString;

   while(pTUploadChar != NULL)
   {
      CStringW strExt;

      strExt = pTUploadChar;


      setResultString.push_back(strExt);
      pTUploadChar = ::wcstok(NULL, delim);
   }
   return setResultString;
}

std::vector<CStringA> SplitStr(const CStringA &strOrg, const char *delim)
{
   std::vector<char> vecProcessTCHAR(strOrg.GetLength() + 1);

   memcpy(vecProcessTCHAR.data(), (LPCSTR)strOrg, strOrg.GetLength() * sizeof(char));
   char *pTUploadChar = ::strtok(vecProcessTCHAR.data(), delim);

   std::vector<CStringA> setResultString;

   while(pTUploadChar != NULL)
   {
      CStringA strExt;

      strExt = pTUploadChar;


      setResultString.push_back(strExt);
      pTUploadChar = ::strtok(NULL, delim);
   }
   return setResultString;
}

CTabStopManager::CTabStopManager()
   :m_bHasReadFile(FALSE),m_dVersion(1.)
{

}

CTabStopManager &CTabStopManager::Instance()
{
   static CTabStopManager Manager;
   return Manager;
}

static BOOL AnalyzeXMLChildDialogue(TiXmlElement *pChildDialogue, deque<int> *pdeqSubDialogues,
   std::list<std::pair<CTabStopManager::CtrlID, CTabStopManager::CCtrlInfo>> *plstIDPair)
{
   if (!plstIDPair)
      return FALSE;
   if (!pdeqSubDialogues)
      return FALSE;

   TiXmlElement *pControlOrChild = pChildDialogue->FirstChildElement();

   while (pControlOrChild)
   {
      const char *pText = pControlOrChild->Value();
      if (0 == strcmp("Control", pText))
      {
         std::pair<CTabStopManager::CtrlID, CTabStopManager::CCtrlInfo> IDPair;
         if (AnalyzeXMLControl(pControlOrChild, *pdeqSubDialogues, &IDPair))
         {
            plstIDPair->push_back(IDPair);
         }
      }
      else if (0 == strcmp("ChildDialogue", pText))
      {
         const char *pszIDD = pControlOrChild->Attribute("IDD");
         if (pszIDD)
         {
            int nIDD = atoi(pszIDD);
            pdeqSubDialogues->push_back(nIDD);
            AnalyzeXMLChildDialogue(pControlOrChild, pdeqSubDialogues, plstIDPair);
            pdeqSubDialogues->pop_back();
         }
      }
      pControlOrChild = pControlOrChild->NextSiblingElement();
   }

   return TRUE;
}

static BOOL AnalyzeXMLControl(TiXmlElement *pControl, const deque<int> &deqSubDialogues,
   std::pair<CTabStopManager::CtrlID, CTabStopManager::CCtrlInfo> *pIDPair)
{
   if (!pIDPair)
      return FALSE;

   const char *pszID = pControl->Attribute("ID");
   if (!pszID)
      return FALSE;

   auto vec = SplitStr(pszID, STR_DELIM);
   if (vec.empty())
      return FALSE;

   CTabStopManager::CtrlID nID(deqSubDialogues.begin(), deqSubDialogues.end()); //继承当前层次
   for (auto Iter = vec.begin(); Iter != vec.end();++Iter)
   {
      nID.push_back(atoi(*Iter));
   }
   CTabStopManager::CtrlID nNextID; //无NextID则为empty
   const char *pszNextID = pControl->Attribute("NextID");
   if (pszNextID)
   {
      if (0 != strncmp(STR_DELIM, pszNextID, strlen(STR_DELIM))) //如果::开头，则NextID被解读为全路径（层次）
         nNextID.assign(deqSubDialogues.begin(), deqSubDialogues.end()); //继承当前层次

      auto vec = SplitStr(pszNextID, STR_DELIM);

      for (auto Iter = vec.begin(); Iter != vec.end();++Iter)
      {
         nNextID.push_back(atoi(*Iter));
      }
   }
   pIDPair->first.swap(nID);
   pIDPair->second.m_NextCtrlID.swap(nNextID);

   const char *pszType = pControl->Attribute("Type");
   if (pszType)
   {
      pIDPair->second.m_sType = pszType;
   }

   const char *pszLeaveCondition = pControl->Attribute("LeaveCondition");
   if (pszLeaveCondition)
   {
      pIDPair->second.m_sCondition = pszLeaveCondition;
   }

   const char *pszEnterEvent = pControl->Attribute("OnEnter");
   if (pszEnterEvent)
   {
      pIDPair->second.m_sOnEnter = pszEnterEvent;
   }
   return TRUE;
}

BOOL CTabStopManager::ReadFile(const CStringA &sPath)
{
   if (!PathFileExistsA(sPath))
   {
      return FALSE;
   }

   TiXmlDocument doc;
   if (!doc.LoadFile(sPath,TIXML_ENCODING_UNKNOWN))
   {
      return FALSE;
   }

   TiXmlElement *pRoot = doc.FirstChildElement();
   if (!pRoot)
      return FALSE;

   const char *pszVersion = pRoot->Attribute("Version");
   if (pszVersion)
   {
      m_dVersion = atof(pszVersion);
   }

   std::map<int, CTabInOneWindow> mapIDD2ID2NextID;

   TiXmlElement *pDialogue = pRoot->FirstChildElement("Dialogue");
   while (pDialogue)
   {
      const char *pszIDD = pDialogue->Attribute("IDD");
      if (pszIDD)
      {
         int nIDD = atoi(pszIDD);
         CTabInOneWindow TabInOneWindow;
         const char *pszFirstControlID = pDialogue->Attribute("FirstControl");
         if (pszFirstControlID)
         {
            //TabInOneWindow.m_nFirstFocusID.push_back(atoi(pszFirstControlID));
            auto vec = SplitStr(pszFirstControlID, STR_DELIM);
            for (auto Iter = vec.begin(); Iter != vec.end();++Iter)
            {
               TabInOneWindow.m_nFirstFocusID.push_back(atoi(*Iter));
            }
         }

         TiXmlElement *pKey = pDialogue->FirstChildElement("Key");
         while (pKey)
         {
            const char *pszHexCode = pKey->Attribute("HexCode");
            WPARAM uHexValue = VK_TAB;
            if (pszHexCode && strlen(pszHexCode) != 0)
            {
               uHexValue = (WPARAM)strtoul(pszHexCode, 0, 16);
               TRACE(_T("%d"), uHexValue);
            }

            std::list<std::pair<CtrlID, CCtrlInfo>> lstIDPair;

            TiXmlElement *pControlOrChild = pKey->FirstChildElement();

            while (pControlOrChild)
            {
               const char *pText = pControlOrChild->Value();
               if (0 == strcmp("Control", pText))
               {
                  std::pair<CTabStopManager::CtrlID, CTabStopManager::CCtrlInfo> IDPair;
                  if (AnalyzeXMLControl(pControlOrChild, deque<int>(), &IDPair))
                  {
                     lstIDPair.push_back(IDPair);
                  }
               }
               else if (0 == strcmp("ChildDialogue", pText))
               {
                  const char *pszIDD = pControlOrChild->Attribute("IDD");
                  if (pszIDD)
                  {
                     int nIDD = atoi(pszIDD);
                     deque<int> deqSubDialogues(1, nIDD);
                     AnalyzeXMLChildDialogue(pControlOrChild, &deqSubDialogues, &lstIDPair);
                  }
               }
               pControlOrChild = pControlOrChild->NextSiblingElement();
            }

            //如果nextID没设置，则为下一个
            std::map<CtrlID, CCtrlInfo> mapID2ID;
            for (auto Iter = lstIDPair.begin(); Iter != lstIDPair.end(); ++Iter)
            {
               if (Iter->second.m_NextCtrlID.empty())
               {
                  auto Iter2 = Iter;
                  ++Iter2;
                  if (Iter2 == lstIDPair.end())
                  {
                     Iter2 = lstIDPair.begin();
                  }
                  Iter->second.m_NextCtrlID = Iter2->first;
               }

               mapID2ID[Iter->first] = Iter->second;
            }

            TabInOneWindow.m_mapKey2ID2ID[uHexValue] = mapID2ID;

            pKey = pKey->NextSiblingElement("Key");
         }

         mapIDD2ID2NextID[nIDD] = TabInOneWindow;
      }

      pDialogue = pDialogue->NextSiblingElement("Dialogue");
   }

   m_mapIDD2ID2NextID.swap(mapIDD2ID2NextID);
   m_bHasReadFile = TRUE;
   return TRUE;
}

CTabStopManager::CtrlID CTabStopManager::GetNextTabID(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode)
{
   if (!m_bHasReadFile)
      return CtrlID();
   auto IterFind = m_mapIDD2ID2NextID.find(nTopParentIDD);
   if (IterFind != m_mapIDD2ID2NextID.end())
   {
      auto IterFindKey = IterFind->second.m_mapKey2ID2ID.find(uKeyCode);
      if (IterFindKey != IterFind->second.m_mapKey2ID2ID.end())
      {
         auto IterFindID = IterFindKey->second.find(nControlID);
         if (IterFindID != IterFindKey->second.end())
         {
            return IterFindID->second.m_NextCtrlID;
         }
      }
   }
   return CtrlID();
}

CTabStopManager::CtrlID CTabStopManager::GetFirstID(int nTopParentIDD)
{
   if (!m_bHasReadFile)
      return CtrlID();
   auto IterFind = m_mapIDD2ID2NextID.find(nTopParentIDD);
   if (IterFind != m_mapIDD2ID2NextID.end())
   {
      return IterFind->second.m_nFirstFocusID;
   }
   return CtrlID();
}

BOOL CTabStopManager::SetCheckFunction(const CString &sControlType, 
   std::function<BOOL(HWND hWnd, const CString &sCondition)> function)
{
   m_mapTypeToFunction[sControlType].m_funcCheckCanLeave = function;
   return TRUE;
}

BOOL CTabStopManager::SetEnterEventFunction(const CString &sControlType, 
   std::function<BOOL(HWND hWnd, const CString &sCondition)> function)
{
   m_mapTypeToFunction[sControlType].m_funcOnEnter = function;
   return TRUE;
}

BOOL CTabStopManager::CheckCanLeave(const CString &sType, const CString &sCondition, HWND hControlWnd)
{
   auto FindIter = m_mapTypeToFunction.find(sType);
   if (FindIter == m_mapTypeToFunction.end())
      return FALSE;

   if (!FindIter->second.m_funcCheckCanLeave)
      return FALSE;
   return FindIter->second.m_funcCheckCanLeave(hControlWnd, sCondition);
}

BOOL CTabStopManager::DoOnEnter(const CString &sType, const CString &sOnEnter, HWND hControlWnd)
{
   auto FindIter = m_mapTypeToFunction.find(sType);
   if (FindIter == m_mapTypeToFunction.end())
      return FALSE;

   if (!FindIter->second.m_funcOnEnter)
      return FALSE;
   return FindIter->second.m_funcOnEnter(hControlWnd, sOnEnter);
}

BOOL CTabStopManager::GetTabInfo(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode,
   CCtrlInfo *pControlInfo)
{
   if (!m_bHasReadFile)
      return FALSE;
   if (!pControlInfo)
      return FALSE;
   auto IterFind = m_mapIDD2ID2NextID.find(nTopParentIDD);
   if (IterFind == m_mapIDD2ID2NextID.end())
      return FALSE;
   auto IterFindKey = IterFind->second.m_mapKey2ID2ID.find(uKeyCode);
   if (IterFindKey == IterFind->second.m_mapKey2ID2ID.end())
      return FALSE;
   auto IterFindID = IterFindKey->second.find(nControlID);
   if (IterFindID == IterFindKey->second.end())
      return FALSE;

   *pControlInfo = IterFindID->second;
   return TRUE;
}