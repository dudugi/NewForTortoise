#pragma once
/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2010 Burnon All Rights Reserved 
//  ����ʱ��:       2011/09/06 19:09
//  ������:         ����������ݶ���
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
//#include "CKnitData.h"
#include "CShapeSpace.h"
#include <vector>
#include <list>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////
/*
ժҪ:��׼ģ������ ���� 
����:linyp
ʱ��:2009-10-11
*/
class  CKDModData
   //:public CKnitData
{
public:
   //UINT     m_uModWidth;                  //���=������Ƶ���׿��1
   //UINT     m_uModOrgWidth;               //ԭʼ��ȣ���ʱ������linyp
   //ShapeSpace::FroBkNeedle m_enFBKnit;    //����װ�==��������
   ShapeSpace::QHLuoBu  m_enLuoBu;        //ǰ���䲼���� 1
   //CString  m_strModType;                 //��׼ģ����֯���� 1
   CString  m_strTransType;               //���������� 1
   //ShapeSpace::Sys_Type m_enMacType;      //��׼ģ����� ��ϵͳ ��ϵͳ1
   //double   m_dRevolution;                //ת��1
   //double   m_dEmptyRevolution;           //��ת��1
   //BOOL     IsBottomExist;                //�Ƿ������װ�      ����װ�Ϊ1������װ�Ϊ0  1
   //BOOL     IsVLFlag;                     //�Ƿ�����:��1,��0 �޿��� = �����ı�׼ģ��  1
   //ShapeSpace::NeedleTrans_Type      m_BZJ;  //����� 1
   //CString  m_strCombType;                //��װ�ģʽ1
   //BOOL     Is_LWJiaSi;                   //�Ƿ����Ƽ�˿
   //UINT     m_uLWJiasi;                   //���Ƽ�˿ת��
   ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� start Duchen 2017/09/07 16:24 dc160904
   //BOOL     m_bWholePiece;                //�Ƿ�����Ƭ�������߻��ұߣ�
   ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� end   Duchen 2017/09/07 16:24
   //////////////////////////////////////////////////////////////////////////////////
   ////������Ʋ�������
   //int m_FirstShaZui;         //��һ��ɴ��
   //int m_SecondShaZui;        //�ڶ���ɴ��
   //int m_RibAddYarn;          //���Ƽ�˿ɴ��
   //BOOL m_bAutoPressYarnMode;          //�Զ�ѹ��ģʽ
   //BOOL m_bAutoPressYarnUseWasteYarn;  //�Զ�ѹ��ģʽʹ�÷�ɴɴ��
   //int  m_DiXiangJYarn;       //����ɴ��
   //BOOL  m_isHouQiKongZhuan;  //����׿�ת
   ////���Ƽ�ɫ start Duchen 2017/09/26 11:08 dc160925
   //std::list<int> m_lstLWJiaSe;    //���Ƽ�ɫ
   //std::list<int> m_lstLWJiaSeColor;    //���Ƽ�ɫɫ��
   ////���Ƽ�ɫ end   Duchen 2017/09/26 11:08
   
public:
   CKDModData(){
      //m_DiXiangJYarn = 0;
      //m_isHouQiKongZhuan = FALSE;
      ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� start Duchen 2017/09/07 16:24 dc160904
      //m_bWholePiece = FALSE;
      ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� end   Duchen 2017/09/07 16:24
   }
   virtual ~CKDModData(){};

   const CKDModData& operator=(const CKDModData& rhs)
   {
      if (this == &rhs) return *this;                                      
      //m_uModWidth             = rhs.m_uModWidth;                          
      //m_enFBKnit              = rhs.m_enFBKnit;                              
      m_enLuoBu               = rhs.m_enLuoBu;                            
      //m_strModType            = rhs.m_strModType;                            
      //m_enMacType             = rhs.m_enMacType;                    
      //m_dRevolution           = rhs.m_dRevolution; 
      m_strTransType          = rhs.m_strTransType;
      //m_dEmptyRevolution      = rhs.m_dEmptyRevolution;      
      //m_uLWJiasi              = rhs.m_uLWJiasi;
      //Is_LWJiaSi              = rhs.Is_LWJiaSi;
      //IsBottomExist           = rhs.IsBottomExist;                
      //IsVLFlag                = rhs.IsVLFlag;                            
      //m_BZJ                   = rhs.m_BZJ;                                
      //m_strCombType           = rhs.m_strCombType;
      //m_RibAddYarn            = rhs.m_RibAddYarn;
      //m_isHouQiKongZhuan      = rhs.m_isHouQiKongZhuan;
      ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� start Duchen 2017/09/07 16:24 dc160904
      //m_bWholePiece           = rhs.m_bWholePiece;
      ////#5408 �����͹��յ�������Ƭѡ����ߺ��ұߵ�ʱ�򣬳��ͳ������ɴ������330û�� end   Duchen 2017/09/07 16:24
      ////���Ƽ�ɫ start Duchen 2017/09/26 11:08 dc160925
      //m_lstLWJiaSe = rhs.m_lstLWJiaSe;    //���Ƽ�ɫ
      //m_lstLWJiaSeColor = rhs.m_lstLWJiaSeColor;    //���Ƽ�ɫɫ��
      //���Ƽ�ɫ end   Duchen 2017/09/26 11:08
      return *this;
   }
};

//---------------------------------------------------------------------------
//�����������
typedef struct tagKnitParams
{
   //Ĭ�Ϲ���
   tagKnitParams()
   {
      bDomain1 = 0;    
      bDomain2 = 0;    
      bSpeed1 = 0;     
      bSpeed2 = 0;     
      bYarn1 = 0;      
      bYarn2 = 0;      
      bRoller1 = 0;    
      bRoller2 = 0;
      Idex=0;
   }
   BYTE bDomain1;       //��Ŀ1 ��֯��Ŀ 207
   BYTE bDomain2;       //��Ŀ2 �����Ŀ
   BYTE bSpeed1;        //�ٶ�1 ��֯�ٶ� 209
   BYTE bSpeed2;        //�ٶ�2 �����ٶ�
   BYTE bYarn1;         //ɴ��1 215
   BYTE bYarn2;         //ɴ��2
   BYTE bRoller1;       //��1 ��֯ʱ�� 210
   BYTE bRoller2;       //��2 ����ʱ��
//    BYTE bRoller1;       //��1 ��֯ʱ�� 211
//    BYTE bRoller2;       //��2 ����ʱ��
   BYTE Idex;
   //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ start Duchen 2016/08/24 16:38 dc160822
   void ApplyChange(const tagKnitParams &Param)
   {
      if (Param.bDomain1)
         bDomain1 = Param.bDomain1;
      if (Param.bDomain2)
         bDomain2 = Param.bDomain2;
      if (Param.bSpeed1)
         bSpeed1 = Param.bSpeed1;
      if (Param.bSpeed2)
         bSpeed2 = Param.bSpeed2;
      if (Param.bYarn1)
         bYarn1 = Param.bYarn1;
      if (Param.bYarn2)
         bYarn2 = Param.bYarn2;
      if (Param.bRoller1)
         bRoller1 = Param.bRoller1;
      if (Param.bRoller2)
         bRoller2 = Param.bRoller2;
   }
   //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ end   Duchen 2016/08/24 16:38
}KnitParams,pKnitParams;

