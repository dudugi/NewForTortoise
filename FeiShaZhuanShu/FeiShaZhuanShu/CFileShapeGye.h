#pragma once
#include "ShapeData.h"
//#include "tinyxml.h"
#include "CFilestreamXmlBase.h"

//#define DEF_SHAPEFILE_NAME L"ShapeDef\\ShapeDefine.gye"
/*
   背面提花 文件定义
*/
class CFileShapeGye:public CFilestreamXmlBase
{
public:
   CFileShapeGye(void);
public:  
   virtual ~CFileShapeGye(void);

public:

   //int  FileNew();

   //int FileNewBySysGye();

   //virtual int FileWrite(const CKnitData *pdata);  //写入数据

   //virtual int FileRead(CKnitData *pdata);  //获取数据

   //virtual int FileSave(LPCTSTR lpszPathName = NULL);

   //virtual bool GetObjectData( IKnitFile* pKnitFile, LP_SUBFILEPARAM pSubFileParam );

   //virtual bool SetObjectData( const char* pData, DWORD dwSize );

   BOOL FileOpen(LPCTSTR lpFilePath, CShapeProfileData *pShapeData);
   BOOL FileWrite(CShapeProfileData *pShapeData);
   //BOOL WriteByStream(CString strFileName);
private:
   //获取可用的gye默认路径 优先用户路径，如果用户路径不存在的情况下使用系统路径
   //CString GetDefaultGyePath();
private:
   BOOL GetShapeSubNode(const CStringW SubName,TiXmlElement** SubNode);
   void InitXmlDoc();
   virtual int DataNew(){return 0;};
   BOOL ReadShapeData(CShapeProfileData *pShapeData);
   BOOL WriteShapeData(CShapeProfileData *pShapeData);
   //BOOL ReadShapeList(CString &strNodeName,TYPE_LIST_SHAPE &shapelist);
   //BOOL WriteShapeList(CString &strNodeName,TYPE_LIST_SHAPE &shapelist);
   //BOOL ReadProfileData(CShapeProfileData *pShapeData);
   //BOOL WriteProfileData(CShapeProfileData *pShapeData);
   //BOOL ReadMacTypeData(CShapeProfileData *pShapeData);
   //BOOL WriteMacTypeData(CShapeProfileData *pShapeData);
   BOOL ReadBodySetData(CShapeProfileData *pShapeData);
   BOOL WriteBodySetData(CShapeProfileData *pShapeData);
   BOOL WriteNeckSetData(CShapeProfileData *pShapeData);
   BOOL ReadNeedleSetData(CShapeProfileData *pShapeData);
   //TYPE_VEC_KNITSIGN GetBianmaInt(CString str);
   //CString GetBianma(TYPE_VEC_KNITSIGN data);
   BOOL WriteNeedleSetData(CShapeProfileData *pShapeData);
   BOOL ReadOtherSetData(CShapeProfileData *pShapeData);
   BOOL ReadBottomSetData(CShapeProfileData *pShapeData);
   BOOL WriteBottomSetData(CShapeProfileData *pShapeData);
   BOOL WriteParamSetData(CShapeProfileData *pShapeData);
   //void ClearBoardDataChange(std::vector<CString> &str_vec,CKnitData &data,BOOL action_idex);
   BOOL ReadBoardSetData(CShapeProfileData *pShapeData);
   BOOL WriteBoardSetData(CShapeProfileData *pShapeData);
   //BOOL ReadCycleData( CString &strNodeName, MAP_CYCLEARTS &shapelist );
   BOOL ReadNeckSetData(CShapeProfileData *pShapeData);
   //BOOL WriteCycleData( CString &strNodeName, MAP_CYCLEARTS &shapelist );
   BOOL WriteOtherSetData(CShapeProfileData *pShapeData);
   BOOL ReadParamSetData(CShapeProfileData *pShapeData);
   bool StreamParseSub(const string& inStream, CShapeProfileData *pShapeData);
   void GetStreamSub(string& strStream, CShapeProfileData *pShapeData);
public:
   bool StreamParse(const string& inStream, CShapeProfileData *pShapeData);
   void GetStream(string& strStream, CShapeProfileData *pShapeData);
   //bool StreamCreate(string& outStream);

   //BOOL WriteModuleInfo( CString &strNodeName, CShapeProfileData *pShapeData);
   //BOOL ReadModuleInfo( CString &strNodeName, CShapeProfileData *pShapeData);
   //void SetShapeData(CShapeProfileData * pData)
   //{
   //   m_pShapeData = pData;
   //}
private:
   CStringW m_strFilePathName;
   //CShapeProfileData *m_pShapeData;
};
