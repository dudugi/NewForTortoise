/********************************************************************
//  ����:           linyp
//  CopyRight(c)    2011 Burnon All Rights Reserved 
//  ����ʱ��:       2011/09/06 19:32
//  ������:         ������������ռ� enum����
//  �޸�ʱ��:       
//  �޸�Ŀ��:       
*********************************************************************/
#pragma once
/*
�Զ���ģ��������Ϣ
*/
//�Զ���ģ���ɴ
#define REFUSEYARN L"RefuseYarn"

//�Զ���ģ�� ϵͳ�Զ���ģ������
#define SYSDEFFSTD L"StdModel"
//ģ���ɴ���ֶ���
#define MODYARNPICK L"�����֯��ɴ"
//��ײ��ֹ��������ݱ�
#define TRANSTYPE  L"STDTRANS"
//�Զ���ģ�� ��װ�����
#define COMBMODEL L"COMBMODEL"



namespace ShapeSpace
{
   //����ѡ��
   enum Sys_Type{
      enSinMachine = 0,       //��ϵͳ
      enMultiMachine = 1,         //��ϵͳ
      enMachineNull = 2,
   };
   //�����
   enum NeedleTrans_Type
   {
      enTransNone = 0,          //�ޱ����
      enTransSin ,              //��������
      enTransMuli               //˫������
   };
   
   /************************************************************/
   //���ղ���ö�ٶ���
   //����/���� ����
   enum Needle_Type
   {
       en_Needle_Null = 0,    //ƽң �޼����붯��
       en_Needle_Add,         //����
       en_Needle_Sub,         //����
       en_Needle_Ps,          //�б߻���ƽ��
       en_Needle_Mark,        //�Ǻ�
       en_Needle_Hole,        //����
       en_Needle_Cotton,      //��ɴ
       en_Needle_LaXian,       //����
		 en_Needle_QiJia,        //������
       en_Needle_SuoZhen,       //����
       en_Needle_KaisPs,       //�������ƽ��
       //ZB-230 �����Ǻ����ʹ������� start Duchen 2018/05/08 16:20 dc180507
       en_Needle_CuZhenLaXian,   //�������� ��ΪҪ���ļ���֤������ ���Բ��ܲ��м�ı���ֵ
       //ZB-230 �����Ǻ����ʹ������� end   Duchen 2018/05/08 16:20
       //ZB-602 �ư��������뷽ʽ��ƽ�������м�������ࣩstart Duchen 2018/11/16 10:01 dc181112
       en_Needle_SuoZhen_Average, //����(��)
       en_Needle_SuoZhen_Middle, //����(��)
       en_Needle_SuoZhen_Side, //����(��)
       //ZB-602 �ư��������뷽ʽ��ƽ�������м�������ࣩend   Duchen 2018/11/16 10:01
       //ZB-619 ���������������´��ޣ���Ҫ��ȹ���� start Duchen 2018/11/26 15:23 dc181126
       en_Needle_SuoZhen_Custom, //����(�û�)
       //ZB-619 ���������������´��ޣ���Ҫ��ȹ���� end   Duchen 2018/11/26 15:23
       //ZB-626 �����������ޣ���ͼ������ͼ���ƶ��ʹ���ɫ����ŷ��ɵ�ͼ������ɫ����� start Duchen 2018/12/10 15:23 dc181210
       en_Needle_SuoZhen_Basemap, //����(��ͼ)
       //ZB-626 �����������ޣ���ͼ������ͼ���ƶ��ʹ���ɫ����ŷ��ɵ�ͼ������ɫ����� end   Duchen 2018/12/10 15:23
       //ZB-30 ��μ���ʱ��ѡ����ӣ�����ʽ������#6355�� start Duchen 2019/02/25 09:35 dc190225
       en_Needle_QiJia2, //���2
       //ZB-30 ��μ���ʱ��ѡ����ӣ�����ʽ������#6355�� end   Duchen 2019/02/25 09:35
       //ZB-912 ���ӼǺŷ�ʽ��Ŀǰֻ�����ߺʹ������� start Duchen 2020/07/08 13:21 dc200706
       en_Needle_LaXian1x4, //����1x4
       en_Needle_LaXian2x4, //����2x4
       //ZB-912 ���ӼǺŷ�ʽ��Ŀǰֻ�����ߺʹ������� end   Duchen 2020/07/08 13:21
       //ZB-897 ��������1X1���������� start Duchen 2020/07/11 12:41 dc200706
       en_Needle_SuoZhen_1x1, //����1X1
       //ZB-897 ��������1X1���������� end   Duchen 2020/07/11 12:41
   };
   //ƽ�շ�ʽ
   enum NeedleFlat_Type
   {
      en_Flat_Simple_1= 0,
      en_Flat_Simple_2,
      en_Flat_Double_1,
      en_Flat_Double_2,
      en_Flat_Space,
	  en_Flat_MainCotton,
	  en_Flat_NewMod,       // 61 71 ���뷽ʽ
	  en_Flat_WasteCotton,
      enMoldPS1_1,          //ƽ��1-1��1���գ�
      enMoldPS1_2,          //ƽ��1-2��1���գ�
      enMoldPS1_3,          //ƽ��1-3��1���գ�
      enMoldPS1_4,          //ƽ��1-4��1���գ�
      enMoldPS1_5,          //ƽ��1-5��1���գ�
      enMoldPS1_6,          //ƽ��1-6��1���գ�
      enMoldPS2_1,          //ƽ��2-1��2���գ�
      enMoldPS2_2,          //ƽ��2-2��2���գ�
      enMoldPS2_3,          //ƽ��2-3��2���գ�
      enMoldPS2_4,          //ƽ��2-4��2���գ�
      enMoldPSLB,           //�䲼��
      enMoldPS1_7           ////ƽ��1-7��1���գ�


   };
   /************************************************************/
   //���Ӳ���
   enum Neck_Type
   {
      en_Neck_Circle,   //Բ��
      en_Neck_VNeck,    //v��
      en_Neck_JLLW,     //�������������룩
      en_Neck_JLDM,     //�����Ŀ
      en_Neck_Sleeve,   //����
	   en_Neck_Attachment,
   };