typedef struct tagKnitParamSet
{
   tagKnitParamSet()
   {
  //    paraBirdEyes.bDomain1 = 1;          //������ƽ1
  //    paraFullNeedle.bDomain1 = 2;        //��ɴ��ƽ2
  //    paraSplitYarn.bDomain1 = 3;         //��ɴ����3
  //    paraMainYarn.bDomain1 = 4;          //��ɴ���4
  //    paraMainRacing.bDomain1 = 5;        //��׿�ת5
  //    paraRibbingKnit.bDomain1 = 6;       //���Ʊ�֯6
  //    paraTransition.bDomain1 = 7;        //������7
  //    paraBody.bDomain1 = 8;              //����8
  //    paraFlatInsert_Left.bDomain1 = 9;   //(ƽ��)�б߲�����9
  //    paraFlatInsert_Right.bDomain1 = 17;  //(ƽ��)�б߲�����17
  //    paraAutoInsert.bDomain1 = 10;        //�Զ�����10
  //    paraVNeck.bDomain1 = 13;             //����13
  //    paraVNeck_Left.bDomain1 = 12;        //������12
  //    paraVNeck_Right.bDomain1 = 12;       //������12
  //    //ZB-804 ����һ��V����е��ٶȶ��� start Duchen 2020/07/30 14:40 dc200727
  //    paraVNeckSpeed_Left.bDomain1 = 8;        //������12
  //    paraVNeckSpeed_Right.bDomain1 = 8;       //������12
  //    //ZB-804 ����һ��V����е��ٶȶ��� end   Duchen 2020/07/30 14:40
  //    paraDoffing1.bDomain1 = 12;          //�䲼12
  //    paraCircleNeck.bDomain1 = 13;        //Բ��13
  //    paraDoffing2.bDomain1 = 14;          //�䲼2 14
  //    paraCotton.bDomain1 = 15;            //��ɴ15
  //    paraTransNeedle.bDomain1 = 23;       //����23
  //    paraDxj.bDomain1 = 16;               //�����ɴ����16 yangjr2016-3-3
  //    paraDxj.Idex = 16;               //�����ɴ����16 yangjr2016-3-3
  //    paraPPYarn.bDomain1 = 3;            //pp�߶��� 3
  //    paraComb.bDomain1 = 20;              //��װ�������� Ĭ��20
  //    m_bMainYarnFirst = 3;           //��ɴ��һ��ɴ��
  //    m_bMainYarnSec = 5;             //��ɴ�ڶ���ɴ��
  //    m_bRubYarnFirst = 1;            //��ɴ��һ��ɴ��
  //    m_bRubYarnSec = 7;              //��ɴ�ڶ���ɴ��
  //    m_NeckYarn = 0;
      m_IsOneYarn = TRUE;             //����ʹ��һ��ɴ��
		//m_NeckIsOneYarn = FALSE;
  //    //#2912 ����֧�ֵ�ɴ�����ֱ�֯ start Duchen 2016/07/20 10:16 dc160718
  //    m_bNeckOneYarnTwoWay = FALSE;   //����һ��ɳ��ֱ�֯
  //    //#2912 ����֧�ֵ�ɴ�����ֱ�֯ end   Duchen 2016/07/20 10:16
	   bSetSecYarnLeft = FALSE;        //2#ɴ�������
      bSetWasteSecYarnLeft = FALSE;   //2#��ɴɴ�������
    //  //#4497 stoll���ֻ���ɴ�����ұߣ�ϣ�����ǳ�����ƿ���֧�ִ���ɴ��2����ɴɴ��2���ұ� start Duchen 2017/03/03 10:11 dc170227
    //  m_bAllYarnRight = FALSE;            //ɳ�����Ҳ�
    //  //#4497 stoll���ֻ���ɴ�����ұߣ�ϣ�����ǳ�����ƿ���֧�ִ���ɴ��2����ɴɴ��2���ұ� end   Duchen 2017/03/03 10:11
	   //bLuoWenYarn = 0;                //����ɴ��2
	   //bRubberYarn = 8;                //���ɴ��
    //  bPPYarn = 1;                    //PP��ɴ�� 2012-3-5 linyp
    //  bLwJsYarn = 0;                  //���Ƽ�˿ɴ��
    //  bDxjYarn = 0;                   //�����ɴ��
    //  //#5652 ɳ��Ͷ�����������ɳ��1 start Duchen 2017/12/05 15:26 dc171205
    //  m_byLuoWnYarn1 = m_bMainYarnFirst;              //����ɳ��1
    //  //#5652 ɳ��Ͷ�����������ɳ��1 end   Duchen 2017/12/05 15:26
	   //m_nParamType = ShapeSpace::enParaMold1;      //����ģʽ
   }
 //  //-------------------------------------------
 //  //��֯����
 //  KnitParams paraBirdEyes;          //������ƽ1
 //  KnitParams paraFullNeedle;        //��ɴ��ƽ2
 //  KnitParams paraSplitYarn;         //��ɴ����3
 //  KnitParams paraMainYarn;          //��ɴ���4
 //  KnitParams paraMainRacing;        //��׿�ת5
 //  KnitParams paraRibbingKnit;       //���Ʊ�֯8
 //  KnitParams paraTransition;        //������7
 //  KnitParams paraBody;              //����8
 //  KnitParams paraFlatInsert_Left;   //(ƽ��)�б߲�����9
 //  KnitParams paraFlatInsert_Right;  //(ƽ��)�б߲�����9
 //  KnitParams paraAutoInsert;        //�Զ�����11
 //  KnitParams paraVNeck;             //����12
 //  KnitParams paraVNeck_Left;        //������12
 //  KnitParams paraVNeck_Right;       //������12
 //  //ZB-804 ����һ��V����е��ٶȶ��� start Duchen 2020/07/30 14:40 dc200727
 //  KnitParams paraVNeckSpeed_Left;        //������12 �ٶ�
 //  KnitParams paraVNeckSpeed_Right;       //������12 �ٶ�
 //  //ZB-804 ����һ��V����е��ٶȶ��� end   Duchen 2020/07/30 14:40
 //  KnitParams paraDoffing1;          //�䲼13
 //  KnitParams paraCircleNeck;        //Բ��14
 //  KnitParams paraDoffing2;          //�䲼2 15
 //  KnitParams paraCotton;            //��ɴ16
 //  KnitParams paraTransNeedle;       //����17
 //  KnitParams paraPPYarn;            //pp�߶��� 21
 //  KnitParams paraComb;              //��װ�������� Ĭ��22
 //  KnitParams paraDxj;               //����ɴ��
 //  //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ start Duchen 2016/08/24 16:38 dc160822
 //  KnitParams paraSuoZhen;           //����
 //  //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ end   Duchen 2016/08/24 16:38
 //  //#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� start Duchen 2016/09/05 15:17 dc160905
 //  KnitParams paraQuanTiHuaTaoKou;           //ȫ�Ứ�׿�
 //  KnitParams paraQuanTiHuaTaoKouFangSong;   //ȫ�Ứ�׿ڷ���
 //  //#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� end   Duchen 2016/09/05 15:17

 //  //ZB-746 �����Ŀ���� start Duchen 2019/05/05 15:15 dc190429
 //  KnitParams paraShouZhenDumuFangSong;      //�����Ŀ����
 //  //ZB-746 �����Ŀ���� end   Duchen 2019/05/05 15:15

 //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ start Duchen 2019/09/29 17:52 dc190923
 //  KnitParams paraAttachmentLoosen;             //�������� ͷβ����
 //  KnitParams paraAttachmentTightYuanTong;      //�������� ��ԲͲ
 //  KnitParams paraAttachmentSipin;              //�������� ��ƽ
 //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ end   Duchen 2019/09/29 17:52

 //  //ZB-950 ɳ��Ͷ������Ӿֲ��Ứ��Ŀ������ start Duchen 2020/08/13 10:17 dc200810
 //  KnitParams paraJuBuTiHua;      //�ֲ��Ứ
 //  //ZB-950 ɳ��Ͷ������Ӿֲ��Ứ��Ŀ������ end   Duchen 2020/08/13 10:17

 //  //------------------------------------------
 //  //ɴ������
 //  BYTE  m_bMainYarnFirst;           //��ɴ��һ��ɴ��
 //  BYTE  m_bMainYarnSec;             //��ɴ�ڶ���ɴ��
 //  BYTE  m_bRubYarnFirst;            //��ɴ��һ��ɴ��
 //  BYTE  m_bRubYarnSec;              //��ɴ�ڶ���ɴ��
 //  BYTE  m_NeckYarn;
   BOOL  m_IsOneYarn;                //����ʹ��һ��ɴ��
   BOOL  m_NeckIsOneYarn;            //����ʹ��һ��ɴ��
 //  //#2912 ����֧�ֵ�ɴ�����ֱ�֯ start Duchen 2016/07/20 10:16 dc160718
 //  BOOL  m_bNeckOneYarnTwoWay;     //����һ��ɳ��ֱ�֯
 //  //#2912 ����֧�ֵ�ɴ�����ֱ�֯ end   Duchen 2016/07/20 10:16
   BOOL  bSetSecYarnLeft;            //2#ɴ�������
   BOOL  bSetWasteSecYarnLeft;            //2#ɴ�������
 //  //#4497 stoll���ֻ���ɴ�����ұߣ�ϣ�����ǳ�����ƿ���֧�ִ���ɴ��2����ɴɴ��2���ұ� start Duchen 2017/03/03 10:11 dc170227
 //  BOOL  m_bAllYarnRight;            //ɳ�����Ҳ�
 //  //#4497 stoll���ֻ���ɴ�����ұߣ�ϣ�����ǳ�����ƿ���֧�ִ���ɴ��2����ɴɴ��2���ұ� end   Duchen 2017/03/03 10:11
	//BYTE  bLuoWenYarn;                //����ɴ��2
 //  //#5652 ɳ��Ͷ�����������ɳ��1 start Duchen 2017/12/05 15:26 dc171205
 //  BYTE m_byLuoWnYarn1;              //����ɳ��1
 //  //#5652 ɳ��Ͷ�����������ɳ��1 end   Duchen 2017/12/05 15:26
	//BYTE  bRubberYarn;                //���ɴ��
 //  BYTE  bPPYarn;                    //PP��ɴ�� 2012-3-5 linyp
 //  BYTE  bLwJsYarn;                  //���Ƽ�˿ɴ��
 //  BYTE  bDxjYarn;                   //����ɴ��
	//ShapeSpace::KnitPara_Type m_nParamType;      //����ģʽ
}ParamSet,*pParamSet;

