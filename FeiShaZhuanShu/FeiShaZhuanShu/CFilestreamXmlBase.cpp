#include "StdAfx.h"
#include "CFilestreamXmlBase.h"
//#include "rnstring.h"


CFilestreamXmlBase::CFilestreamXmlBase(void)
{
	m_pDoc = new TiXmlDocument;
}

CFilestreamXmlBase::~CFilestreamXmlBase(void)
{
	if (NULL != m_pDoc)
	{
		m_pDoc->Clear();
		delete m_pDoc;
	}
}

//��ȡ��
void CFilestreamXmlBase::GetStream( string& strStream )
{
	TiXmlPrinter printer;
	m_pDoc->Accept(&printer);

	strStream = printer.CStr();
}

//bool CFilestreamXmlBase::SetObjectData( const char* pData, DWORD dwSize )
//{
//	// �ļ������ڣ�����
//	if (0 == dwSize)
//	{
//		DataNew();
//		return true;
//	}
//	// �����ļ���������
//	else
//	{
//      std::string inStream;
//      inStream.insert(inStream.begin(),pData,pData + dwSize);
//		if (false == StreamParse(inStream))
//			return false;
//
//	}
//
//	return true;
//}

//bool CFilestreamXmlBase::GetObjectData( IKnitFile* pKnitFile, LP_SUBFILEPARAM pSubFileParam )
//{
//	ASSERT(pSubFileParam);
//	ASSERT(pKnitFile);
//
//	//��ȡ�洢xml�� 
//	string xmlStr;
//	if(false == StreamCreate(xmlStr))
//		return true;
//
//	//�����ڴ�
//	unsigned long lBufferSize = xmlStr.length();
//	if (false == (*pKnitFile)->AskBuffer(lBufferSize + 1, &(pSubFileParam->pBuffer)))
//		return false;
//
//	// ���ݲ�Ϊ0ʱ�����ڴ�
//	if (0 < lBufferSize)
//	{
//		memcpy(pSubFileParam->pBuffer, xmlStr.data(), lBufferSize);
//	}
//
//   strcpy_s(pSubFileParam->szSuffixName, 8, RnString::WCStr2StrACP(m_exName).c_str());
//	pSubFileParam->iTypeCompress = 0;
//	pSubFileParam->iTypeCrypt    = 0;
//	pSubFileParam->ulFileSize    = lBufferSize;
//
//	return true;
//}

bool CFilestreamXmlBase::Init(void)
{
	if(NULL == m_pDoc) return false;

	m_pDoc->Clear();
	//�����ڵ�
	TiXmlDeclaration* decl = new TiXmlDeclaration(DECL_VER,DECL_ENCODE, "" );
	m_pDoc->LinkEndChild(decl);

	return true;
}

TiXmlElement* CFilestreamXmlBase::AddRootDataNode( const string& RootName )
{
	if(NULL == m_pDoc)	return NULL;

	//���ڵ�
	TiXmlElement* root = new TiXmlElement(RootName.c_str());
	m_pDoc->LinkEndChild(root);

	return root;
}

//TiXmlElement* CFilestreamXmlBase::AddSubDataNode( const string& SubName,TiXmlNode* parentNode)
//{
//	if(NULL == parentNode) return NULL;
//
//	if(NULL != parentNode->FirstChild(SubName.c_str())) return NULL;//��ֹ����ͬ���ڵ�
//	//�ӽڵ�
//	TiXmlElement* SubEle = new TiXmlElement(SubName.c_str());
//	parentNode->LinkEndChild(SubEle);
//
//	return SubEle;
//}

bool CFilestreamXmlBase::GetRootDataNode(TiXmlElement** RootNode)
{
	if(NULL == m_pDoc||NULL == (*RootNode = m_pDoc->RootElement()))
		return false;

	return true	;
}

//bool CFilestreamXmlBase::GetSubDataNode( const string& SubName,TiXmlElement** SubNode,TiXmlNode* parentNode )
//{
//	if(NULL == parentNode||NULL == (*SubNode = parentNode->FirstChildElement(SubName.c_str())))
//		return false;
//
//	return true;
//}