   /************************************************************/
   //��������
   enum KnitPara_Type{
      enParaNone = 0,   //�޲���
      enParaDefined,    //�Զ������
      enParaMold1       //����ģʽ1
   };

	enum Add_Type{
		enAdd_Yarn,
		enAdd_One1,
		enAdd_One2,
		enAdd_Two
      //#4621 ���ͼ���������ȫ͵��ѡ�� start Duchen 2017/04/18 11:15 dc170417
      ,enAdd_All1
      ,enAdd_All2
      //#4621 ���ͼ���������ȫ͵��ѡ�� end   Duchen 2017/04/18 11:15
	};
	enum CANCEL_TYPE{
		en_Cancel_NON = 0,
		en_Cancel_1N,
		en_Cancel_2N,
	};
   enum ENeck_Type{
      enENeckKnit,                    //��֯��ǰ��
      enENeckMainYarn1,               //��ɴ�䲼1
      enENeckMainYarn2,               //��ɴ�䲼2      
      enENeckScrapYarn,               //��ɴ�䲼
      enENeckSimpleNeedle_one,        //���루1��
      enENeckSimpleNeedle_double,     //����(2) 
      //#6266 ���ƽ��ҲҪ��˫��1ѡ�� start Duchen 2018/01/04 18:06 dc180104
      enENeckDoubleNeedle2,            //˫��2(2) 
      //enENeckDoubleNeedle,            //˫��2(2) 
      //#6266 ���ƽ��ҲҪ��˫��1ѡ�� end   Duchen 2018/01/04 18:06
      enENeckSeperateNeedle,           //���� 
      enENeckScrapYarn_LX,             //��ɴ�䲼�����ƣ�
      enENeckKnitBack                //��֯��ǰ�� 
      //#4120 ��������˫���Ứ�䲼��ʽ����ɴ�䲼2�� start Duchen 2016/12/26 18:05 dc161226
      ,enENeckScrapYarn2               //��ɴ�䲼2
      //#4120 ��������˫���Ứ�䲼��ʽ����ɴ�䲼2�� end   Duchen 2016/12/26 18:05
      //#6266 ���ƽ��ҲҪ��˫��1ѡ�� start Duchen 2018/01/04 18:06 dc180104
      ,enENeckDoubleNeedle1            //˫��2(1)
      //#6266 ���ƽ��ҲҪ��˫��1ѡ�� end   Duchen 2018/01/04 18:06
   };
   enum Cotton_Type{
      enDirecrt_Knit=0,
      enAddNeedle_one,
      enAddNeedle_double,
		enAddNeedle_Third,
		enAddNeedle_Forou,
		enAddNeedle_Five
   };
   enum Rib_Type{
      enRibFull,
      enRibBroken
   };