typedef struct tagOtherParamSet     //�߼���������
{ 
   tagOtherParamSet()
   {
    //  iMinSuspendNeedleNum = 10;   
      iCottonRowNum = 8;
    //  LessColor = 16;
    //  m_nCottontype = ShapeSpace::enAddNeedle_double;
      m_AddType = ShapeSpace::enAdd_One1; //���뷽ʽ,XUYH
    //  DoubleRibColor = 1;
    //  m_nRibtype = ShapeSpace::enRibFull;
    //  ModeJDM = 0;
    //  effectiveNum = 7;
    //  iNotTreatmentNeedle = 3;            //��ɴ����������
    //  iYarnKickBackNeedle = 3;            //��ɴ���л�������
    //  iNeckUseOneYarn = 8;                //��ɴ�쿪�����
    //  m_bRibSaving = TRUE;                //���ƽ�Լ
    //  m_bJiaBPs = TRUE;                   //��ϵͳ�б�ƽ��һ��
	   //m_bAutoNeckCenter = TRUE;           //�������������ӵײ�
	   //m_bSeperateLine = TRUE;             //����
	   //m_bVNeckYarn = TRUE;                //V��׽ʻ�
	   m_uAbandon_RowCount = TRUE;         //��ɴת��
	   m_IsAbandon_Oneyarn = TRUE;         //��ɴ�Ƿ�ʹ��һ��ɴ��
    //  m_IsAbandon_Yintax = TRUE;          //��ɴ������ͬʱ����������
    //  m_bPackMode = TRUE;
    //  m_bCZTuck = FALSE;                  // �����Ŀ
	   //m_bFeiShaAllQidiMode = TRUE;			//�Ƿ�ʹ�÷�ɴ�䲼
    //  m_bAutoPressYarnMode = TRUE;        //�Զ�ѹ��ģʽ
    //  m_bAutoPressYarnUseWasteYarn = TRUE;//�Զ�ѹ��ģʽʹ�÷�ɴɴ��
      //m_ClipYarnPos = 61;
		//m_cancelType = ShapeSpace::en_Cancel_NON;
      /*m_bDaiShaDaJie = TRUE;
		m_bDaiShaOut   = FALSE;
		m_bChaiXian    = FALSE;
		m_bVLDiJiaoHua = FALSE;
		m_enJLTuckColor = ShapeSpace::enJLTuck;*/
		//m_nCZType = ShapeSpace::enTuck;
      //#3111 ƽ���䲼������������ start Duchen 2016/08/03 14:02 dc160801
      //m_nFlatReduceLuoBuLineCount = 5; //ƽ���䲼��������
      ////#3111 ƽ���䲼������������ end   Duchen 2016/08/03 14:02
      ////#3663 ���Ͳ�����ӷ�ɴɴ�������ɴ��ѡ�� start Duchen 2016/09/26 11:36 dc160926
      //m_bRubYarnOut = TRUE; //��ɴɴ��
      //m_bRubberYarnOut = TRUE; //���ɴ��
      //#3663 ���Ͳ�����ӷ�ɴɴ�������ɴ��ѡ�� end   Duchen 2016/09/26 11:36
      //#3665 ����������ɴ���ɴ��ʽ start Duchen 2017/12/12 17:58 dc161211
      m_bSingleSplitYarnNeck = FALSE; //���쵥ɴ���ɴ��ʽ
      //#3665 ����������ɴ���ɴ��ʽ end   Duchen 2017/12/12 17:58
      //m_bAutoCutClip = TRUE; //�Զ���������yangjr 2016-11-3
      //#4373 �ֱ����check��listbox�����0��ʹ���ֱܷ���ì�� start Duchen 2017/04/25 13:14 dc170424
      //m_fbfz = 1;
      //m_bFBFZ = TRUE;
      //#4373 �ֱ����check��listbox�����0��ʹ���ֱܷ���ì�� end   Duchen 2017/04/25 13:14
      //#4629 V�����ʱ��������������һ�Σ�������� ���� start Duchen 2017/08/22 10:00 dc160821
      //m_nVNeckCZType = ShapeSpace::enBoLiuZhenFirst;
      //#4629 V�����ʱ��������������һ�Σ�������� ���� end   Duchen 2017/08/22 10:00

      //ZB-381 ��������ɴ���Զ����빦��ѡ�� start Duchen 2018/07/06 17:11 dc180702
      //m_bYarnInAutoAlign = FALSE;
      //ZB-381 ��������ɴ���Զ����빦��ѡ�� end   Duchen 2018/07/06 17:11

      //ZB-962 �������ã�����ҳ�������������䲼������ start Duchen 2020/07/22 16:29 dc200720
      //m_nLuoBuHangShu = 4; //�䲼���� //[XML]
      //ZB-962 �������ã�����ҳ�������������䲼������ end   Duchen 2020/07/22 16:29
   }
 //  UINT iMinSuspendNeedleNum;   
   UINT iCottonRowNum;
 //  BYTE LessColor;
 //  BYTE m_fbfz;
 //  ShapeSpace::Cotton_Type m_nCottontype;
   ShapeSpace::Add_Type m_AddType;  //���뷽ʽ,XUYH
	//ShapeSpace::CANCEL_TYPE m_cancelType;  //�Զ�͵�Է�ʽ
 //  BYTE DoubleRibColor;
 //  ShapeSpace::Rib_Type m_nRibtype;
	//ShapeSpace::CHANZHENTUCK m_nCZType;
 //  //#4629 V�����ʱ��������������һ�Σ�������� ���� start Duchen 2017/08/22 10:00 dc160821
 //  ShapeSpace::VNECKCHANZHENTYPE m_nVNeckCZType;
 //  //#4629 V�����ʱ��������������һ�Σ�������� ���� end   Duchen 2017/08/22 10:00
 //  UINT ModeJDM;                    //�ٵ�Ŀ��ʽ
 //  UINT  m_jiadmgd;                 //�ٵ�Ŀ�߶�
	//UINT effectiveNum;
 //  int  iNotTreatmentNeedle;        //��ɴ����������
 //  int  iYarnKickBackNeedle;        //��ɴ���л�������
 //  int  iNeckUseOneYarn;            //��ɴ�쿪�����
	//BOOL m_bRibSaving;               //���ƽ�Լ
	//BOOL m_bJiaBPs;                  //��ϵͳ�б�ƽ��һ��
	//BOOL m_bAutoNeckCenter;          //�������������ӵײ�
	//BOOL m_bSeperateLine;            //����
	//BOOL m_bVNeckYarn;               //V��׽ʻ�
	UINT m_uAbandon_RowCount;        //��ɴת��
   BOOL m_IsAbandon_Oneyarn;        //��ɴ�Ƿ�ʹ��һ��ɴ��
 //  BOOL m_IsAbandon_Yintax;         //��ɴ������ͬʱ����������
 //  BOOL m_bPackMode;
 //  BOOL      m_bCZTuck;             // �����Ŀ
	//BOOL m_bFeiShaAllQidiMode;			//�Ƿ�ʹ�÷�ɴ�䲼
 //  BOOL m_bAutoPressYarnMode;          //�Զ�ѹ��ģʽ
 //  BOOL m_bAutoPressYarnUseWasteYarn;  //�Զ�ѹ��ģʽʹ�÷�ɴɴ��
   int  m_iLiuBianZS;				   //ֱλ����ת��
 //  int  m_ClipYarnPos;              //���߸߶ȣ�ת��
	//BOOL m_bDaiShaDaJie;
	//BOOL m_bDaiShaOut;               //��ɴ����Ե
	//BOOL m_bChaiXian;                //����
	//BOOL m_bVLDiJiaoHua;                //V��׽ʻ�
 //  BOOL m_bFBFZ;                       //�ֱ���
 //  int  m_iQiJiaZhuanshu;              //���ת��

	//ShapeSpace::JIADLINGTUCK  m_enJLTuckColor;

   ShapeSpace::NeedleFlat_Type  m_nKaiSFlatType;//����ƽ�շ�ʽ
   ShapeSpace::NeedleFlat_Type  m_nNeckFlatType;//����ƽ�շ�ʽ
 //  //#3111 ƽ���䲼������������ start Duchen 2016/08/03 14:02 dc160801
 //  int m_nFlatReduceLuoBuLineCount; //ƽ���䲼��������
 //  //#3111 ƽ���䲼������������ end   Duchen 2016/08/03 14:02
 //  //#3663 ���Ͳ�����ӷ�ɴɴ�������ɴ��ѡ�� start Duchen 2016/09/26 11:36 dc160926
 //  BOOL m_bRubYarnOut; //��ɴɴ��
 //  BOOL m_bRubberYarnOut; //���ɴ��
 //  //#3663 ���Ͳ�����ӷ�ɴɴ�������ɴ��ѡ�� end   Duchen 2016/09/26 11:36
 //  BOOL m_bAutoCutClip; //�Զ���������yangjr 2016-11-3
   //#3665 ����������ɴ���ɴ��ʽ start Duchen 2017/12/12 17:58 dc161211
   BOOL m_bSingleSplitYarnNeck; //���쵥ɴ���ɴ��ʽ
   //#3665 ����������ɴ���ɴ��ʽ end   Duchen 2017/12/12 17:58

   ////ZB-381 ��������ɴ���Զ����빦��ѡ�� start Duchen 2018/07/06 17:11 dc180702
   //BOOL m_bYarnInAutoAlign;
   ////ZB-381 ��������ɴ���Զ����빦��ѡ�� end   Duchen 2018/07/06 17:11

   ////ZB-962 �������ã�����ҳ�������������䲼������ start Duchen 2020/07/22 16:29 dc200720
   //int m_nLuoBuHangShu; //�䲼���� //[XML]
   ////ZB-962 �������ã�����ҳ�������������䲼������ end   Duchen 2020/07/22 16:29
}OtherParamSet;
//--------------------------------------------------------------------
//������������

typedef std::vector<BYTE>                TYPE_VEC_KNITSIGN;   //��֯���� 
//ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
class TYPE_VEC_LEFT_RIGHT_KNITSIGN
{
public:
   TYPE_VEC_KNITSIGN vecLeft;
   TYPE_VEC_KNITSIGN vecLoop;
   TYPE_VEC_KNITSIGN vecRight;
};

inline bool operator==(TYPE_VEC_LEFT_RIGHT_KNITSIGN &left, TYPE_VEC_LEFT_RIGHT_KNITSIGN &right)
{
   return left.vecLeft == right.vecLeft
      && left.vecLoop == right.vecLoop
      && left.vecRight == right.vecRight;
}

