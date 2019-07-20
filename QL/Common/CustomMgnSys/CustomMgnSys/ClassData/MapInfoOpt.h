#pragma once
#include "CDataTableDlgDefine.h"

class CMapInfoOpt
{
public:
	CMapInfoOpt(void);
	~CMapInfoOpt(void); 

public:
   static void InsertRowData(CString strFiedID,CString strValue,
      MAP_GridCtrl_RowData& map_row_data,ENUM_FIELDTYPE_DATA nFieldType= CB_enum_FieldData_CString,
      ENUM_FIELDTYPE_CONTROL nFieldTypeCtr= CB_enum_FieldCtrl_Text);
};


class CMapInfo
{
public:
	CMapInfo()
	{

	}
	~CMapInfo()
	{

	}

public:
	MAP_GridCtrl_AllData m_mapAllData;
};

typedef std::map<CString/*¹¤ºÅ*/,CMapInfo*> MAP_PERSON_GXRD_INFO;

typedef std::map<CString/*¹¤ÐòÃû*/,MAP_PERSON_GXRD_INFO> MAP_GX_GXRD_INFO;

class CMapDataOpt
{
public:
	CMapDataOpt();
	~CMapDataOpt();

public:

	static MAP_GridCtrl_AllData *GetMapInfo(MAP_GX_GXRD_INFO &MapGxRdData,
		CString strGX,CString strPersonCode)
	{
		auto it = MapGxRdData.find(strGX);
		if (it!=MapGxRdData.end())
		{
			auto itData = it->second.find(strPersonCode);
			if (itData!=it->second.end())
			{
				if (nullptr !=itData->second)
				{
					return &(itData->second->m_mapAllData);
				}	
			}	
		}

		return nullptr;

	}

   //static BOOL ClearMapInfoByGxAndPerson(MAP_GX_GXRD_INFO &MapGxRdData,
   //   CString strGX,CString strPersonCode)
   //{

   //}

	static BOOL AddMapInfo(MAP_GX_GXRD_INFO &MapGxRdData,CString strGX,
		CString strPersonCode, MAP_GridCtrl_AllData *pData)
	{
		if (strGX.IsEmpty())
		{
			return FALSE;
		}
		if (strPersonCode.IsEmpty())
		{
			return FALSE;
		}
		if (nullptr == pData)
		{
			return FALSE;
		}

		MAP_GridCtrl_AllData *pMapData = nullptr;
		auto it = MapGxRdData.find(strGX);
		if (it!=MapGxRdData.end())
		{
			auto itData = it->second.find(strPersonCode);
			if (itData!=it->second.end())
			{
				if (nullptr == itData->second)
				{
					itData->second = new CMapInfo;
				}

				pMapData = &(itData->second->m_mapAllData);

			}
			else
			{
				CMapInfo *pMapInfo = new CMapInfo;
				pMapData = &(pMapInfo->m_mapAllData);
				MAP_PERSON_GXRD_INFO &mapPersonGxInfo = it->second;
				mapPersonGxInfo.insert(MAP_PERSON_GXRD_INFO::value_type(strPersonCode,pMapInfo));
			}
		}
		else
		{
			MAP_PERSON_GXRD_INFO mapPerson;
			CMapInfo *pMapInfo = new CMapInfo;
			pMapData = &(pMapInfo->m_mapAllData);


			mapPerson.insert(MAP_PERSON_GXRD_INFO::value_type(strPersonCode,pMapInfo));
			MapGxRdData.insert(MAP_GX_GXRD_INFO::value_type(strGX,mapPerson));
		}

		{
			auto itInfo = pData->begin();
			for (;itInfo!=pData->end(); ++itInfo)
			{
				auto itFind = pMapData->find(itInfo->first);
				if (itFind!=pMapData->end())
				{
					itFind->second = itInfo->second;
				}
				else
				{
					pMapData->insert(MAP_GridCtrl_AllData::value_type(itInfo->first,itInfo->second));
				}
			}
		}

		return TRUE;
	}

	static BOOL ClearMapInfo(MAP_GX_GXRD_INFO &MapGxRdData)
	{
		auto it=MapGxRdData.begin();
		while(it!=MapGxRdData.end())
		{
			auto &mapPersonRd = it->second;
			auto itPerson = mapPersonRd.begin();
			while (itPerson != mapPersonRd.end())
			{
				auto pMapInfo = itPerson->second;
				if (nullptr != pMapInfo)
				{
					pMapInfo->m_mapAllData.clear();
					delete pMapInfo;
					pMapInfo = nullptr;
				}

				++itPerson;
			}
			mapPersonRd.clear();

			++it;
		}

		MapGxRdData.clear();

		return TRUE;
	}
	//		by WangZY 2018/04/23
	static CString CStrWeightKG2G(CString strKG)

	{
		CString strG;

		double fTmp = _ttof(strKG)*1000;
		strG.Format(_T("%.1f"),fTmp);

		return strG;
	}

	//		by WangZY 2018/04/23
	static CString CStrWeightG2KG(CString strG)
	{
		CString strKG;

		double fTmp = _ttof(strG)/1000;
		strKG.Format(_T("%.4f"),fTmp);

		return strKG;
	}


	static void ConvertWeightUnitKg2G(__inout MAP_GridCtrl_AllData &mapData,
		__in std::vector<CString> &vecWeightField)
	{
		auto it=mapData.begin();
		while(it!=mapData.end())
		{
			for (auto itVec=vecWeightField.begin();
				itVec!=vecWeightField.end();++itVec)
			{
				auto itVal = it->second.find(*itVec);
				if (itVal!=it->second.end())
				{
					CString strVal = CStrWeightKG2G(itVal->second.strValue);
					itVal->second.strValue = strVal;
				}
			}

			++it;
		}
	}

	//std::vector<>
};