   //��Ƭ�趨
   enum Shape_Type
   {
      en_Shape_All,  //��Ƭ
      en_Shape_Left, //��Ƭ
      en_Shape_Right //��Ƭ
   };

   //����װ�����
   enum FroBkNeedle
   {
      enFrontBkNull,    //��
      enFrontKnit1,     //��1֧��
      enFrontKnit2,     //��2֧��
      enFrontKnit3,     //��3֧��
      enBackKnit1,      //��1֧��
      enBackKnit2,      //��2֧��
      enBackKnit3,      //��3֧��
      //ZB-928 �����Ų���бһ֧�� �ư���߳��ͳ�������û���ų�бһ֧������+�ư濨÷�ؿ��� start Duchen 2020/08/11 13:17 dc200810
      enObliqueKnit1,   //бһ֧��
      enObliqueKnit2,   //б��֧��
      enObliqueKnit3,   //б��֧��
      //ZB-928 �����Ų���бһ֧�� �ư���߳��ͳ�������û���ų�бһ֧������+�ư濨÷�ؿ��� end   Duchen 2020/08/11 13:17
   };
   //�䲼�趨
   enum QHLuoBu
   {
      enModLbQLB = 0,         //�䲼 ǰ�䲼
      enModLbHLB = 1,         //�޲� ���䲼
      enModPTBZ = 2,          //��ͨ��֯���֯
      enModQBZ = 3,           //  ǰ��֯
      //ZB-924 ��б�󣬺�ǿ����ѡ���Զ����ͣ��ư棩 start Duchen 2020/08/03 13:17 dc200803
      enModDmGXSQ = 4,        //�����б��(ǰ)
      enModDmGXSH = 5         //�����б��(��)
      //ZB-924 ��б�󣬺�ǿ����ѡ���Զ����ͣ��ư棩 end   Duchen 2020/08/03 13:17
   };
   enum{
      enUnionLine = 0,        //ͬ��
      enStaggerLine           //����
   };
   enum Row_Type{
      enUnionState = 0,       //ͬ��״̬
      enStaggerState,         //����״̬
      enStaggerState_Right,         //����״̬
   };

   enum
   {
      enModSzfsZYTH = 1,   //����ͬ��
      enModSzfsZYFH = 2,   //���ҷ���
      enModSzfsZYFH2 = 3   //���Ҹ���
   };