//ZB-971 �����Ƕ��ܶȶΣ� ת�ư����Ҫ֪��ÿһ�β�ͬ�� ֮ǰ��Ĭ�ϴ�31��ʼ�֣����ڲ��ֶ�Ŀ�� start Duchen 2020/07/24 11:49 dc200720
inline bool operator<(const TYPE_VEC_LEFT_RIGHT_KNITSIGN &left, const TYPE_VEC_LEFT_RIGHT_KNITSIGN &right)
{
   if (left.vecLeft < right.vecLeft)
   {
      return true;
   }
   else if (left.vecLeft == right.vecLeft)
   {
      if (left.vecLoop < right.vecLoop)
      {
         return true;
      }
      else if (left.vecLoop == right.vecLoop)
      {
         if (left.vecRight < right.vecRight)
         {
            return true;
         }
      }
   }
   return false;
}
//ZB-971 �����Ƕ��ܶȶΣ� ת�ư����Ҫ֪��ÿһ�β�ͬ�� ֮ǰ��Ĭ�ϴ�31��ʼ�֣����ڲ��ֶ�Ŀ�� end   Duchen 2020/07/24 11:49

inline bool operator==(const TYPE_VEC_LEFT_RIGHT_KNITSIGN &left, const TYPE_VEC_LEFT_RIGHT_KNITSIGN &right)
{
   return left.vecLeft == right.vecLeft
      && left.vecLoop == right.vecLoop
      && left.vecRight == right.vecRight;
}
typedef std::vector<TYPE_VEC_LEFT_RIGHT_KNITSIGN>   TYPE_2D_VECTSIGN;
//typedef std::vector<TYPE_VEC_KNITSIGN>   TYPE_2D_VECTSIGN;
//ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21
//��������
class ShapeProfileRow//:
   //public CKnitData
{
public:
   ShapeProfileRow()       //Ĭ�Ϲ��캯��
   {
      iRowCount = 0;
      iNeedleNum = 0;    
      iTimes = 1;        
      iNeedleMoveNum = 0;
      iNeedleLess = 0;   
      en_NeedleType = ShapeSpace::en_Needle_Null;             
      bEffective = false;   
      iHeight=0;
      //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
      TYPE_VEC_KNITSIGN vecKnitSignLoop;               //��֯����
      vecKnitSignLoop.push_back(1);
      vecKnitSign.vecLoop = vecKnitSignLoop;
      //vecKnitSign.push_back(1);
      //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21
      //#4907 ������ͼ�����ڴ泬�� start Duchen 2017/12/21 09:44 dc161218
      m_vect2DKnit.push_back(vecKnitSign); //Ĭ��Ϊ1��1��ɫ
      //#4907 ������ͼ�����ڴ泬�� end   Duchen 2017/12/21 09:44
		effective = 0;
		Real_effective = 0;
      iMarkPos = 0;
      bNeckKaisPs    = FALSE;
      //ZB-831 ���������Զ�������չ start Duchen 2020/03/09 10:52 dc20200309
      m_nNeedlePackagePageCount = 0;
      //ZB-831 ���������Զ�������չ end   Duchen 2020/03/09 10:52
   }
	int AutoCancel(ShapeSpace::CANCEL_TYPE cancelType)
	{
		if (iNeedleNum<0 && iRowCount !=0 && ShapeSpace::en_Needle_Null==en_NeedleType && ShapeSpace::en_Cancel_NON !=cancelType)
		{
			if ((abs(iNeedleNum)>1 && ShapeSpace::en_Cancel_1N ==cancelType)
				|| (abs(iNeedleNum)==2 && ShapeSpace::en_Cancel_2N ==cancelType))
			{
				return 1;
			}
			else if (abs(iNeedleNum)>2 && ShapeSpace::en_Cancel_2N ==cancelType)
			{
				return 2;
			}
			return 0;
		}
		return 0;
	}
   //#4217 ���͡���֯������������֯�����б� start Duchen 2016/01/20 10:06 dc170116
   /*inline static list<CString> GetBianmaOneLineString(CString str)
   {
      CString temp;
      list<CString> listString;
      int pos = 0, size = 0;
      while ((pos = str.Find(_T(";"), 0)) != -1)
      {
         size   =   str.GetLength();
         temp   =   str.Left(pos);
         str    =   str.Right(size-pos-1);
         listString.push_back(temp);
      }
      if (str != _T(""))
      {
         listString.push_back(str);
      }
      return listString;
   }*/

   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
   inline static TYPE_VEC_KNITSIGN GetBianmaVectorInt(CString str)
   //inline static TYPE_VEC_KNITSIGN GetBianmaInt(CString str)
   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21
   {
      CString temp;
      TYPE_VEC_KNITSIGN vectColor;
      int pos = 0, size = 0;
      while ( (pos = str.Find(_T(","),0)) != -1)
      {
         size   =   str.GetLength();
         temp   =   str.Left(pos);
         str    =   str.Right(size-pos-1);
         vectColor.push_back(_tstoi(temp));
      }
      if (str!="")
      {
         vectColor.push_back(_tstoi(str));
      }
      return vectColor;
   }

   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
   inline static TYPE_VEC_LEFT_RIGHT_KNITSIGN GetBianmaInt(CString str)
   {
      TYPE_VEC_LEFT_RIGHT_KNITSIGN sign;
      int nPosLeft = str.Find(_T("["), 0);
      if (nPosLeft != -1)
      {
         CString strLeft = str.Left(nPosLeft);
         sign.vecLeft = GetBianmaVectorInt(strLeft);
         ++nPosLeft;
      }
      else
      {
         nPosLeft = 0;
      }
      int nPosRight = str.Find(_T("]"), 0);
      if (nPosRight != -1)
      {
         CString strLeft = str.Mid(nPosRight + 1);
         sign.vecRight = GetBianmaVectorInt(strLeft);
      }
      else
      {
         nPosRight = str.GetLength();
      }
      CString strMid = str.Mid(nPosLeft, nPosRight - nPosLeft);
      sign.vecLoop = GetBianmaVectorInt(strMid);
      return sign;
   }
   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21

//   void GetKnitSign(const CString &sBianma)
//   {
//       list<CString> lstBianmaString = ShapeProfileRow::GetBianmaOneLineString(sBianma);
//       //#4217 ���͡���֯������������֯�����б� start Duchen 2017/12/29 11:54 dc171225
//       if (!lstBianmaString.empty())
//       {
//          vecKnitSign = ShapeProfileRow::GetBianmaInt(lstBianmaString.front());
//          m_vect2DKnit.clear();
//          for (auto Iter = lstBianmaString.begin(); Iter != lstBianmaString.end(); ++Iter)
//          {
//             m_vect2DKnit.push_back(ShapeProfileRow::GetBianmaInt(*Iter));
//          }
//       }
//       else
//       {
//          m_vect2DKnit.clear();
//          m_vect2DKnit.push_back(vecKnitSign);
//       }
////        if (!lstBianmaString.empty())
////           this->vecKnitSign = ShapeProfileRow::GetBianmaInt(lstBianmaString.front());
////  
////        this->m_vect2DKnit.clear();
////        for (auto Iter = lstBianmaString.begin(); Iter != lstBianmaString.end(); ++Iter)
////        {
////           this->m_vect2DKnit.push_back(ShapeProfileRow::GetBianmaInt(*Iter));
////        }
//       //#4217 ���͡���֯������������֯�����б� end   Duchen 2017/12/29 11:54
//   }

   //ZB-619 ���������������´��ޣ���Ҫ��ȹ���� start Duchen 2018/11/26 15:23 dc181126
   inline BOOL IsSuoZhen() const
   {
      if (ShapeSpace::en_Needle_SuoZhen == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Average == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Middle == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Side == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Custom == en_NeedleType
         //ZB-897 ��������1X1���������� start Duchen 2020/07/11 12:41 dc200706
         || ShapeSpace::en_Needle_SuoZhen_1x1 == en_NeedleType
         //ZB-897 ��������1X1���������� end   Duchen 2020/07/11 12:41
         || ShapeSpace::en_Needle_SuoZhen_Basemap == en_NeedleType)
      {
         return TRUE;
      }
      return FALSE;
   }
   //ZB-619 ���������������´��ޣ���Ҫ��ȹ���� end   Duchen 2018/11/26 15:23

   //inline static TYPE_2D_VECTSIGN GetKnitSign2D(const CString &sBianma)
   //{
   //   TYPE_2D_VECTSIGN TempVecKnitSign;
   //   list<CString> lstBianmaString = ShapeProfileRow::GetBianmaOneLineString(sBianma);

   //   TempVecKnitSign.clear();
   //   for (auto Iter = lstBianmaString.begin(); Iter != lstBianmaString.end(); ++Iter)
   //   {
   //      TempVecKnitSign.push_back(ShapeProfileRow::GetBianmaInt(*Iter));
   //   }
   //   return TempVecKnitSign;
   //}

   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
   inline static CString GetOneLineBianmaSub(const TYPE_VEC_KNITSIGN &vecLoop)
   {
      CString sTemp;
      CString sValue;
      TYPE_VEC_KNITSIGN::const_iterator sign_Iter = vecLoop.begin();
      for (;sign_Iter != vecLoop.end();++sign_Iter)
      {
         if ((sign_Iter + 1) != vecLoop.end())
         {
            sTemp.Format(L"%d,",(*sign_Iter));
            sValue += sTemp;
         }
         else
         {
            sTemp.Format(L"%d",(*sign_Iter));
            sValue += sTemp;
            break;
         }
      }
      return sValue;
   }
   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21

   inline static CString GetMultlineBianma(const TYPE_2D_VECTSIGN &vect2DKnit)
   {
      CString sValue = L"";
      CString sTemp;
      for (auto IterLine = vect2DKnit.begin(); 
         IterLine != vect2DKnit.end();
         ++IterLine)
      {
         //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
         CString sLeft = GetOneLineBianmaSub(IterLine->vecLeft);
         CString sLoop = GetOneLineBianmaSub(IterLine->vecLoop);
         CString sRight = GetOneLineBianmaSub(IterLine->vecRight);
         if (!sLeft.IsEmpty())
         {
            sValue += sLeft;
            sValue += _T("[");
         }
         sValue += sLoop;
         if (!sRight.IsEmpty())
         {
            sValue += _T("]");
            sValue += sRight;
         }

         //TYPE_VEC_KNITSIGN::const_iterator sign_Iter = IterLine->begin();
         //for (;sign_Iter != IterLine->end();++sign_Iter)
         //{
         //   if ((sign_Iter + 1) != IterLine->end())
         //   {
         //      sTemp.Format(L"%d,",(*sign_Iter));
         //      sValue += sTemp;
         //   }
         //   else
         //   {
         //      sTemp.Format(L"%d",(*sign_Iter));
         //      sValue += sTemp;
         //      break;
         //   }
         //}
         //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21

         if (IterLine + 1 != vect2DKnit.end())
         {
            sValue += _T(";");
         }
      }
      return sValue;
   }
   //#4217 ���͡���֯������������֯�����б� end   Duchen 2016/01/20 10:06
   UINT iRowIndex;                              //�к�
   //#4170 ����bug ��ͬGYE ���¾ɰ汾�ϳ��ֲ�ͬ�Ľ�� start Duchen 2016/11/23 15:47 dc161121
   UINT m_nRowIndexReal;                              //���յ��к�
   //#4170 ����bug ��ͬGYE ���¾ɰ汾�ϳ��ֲ�ͬ�Ľ�� end   Duchen 2016/11/23 15:47
   UINT iRowCount;                              //���� = ת����2
   int iNeedleNum;                             //����
   UINT iTimes;                                 //����
   UINT iNeedleMoveNum;                         //����Ŀ��
   UINT iNeedleLess;                            //͵�ԣ����룩
   UINT iMarkPos;                               //�����Ǻ�λ��
   ShapeSpace::Needle_Type en_NeedleType; //�������ͣ��������ͣ�
   //ZB-780 ��������һЩ�������������Զ����� start Duchen 2019/09/02 18:16 dc190902
   std::vector<BYTE> m_vecNeedlePackageStandColor; //�գ��ţ�����Сͼ����ɫ��
   CString m_sNeedlePackageModName; //�գ��ţ�����Сͼģ����
   //ZB-831 ���������Զ�������չ start Duchen 2020/03/09 10:52 dc20200309
   int m_nNeedlePackagePageCount;
   //ZB-831 ���������Զ�������չ end   Duchen 2020/03/09 10:52
   //ZB-780 ��������һЩ�������������Զ����� end   Duchen 2019/09/02 18:16
   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� start Duchen 2020/06/23 09:21 dc200622
   TYPE_VEC_LEFT_RIGHT_KNITSIGN vecKnitSign;               //��֯����
   //TYPE_VEC_KNITSIGN vecKnitSign;               //��֯����
   //ZB-892 ������֯����TXTת�ư��������ұ��ϲ�ѭ�� end   Duchen 2020/06/23 09:21
   //#4217 ���͡���֯������������֯�����б� start Duchen 2016/01/20 10:06 dc170116
   TYPE_2D_VECTSIGN m_vect2DKnit;
   //#4217 ���͡���֯������������֯�����б� end   Duchen 2016/01/20 10:06
   //#3125 ���ͼ��ת���������� start Duchen 2016/01/10 14:30 dc170109
   CString m_sOrgKnitSignName;
   //#3125 ���ͼ��ת���������� end   Duchen 2016/01/10 14:30
   //#4638 ����������������֯���� start Duchen 2017/04/19 10:53 dc170417
   CString m_sModType; //���������ṹ
   //#4638 ����������������֯���� end   Duchen 2017/04/19 10:53
   KnitParams paramKnitRow;                     //�����в���       
   double iHeight;                              //�߶�
	UINT effective ;                             //��Ч����
	UINT Real_effective;
   BOOL bEffective;                             //��Ч���

   //����ת����������
   BOOL bNeckKaisPs;                            //����ƽ��
};
typedef std::vector<ShapeProfileRow> TYPE_LIST_SHAPE;
typedef std::list<ShapeProfileRow>::iterator TYPE_LISTITER_SHAPE;
//---------------------------------------------------------------------------
//������ű�
typedef std::map<BYTE,TYPE_VEC_KNITSIGN> TYPE_MAP_SIGN;        //BYTE ������
typedef std::pair<BYTE,TYPE_VEC_KNITSIGN> TYPE_MAP_SIGN_PAIR;

