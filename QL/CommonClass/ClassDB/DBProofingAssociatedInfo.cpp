#include "StdAfx.h"
#include "DBProofingAssociatedInfo.h"
#include "DBKeyDef.h"

///////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDBProofingAssociatedData,  CDataMid, 1)


CDBProofingAssociatedData::CDBProofingAssociatedData()
{
   ResetData(); 
} 

CDBProofingAssociatedData::~CDBProofingAssociatedData()
{
}

void CDBProofingAssociatedData::ResetData()
{
   m_nID             =  0;
   m_nType           =  En_Type_NULL;
   m_nAssociatedID   =  0;
}

void CDBProofingAssociatedData:: Copy(CDBProofingAssociatedData *pData)
{
   ASSERT(pData != NULL);
   CDataMid::Copy(pData);

   m_nID             =  pData->m_nID          ;
   m_nType           =  pData->m_nType        ;
   m_nAssociatedID   =  pData->m_nAssociatedID;
}