   enum Body_Type
   {
      //˳���ܱ�� ֻ���������,������صĶ���
      en_UserDefine          =  0,          //Ϊ�û����Ƶ����������ʹ���û�����
      en_BirdEyes_Bottom     =  1,          //������ƽ1
      en_FullNeedle          =  2,          //��ɴ��ƽ2
      en_SplitYarn_Bottom    =  3,          //��ɴ����3
      en_MainYarn            =  4,          //��ɴ���4
      en_MainRacing          =  5,          //��׿�ת5
      en_RibbingKnit         =  6,          //���Ʊ�֯8
      en_Transition          =  7,          //������7
      en_Body                =  8,          //����8
      en_FlatInsert_LEFT     =  9,          //(ƽ��)�б߲���9  ��
      en_FlatInsert_RIGHT    =  10,         //(ƽ��)�б߲��� ��
      en_AutoInsert          =  11,         //�Զ�����11
      en_VNeck               =  12,         //����12
      en_CircleNeckBottom    =  13,         //��ײ���
      en_VNeck_Left          =  14,         //������
      en_VNeck_Right         =  15,         //������
      en_TransNeedle         =  16,         //����17
      en_Doffing1            =  17,         //�䲼13
      en_Cotton              =  18,         //��ɴ16
      en_Doffing2            =  19,         //�䲼2 15
      en_PPYarnBottom        =  20,         //PP�߶���
      en_CombBottom          =  21,         //��װ�
      en_FullNeedleComb      =  22,         //��ɴ��ƽ2
      en_LuowenDxj           =  23,         //�����
      //#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� start Duchen 2016/09/05 15:17 dc160905
      en_Taokou              =  24,         //�׿�
      en_TaokouFangSong              =  25,         //�׿ڷ���
      //#3346 ȫ�Ứ ����ʱ�Զ���ӷ����棨����ɴ�������֯һת�� end   Duchen 2016/09/05 15:17
      //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ start Duchen 2019/09/29 17:52 dc190923
      //��������-β����
      enAttachmentLoosenTail    = 26,
      //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ end   Duchen 2019/09/29 17:52
      en_BodyType_DaiSha    = 27,       //��ɴ ��Ҫ����ñ��벻�����߹��� yangjr 2020/08/25

      //�����޹صĶ�����ֻ�ڳ��͹�����ʹ��
      //-˳����Ա������
      en_TopCotton,                          //��ɴ
      en_CircleNeckMainYarn,
      en_CircleNeck,                        //Բ��14
      en_FlatInsert,
	   en_FlatInseetWaste_Left,
	   en_FlatInseetWaste_Right,
		en_CircleNeckBottom_LastRow,          //Բ�����һ�У�Ҫ���Ŀ������Ŀ��ͬ
	   en_FlatDoffing,                       //ƽ�յ����䲼
      en_VNeckIntersia,                     //V��������
      en_ConttonIntersia,                   //��ɴ������
      en_NeckIna_Left_Bottom,
      en_NeckIna_Left_Top,
      en_NeckIna_Right_Bottom,
      en_NeckIna_Right_Top,
      en_CottonIna_Left_Bottom,             //�÷�ɴɴ��1���ɴ�� ��Ŀ�ٶ�û��(V��������ʱʹ��)
      en_CottonIna_Left_Top,                //�÷�ɴɴ��1���ɴ�� ��Ŀ�ٶ�û��(V��������ʱʹ��)
      en_CottonIna_Right_Bottom,            //�÷�ɴɴ��2���ɴ�� ��Ŀ�ٶ�û��(V��������ʱʹ��)
      en_CottonIna_Right_Top,               //�÷�ɴɴ��2���ɴ�� ��Ŀ�ٶ�û��(V��������ʱʹ��)
      en_FlatInsertIna_Left,
      en_FlatInsertIna_Right,
      en_FlatInsertSeparate_Left,
      en_FlatInsertSeparate_Right,

      en_FlatInsert_2NdLeft_LEFT,
      en_FlatInsert_2NdLeft_RIGHT,
      en_FlatInsert_2NdLeft_Rev_LEFT,
      en_FlatInsert_2NdLeft_Rev_RIGHT,