typedef struct tagNeedleSign
{
   tagNeedleSign(){
      //Ĭ�ϲ���
      //bFrontLMarkSign = 71;
      //bFrontRMarkSign = 61;
      //bBackLMarkSign = 91; 
      //bBackRMarkSign = 81;
   }
   //TYPE_MAP_SIGN vecFrontLTranSigns;        //ǰ��֯����������
   //TYPE_MAP_SIGN vecFrontRTranSigns;        //ǰ��֯�ұ��������
   //TYPE_MAP_SIGN vecBackLTranSigns;         //���֯����������
   //TYPE_MAP_SIGN vecBackRTranSigns;         //���֯�ұ��������
   //TYPE_MAP_SIGN vecFrontNeckLTranSigns;    //V������������
   //TYPE_MAP_SIGN vecFrontNeckRTranSigns;    //V���ұ��������
   //TYPE_MAP_SIGN vecBackNeckLTranSigns;     //V������������
   //TYPE_MAP_SIGN vecBackNeckRTranSigns;     //V���ұ��������
   //BYTE      bFrontLMarkSign;               //ǰ��֯�߼ʣ��Ǻţ����� ���
   //BYTE      bFrontRMarkSign;               //ǰ��֯�߼ʣ��Ǻţ����� �Ҳ�
   //BYTE      bBackLMarkSign;                //���֯�߼ʣ��Ǻţ����� ���
   //BYTE      bBackRMarkSign;                //���֯�߼ʣ��Ǻţ����� �Ҳ�
   ShapeSpace::NeedleFlat_Type  m_nFlatType;//ƽ�շ�ʽ
   //ShapeSpace::Reduce_Type m_bodyneedle2type;    //�������뷽ʽ(2)  (����)
   //ShapeSpace::Reduce_Type m_bodyneedle3type;    //�������뷽ʽ(3)  (����)
   //ShapeSpace::Reduce_Type m_neckneedle2type;    //�������뷽ʽ(2)  (����)
   //ShapeSpace::Reduce_Type m_neckneedle3type;    //�������뷽ʽ(3)  (����)
}NeedleSign,*pNeedleSign;

////��߲���
//typedef std::vector<ShapeSpace::CLEARBORDERTYPE> TYPE_VEC_CLB;
//class CClearBorderCData:public CKnitData
//{
//public:
//   CClearBorderCData(){bClearBorder=FALSE;iClearCount=0;};
//   ~CClearBorderCData(){};
//public:
//   BOOL bClearBorder;            //�Ƿ����
//   int  iClearCount;             //�����
//   TYPE_VEC_CLB vecClearBorder;  //���ǰɫ������
//   std::vector<BYTE> vecCustomColor; //���ǰ�Զ���ɫ������
//   std::vector<BYTE> vecFinalColor;  //��ߺ�ɫ������
//};
//struct tagKeepInfo
//{
//	tagKeepInfo()
//	{
//		sizeModule   =  CSize(0, 0);
//	}
//	tagKeepInfo(std::vector<BYTE> &vectModuleData,  CSize size)
//	{
//		this->vectModuleData = vectModuleData;
//		sizeModule   =  size;
//	}
//	void GetReplaceColor(int x, int y, BYTE &color)
//	{
//		if (mapReplaceColor.find(y) != mapReplaceColor.end() &&
//			false==mapReplaceColor[y].empty())
//		{
//			color = mapReplaceColor[y].at(x % mapReplaceColor[y].size());
//		}
//	}
//	std::vector<BYTE>   vectModuleData;
//	std::map<int, TYPE_VEC_KNITSIGN>   mapReplaceColor;
//	CSize    sizeModule;
//};
//
//typedef std::vector<tagKeepInfo> VECT_MOD_INFO;
//
//
//// Cycle data of Arts
//struct tagCycleArts
//{
//	tagCycleArts(int ibgn, int iend)
//	{
//		iIndexBegin = ibgn; 
//		iIndexEnd = iend;
//	}
//	int          iIndexBegin;
//	int          iIndexEnd;
//
//	bool operator <(const tagCycleArts &rhs) const
//	{
//		if (iIndexBegin == rhs.iIndexBegin)
//		{
//			return iIndexEnd<rhs.iIndexEnd;
//		}
//		else if (iIndexBegin < rhs.iIndexBegin)
//		{
//			return iIndexEnd<rhs.iIndexEnd;
//		}
//		else
//		{
//			return iIndexEnd<=rhs.iIndexEnd;
//		}
//	}
//
//	bool operator ==(const tagCycleArts &rhs) const
//	{
//		return (iIndexBegin==rhs.iIndexBegin && iIndexEnd==rhs.iIndexEnd);
//	}
//};
//
//typedef std::map<tagCycleArts, int> MAP_CYCLEARTS;

