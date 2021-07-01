/********************************************************************
//  作者:           lvjj
//  CopyRight(c)    2011 Burnon All Rights Reserved 
//  创建时间:       2011/12/12 11:26
//  类描述:         xml流形式保存文件基类
//  修改时间:       
//  修改目的:       
*********************************************************************/
#pragma once

//#include "CFileBase.h"
//#include "tinyxml.h"
#include <string>
#include <vector>
#include <map>


#define DECL_VER "1.0"				//版本声明
#define DECL_ENCODE "utf-8"			//编码声明

#define NAME(name)   #name    //每个数据对应的存储名（与数据变量名一样）

using std::string;
using std::vector;
using std::map;


class CFilestreamXmlBase//:public CFileBase 
{
public:
	CFilestreamXmlBase(void);
	virtual ~CFilestreamXmlBase(void);

protected:	
	TiXmlDocument* m_pDoc;  //xml对象指针
//public:
//   virtual int FileOpen(LPCTSTR lpszPathName) = 0;
//protected:
//	virtual int FileSave(LPCTSTR lpszPathName){return 0;};
//
//   //新建数据类
//   virtual int DataNew() = 0;

protected:
	//初始化：版本和编码
	virtual bool Init(void);
	//加根节点
	virtual TiXmlElement* AddRootDataNode(const string& RootName );
	//获取根节点指针
	virtual bool GetRootDataNode(TiXmlElement** RootNode);
	////往指定节点中加入子节点
	//virtual TiXmlElement* AddSubDataNode(const string& SubName,TiXmlNode* parentNode);
	////从指定节点中获取子节点
	//virtual bool GetSubDataNode(const string& SubName,TiXmlElement** SubNode,TiXmlNode* parentNode);

	//-----------------------------------
	// 函数名:  [StreamCreate]
	// 返回值:  [bool]   
	// 参数:    [string outStream]         生产的xml流/out   
	// 函数描述:创建流
	// 作者:    lvjj 2011/12/12 11:20
	// 修改时间:
	// 修改目的:
	//-----------------------------------
	//virtual bool StreamCreate(string& outStream) = 0;
public:
	//-----------------------------------
	// 函数名:  [StreamParse]
	// 返回值:  [bool]   
	// 参数:    [const string inStream]    输入的xml流/in      
	// 函数描述:流解析
	// 作者:    lvjj 2011/12/12 11:20
	// 修改时间:
	// 修改目的:
	//-----------------------------------
	//virtual bool StreamParse(const string& inStream) = 0;

	//-----------------------------------
	// 函数名:  [GetStream]
	// 返回值:  [void]   
	// 参数:    [string & strStream]      /out      
	// 函数描述:获取流
	// 作者:    lvjj 2011/12/12 21:40
	// 修改时间:
	// 修改目的:
	//-----------------------------------
	virtual void GetStream(string& strStream);

public:
	//-----------------------------------
	// 函数名:  [SetObjectData]
	// 返回值:  [bool]   
	// 参数:    [const char * pData]            
	// 参数:    [DWORD dwSize]            
	// 函数描述:设置对象数据，数据源自Kxx文件
	// 作者:    lvjj 2011/12/13 20:37
	// 修改时间:
	// 修改目的:
	//-----------------------------------
	//virtual bool SetObjectData(const char* pData, DWORD dwSize);

	//-----------------------------------
	// 函数名:  [GetObjectData]
	// 返回值:  [bool]   
	// 参数:    [IKnitFile * pKnitFile]            
	// 参数:    [LP_SUBFILEPARAM pSubFileParam]            
	// 函数描述:获取对象数据，以备写入Kxx文件
	// 作者:    lvjj 2011/12/13 20:37
	// 修改时间:
	// 修改目的:
	//-----------------------------------
	//virtual bool GetObjectData(IKnitFile* pKnitFile, LP_SUBFILEPARAM pSubFileParam);


};

////一般数据类型 写操作
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

////一般数据类型 读操作
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

////容器vector<T>数据类型 写操作
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
////容器vector<T>数据类型 读操作
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
////容器map<T_key,T_vaule>数据类型 写操作
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
////容器map<T_key,T_vaule>数据类型 读操作
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