      en_Doffing3,                          //����װ�ʱ������ɴ���䲼��
      en_TurnNeedle,                        //������
      en_Cotton_Left,                       //��ɴ������
      en_Cotton_right,                      //��ɴ������
      en_SplitYarn,                         //��ɴ����3
      en_BirdEyes,                          //������ƽ1
      en_TypeSeted,                         //��������
      en_SplitYarnAdd_Right,
      en_SplitYarnAdd_Left_BirdEyes,                 //�������߲�����(�÷�ɴ1)   ��Ŀ�ٶ�û��
      en_SplitYarnAdd_Left_FullNeedle,               //�������߲�����(�÷�ɴ1)   ��Ŀ�ٶ�û��
      en_SplitYarnAdd_Left_SplitYarn_Bottom,         //�������߲�����(�÷�ɴ1)   ��Ŀ�ٶ�û��  
      en_SplitYarnAdd_Left_Doffing,                 //�������߲�����(�÷�ɴ1)   ��Ŀ�ٶ�û��      
      en_SplitYarnAdd_Right_BirdEyes,                //�������߲�����(�÷�ɴ2)   ��Ŀ�ٶ�û��        
      en_SplitYarnAdd_Right_FullNeedle,              //�������߲�����(�÷�ɴ2)   ��Ŀ�ٶ�û��        
      en_SplitYarnAdd_Right_SplitYarn_Bottom,        //�������߲�����(�÷�ɴ2)   ��Ŀ�ٶ�û��         
      en_SplitYarnAdd_Right_Doffing,                //�������߲�����(�÷�ɴ2)   ��Ŀ�ٶ�û��    
      en_CottonAdd_left,                    //�����֯��ɴ��
      en_CottonAdd_right,                   //�����֯��ɴ��
      en_CottonSpec_SplitYarn,              //�������еķ�ɴ����
      en_CottonSpec_FullNeedle,             //�������еķ�ɴ��ƽ
      en_CottonSpec_Left_SplitYarn,         //�������еķ�ɴ����
      en_CottonSpec_Left_FullNeedle,        //�������еķ�ɴ��ƽ
      en_CottonSpec_Right_SplitYarn,        //�������еķ�ɴ����
      en_CottonSpec_Right_FullNeedle,       //�������еķ�ɴ��ƽ
      en_SplitYarnNeckBottom,               //��ײ��з�ɴ
      en_0Zhuan,
      en_MainYarnFstOut,                    // ��ɴ1����
      en_MainYarnSecOut,                    // ��ɴ2����
      en_bottomCotton,
      en_JiaSi_SendOut,				           //��˿ɴ�����
      //#2912 ����֧�ֵ�ɴ�����ֱ�֯ start Duchen 2016/07/20 10:16 dc160718
      en_AutoInsert_SinYarnSeperateTwoWayMainYarn,               //����ֱ�֯��ɴ
      en_AutoInsert_SinYarnSeperateTwoWaySplitYarn,               //����ֱ�֯��ɴ
      //#2912 ����֧�ֵ�ɴ�����ֱ�֯ end   Duchen 2016/07/20 10:16
      //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ start Duchen 2016/08/24 16:38 dc160822
      en_SuoZhen,
      //#2393 ���������з����Ŀ�����ȿ��Ե�������һ�ζ�Ŀ end   Duchen 2016/08/24 16:38
      //#4219 V�����ʹ��˫���Ứ�����Ứ��ͼ�����߷�����ͬһ��ɴ�� start Duchen 2016/12/06 11:17 dc161205
      en_TaokouRight,
      //#4219 V�����ʹ��˫���Ứ�����Ứ��ͼ�����߷�����ͬһ��ɴ�� end   Duchen 2016/12/06 11:17
      //#4219 V�����ʹ��˫���Ứ�����Ứ��ͼ�����߷�����ͬһ��ɴ�� start Duchen 2016/12/06 11:17 dc161205
      en_TaokouIntarsia,
      //#4219 V�����ʹ��˫���Ứ�����Ứ��ͼ�����߷�����ͬһ��ɴ�� end   Duchen 2016/12/06 11:17
      //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ start Duchen 2019/09/29 17:52 dc190923
      //��������-ͷ����
      enAttachmentLoosenHead,
      //��������-��ԲͲ
      enAttachmentTightYuanTong,
      //��������-��ƽ
      enAttachmentSiPing,
      //ZB-784 ��������ͷβ�������ԣ�ת�ư��Զ���ͷβ���÷��ɶ�Ŀ end   Duchen 2019/09/29 17:52
      //ZB-859 ���ʹ������һ����ɴ��Ŀ���� start Duchen 2020/04/16 15:13 dc200413
      en_MainYarnFangSong,
      //ZB-859 ���ʹ������һ����ɴ��Ŀ���� end   Duchen 2020/04/16 15:13
      en_End,
   };
   static BOOL isTypeDaShen(const Body_Type &type) //��Ȧͳ�ƴ�������
   {
      if (en_Body == type || //����8
         en_FlatInsert_LEFT == type  || //(ƽ��)�б߲���9  ��
         en_FlatInsert_RIGHT == type||  //(ƽ��)�б߲��� ��
         en_AutoInsert == type|| //�Զ�����11
         en_VNeck  == type|| //����12
         en_CircleNeckBottom  == type|| //��ײ���
         en_VNeck_Left== type || //������
         en_VNeck_Right== type  //������
         )
      {
         return TRUE;
      }
      return FALSE;
   }
   static BOOL isTypeLuoWen(const Body_Type &type) //��Ȧͳ����������
   {
      if (en_MainYarn == type || //��ɴ���4
         en_MainRacing == type  || //��׿�ת5
         en_RibbingKnit == type||  //���Ʊ�֯6
         en_Transition == type //������7
         )
      {
         return TRUE;
      }
      return FALSE;
   }    
   static BOOL isTypeNeedWeave(const Body_Type &type) //��Ҫ���沿λ����
   {
      if (en_BirdEyes_Bottom == type || 
         en_FullNeedle == type  ||
         en_SplitYarn_Bottom == type||
         en_PPYarnBottom == type||
         en_CombBottom  == type||
         en_FullNeedleComb== type
         )
      {
         return FALSE;
      }
      return TRUE;
   }
   static BOOL IsTypeBottom(const Body_Type &type)
   {
      if (en_BirdEyes_Bottom == type||en_FullNeedle ==type ||en_LuowenDxj ==type 
         || en_SplitYarn_Bottom == type  || en_MainYarn == type
         || en_MainRacing == type || en_RibbingKnit == type || en_Transition == type
         || en_PPYarnBottom == type || en_CombBottom == type|| en_FullNeedleComb == type)
      {
         return TRUE;
      }
      return FALSE;
   }

