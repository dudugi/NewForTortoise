#pragma once
#include <map>
#include <vector>

/*
���������ݶ���ͷ�ļ� yangjr 2017-6-2
*/

using namespace std;

const BYTE CB_GRIDCTRL_DEFAULT_FONT = 11; //���ؼ�Ĭ�������С
const BYTE CB_GRIDCTRL_DEFAULT_ROWHEIGHT = 24; //���ؼ�Ĭ���и�
const CString CS_GRIDCTRL_DEFAULT_DATAFORMAT = _T("%Y-%m-%d");		//���ؼ�ʱ��Ĭ�ϸ�ʽ��

//�ֶ���������
#pragma region �ֶ���������

typedef BYTE ENUM_FIELDTYPE_DATA;
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_CString = 0;							//�ַ���
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Int = 1;								//����
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double2Point = 2;						//������2λС��
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double3Point = 3;						//������3λС��
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Double4Point = 4;						//������4λС��
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Time = CB_enum_FieldData_CString;		//ʱ��wangzl 2017-7-15
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_TimeLong = CB_enum_FieldData_CString;	//ʱ��wangzl 2017-11-10
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_Button = 6;							//��ť������
const ENUM_FIELDTYPE_DATA CB_enum_FieldData_BallColor = 7;                 //ɫ�����Ϣ
#pragma endregion �ֶ���������


//�ֶοؼ�����
#pragma region �ֶοؼ�����

typedef BYTE ENUM_FIELDTYPE_CONTROL;
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Text = 0;							//�ı�
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Checkbox = 1;						//��ѡ��
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_NormalCombox = 2;					//��ͨ������ؼ�
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_SpecialCombox = 3;					//����������ؼ� ����Ϊgridctrl
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Radio = 4;							//��ѡ�ؼ� һ�����ĳ���ֶ�ֻ��һ��ѡ��ʱʹ�� yangjr 2017-6-9
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_EditCombox = 5;						//��ͨ�ɱ༭������ؼ�
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_DateTime = CB_enum_FieldCtrl_Text;	//ʱ��ؼ�wangzl 2017-7-15
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_TimeLong = CB_enum_FieldCtrl_Text;	//ʱ���ؼ�wangzl 2017-11-10
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_Button = 6;									//��ť�ؼ�		by WangZY 2017/11/21
const ENUM_FIELDTYPE_CONTROL CB_enum_FieldCtrl_BallColor = 7;								//��ʾ������ɫ��Ŀؼ�      by wangzl 2018/7/23

#pragma endregion �ֶοؼ�����


#pragma region ���ݶ���
//һ���ֶ����ݶ���
typedef struct tag_GridCtrl_FieldData
{
	tag_GridCtrl_FieldData()
	{
		strValue = _T("");
		fieldDataType = CB_enum_FieldData_CString;
		fieldCtrlType = CB_enum_FieldCtrl_Text;
		//sptr_normalComboxData->clear();
		//normalComboxData.clear();
		//cellBackgroundClrVec.clear();
		//sptr_cellBackgroundClrVec->clear();
		//sptr_cellBackgroundClrVec.reset();
		byteProgress = 255;	//255ΪĬ�ϲ�ʹ��,��Χ0��100Ϊ��Чֵ	by WangZY 2017/08/23
	}

   //���ؼ�����Ϊ CB_enum_FieldCtrl_BallColor ʱ ��������ͬɫ����ı�(һ��֧�������ַ�)
	shared_ptr<std::vector<CString>> sptr_normalComboxData;//��ͨ������ؼ��õ�������
   //���ؼ�����Ϊ CB_enum_FieldCtrl_BallColor ʱ �ڶ����͵��������ݷֱ�������������ɫ����ֵ
	shared_ptr<std::vector<int>> sptr_cellBackgroundClrVec;//�ֶε�Ԫ�񱳾���ɫ vectorΪ��ʹ���ڲ�Ĭ����ɫ yangjr 2017-6-13
	//MAP_GridCtrl_AllData specialComboxData;//����������ؼ��õ�������
	CString strValue; //����ֵ
	int nNum;
	ENUM_FIELDTYPE_DATA fieldDataType;//�ֶ���������
	ENUM_FIELDTYPE_CONTROL fieldCtrlType;//�ֶοؼ�����
	BYTE	byteProgress;	//������ɫ�Ŀ�ȱ���,255ΪĬ�ϲ�ʹ��,��Χ0��100Ϊ��Чֵ		by WangZY 2017/08/23

}S_GridCtrl_FieldData;

//���һ�����ݶ���
typedef std::map<CString/*strColID ������ID*/,S_GridCtrl_FieldData/*������*/> MAP_GridCtrl_RowData;