//----------------------------------------------------------------------------
//��������
class CShapeProfileData//:
   //public CKnitData
{
public:
   CShapeProfileData()
   {
      //IsZhiXuanZhen = FALSE;                                //�Ƿ�ֱѡ�����
      //IsBottomExist = FALSE;                                //�Ƿ�����װ�
      //m_nMachineType = ShapeSpace::enMultiMachine;          //����ϵͳ
      //m_nNeedleTrans = ShapeSpace::enTransNone;             //�����
      //m_CombType = L"";                                     //��װ�ģʽ
      ////------------------------------------------------------------
      ////������أ�����ѡ�
      //m_iStartWidth = 100;                    //��֯��ʼ���
      //m_iStartOffset = 0;                     //��ʼƫ��
      //m_iNeckStartHeight = 0;                 //����λ ���� ������Ҫ��(ת�� = m_iNeckStartHeight /2)��ʾ
      //m_bNeckAutoHeight = TRUE;                //�Ƿ��Զ�����V��
      //m_iNeckStartWidth = 0;                  //����ױ߿��
      //IsBodySymmetry = TRUE;                  //�����Ƿ�Գ�
      //IsNeckSymmetry = TRUE;                 //�����Ƿ�Գ�
      m_enShapeType = ShapeSpace::en_Shape_All;                    //���ɲ�Ƭ
      //m_nNeedleType = ShapeSpace::enStaggerState;          //���뷽ʽ
      ////-----------------------------------------------------------
      ////v��ѡ��
      //m_nNeckType = ShapeSpace::en_Neck_Sleeve;          //����ģʽ         	--��0��ʼ
      //m_bNeedleSafeNO = 15;                   //V�찲ȫ����
      m_bNeckSplit = 2;                      //���������
    //  m_iNeckOffSet = 0;                     //����ˮƽƫ��
      m_isVneckYTX = FALSE;                  //�Ƿ�V�������� 
      m_isNeckSeparate = TRUE;               //�Ƿ�V�����
      m_isBottomSeparate = TRUE;             //�Ƿ���ײ���
    //  m_nEnecktype = ShapeSpace::enENeckSimpleNeedle_one;         //�ɸ߼���������ת�ƹ���XUYH Բ��ײ��з�ʽ
    //  m_bVNeckCZ = FALSE;                        //V�����
    //  m_bDeleteCenterLine = FALSE;					//��������
    //  //ɾ��������� start Duchen 2017/12/06 19:09 dc171205
    //  //m_bNeckSinYarn = FALSE;
    //  //ɾ��������� end   Duchen 2017/12/06 19:09
    //  //----------------------------------------------------------
    //  //��������
    //  m_ptCenter.x = 0;               //���������ĵ��Ի��������½�Ϊԭ�����꣬��1��ʼ
    //  m_ptCenter.y = 0;               //���������ĵ��Ի��������½�Ϊԭ�����꣬��1��ʼ
    //  m_sizeCanvas.cx = 0;            //������С
    //  m_sizeCanvas.cy = 0;            //������С
    //  IsKeepPattern = FALSE;          //�Ƿ�������
    //  IsKeepIntersia = FALSE;         //�Ƿ���������
	   //IsKeepOpt = FALSE;				  //�Ƿ���������
    //  //#4168 ��ͼʱ������Ŀͼ������ start Duchen 2017/05/26 9:56 dc160522
    //  m_bKeepDumu = FALSE;            //�Ƿ�����Ŀͼ
    //  //#4168 ��ͼʱ������Ŀͼ������ end   Duchen 2017/05/26 9:56
      x_Border_up = 0;                //��������(�б���)
      x_Border_down = 0;              //��������(�б���)
      y_Border = 0;                   //��������
      //#4066 ���ʱ������δʹ��ָ��ɫ����� start Duchen 2016/11/04 15:02 dc161031
      m_nYNeckBottomBorder = 0;        //���������
      //#4066 ���ʱ������δʹ��ָ��ɫ����� end   Duchen 2016/11/04 15:02
    //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ start Duchen 2019/09/29 17:52 dc190923
    //  m_enStartType = enAttachmentStartTypeNone;   //��ͷ��ʽ
    //  m_enEndType = enAttachmentEndTypeNone;     //ĩβ��ʽ
    //  m_enConnectType = enAttachmentConnectTypeNone; //�νӷ�ʽ
    //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ end   Duchen 2019/09/29 17:52
	   //// 2012-12-5 xuyh�����ɴ���
	   //iMianshaCenterNum   = _T("");
	   //bIsMianshaCenter = TRUE;
	   //enBodySizeFlag  = ShapeSpace::enSize_XS;
	   //enBodySizeType = ShapeSpace::enSizeType_diaomu;
    //  bGetDataFromCanvas = TRUE;
      //ɾ��������� start Duchen 2017/12/06 19:09 dc171205
      //m_isSignHorizontal = TRUE;
      //ɾ��������� end   Duchen 2017/12/06 19:09

      m_bTiHuaShouZhen = FALSE;
  //    m_pNextPieceData  = NULL;
  //    m_pPrePieceData   = NULL;
  //    //#4213 �������յ�����֯Ϊ2�����֯��ʱ������䲼���� start Duchen 2017/02/10 15:56 dc170206
  //    m_bTopUseBack = FALSE;               //���ɴʹ�ñ���
	 // m_bNoBottomNeckcalulateKnit2 = FALSE;
  //    //#4213 �������յ�����֯Ϊ2�����֯��ʱ������䲼���� end   Duchen 2017/02/10 15:56
  //   //#4638 ����������������֯���� start Duchen 2017/04/19 10:53 dc170417
  //   m_bQLDataShapeNotFromDitu = FALSE;     //�Ƿ���ʹ��rnf�׵�ͼ
  //   //#4638 ����������������֯���� end   Duchen 2017/04/19 10:53
  //   //�Ứͼ�⴦�� start Duchen 2016/11/13 10:37 dc161113
  //   m_bTiHuaTuku = FALSE;
  //   //�Ứͼ�⴦�� end   Duchen 2016/11/13 10:37
  //   //#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� start Duchen 2017/10/27 16:26 dc161023
  //   m_bChangeTail = FALSE;
  //   //#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� end   Duchen 2017/10/27 16:26
  //   //#6050 ��ɫ���� start Duchen 2017/11/17 15:57 dc171117
  //   m_bDaShenJiaSe = FALSE;
  //   //#6050 ��ɫ���� end   Duchen 2017/11/17 15:57

  //   //ZB-273 3Dת�ư棺�����ɫʱ��ƽ��ɫ��ȡ��������ɫ����� start Duchen 2018/06/05 16:11 dc180604
  //   m_bDaShenJiaSeNoCreateZuZhiTu = FALSE; //�Ǵ����ɫ�����������µ���֯ͼ����
  //   //ZB-273 3Dת�ư棺�����ɫʱ��ƽ��ɫ��ȡ��������ɫ����� end   Duchen 2018/06/05 16:11

  //   //ZB-253 �������ӽӿڣ�����֮ǰ�����ݣ�Duc֪����ʵ�ֳ��ͺ���֯ͼ��ָ�����ݣ�������Chenjw������Duc֪������ָ����֯ͼ����ͼ��ָ��λ���������� start Duchen 2018/05/04 10:11 dc180308
  //   m_bInaNoAdditionColor = FALSE;
  //   //ZB-253 �������ӽӿڣ�����֮ǰ�����ݣ�Duc֪����ʵ�ֳ��ͺ���֯ͼ��ָ�����ݣ�������Chenjw������Duc֪������ָ����֯ͼ����ͼ��ָ��λ���������� end   Duchen 2018/05/04 10:11

  //   //ZB-905 ������֯����TXTת�ư��������ұ��ϲ�ѭ�����бߵ�����֮���ɫ�봦��� start Duchen 2020/07/03 12:21 dc200629
  //   m_bEdgeNeedleFix = FALSE; //�б������Ե�̶�
  //   //ZB-905 ������֯����TXTת�ư��������ұ��ϲ�ѭ�����бߵ�����֮���ɫ�봦��� end   Duchen 2020/07/03 12:21
   }
   ~CShapeProfileData(){}
public:
   //TYPE_LIST_SHAPE m_LShapeData;                //��๤�������� //[XML][RNF]
   //MAP_CYCLEARTS  m_vectLCycle;                 //��๤����ѭ������ //[XML]
   //TYPE_LIST_SHAPE m_RShapeData;                //�Ҳ๤�������� //[XML][RNF]
   //MAP_CYCLEARTS  m_vectRCycle;                 //�Ҳ๤����ѭ������ //[XML]
   //TYPE_LIST_SHAPE m_VLShapeData;               //��V�칤�������� //[XML][RNF]
   //MAP_CYCLEARTS  m_vectLNCycle;                //��V�칤����ѭ������ //[XML]
   //TYPE_LIST_SHAPE m_VRShapeData;               //��V�칤�������� //[XML][RNF]
   //MAP_CYCLEARTS  m_vectRNCycle;                //��V�칤����ѭ������ //[XML]
   ////----------------------------------------------------------
   ////�������
   //BOOL     IsZhiXuanZhen;                      //�Ƿ�ֱѡ����� //[XML]
   //BOOL     IsBottomExist;                      //�Ƿ�����װ� //[XML]
   //ShapeSpace::Sys_Type m_nMachineType;         //����ϵͳ //[XML]

   ParamSet m_ParamSet;                         //����ֵ���� //[XML]
   OtherParamSet m_OtherParamSet;               //�߼��������� //[XML]
   //ShapeSpace::NeedleTrans_Type  m_nNeedleTrans;//����� //[XML]
   //CString  m_CombType;                         //��װ�ģʽ //[XML]
   ////------------------------------------------------------------
   ////������أ�����ѡ�
   //UINT     m_iStartWidth;                      //��֯��ʼ��� //[XML][RNF]
   //int      m_iStartOffset;                     //��ʼƫ�� //[XML][RNF]
   //UINT     m_iNeckStartHeight;                 //����λ ���� ������Ҫ��(ת�� = m_iNeckStartHeight /2)��ʾ //[XML]
   //BOOL     m_bNeckAutoHeight;                  //�Ƿ��Զ�����V�� //[XML]
   //int      m_iNeckStartWidth;                  //����ױ߿�� ������ //[XML][RNF]
   //BOOL     IsBodySymmetry;                     //�����Ƿ�Գ� //[XML][RNF]
   //BOOL     IsNeckSymmetry;                     //�����Ƿ�Գ� //[XML][RNF]
   ShapeSpace::Shape_Type m_enShapeType;                    //���ɲ�Ƭ ��Ƭ������ //[XML][RNF]
   //��������
   NeedleSign m_NeedleSigns;                    //������ű� //[XML]
   //ShapeSpace::Row_Type m_nNeedleType;          //���뷽ʽ //[XML]
   ////-----------------------------------------------------------
   ////v��ѡ��
   //ShapeSpace::Neck_Type  m_nNeckType;          //����ģʽ Բ�� V�� ���� �� --��0��ʼ //[XML][RNF]
   //BYTE      m_bNeedleSafeNO;                   //V�찲ȫ���� //[XML]
   BYTE      m_bNeckSplit;                      //��������� //[XML]
   //int       m_iNeckOffSet;                     //����ˮƽƫ�� //[XML][RNF]
   BOOL      m_isVneckYTX;                      //�Ƿ�V�������� //[XML]
   BOOL      m_isNeckSeparate;                  //�Ƿ�V����� //[XML]
   BOOL      m_isBottomSeparate;                //�Ƿ���ײ��� //[XML]
   ShapeSpace::ENeck_Type m_nEnecktype;         //�ɸ߼���������ת�ƹ���XUYH Բ��ײ��з�ʽ //[XML]
   //BOOL      m_bVNeckCZ;                        //V����� //[XML]
   //BOOL      m_bDeleteCenterLine;					//�������� //[XML][RNF]
   ////ɾ��������� start Duchen 2017/12/06 19:09 dc171205
   ////BOOL      m_bNeckSinYarn;
   ////ɾ��������� end   Duchen 2017/12/06 19:09
   ////----------------------------------------------------------
   ////�����֯����
   //
   CKDModData m_ModData;                 //������� //[XML][RNF]
   ////----------------------------------------------------------
   ////��������
   //CPoint m_ptCenter;               //���������ĵ��Ի��������½�Ϊԭ�����꣬��1��ʼ //[XML][RNF]
   //CSize  m_sizeCanvas;             //������С //[RNF]
   //std::vector<BYTE> m_vecPatData;  //������������ //[RNF]
   //std::vector<BYTE> m_vecInaData;  //����������
   ////#4168 ��ͼʱ������Ŀͼ������ start Duchen 2017/05/26 9:56 dc160522
   //std::vector<BYTE> m_vecDumuData;  //����������
   ////#4168 ��ͼʱ������Ŀͼ������ end   Duchen 2017/05/26 9:56
   ////#4635 ��ͼ�����Ҫ����������Ǻ� start Duchen 2017/04/14 11:15 dc170410
   //std::vector<BYTE> m_vecAssistRegion; //�����������������,���������м��ڿղ��ֱ�ʾΪ0 //[RNF]
   ////#4635 ��ͼ�����Ҫ����������Ǻ� end   Duchen 2017/04/14 11:15
   ////ZB-285 ���ͽӿ�patData������1��ɫ�����⴦��͸��͸���������޷���ȷ���ú���1��ɫ����֯���ݣ���֯ͼͬ����Ҫ���⴦�� start Duchen 2018/05/14 16:21 dc180514
   //std::vector<BYTE> m_vec3DPatRegion; //3d����ͼСͼ�����ݣ����ڴ�ռ���൱��ȫ��ͼ��
   ////ZB-285 ���ͽӿ�patData������1��ɫ�����⴦��͸��͸���������޷���ȷ���ú���1��ɫ����֯���ݣ���֯ͼͬ����Ҫ���⴦�� end   Duchen 2018/05/14 16:21
   //BOOL IsKeepPattern;              //�Ƿ������� //[XML][RNF]
   //BOOL IsKeepIntersia;             //�Ƿ��������� //[XML][RNF]
   //BOOL IsKeepOpt;                  //�Ƿ��������� //[XML]
   ////#4168 ��ͼʱ������Ŀͼ������ start Duchen 2017/05/26 9:56 dc160522
   //BOOL m_bKeepDumu;                //�Ƿ��Ŀͼ //[XML]
   ////#4168 ��ͼʱ������Ŀͼ������ end   Duchen 2017/05/26 9:56
   //BOOL bGetDataFromCanvas;         //�Ƿ�ӻ�����ȥȡ����
   ////#4638 ����������������֯���� start Duchen 2017/04/19 10:53 dc170417
   //BOOL m_bQLDataShapeNotFromDitu;     //�Ƿ��Ǵ�rnfֱ�ӳ��ͣ�û���׵�ͼ
   ////#4638 ����������������֯���� end   Duchen 2017/04/19 10:53
   ////�Ứͼ�⴦�� start Duchen 2016/11/13 10:37 dc161113
   //BOOL m_bTiHuaTuku; //�Ƿ����Ứͼ�⴦�� //[RNF]
   ////�Ứͼ�⴦�� end   Duchen 2016/11/13 10:37
   ////#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� start Duchen 2017/10/27 16:26 dc161023
   //BOOL m_bChangeTail;              //�Ƿ��Ǹ�����β
   ////#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� end   Duchen 2017/10/27 16:26
   UINT x_Border_up;                //��������(�б���) //[XML]
   UINT x_Border_down;              //��������(�б���) //[XML]
   UINT y_Border;                   //�������� //[XML]
   //#4066 ���ʱ������δʹ��ָ��ɫ����� start Duchen 2016/11/04 15:02 dc161031
   int m_nYNeckBottomBorder;         //��������� //[XML]
 //  //#4066 ���ʱ������δʹ��ָ��ɫ����� end   Duchen 2016/11/04 15:02
   BOOL m_bTiHuaShouZhen;           //�Ứ���� //[XML]
 //  //��߲���
 //  CClearBorderCData m_ClearBorderPara;   //��߲��� //[XML]

	//// 2012-12-5 xuyh�����ɴ���
	//CString iMianshaCenterNum ;   //���ļǺ� //[XML][RNF]
 //  //ɾ��������� start Duchen 2017/12/06 19:09 dc171205
 //  //BOOL m_isSignHorizontal; //�Ǻź�����
 //  //ɾ��������� end   Duchen 2017/12/06 19:09
	//BOOL bIsMianshaCenter;  //���� //[XML][RNF]

	//ShapeSpace::BODYSIZEFLAG enBodySizeFlag;  //����(S,M,L��) //[XML]
	//ShapeSpace::BODYSIZETYPE enBodySizeType;  //�����ʾ��ʽ����Ŀ�����ף� //[XML]

	//VECT_MOD_INFO  m_vectModuleInfo; //��������ģ����Ϣ //[XML][RNF]

 //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ start Duchen 2019/09/29 17:52 dc190923
 //  enum AttachmentStartType
 //  {
 //     enAttachmentStartTypeNone = 0, //��
 //     enAttachmentStartTypeAfterKongZhuanFirst = 1, //��ת���һ��/�����һ��
 //     enAttachmentStartTypeLastKongZhuan = 2,//��ת���һ��/����ڶ���
 //  };
 //  AttachmentStartType m_enStartType;   //��ͷ��ʽ //[RNF]
 //  enum AttachmentEndType
 //  {
 //     enAttachmentEndTypeNone = 0, //��
 //     enAttachmentEndTypeLastLine = 1, //�����������һ�з��ɣ���ת��תΪ��λ��Ϊ���һת��
 //     enAttachmentEndTypeSecondLastLine = 2, //�������浹���ڶ��з��ɣ���ת��תΪ��λ��Ϊ�����ڶ�ת��
 //     enAttachmentEndTypeTransFirstLine = 3, //���굥���һ��
 //     //ZB-925 ������֧�ַ���ֻ��1�� start Duchen 2020/07/15 13:21 dc200713
 //     enAttachmentEndTypeTransFirstLineSingle = 4, //���굥���һ�� ����
 //     //ZB-925 ������֧�ַ���ֻ��1�� end   Duchen 2020/07/15 13:21
 //  };
 //  AttachmentEndType m_enEndType;     //ĩβ��ʽ //[RNF]
 //  enum AttachmentConnectType
 //  {
 //     enAttachmentConnectTypeNone = 0, //��
 //     enAttachmentConnectTypeLuowenZimaYuanTongSipinJiaJin = 1, //��������ԲͲ��ƽ�ӽ�
 //     enAttachmentConnectTypeJinZimaYuanTongSipinJiaJin = 2, //������ԲͲ��ƽ�ӽ�
 //     enAttachmentConnectTypeSipinJiaJin = 3 //��ƽ�ӽ�
 //  };

 //  AttachmentConnectType m_enConnectType; //�νӷ�ʽ //[RNF]
 //  //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ end   Duchen 2019/09/29 17:52

 //  //ZB-905 ������֯����TXTת�ư��������ұ��ϲ�ѭ�����бߵ�����֮���ɫ�봦��� start Duchen 2020/07/03 12:21 dc200629
 //  BOOL m_bEdgeNeedleFix; //�б������Ե�̶�
 //  //ZB-905 ������֯����TXTת�ư��������ұ��ϲ�ѭ�����бߵ�����֮���ɫ�봦��� end   Duchen 2020/07/03 12:21

	//// �����������
	//BOOL  m_IsTrans;                 // �Ƿ񷭵��� //[XML][RNF]
	//int   m_iLoopCount;              // ѭ������ //[XML]
	//BOOL  m_TempIsGreet;		         // �Ƿ�ӱ�(�����м�����, �ǽ������ݣ���Ҫ����)
 //  int   m_iOrgLeftWidth;
 //  int   m_iFirstPieceCenter;       //���ڼ������һƬ�ķ�ɴλ�ã��ǽ������ݣ���Ҫ����)
 //  int   m_iLastPieceOffset;       // ���ڼ������һƬ�ķ�ɴλ�ã��ǽ������ݣ���Ҫ����)
 //  //#4213 �������յ�����֯Ϊ2�����֯��ʱ������䲼���� start Duchen 2017/02/10 15:56 dc170206
 //  BOOL  m_bTopUseBack;               //���ɴʹ�ñ���
 //  BOOL  m_bNoBottomNeckcalulateKnit2; //�Ƿ�Ϊ���ɴ����״���ʽ2
 //  //#4213 �������յ�����֯Ϊ2�����֯��ʱ������䲼���� end   Duchen 2017/02/10 15:56

 //  //#5651 ����������֯�����Զ����ɺ��ʵ����뷽ʽ start Duchen 2017/10/19 10:32 dc161016
 //  CString m_sDaShenTypeName;     //������֯������
 //  //#5651 ����������֯�����Զ����ɺ��ʵ����뷽ʽ end   Duchen 2017/10/19 10:32

 //  //#6050 ��ɫ���� start Duchen 2017/11/17 15:57 dc171117
 //  BOOL m_bDaShenJiaSe;    //�Ƿ�����ɫ������ת�ư��ͼΪ��ɫ��//[RNF]
 //  //#6050 ��ɫ���� end   Duchen 2017/11/17 15:57

 //  //ZB-273 3Dת�ư棺�����ɫʱ��ƽ��ɫ��ȡ��������ɫ����� start Duchen 2018/06/05 16:11 dc180604
 //  BOOL m_bDaShenJiaSeNoCreateZuZhiTu; //�Ǵ����ɫ�����������µ���֯ͼ����
 //  //ZB-273 3Dת�ư棺�����ɫʱ��ƽ��ɫ��ȡ��������ɫ����� end   Duchen 2018/06/05 16:11

 //  //ZB-253 �������ӽӿڣ�����֮ǰ�����ݣ�Duc֪����ʵ�ֳ��ͺ���֯ͼ��ָ�����ݣ�������Chenjw������Duc֪������ָ����֯ͼ����ͼ��ָ��λ���������� start Duchen 2018/05/04 10:11 dc180308
 //  BOOL m_bInaNoAdditionColor; //��֯ͼ����Ӷ���ɫ�룬�����룬��ߣ���ɴ�ȣ���ʱ���õ�flag,Ĭ��FALSE
 //  //ZB-253 �������ӽӿڣ�����֮ǰ�����ݣ�Duc֪����ʵ�ֳ��ͺ���֯ͼ��ָ�����ݣ�������Chenjw������Duc֪������ָ����֯ͼ����ͼ��ָ��λ���������� end   Duchen 2018/05/04 10:11

   ////ZB-780 ��������һЩ�������������Զ����� start Duchen 2019/09/02 18:16 dc190902
   //struct NeedlePackageData
   //{
   //   std::vector<BYTE> vecLeftStandData;
   //   std::vector<BYTE> vecRightStandData;
   //   int nModPacSizeX;
   //   int nModPacSizeY;
   //   vector<BYTE> vecPatModPacData;
   //   vector<BYTE> vecInaModPacData;
   //   vector<BYTE> vecJqdModPacData;
   //   vector<BYTE> vecCtrlModPacData;
   //   //ZB-831 ���������Զ�������չ start Duchen 2020/03/09 10:52 dc20200309
   //   int nLeftPageCount;
   //   int nRightPageCount;
   //   //ZB-831 ���������Զ�������չ end   Duchen 2020/03/09 10:52
   //};
   //std::map<CString, NeedlePackageData> m_mapNeedlePackageData; //����dll�ڲ���������
   ////ZB-780 ��������һЩ�������������Զ����� end   Duchen 2019/09/02 18:16

   //CShapeProfileData*       m_pNextPieceData;   //��Ƭ��֯����һƬ����
   //CShapeProfileData*       m_pPrePieceData;   //��Ƭ��֯����һƬ����
private:
	//void AutoNeedleLess(TYPE_LIST_SHAPE &listdata)
	//{
	//	if (ShapeSpace::en_Cancel_1N == m_OtherParamSet.m_cancelType || ShapeSpace::en_Cancel_2N == m_OtherParamSet.m_cancelType)
	//	{
	//		TYPE_LIST_SHAPE::iterator IterShapeList = listdata.begin();
	//		for (;IterShapeList!= listdata.end();++IterShapeList)
	//		{
	//			int iNeedleLess = IterShapeList->AutoCancel(m_OtherParamSet.m_cancelType);
	//			if (0 == IterShapeList->iNeedleLess && iNeedleLess != 0 )
	//			{
	//				IterShapeList->iNeedleLess = iNeedleLess;
	//			}  
	//		}
	//	}
	//}
public:
	//void AllShapeListAutoLess()
	//{
	//	AutoNeedleLess(m_LShapeData);
	//	AutoNeedleLess(m_RShapeData);
	//	AutoNeedleLess(m_VLShapeData);
	//	AutoNeedleLess(m_VRShapeData);
	//}

   /*void ReSetTecEffective()
   {
      int iEffectNum = m_OtherParamSet.effectiveNum;
      if(!m_LShapeData.empty())
      {
         ReSetOneListEffective(m_LShapeData, iEffectNum);
      }
      if(!m_RShapeData.empty())
      {
         ReSetOneListEffective(m_RShapeData, iEffectNum);
      }
      if(!m_VLShapeData.empty())
      {
         ReSetOneListEffective(m_VLShapeData, iEffectNum);
      }
      if(!m_VRShapeData.empty())
      {
         ReSetOneListEffective(m_VRShapeData, iEffectNum);
      }
   }*/
   ////#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� start Duchen 2016/09/05 15:17 dc160905
   //BOOL IsQuanTiHua()
   //{
   //   return (_T("shuangmiantihua") == this->m_ModData.m_strTransType || this->m_bTiHuaShouZhen);
   //}
   ////#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� end   Duchen 2016/09/05 15:17

   ////#5651 ����������֯�����Զ����ɺ��ʵ����뷽ʽ start Duchen 2017/10/19 10:32 dc161016
   //void SetKnitSignAll(const CString &sBianma)
   //{
   //   TYPE_2D_VECTSIGN vecSign2D = ShapeProfileRow::GetKnitSign2D(sBianma);

   //   for (auto Iter = m_LShapeData.begin(); Iter != m_LShapeData.end(); ++Iter)
   //   {
   //      Iter->m_vect2DKnit = vecSign2D;
   //      if (!vecSign2D.empty())
   //      {
   //         Iter->vecKnitSign = vecSign2D.front();
   //      }
   //   }

   //   for (auto Iter = m_RShapeData.begin(); Iter != m_RShapeData.end(); ++Iter)
   //   {
   //      Iter->m_vect2DKnit = vecSign2D;
   //      if (!vecSign2D.empty())
   //      {
   //         Iter->vecKnitSign = vecSign2D.front();
   //      }
   //   }
   //}
   ////#5651 ����������֯�����Զ����ɺ��ʵ����뷽ʽ end   Duchen 2017/10/19 10:32
   ////#4171 �����RNF���뷨��ͼ ��ʾ�ڴ治�� ���±��� start Duchen 2017/12/07 14:20 dc171207
   //void ClearCanvasData() //��������������
   //{
   //   m_vecPatData.clear();
   //   m_vecPatData.shrink_to_fit();
   //   m_vecInaData.clear();
   //   m_vecInaData.shrink_to_fit();
   //   m_vecDumuData.clear();
   //   m_vecDumuData.shrink_to_fit();
   //   m_vecAssistRegion.clear();
   //   m_vecAssistRegion.shrink_to_fit();
   //   //ZB-285 ���ͽӿ�patData������1��ɫ�����⴦��͸��͸���������޷���ȷ���ú���1��ɫ����֯���ݣ���֯ͼͬ����Ҫ���⴦�� start Duchen 2018/05/14 16:21 dc180514
   //   m_vec3DPatRegion.clear();
   //   m_vec3DPatRegion.shrink_to_fit();
   //   //ZB-285 ���ͽӿ�patData������1��ɫ�����⴦��͸��͸���������޷���ȷ���ú���1��ɫ����֯���ݣ���֯ͼͬ����Ҫ���⴦�� end   Duchen 2018/05/14 16:21
   //}
   ////#4171 �����RNF���뷨��ͼ ��ʾ�ڴ治�� ���±��� end   Duchen 2017/12/07 14:20
private:
   void ReSetOneListEffective(TYPE_LIST_SHAPE &shapeList , int iEffect)
   {
      TYPE_LIST_SHAPE::iterator iter_Beg = shapeList.begin();
      for(; iter_Beg != shapeList.end(); ++iter_Beg)
      {
         if (iter_Beg->effective ==0 )
         {
            iter_Beg->Real_effective = iEffect;
         }
         else
            iter_Beg->Real_effective = iter_Beg->effective;
      }
   }

};