   //#6002 �������������ӷ��ɵĶ�Ŀ�� start Duchen 2016/11/15 16:27 dc161113
   static BOOL IsColorBottom(BYTE byColor)
   {
      if (en_BirdEyes_Bottom == byColor||en_FullNeedle ==byColor ||en_LuowenDxj ==byColor 
         || en_SplitYarn_Bottom == byColor  || en_MainYarn == byColor
         || en_MainRacing == byColor || en_RibbingKnit == byColor || en_Transition == byColor
         || en_PPYarnBottom == byColor || en_CombBottom == byColor|| en_FullNeedleComb == byColor
         || en_Taokou == byColor)
      {
         return TRUE;
      }
      return FALSE;
   }
   //#6002 �������������ӷ��ɵĶ�Ŀ�� end   Duchen 2016/11/15 16:27

   //#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� start Duchen 2017/10/27 16:26 dc161023
   static BOOL IsColorTail(const Body_Type &type)
   {
      switch(type)
      {
      case en_Cotton: //��ɴ
      case en_FullNeedle: //��ɴ��ƽ
      case en_SplitYarn_Bottom: //��ɴ����
      case en_Doffing2: //�䲼2
      case en_BirdEyes_Bottom: //������ƽ
      case en_TransNeedle: //����
         return TRUE;
      }
      return FALSE;
   }
   static BOOL IsTypeTail(const Body_Type &type)
   {
      if (en_Cotton_Left == type||en_Cotton_right ==type ||en_CottonSpec_Left_FullNeedle ==type 
         || en_CottonSpec_Left_SplitYarn == type  || en_CottonSpec_Right_FullNeedle == type
         || en_CottonSpec_Right_SplitYarn == type || en_SplitYarn == type || en_Doffing3 == type
         || en_BirdEyes == type
         || en_ConttonIntersia == type || en_CottonSpec_FullNeedle == type || en_CottonSpec_SplitYarn == type 
         || en_Cotton == type || en_FullNeedle == type
         || en_Doffing2 == type
         || en_CottonAdd_right == type || en_CottonAdd_left == type
         || en_TurnNeedle == type)
      {
         return TRUE;
      }
      return FALSE;
   }
   //#5803 ʹ�á�������ͷ��������ǰ�ķ�ɴҲӦ���滻��Ŀǰֻ�滻���˿�ʼ�ķ�ɴ���� end   Duchen 2017/10/27 16:26
   enum Yarn_Type
   {
      en_YarnNull,       //��ɴ��
      en_YarnMain1,      //��ɴ��1 = 1
      en_YarnMain2,      //��ɴ��2 =2
      en_YarnSpilt1,     //��ɴ1  =3
      en_YarnSpilt2,     //��ɴ2 =4
      en_YarnOrgLuoWen,  //����ɴ��2 =5
      en_YarnNeckSpilt,  //V���ɴ = 6
      en_YarnVIntersia,  //V�������� = 7
      en_PPYarn,         //pp��ɴ�� = 8
      en_YarnDxj,    //�������� = 9 20151221 LINYP
      //#5652 ɳ��Ͷ�����������ɳ��1 start Duchen 2017/12/05 15:26 dc171205
      en_YarnMainLuoWen, //����ɳ��1 = 10
      //#5652 ɳ��Ͷ�����������ɳ��1 end   Duchen 2017/12/05 15:26
      en_YarnRubb = 100, //���ɴ�� = 100 һ�㲻����� ��������ݿ�ҲҪ��Ӧ���޸�
      en_YarnSeted,      //�ѷ���ɴ��
	   en_YarnJiaSi,
      