//������������ݶ���
typedef std::map<int/*�к�*/,MAP_GridCtrl_RowData/*���һ������*/> MAP_GridCtrl_AllData;

#pragma endregion ���ݶ���


/************************����ڲ�ʹ������ begin*********************************/

#pragma region �ϼƷ�ʽ(ͳ������)

typedef BYTE ENUM_COLSUMTYPE;		//�ϼƷ�ʽ
const ENUM_COLSUMTYPE CB_enum_ColSumType_None = 0;		//��
const ENUM_COLSUMTYPE CB_enum_ColSumType_Sum = 1;		//���
const ENUM_COLSUMTYPE CB_enum_ColSumType_Count = 2;	//����
const ENUM_COLSUMTYPE CB_enum_ColSumType_Average = 3;	//��ƽ��ֵ

#pragma endregion �ϼƷ�ʽ(ͳ������)

#pragma region ��������

typedef BYTE ENUM_COLSERCHTYPE;
const ENUM_COLSERCHTYPE	CB_enum_ColSerchType_Contain = 0;			//����
const ENUM_COLSERCHTYPE	CB_enum_ColSerchType_Equal = 1;				//���

#pragma endregion ��������


#pragma region �ֶ�����

//gridctrl �ֶ�����
typedef struct tag_GridCtrl_FieldAtrri 
{
	CString strColID; //������
	CString strColShowName;//��ʾ����
	CString strColFormat;//��ʽ��

	short iColWidth;//���
	short iColIndex;//��ǰ�ֶ��ڱ������ʾ�ڵڼ��� 

	BYTE iColFont;//�����С
	bool IsFontWeight;//�����Ƿ�Ӵ�
	bool isEnableFilter;//��ǰ�ֶ��Ƿ�����ɸѡ
	bool isShow;//�Ƿ���ʾ

	bool isEdit;//�Ƿ�༭
	BYTE iLock;//���� 0������ 1������� 2�����Ҳ�
	ENUM_COLSUMTYPE enColSumType;//�ϼƷ�ʽ 0�� 1��� 2���� 3��ƽ��ֵ
	ENUM_COLSERCHTYPE enSerchType;//������ʽ 0���� 1���

   CString strColDestribution;//�ֶ�˵��������Ա���������������� wangzl
   CString strTableID;//�ֶ��������ű��� yangjr 2018/2/27
	tag_GridCtrl_FieldAtrri()
	{
		strColID = _T(""); //������
		strColShowName = _T("");//��ʾ����
		iColWidth = 75;//���
		isShow = true;//�Ƿ���ʾ
		isEdit = true;//�Ƿ�༭
		iLock = 0;//���� 0������ 1�������
		strColFormat = _T("");//��ʽ��
		enColSumType = CB_enum_ColSumType_None;//�ϼƷ�ʽ 0��
		enSerchType = CB_enum_ColSerchType_Contain;//������ʽ 0
		iColFont = CB_GRIDCTRL_DEFAULT_FONT;//�����С
		IsFontWeight = false;//�����Ƿ�Ӵ�
		iColIndex = -1;//��ǰ�ֶ��ڱ������ʾ�ڵڼ�
		isEnableFilter = true;//��ǰ�ֶ��Ƿ�����ɸѡ
      strColDestribution = _T("");
      strTableID = _T("");//�ֶ��������ű��� yangjr 2018/2/27
	}

	tag_GridCtrl_FieldAtrri(CString strColID_In,short iColIndex_In,CString strColShowName_In = _T(""),
		bool isShow_In = true,bool isEdit_In = true,short iColWidth_In = 75,
		bool isEnableFilter_In = true,BYTE iLock_In = 0,ENUM_COLSUMTYPE enColSumType_In = CB_enum_ColSumType_None,
		BYTE iColFont_In = CB_GRIDCTRL_DEFAULT_FONT, bool IsFontWeight_In = false,
		ENUM_COLSERCHTYPE enSerchType_In = CB_enum_ColSerchType_Contain,CString strColFormat_In=_T(""),CString strColDestribution_In = _T("")
      ,CString strTableID_In = _T(""))
	{
		strColID = strColID_In; //������ 
		iColIndex = iColIndex_In;//��ǰ�ֶ��ڱ������ʾ�ڵڼ�
		strColShowName = strColShowName_In;//��ʾ����
		isShow = isShow_In;//�Ƿ���ʾ
		isEdit = isEdit_In;//�Ƿ�༭
		iColWidth = iColWidth_In;//���
		isEnableFilter = isEnableFilter_In;//��ǰ�ֶ��Ƿ�����ɸѡ
		iLock = iLock_In;//���� 0������ 1������� 2�����ұ�
		enColSumType = enColSumType_In;
		IsFontWeight = IsFontWeight_In;//�����Ƿ�Ӵ�
		iColFont = iColFont_In;//�����С
		enSerchType = enSerchType_In;//������ʽ 0
		strColFormat = strColFormat_In;//��ʽ��
      strColDestribution = strColDestribution_In;
      strTableID = strTableID_In;//�ֶ��������ű��� yangjr 2018/2/27
	}   
}S_GridCtrl_FieldAtrri;

