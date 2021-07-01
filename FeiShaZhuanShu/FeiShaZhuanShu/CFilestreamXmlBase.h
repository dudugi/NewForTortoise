/********************************************************************
//  ����:           lvjj
//  CopyRight(c)    2011 Burnon All Rights Reserved 
//  ����ʱ��:       2011/12/12 11:26
//  ������:         xml����ʽ�����ļ�����
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#pragma once

//#include "CFileBase.h"
//#include "tinyxml.h"
#include <string>
#include <vector>
#include <map>


#define DECL_VER "1.0"				//�汾����
#define DECL_ENCODE "utf-8"			//��������

#define NAME(name)   #name    //ÿ�����ݶ�Ӧ�Ĵ洢���������ݱ�����һ����

using std::string;
using std::vector;
using std::map;


class CFilestreamXmlBase//:public CFileBase 
{
public:
	CFilestreamXmlBase(void);
	virtual ~CFilestreamXmlBase(void);

protected:	
	TiXmlDocument* m_pDoc;  //xml����ָ��
//public:
//   virtual int FileOpen(LPCTSTR lpszPathName) = 0;
//protected:
//	virtual int FileSave(LPCTSTR lpszPathName){return 0;};
//
//   //�½�������
//   virtual int DataNew() = 0;

protected:
	//��ʼ�����汾�ͱ���
	virtual bool Init(void);
	//�Ӹ��ڵ�
	virtual TiXmlElement* AddRootDataNode(const string& RootName );
	//��ȡ���ڵ�ָ��
	virtual bool GetRootDataNode(TiXmlElement** RootNode);
	////��ָ���ڵ��м����ӽڵ�
	//virtual TiXmlElement* AddSubDataNode(const string& SubName,TiXmlNode* parentNode);
	////��ָ���ڵ��л�ȡ�ӽڵ�
	//virtual bool GetSubDataNode(const string& SubName,TiXmlElement** SubNode,TiXmlNode* parentNode);

	//-----------------------------------
	// ������:  [StreamCreate]
	// ����ֵ:  [bool]   
	// ����:    [string outStream]         ������xml��/out   
	// ��������:������
	// ����:    lvjj 2011/12/12 11:20
	// �޸�ʱ��:
	// �޸�Ŀ��:
	//-----------------------------------
	//virtual bool StreamCreate(string& outStream) = 0;
public:
	//-----------------------------------
	// ������:  [StreamParse]
	// ����ֵ:  [bool]   
	// ����:    [const string inStream]    �����xml��/in      
	// ��������:������
	// ����:    lvjj 2011/12/12 11:20
	// �޸�ʱ��:
	// �޸�Ŀ��:
	//-----------------------------------
	//virtual bool StreamParse(const string& inStream) = 0;

	//-----------------------------------
	// ������:  [GetStream]
	// ����ֵ:  [void]   
	// ����:    [string & strStream]      /out      
	// ��������:��ȡ��
	// ����:    lvjj 2011/12/12 21:40
	// �޸�ʱ��:
	// �޸�Ŀ��:
	//-----------------------------------
	virtual void GetStream(string& strStream);

public:
	//-----------------------------------
	// ������:  [SetObjectData]
	// ����ֵ:  [bool]   
	// ����:    [const char * pData]            
	// ����:    [DWORD dwSize]            
	// ��������:���ö������ݣ�����Դ��Kxx�ļ�
	// ����:    lvjj 2011/12/13 20:37
	// �޸�ʱ��:
	// �޸�Ŀ��:
	//-----------------------------------
	//virtual bool SetObjectData(const char* pData, DWORD dwSize);

	//-----------------------------------
	// ������:  [GetObjectData]
	// ����ֵ:  [bool]   
	// ����:    [IKnitFile * pKnitFile]            
	// ����:    [LP_SUBFILEPARAM pSubFileParam]            
	// ��������:��ȡ�������ݣ��Ա�д��Kxx�ļ�
	// ����:    lvjj 2011/12/13 20:37
	// �޸�ʱ��:
	// �޸�Ŀ��:
	//-----------------------------------
	//virtual bool GetObjectData(IKnitFile* pKnitFile, LP_SUBFILEPARAM pSubFileParam);


};

////һ���������� д����
//template<class T>
//void SetData(const string& DataName, const T Data,TiXmlElement* operateNode)
//{
//	if(NULL == operateNode) return;
//
//	std::ostringstream ostr;
//	ostr<<Data;
//
//	operateNode->SetAttribute(DataName,ostr.str());
//}

////һ���������� ������
//template<class T>
//bool GetData( const string& DataName,T* Data,TiXmlElement* operateNode )
//{
//	if(NULL == operateNode||DataName.empty()) return false;
//
//	const string* tmpstr = operateNode->Attribute(DataName);
//	if(NULL != tmpstr)
//	{
//		std::istringstream istr(*tmpstr);
//		istr>>*Data;
//		return true;
//	}
//	return false;
//}

////����vector<T>�������� д����
//template<class T>
//void SetVectorData( const string& DataName,const vector<T>& Data,TiXmlElement* operateNode )
//{
//	if(NULL == operateNode) return;
//
//	std::ostringstream ostr;
//	vector<T>::const_iterator it = Data.begin();
//	for (;Data.end()!=it;++it)
//		ostr<<' '<<*it;
//
//	operateNode->SetAttribute(DataName,ostr.str());
//}
//
////����vector<T>�������� ������
//template<class T>
//bool GetVectorData( const string& DataName,vector<T>& Data,TiXmlElement* operateNode )
//{
//	if(NULL == operateNode||DataName.empty()||!Data.empty()) return false;
//
//	const string* tmpstr = operateNode->Attribute(DataName);
//	if(NULL != tmpstr)
//	{
//		std::istringstream istr(*tmpstr);
//		T one_data;
//		while(istr>>one_data)
//			Data.push_back(one_data);
//		return true;
//	}
//	return false;
//}
//
////����map<T_key,T_vaule>�������� д����
//template<class T_key,class T_vaule>
//void SetMapData( const string& DataName,const map<T_key,T_vaule>& Data,TiXmlElement* operateNode )
//{
//	if(NULL == operateNode) return;
//
//	std::ostringstream ostr;
//	map<T_key,T_vaule>::const_iterator it = Data.begin();
//	for (;Data.end()!=it;++it)
//		ostr<<' '<<it->first<<','<<it->second;
//
//	operateNode->SetAttribute(DataName,ostr.str());
//}
//
////����map<T_key,T_vaule>�������� ������
//template<class T_key,class T_vaule>
//bool GetMapData( const string& DataName,map<T_key,T_vaule>& Data,TiXmlElement* operateNode )
//{
//	if(NULL == operateNode||DataName.empty()||!Data.empty()) return false;
//
//	const string* tmpstr = operateNode->Attribute(DataName);
//	if(NULL != tmpstr)
//	{
//		CStringA fixstr(tmpstr->c_str());
//		fixstr.Replace(',',' ');
//		std::istringstream istr(fixstr.GetBuffer());
//		T_key one_data_key;
//		T_vaule one_data_value;
//		while(istr>>one_data_key && istr>>one_data_value)
//		{
//			Data.insert(std::make_pair(one_data_key,one_data_value));
//		}
//		return true;
//	}
//	return false;
//}