	   en_Yarn255,
   };
   enum Spec_Type
   {
      en_NeckIna = 0x01,       //v��������
   };
   enum Reduce_Type
   {
      en_Ladder,
      en_Normal
   };
   enum
   {
      en_DrawFail = 0,
      en_DrawOk
   };
   enum
   {
      en_RowNormal = 0,
      en_RowZhuanShu,
      en_RowKongZhuanShu
   };
   enum
   {
      en_PosLeft,
      en_PosRight,
      en_PosCenter
   };
   enum KNITYARNTYPE
   {
      en_KnitMainFirst, // ֻ����ɴ1֯ ��ֻ��һ��ɴ��(ɴ��1=ɴ��2)��V�����/V�������ĵײ���V��/V����������ߣ�
      en_KnitMainSec,   // ֻ����ɴ2֯ ��V��/V���������ұߣ�  
      en_KnitMainBoth   // ��ɴ12һ��֯������ɴ��֯ʱ�ķ�V�����/V�������ĵײ�����ƽ�մ��������Ӵ���
   };
   //�������
   enum CLEARBORDERTYPE
   {
      en_KnitFront,     //ǰ��֯
      en_KnitRear,      //���֯
      en_TuckFront,     //ǰ��Ŀ
      en_TuckRear,      //���Ŀ
      en_Transfer,      //����
      en_Custom         // �Զ���
   };
	//��ɴ������
	enum BODYSIZEFLAG
	{
		enSize_XS = 0,
		enSize_S = 1,
		enSize_M = 2,
		enSize_L = 3,
		enSize_XL = 4,
		enSize_XXL = 5,
		enSize_XXXL = 6
	};
	enum BODYSIZETYPE
	{
		enSizeType_diaomu,
		enSizeType_Tiaokong
	};

	enum JIADLINGTUCK
	{
		enJLTuck = 0,
		enJLKnit = 1,
		enJLNull = 2,
	};

	enum CHANZHENTUCK
	{
		enTuck = 0,
		enTrans = 1,
		enNull = 2,
	};

   //#4629 V�����ʱ��������������һ�Σ�������� ���� start Duchen 2017/08/22 10:00 dc160821
   enum VNECKCHANZHENTYPE
   {
      enBoLiuZhenFirst = 0,
      enZhongLiuZhenFirst,
   };
   //#4629 V�����ʱ��������������һ�Σ�������� ���� end   Duchen 2017/08/22 10:00
}