#pragma endregion �ֶ�����

#pragma region �ֶμ����Ӧ��ʾ��

//wangzl 2017-1-2 �ֶ��ж�Ӧ��Ϣ
typedef struct tag_FieldCol_Data
{
   CString strColID; //������
   CString strColDestribution;//�ֶ�˵��������Ա���������������� wangzl
   CString strTableID;//�ֶι������� yangjr 2018/3/1
   tag_FieldCol_Data(CString strColID_In,CString strColDestribution_In,CString strTableID_In)
   {
      strColID = strColID_In;
      strColDestribution = strColDestribution_In;
      strTableID = strTableID_In;
   }

}S_FieldCol_Data;

#pragma endregion �ֶμ����Ӧ��ʾ��


typedef std::map<CString/*strColID ������*/,S_GridCtrl_FieldAtrri> MAP_GridCtrl_FieldAtrri;

typedef std::map<int/*�����ʽ��ʾ����*/,CString/*strColID ������*/> MAP_GridCtrl_FieldPos;


#pragma region �������

//gridctrl �������
typedef struct tag_GridCtrl_TableAttri 
{
	MAP_GridCtrl_FieldAtrri mapFeildAtrri;//һ�����������ֶ�����
	MAP_GridCtrl_FieldPos mapTableFeildPos;//��ǰ�ֶ��ڱ����ʽ����ʾ�еڼ���
	
	BYTE	nDataRowHeight;				//���ݵ��и�
	BYTE  iDataRowFont;				//���ݵ����� yangjr 2017-6-7
	bool isShowTitleFilter;	//�Ƿ���ʾ�б���ɸѡ��		by WangZY 2017/06/07
	bool isShowSortBar; //�Ƿ���ʾɸѡ��

	bool isAllowSort;//�Ƿ���������
	bool isWholeRowSelect;//����ѡ��
	bool isShowSumBar;//�Ƿ���ʾ�ϼ���
	bool isMultiRowSelect;//����ѡ��  

	bool IsMultiRowSelectNoLoseFocus;//����ѡ��ʧ���� ===> �����Ϊ����ѡ�񵥻�ѡ�й��� by lida 2018/01/31
	bool isEnableDragCol;  //��λ���ܷ��϶� yangjr 2017-6-13
	bool isEnableEdit;	  //���Ƿ�ɱ༭		by WangZY 2017/06/15
	bool isPrintHengXiang; //�Ƿ�����ӡ		by yangjr 2017/09/19
   CString strUpdateTime; //��������
   bool isNoUpdateServerStyle; //�Ƿ񲻸��·�������ʽ	by yangjr 2018/5/29
   int  iPageRows;
	tag_GridCtrl_TableAttri()
	{
		isShowTitleFilter = false;
		isShowSortBar = false;
		isAllowSort = false;
		isWholeRowSelect = false;
		isShowSumBar = false;
		isMultiRowSelect = false;
		IsMultiRowSelectNoLoseFocus = false;
		nDataRowHeight = CB_GRIDCTRL_DEFAULT_ROWHEIGHT;
		iDataRowFont = CB_GRIDCTRL_DEFAULT_FONT;
		isEnableDragCol = true;
		isEnableEdit = true;		//���Ƿ�ɱ༭		by WangZY 2017/06/15
		isPrintHengXiang = false;
      strUpdateTime = _T("");
      isNoUpdateServerStyle = false;
      iPageRows = 50;
	}
}S_GridCtrl_TableAttri;

#pragma endregion �������


//������ɸѡ���ݶ���
typedef struct tag_SHAIXUAN_DATA
{
   CString strText;//�ı�
   BOOL isChecked; //�Ƿ�ѡ
}SHAIXUAN_DATA;

typedef std::vector<SHAIXUAN_DATA> VEC_SHAIXUAN_DATA;//���е�ɸѡ����

typedef struct tag_SERCH_DATA
{
   VEC_SHAIXUAN_DATA vecShaiXuanData; //����ɸѡ����
   CString strText;//ɸѡ�������ı�   
}SERCH_DATA;

//��Ӧ��ID��GridCtrl�е�ɸѡ��Ϣ
typedef std::map<CString/*strColID ������*/,SERCH_DATA/*ɸѡ������*/> MAP_SERCH_DATAS;
/**********************����ڲ�ʹ������ end*********************************/





