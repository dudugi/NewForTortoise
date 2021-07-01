#pragma once
/********************************************************************
//  作者:           linyp
//  CopyRight(c)    2010 Burnon All Rights Reserved 
//  创建时间:       2011/09/06 19:09
//  类描述:         成型设计数据定义
//  修改时间:       
//  修改目的:       
*********************************************************************/
//#include "CKnitData.h"
#include "CShapeSpace.h"
#include <vector>
#include <list>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////
/*
摘要:标准模块数据 定义 
作者:linyp
时间:2009-10-11
*/
class  CKDModData
   //:public CKnitData
{
public:
   //UINT     m_uModWidth;                  //宽度=成型设计的起底宽度1
   //UINT     m_uModOrgWidth;               //原始宽度，临时处理。。linyp
   //ShapeSpace::FroBkNeedle m_enFBKnit;    //面包底包==螺纹排列
   ShapeSpace::QHLuoBu  m_enLuoBu;        //前后落布设置 1
   //CString  m_strModType;                 //标准模块组织类型 1
   CString  m_strTransType;               //过度行配置 1
   //ShapeSpace::Sys_Type m_enMacType;      //标准模块机型 单系统 多系统1
   //double   m_dRevolution;                //转数1
   //double   m_dEmptyRevolution;           //空转数1
   //BOOL     IsBottomExist;                //是否存在起底板      有起底板为1，无起底板为0  1
   //BOOL     IsVLFlag;                     //是否开领标记:有1,无0 无开领 = 单独的标准模块  1
   //ShapeSpace::NeedleTrans_Type      m_BZJ;  //变针距 1
   //CString  m_strCombType;                //起底板模式1
   //BOOL     Is_LWJiaSi;                   //是否罗纹加丝
   //UINT     m_uLWJiasi;                   //罗纹加丝转数
   ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 start Duchen 2017/09/07 16:24 dc160904
   //BOOL     m_bWholePiece;                //是否是整片（相对左边或右边）
   ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 end   Duchen 2017/09/07 16:24
   //////////////////////////////////////////////////////////////////////////////////
   ////成型设计参数传入
   //int m_FirstShaZui;         //第一把纱嘴
   //int m_SecondShaZui;        //第二把纱嘴
   //int m_RibAddYarn;          //螺纹加丝纱嘴
   //BOOL m_bAutoPressYarnMode;          //自动压线模式
   //BOOL m_bAutoPressYarnUseWasteYarn;  //自动压线模式使用废纱纱嘴
   //int  m_DiXiangJYarn;       //底橡胶纱嘴
   //BOOL  m_isHouQiKongZhuan;  //后起底空转
   ////罗纹夹色 start Duchen 2017/09/26 11:08 dc160925
   //std::list<int> m_lstLWJiaSe;    //罗纹夹色
   //std::list<int> m_lstLWJiaSeColor;    //罗纹夹色色码
   ////罗纹夹色 end   Duchen 2017/09/26 11:08
   
public:
   CKDModData(){
      //m_DiXiangJYarn = 0;
      //m_isHouQiKongZhuan = FALSE;
      ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 start Duchen 2017/09/07 16:24 dc160904
      //m_bWholePiece = FALSE;
      ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 end   Duchen 2017/09/07 16:24
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
      ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 start Duchen 2017/09/07 16:24 dc160904
      //m_bWholePiece           = rhs.m_bWholePiece;
      ////#5408 当成型工艺单不是正片选择左边和右边的时候，成型出来后费纱有问题330没事 end   Duchen 2017/09/07 16:24
      ////罗纹夹色 start Duchen 2017/09/26 11:08 dc160925
      //m_lstLWJiaSe = rhs.m_lstLWJiaSe;    //罗纹夹色
      //m_lstLWJiaSeColor = rhs.m_lstLWJiaSeColor;    //罗纹夹色色码
      //罗纹夹色 end   Duchen 2017/09/26 11:08
      return *this;
   }
};

//---------------------------------------------------------------------------
//参数设置相关
typedef struct tagKnitParams
{
   //默认构造
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
   BYTE bDomain1;       //度目1 编织度目 207
   BYTE bDomain2;       //度目2 翻针度目
   BYTE bSpeed1;        //速度1 编织速度 209
   BYTE bSpeed2;        //速度2 翻针速度
   BYTE bYarn1;         //纱嘴1 215
   BYTE bYarn2;         //纱嘴2
   BYTE bRoller1;       //卷布1 编织时卷布 210
   BYTE bRoller2;       //卷布2 翻针时卷布
//    BYTE bRoller1;       //卷布1 编织时卷布 211
//    BYTE bRoller2;       //卷布2 翻针时卷布
   BYTE Idex;
   //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 start Duchen 2016/08/24 16:38 dc160822
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
   //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 end   Duchen 2016/08/24 16:38
}KnitParams,pKnitParams;

typedef struct tagKnitParamSet
{
   tagKnitParamSet()
   {
  //    paraBirdEyes.bDomain1 = 1;          //鸟眼四平1
  //    paraFullNeedle.bDomain1 = 2;        //废纱四平2
  //    paraSplitYarn.bDomain1 = 3;         //废纱拆线3
  //    paraMainYarn.bDomain1 = 4;          //主纱起底4
  //    paraMainRacing.bDomain1 = 5;        //起底空转5
  //    paraRibbingKnit.bDomain1 = 6;       //螺纹编织6
  //    paraTransition.bDomain1 = 7;        //过度行7
  //    paraBody.bDomain1 = 8;              //大身8
  //    paraFlatInsert_Left.bDomain1 = 9;   //(平收)夹边插行左9
  //    paraFlatInsert_Right.bDomain1 = 17;  //(平收)夹边插行右17
  //    paraAutoInsert.bDomain1 = 10;        //自动插行10
  //    paraVNeck.bDomain1 = 13;             //领子13
  //    paraVNeck_Left.bDomain1 = 12;        //领子左12
  //    paraVNeck_Right.bDomain1 = 12;       //领子右12
  //    //ZB-804 增加一个V领拆行的速度段数 start Duchen 2020/07/30 14:40 dc200727
  //    paraVNeckSpeed_Left.bDomain1 = 8;        //领子左12
  //    paraVNeckSpeed_Right.bDomain1 = 8;       //领子右12
  //    //ZB-804 增加一个V领拆行的速度段数 end   Duchen 2020/07/30 14:40
  //    paraDoffing1.bDomain1 = 12;          //落布12
  //    paraCircleNeck.bDomain1 = 13;        //圆领13
  //    paraDoffing2.bDomain1 = 14;          //落布2 14
  //    paraCotton.bDomain1 = 15;            //棉纱15
  //    paraTransNeedle.bDomain1 = 23;       //翻针23
  //    paraDxj.bDomain1 = 16;               //底橡筋纱段数16 yangjr2016-3-3
  //    paraDxj.Idex = 16;               //底橡筋纱段数16 yangjr2016-3-3
  //    paraPPYarn.bDomain1 = 3;            //pp线段数 3
  //    paraComb.bDomain1 = 20;              //起底板参数设置 默认20
  //    m_bMainYarnFirst = 3;           //主纱第一把纱嘴
  //    m_bMainYarnSec = 5;             //主纱第二把纱嘴
  //    m_bRubYarnFirst = 1;            //废纱第一把纱嘴
  //    m_bRubYarnSec = 7;              //废纱第二把纱嘴
  //    m_NeckYarn = 0;
      m_IsOneYarn = TRUE;             //大身使用一把纱嘴
		//m_NeckIsOneYarn = FALSE;
  //    //#2912 成型支持单纱嘴最开领分边织 start Duchen 2016/07/20 10:16 dc160718
  //    m_bNeckOneYarnTwoWay = FALSE;   //领子一把沙嘴分边织
  //    //#2912 成型支持单纱嘴最开领分边织 end   Duchen 2016/07/20 10:16
	   bSetSecYarnLeft = FALSE;        //2#纱嘴在左边
      bSetWasteSecYarnLeft = FALSE;   //2#废纱纱嘴在左边
    //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 start Duchen 2017/03/03 10:11 dc170227
    //  m_bAllYarnRight = FALSE;            //沙嘴在右侧
    //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 end   Duchen 2017/03/03 10:11
	   //bLuoWenYarn = 0;                //罗纹纱嘴2
	   //bRubberYarn = 8;                //橡筋纱嘴
    //  bPPYarn = 1;                    //PP线纱嘴 2012-3-5 linyp
    //  bLwJsYarn = 0;                  //罗纹加丝纱嘴
    //  bDxjYarn = 0;                   //底橡筋纱嘴
    //  //#5652 沙嘴和段数增加罗纹沙嘴1 start Duchen 2017/12/05 15:26 dc171205
    //  m_byLuoWnYarn1 = m_bMainYarnFirst;              //罗纹沙嘴1
    //  //#5652 沙嘴和段数增加罗纹沙嘴1 end   Duchen 2017/12/05 15:26
	   //m_nParamType = ShapeSpace::enParaMold1;      //参数模式
   }
 //  //-------------------------------------------
 //  //编织参数
 //  KnitParams paraBirdEyes;          //鸟眼四平1
 //  KnitParams paraFullNeedle;        //废纱四平2
 //  KnitParams paraSplitYarn;         //废纱拆线3
 //  KnitParams paraMainYarn;          //主纱起底4
 //  KnitParams paraMainRacing;        //起底空转5
 //  KnitParams paraRibbingKnit;       //螺纹编织8
 //  KnitParams paraTransition;        //过度行7
 //  KnitParams paraBody;              //大身8
 //  KnitParams paraFlatInsert_Left;   //(平收)夹边插行左9
 //  KnitParams paraFlatInsert_Right;  //(平收)夹边插行右9
 //  KnitParams paraAutoInsert;        //自动插行11
 //  KnitParams paraVNeck;             //领子12
 //  KnitParams paraVNeck_Left;        //领子左12
 //  KnitParams paraVNeck_Right;       //领子右12
 //  //ZB-804 增加一个V领拆行的速度段数 start Duchen 2020/07/30 14:40 dc200727
 //  KnitParams paraVNeckSpeed_Left;        //领子左12 速度
 //  KnitParams paraVNeckSpeed_Right;       //领子右12 速度
 //  //ZB-804 增加一个V领拆行的速度段数 end   Duchen 2020/07/30 14:40
 //  KnitParams paraDoffing1;          //落布13
 //  KnitParams paraCircleNeck;        //圆领14
 //  KnitParams paraDoffing2;          //落布2 15
 //  KnitParams paraCotton;            //棉纱16
 //  KnitParams paraTransNeedle;       //翻针17
 //  KnitParams paraPPYarn;            //pp线段数 21
 //  KnitParams paraComb;              //起底板参数设置 默认22
 //  KnitParams paraDxj;               //底橡胶纱嘴
 //  //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 start Duchen 2016/08/24 16:38 dc160822
 //  KnitParams paraSuoZhen;           //缩针
 //  //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 end   Duchen 2016/08/24 16:38
 //  //#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） start Duchen 2016/09/05 15:17 dc160905
 //  KnitParams paraQuanTiHuaTaoKou;           //全提花套口
 //  KnitParams paraQuanTiHuaTaoKouFangSong;   //全提花套口放松
 //  //#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） end   Duchen 2016/09/05 15:17

 //  //ZB-746 收针度目放松 start Duchen 2019/05/05 15:15 dc190429
 //  KnitParams paraShouZhenDumuFangSong;      //收针度目放松
 //  //ZB-746 收针度目放松 end   Duchen 2019/05/05 15:15

 //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
 //  KnitParams paraAttachmentLoosen;             //附件段数 头尾放松
 //  KnitParams paraAttachmentTightYuanTong;      //附件段数 紧圆筒
 //  KnitParams paraAttachmentSipin;              //附件段数 四平
 //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52

 //  //ZB-950 沙嘴和段数增加局部提花度目段设置 start Duchen 2020/08/13 10:17 dc200810
 //  KnitParams paraJuBuTiHua;      //局部提花
 //  //ZB-950 沙嘴和段数增加局部提花度目段设置 end   Duchen 2020/08/13 10:17

 //  //------------------------------------------
 //  //纱嘴设置
 //  BYTE  m_bMainYarnFirst;           //主纱第一把纱嘴
 //  BYTE  m_bMainYarnSec;             //主纱第二把纱嘴
 //  BYTE  m_bRubYarnFirst;            //废纱第一把纱嘴
 //  BYTE  m_bRubYarnSec;              //废纱第二把纱嘴
 //  BYTE  m_NeckYarn;
   BOOL  m_IsOneYarn;                //大身使用一把纱嘴
   BOOL  m_NeckIsOneYarn;            //领子使用一把纱嘴
 //  //#2912 成型支持单纱嘴最开领分边织 start Duchen 2016/07/20 10:16 dc160718
 //  BOOL  m_bNeckOneYarnTwoWay;     //领子一把沙嘴分边织
 //  //#2912 成型支持单纱嘴最开领分边织 end   Duchen 2016/07/20 10:16
   BOOL  bSetSecYarnLeft;            //2#纱嘴在左边
   BOOL  bSetWasteSecYarnLeft;            //2#纱嘴在左边
 //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 start Duchen 2017/03/03 10:11 dc170227
 //  BOOL  m_bAllYarnRight;            //沙嘴在右侧
 //  //#4497 stoll部分机型纱嘴在右边，希望我们成型设计可以支持大身纱嘴2、废纱纱嘴2在右边 end   Duchen 2017/03/03 10:11
	//BYTE  bLuoWenYarn;                //罗纹纱嘴2
 //  //#5652 沙嘴和段数增加罗纹沙嘴1 start Duchen 2017/12/05 15:26 dc171205
 //  BYTE m_byLuoWnYarn1;              //罗纹沙嘴1
 //  //#5652 沙嘴和段数增加罗纹沙嘴1 end   Duchen 2017/12/05 15:26
	//BYTE  bRubberYarn;                //橡筋纱嘴
 //  BYTE  bPPYarn;                    //PP线纱嘴 2012-3-5 linyp
 //  BYTE  bLwJsYarn;                  //罗纹加丝纱嘴
 //  BYTE  bDxjYarn;                   //底橡胶纱嘴
	//ShapeSpace::KnitPara_Type m_nParamType;      //参数模式
}ParamSet,*pParamSet;

typedef struct tagOtherParamSet     //高级其他设置
{ 
   tagOtherParamSet()
   {
    //  iMinSuspendNeedleNum = 10;   
      iCottonRowNum = 8;
    //  LessColor = 16;
    //  m_nCottontype = ShapeSpace::enAddNeedle_double;
      m_AddType = ShapeSpace::enAdd_One1; //加针方式,XUYH
    //  DoubleRibColor = 1;
    //  m_nRibtype = ShapeSpace::enRibFull;
    //  ModeJDM = 0;
    //  effectiveNum = 7;
    //  iNotTreatmentNeedle = 3;            //带纱不处理针数
    //  iYarnKickBackNeedle = 3;            //带纱插行回踢针数
    //  iNeckUseOneYarn = 8;                //单纱嘴开领深度
    //  m_bRibSaving = TRUE;                //罗纹节约
    //  m_bJiaBPs = TRUE;                   //两系统夹边平收一行
	   //m_bAutoNeckCenter = TRUE;           //领子中心在领子底部
	   //m_bSeperateLine = TRUE;             //拆线
	   //m_bVNeckYarn = TRUE;                //V领底绞花
	   m_uAbandon_RowCount = TRUE;         //废纱转数
	   m_IsAbandon_Oneyarn = TRUE;         //废纱是否使用一把纱嘴
    //  m_IsAbandon_Yintax = TRUE;          //废纱与领子同时拆行引塔下
    //  m_bPackMode = TRUE;
    //  m_bCZTuck = FALSE;                  // 铲针吊目
	   //m_bFeiShaAllQidiMode = TRUE;			//是否使用废纱落布
    //  m_bAutoPressYarnMode = TRUE;        //自动压线模式
    //  m_bAutoPressYarnUseWasteYarn = TRUE;//自动压线模式使用废纱纱嘴
      //m_ClipYarnPos = 61;
		//m_cancelType = ShapeSpace::en_Cancel_NON;
      /*m_bDaiShaDaJie = TRUE;
		m_bDaiShaOut   = FALSE;
		m_bChaiXian    = FALSE;
		m_bVLDiJiaoHua = FALSE;
		m_enJLTuckColor = ShapeSpace::enJLTuck;*/
		//m_nCZType = ShapeSpace::enTuck;
      //#3111 平收落布拉针行数设置 start Duchen 2016/08/03 14:02 dc160801
      //m_nFlatReduceLuoBuLineCount = 5; //平收落布拉针行数
      ////#3111 平收落布拉针行数设置 end   Duchen 2016/08/03 14:02
      ////#3663 成型参数添加废纱纱出、橡筋纱出选项 start Duchen 2016/09/26 11:36 dc160926
      //m_bRubYarnOut = TRUE; //废纱纱出
      //m_bRubberYarnOut = TRUE; //橡筋纱出
      //#3663 成型参数添加废纱纱出、橡筋纱出选项 end   Duchen 2016/09/26 11:36
      //#3665 开领新增单纱嘴废纱方式 start Duchen 2017/12/12 17:58 dc161211
      m_bSingleSplitYarnNeck = FALSE; //开领单纱嘴废纱方式
      //#3665 开领新增单纱嘴废纱方式 end   Duchen 2017/12/12 17:58
      //m_bAutoCutClip = TRUE; //自动剪刀夹子yangjr 2016-11-3
      //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 start Duchen 2017/04/25 13:14 dc170424
      //m_fbfz = 1;
      //m_bFBFZ = TRUE;
      //#4373 分别翻针的check和listbox里面的0：使不能分别翻针矛盾 end   Duchen 2017/04/25 13:14
      //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 start Duchen 2017/08/22 10:00 dc160821
      //m_nVNeckCZType = ShapeSpace::enBoLiuZhenFirst;
      //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 end   Duchen 2017/08/22 10:00

      //ZB-381 成型增加纱嘴自动对齐功能选项 start Duchen 2018/07/06 17:11 dc180702
      //m_bYarnInAutoAlign = FALSE;
      //ZB-381 成型增加纱嘴自动对齐功能选项 end   Duchen 2018/07/06 17:11

      //ZB-962 成型设置：其他页面新增参数“落布行数” start Duchen 2020/07/22 16:29 dc200720
      //m_nLuoBuHangShu = 4; //落布行数 //[XML]
      //ZB-962 成型设置：其他页面新增参数“落布行数” end   Duchen 2020/07/22 16:29
   }
 //  UINT iMinSuspendNeedleNum;   
   UINT iCottonRowNum;
 //  BYTE LessColor;
 //  BYTE m_fbfz;
 //  ShapeSpace::Cotton_Type m_nCottontype;
   ShapeSpace::Add_Type m_AddType;  //加针方式,XUYH
	//ShapeSpace::CANCEL_TYPE m_cancelType;  //自动偷吃方式
 //  BYTE DoubleRibColor;
 //  ShapeSpace::Rib_Type m_nRibtype;
	//ShapeSpace::CHANZHENTUCK m_nCZType;
 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 start Duchen 2017/08/22 10:00 dc160821
 //  ShapeSpace::VNECKCHANZHENTYPE m_nVNeckCZType;
 //  //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 end   Duchen 2017/08/22 10:00
 //  UINT ModeJDM;                    //假吊目方式
 //  UINT  m_jiadmgd;                 //假吊目高度
	//UINT effectiveNum;
 //  int  iNotTreatmentNeedle;        //带纱不处理针数
 //  int  iYarnKickBackNeedle;        //带纱插行回踢针数
 //  int  iNeckUseOneYarn;            //单纱嘴开领深度
	//BOOL m_bRibSaving;               //罗纹节约
	//BOOL m_bJiaBPs;                  //两系统夹边平收一行
	//BOOL m_bAutoNeckCenter;          //领子中心在领子底部
	//BOOL m_bSeperateLine;            //拆线
	//BOOL m_bVNeckYarn;               //V领底绞花
	UINT m_uAbandon_RowCount;        //废纱转数
   BOOL m_IsAbandon_Oneyarn;        //废纱是否使用一把纱嘴
 //  BOOL m_IsAbandon_Yintax;         //废纱与领子同时拆行引塔下
 //  BOOL m_bPackMode;
 //  BOOL      m_bCZTuck;             // 铲针吊目
	//BOOL m_bFeiShaAllQidiMode;			//是否使用废纱落布
 //  BOOL m_bAutoPressYarnMode;          //自动压线模式
 //  BOOL m_bAutoPressYarnUseWasteYarn;  //自动压线模式使用废纱纱嘴
   int  m_iLiuBianZS;				   //直位留边转数
 //  int  m_ClipYarnPos;              //夹线高度，转数
	//BOOL m_bDaiShaDaJie;
	//BOOL m_bDaiShaOut;               //带纱到边缘
	//BOOL m_bChaiXian;                //拆线
	//BOOL m_bVLDiJiaoHua;                //V领底绞花
 //  BOOL m_bFBFZ;                       //分别翻针
 //  int  m_iQiJiaZhuanshu;              //齐加转数

	//ShapeSpace::JIADLINGTUCK  m_enJLTuckColor;

   ShapeSpace::NeedleFlat_Type  m_nKaiSFlatType;//开衫平收方式
   ShapeSpace::NeedleFlat_Type  m_nNeckFlatType;//开衫平收方式
 //  //#3111 平收落布拉针行数设置 start Duchen 2016/08/03 14:02 dc160801
 //  int m_nFlatReduceLuoBuLineCount; //平收落布拉针行数
 //  //#3111 平收落布拉针行数设置 end   Duchen 2016/08/03 14:02
 //  //#3663 成型参数添加废纱纱出、橡筋纱出选项 start Duchen 2016/09/26 11:36 dc160926
 //  BOOL m_bRubYarnOut; //废纱纱出
 //  BOOL m_bRubberYarnOut; //橡筋纱出
 //  //#3663 成型参数添加废纱纱出、橡筋纱出选项 end   Duchen 2016/09/26 11:36
 //  BOOL m_bAutoCutClip; //自动剪刀夹子yangjr 2016-11-3
   //#3665 开领新增单纱嘴废纱方式 start Duchen 2017/12/12 17:58 dc161211
   BOOL m_bSingleSplitYarnNeck; //开领单纱嘴废纱方式
   //#3665 开领新增单纱嘴废纱方式 end   Duchen 2017/12/12 17:58

   ////ZB-381 成型增加纱嘴自动对齐功能选项 start Duchen 2018/07/06 17:11 dc180702
   //BOOL m_bYarnInAutoAlign;
   ////ZB-381 成型增加纱嘴自动对齐功能选项 end   Duchen 2018/07/06 17:11

   ////ZB-962 成型设置：其他页面新增参数“落布行数” start Duchen 2020/07/22 16:29 dc200720
   //int m_nLuoBuHangShu; //落布行数 //[XML]
   ////ZB-962 成型设置：其他页面新增参数“落布行数” end   Duchen 2020/07/22 16:29
}OtherParamSet;
//--------------------------------------------------------------------
//成型轮廓数据

typedef std::vector<BYTE>                TYPE_VEC_KNITSIGN;   //编织符号 
//ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
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

//ZB-971 工艺是多密度段， 转制版后需要知道每一段不同， 之前是默认从31开始分，现在不分度目了 start Duchen 2020/07/24 11:49 dc200720
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
//ZB-971 工艺是多密度段， 转制版后需要知道每一段不同， 之前是默认从31开始分，现在不分度目了 end   Duchen 2020/07/24 11:49

inline bool operator==(const TYPE_VEC_LEFT_RIGHT_KNITSIGN &left, const TYPE_VEC_LEFT_RIGHT_KNITSIGN &right)
{
   return left.vecLeft == right.vecLeft
      && left.vecLoop == right.vecLoop
      && left.vecRight == right.vecRight;
}
typedef std::vector<TYPE_VEC_LEFT_RIGHT_KNITSIGN>   TYPE_2D_VECTSIGN;
//typedef std::vector<TYPE_VEC_KNITSIGN>   TYPE_2D_VECTSIGN;
//ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21
//大身工艺行
class ShapeProfileRow//:
   //public CKnitData
{
public:
   ShapeProfileRow()       //默认构造函数
   {
      iRowCount = 0;
      iNeedleNum = 0;    
      iTimes = 1;        
      iNeedleMoveNum = 0;
      iNeedleLess = 0;   
      en_NeedleType = ShapeSpace::en_Needle_Null;             
      bEffective = false;   
      iHeight=0;
      //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
      TYPE_VEC_KNITSIGN vecKnitSignLoop;               //编织符号
      vecKnitSignLoop.push_back(1);
      vecKnitSign.vecLoop = vecKnitSignLoop;
      //vecKnitSign.push_back(1);
      //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21
      //#4907 附件套图出现内存超出 start Duchen 2017/12/21 09:44 dc161218
      m_vect2DKnit.push_back(vecKnitSign); //默认为1个1号色
      //#4907 附件套图出现内存超出 end   Duchen 2017/12/21 09:44
		effective = 0;
		Real_effective = 0;
      iMarkPos = 0;
      bNeckKaisPs    = FALSE;
      //ZB-831 收针类型自动处理扩展 start Duchen 2020/03/09 10:52 dc20200309
      m_nNeedlePackagePageCount = 0;
      //ZB-831 收针类型自动处理扩展 end   Duchen 2020/03/09 10:52
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
   //#4217 成型【编织】新增常用组织类型列表 start Duchen 2016/01/20 10:06 dc170116
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

   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
   inline static TYPE_VEC_KNITSIGN GetBianmaVectorInt(CString str)
   //inline static TYPE_VEC_KNITSIGN GetBianmaInt(CString str)
   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21
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

   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
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
   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21

//   void GetKnitSign(const CString &sBianma)
//   {
//       list<CString> lstBianmaString = ShapeProfileRow::GetBianmaOneLineString(sBianma);
//       //#4217 成型【编织】新增常用组织类型列表 start Duchen 2017/12/29 11:54 dc171225
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
//       //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2017/12/29 11:54
//   }

   //ZB-619 成型新增第四种新打褶，主要给裙子用 start Duchen 2018/11/26 15:23 dc181126
   inline BOOL IsSuoZhen() const
   {
      if (ShapeSpace::en_Needle_SuoZhen == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Average == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Middle == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Side == en_NeedleType 
         || ShapeSpace::en_Needle_SuoZhen_Custom == en_NeedleType
         //ZB-897 增加缩针1X1整条缩功能 start Duchen 2020/07/11 12:41 dc200706
         || ShapeSpace::en_Needle_SuoZhen_1x1 == en_NeedleType
         //ZB-897 增加缩针1X1整条缩功能 end   Duchen 2020/07/11 12:41
         || ShapeSpace::en_Needle_SuoZhen_Basemap == en_NeedleType)
      {
         return TRUE;
      }
      return FALSE;
   }
   //ZB-619 成型新增第四种新打褶，主要给裙子用 end   Duchen 2018/11/26 15:23

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

   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
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
   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21

   inline static CString GetMultlineBianma(const TYPE_2D_VECTSIGN &vect2DKnit)
   {
      CString sValue = L"";
      CString sTemp;
      for (auto IterLine = vect2DKnit.begin(); 
         IterLine != vect2DKnit.end();
         ++IterLine)
      {
         //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
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
         //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21

         if (IterLine + 1 != vect2DKnit.end())
         {
            sValue += _T(";");
         }
      }
      return sValue;
   }
   //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2016/01/20 10:06
   UINT iRowIndex;                              //行号
   //#4170 成型bug 相同GYE 在新旧版本上出现不同的结果 start Duchen 2016/11/23 15:47 dc161121
   UINT m_nRowIndexReal;                              //工艺单行号
   //#4170 成型bug 相同GYE 在新旧版本上出现不同的结果 end   Duchen 2016/11/23 15:47
   UINT iRowCount;                              //行数 = 转数×2
   int iNeedleNum;                             //针数
   UINT iTimes;                                 //次数
   UINT iNeedleMoveNum;                         //移针目数
   UINT iNeedleLess;                            //偷吃（少针）
   UINT iMarkPos;                               //琪利记号位置
   ShapeSpace::Needle_Type en_NeedleType; //收针类型（轮廓类型）
   //ZB-780 成型增加一些特殊收针类型自动处理 start Duchen 2019/09/02 18:16 dc190902
   std::vector<BYTE> m_vecNeedlePackageStandColor; //收（放？）针小图代表色码
   CString m_sNeedlePackageModName; //收（放？）针小图模块名
   //ZB-831 收针类型自动处理扩展 start Duchen 2020/03/09 10:52 dc20200309
   int m_nNeedlePackagePageCount;
   //ZB-831 收针类型自动处理扩展 end   Duchen 2020/03/09 10:52
   //ZB-780 成型增加一些特殊收针类型自动处理 end   Duchen 2019/09/02 18:16
   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 start Duchen 2020/06/23 09:21 dc200622
   TYPE_VEC_LEFT_RIGHT_KNITSIGN vecKnitSign;               //编织符号
   //TYPE_VEC_KNITSIGN vecKnitSign;               //编织符号
   //ZB-892 工艺组织利用TXT转制版增加左右边上不循环 end   Duchen 2020/06/23 09:21
   //#4217 成型【编织】新增常用组织类型列表 start Duchen 2016/01/20 10:06 dc170116
   TYPE_2D_VECTSIGN m_vect2DKnit;
   //#4217 成型【编织】新增常用组织类型列表 end   Duchen 2016/01/20 10:06
   //#3125 成型检查转数计算有误 start Duchen 2016/01/10 14:30 dc170109
   CString m_sOrgKnitSignName;
   //#3125 成型检查转数计算有误 end   Duchen 2016/01/10 14:30
   //#4638 坑条大身与罗纹组织对齐 start Duchen 2017/04/19 10:53 dc170417
   CString m_sModType; //大身坯布结构
   //#4638 坑条大身与罗纹组织对齐 end   Duchen 2017/04/19 10:53
   KnitParams paramKnitRow;                     //工艺行参数       
   double iHeight;                              //高度
	UINT effective ;                             //有效针数
	UINT Real_effective;
   BOOL bEffective;                             //有效标记

   //工艺转换缓存数据
   BOOL bNeckKaisPs;                            //开衫平收
};
typedef std::vector<ShapeProfileRow> TYPE_LIST_SHAPE;
typedef std::list<ShapeProfileRow>::iterator TYPE_LISTITER_SHAPE;
//---------------------------------------------------------------------------
//收针符号表
typedef std::map<BYTE,TYPE_VEC_KNITSIGN> TYPE_MAP_SIGN;        //BYTE 收针数
typedef std::pair<BYTE,TYPE_VEC_KNITSIGN> TYPE_MAP_SIGN_PAIR;

typedef struct tagNeedleSign
{
   tagNeedleSign(){
      //默认参数
      //bFrontLMarkSign = 71;
      //bFrontRMarkSign = 61;
      //bBackLMarkSign = 91; 
      //bBackRMarkSign = 81;
   }
   //TYPE_MAP_SIGN vecFrontLTranSigns;        //前编织左边移针符号
   //TYPE_MAP_SIGN vecFrontRTranSigns;        //前编织右边移针符号
   //TYPE_MAP_SIGN vecBackLTranSigns;         //后编织左边移针符号
   //TYPE_MAP_SIGN vecBackRTranSigns;         //后编织右边移针符号
   //TYPE_MAP_SIGN vecFrontNeckLTranSigns;    //V领左边收针符号
   //TYPE_MAP_SIGN vecFrontNeckRTranSigns;    //V领右边收针符号
   //TYPE_MAP_SIGN vecBackNeckLTranSigns;     //V领左边收针符号
   //TYPE_MAP_SIGN vecBackNeckRTranSigns;     //V领右边收针符号
   //BYTE      bFrontLMarkSign;               //前编织边际（记号）符号 左侧
   //BYTE      bFrontRMarkSign;               //前编织边际（记号）符号 右侧
   //BYTE      bBackLMarkSign;                //后编织边际（记号）符号 左侧
   //BYTE      bBackRMarkSign;                //后编织边际（记号）符号 右侧
   ShapeSpace::NeedleFlat_Type  m_nFlatType;//平收方式
   //ShapeSpace::Reduce_Type m_bodyneedle2type;    //大身收针方式(2)  (两针)
   //ShapeSpace::Reduce_Type m_bodyneedle3type;    //大身收针方式(3)  (三针)
   //ShapeSpace::Reduce_Type m_neckneedle2type;    //领子收针方式(2)  (两针)
   //ShapeSpace::Reduce_Type m_neckneedle3type;    //领子收针方式(3)  (三针)
}NeedleSign,*pNeedleSign;

////清边参数
//typedef std::vector<ShapeSpace::CLEARBORDERTYPE> TYPE_VEC_CLB;
//class CClearBorderCData:public CKnitData
//{
//public:
//   CClearBorderCData(){bClearBorder=FALSE;iClearCount=0;};
//   ~CClearBorderCData(){};
//public:
//   BOOL bClearBorder;            //是否清边
//   int  iClearCount;             //清边数
//   TYPE_VEC_CLB vecClearBorder;  //清边前色码容器
//   std::vector<BYTE> vecCustomColor; //清边前自定义色码容器
//   std::vector<BYTE> vecFinalColor;  //清边后色码容器
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
//工艺数据
class CShapeProfileData//:
   //public CKnitData
{
public:
   CShapeProfileData()
   {
      //IsZhiXuanZhen = FALSE;                                //是否直选针机型
      //IsBottomExist = FALSE;                                //是否有起底板
      //m_nMachineType = ShapeSpace::enMultiMachine;          //单多系统
      //m_nNeedleTrans = ShapeSpace::enTransNone;             //变针距
      //m_CombType = L"";                                     //起底板模式
      ////------------------------------------------------------------
      ////轮廓相关（外型选项）
      //m_iStartWidth = 100;                    //编织起始宽度
      //m_iStartOffset = 0;                     //起始偏移
      //m_iNeckStartHeight = 0;                 //开领位 行数 界面需要用(转数 = m_iNeckStartHeight /2)表示
      //m_bNeckAutoHeight = TRUE;                //是否自动生成V领
      //m_iNeckStartWidth = 0;                  //衣领底边宽度
      //IsBodySymmetry = TRUE;                  //大身是否对称
      //IsNeckSymmetry = TRUE;                 //领子是否对称
      m_enShapeType = ShapeSpace::en_Shape_All;                    //生成布片
      //m_nNeedleType = ShapeSpace::enStaggerState;          //收针方式
      ////-----------------------------------------------------------
      ////v领选项
      //m_nNeckType = ShapeSpace::en_Neck_Sleeve;          //衣领模式         	--从0开始
      //m_bNeedleSafeNO = 15;                   //V领安全针数
      m_bNeckSplit = 2;                      //衣领拆行数
    //  m_iNeckOffSet = 0;                     //衣领水平偏移
      m_isVneckYTX = FALSE;                  //是否V领引塔夏 
      m_isNeckSeparate = TRUE;               //是否V领拆行
      m_isBottomSeparate = TRUE;             //是否领底拆行
    //  m_nEnecktype = ShapeSpace::enENeckSimpleNeedle_one;         //由高级其他设置转移过来XUYH 圆领底拆行方式
    //  m_bVNeckCZ = FALSE;                        //V领铲针
    //  m_bDeleteCenterLine = FALSE;					//抽中心线
    //  //删除多余代码 start Duchen 2017/12/06 19:09 dc171205
    //  //m_bNeckSinYarn = FALSE;
    //  //删除多余代码 end   Duchen 2017/12/06 19:09
    //  //----------------------------------------------------------
    //  //保留花样
    //  m_ptCenter.x = 0;               //保留花样的点以画布的左下角为原点坐标，从1开始
    //  m_ptCenter.y = 0;               //保留花样的点以画布的左下角为原点坐标，从1开始
    //  m_sizeCanvas.cx = 0;            //画布大小
    //  m_sizeCanvas.cy = 0;            //画布大小
    //  IsKeepPattern = FALSE;          //是否保留花样
    //  IsKeepIntersia = FALSE;         //是否保留引塔夏
	   //IsKeepOpt = FALSE;				  //是否保留功能线
    //  //#4168 套图时保留度目图的内容 start Duchen 2017/05/26 9:56 dc160522
    //  m_bKeepDumu = FALSE;            //是否保留度目图
    //  //#4168 套图时保留度目图的内容 end   Duchen 2017/05/26 9:56
      x_Border_up = 0;                //左右留边(夹边上)
      x_Border_down = 0;              //左右留边(夹边下)
      y_Border = 0;                   //上下留边
      //#4066 清边时上留边未使用指定色码清边 start Duchen 2016/11/04 15:02 dc161031
      m_nYNeckBottomBorder = 0;        //领底上留边
      //#4066 清边时上留边未使用指定色码清边 end   Duchen 2016/11/04 15:02
    //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
    //  m_enStartType = enAttachmentStartTypeNone;   //起头方式
    //  m_enEndType = enAttachmentEndTypeNone;     //末尾方式
    //  m_enConnectType = enAttachmentConnectTypeNone; //衔接方式
    //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52
	   //// 2012-12-5 xuyh添加棉纱标记
	   //iMianshaCenterNum   = _T("");
	   //bIsMianshaCenter = TRUE;
	   //enBodySizeFlag  = ShapeSpace::enSize_XS;
	   //enBodySizeType = ShapeSpace::enSizeType_diaomu;
    //  bGetDataFromCanvas = TRUE;
      //删除多余代码 start Duchen 2017/12/06 19:09 dc171205
      //m_isSignHorizontal = TRUE;
      //删除多余代码 end   Duchen 2017/12/06 19:09

      m_bTiHuaShouZhen = FALSE;
  //    m_pNextPieceData  = NULL;
  //    m_pPrePieceData   = NULL;
  //    //#4213 附件工艺单，编织为2（后编织）时，最后落布错误 start Duchen 2017/02/10 15:56 dc170206
  //    m_bTopUseBack = FALSE;               //封口纱使用背床
	 // m_bNoBottomNeckcalulateKnit2 = FALSE;
  //    //#4213 附件工艺单，编织为2（后编织）时，最后落布错误 end   Duchen 2017/02/10 15:56
  //   //#4638 坑条大身与罗纹组织对齐 start Duchen 2017/04/19 10:53 dc170417
  //   m_bQLDataShapeNotFromDitu = FALSE;     //是否是使用rnf套底图
  //   //#4638 坑条大身与罗纹组织对齐 end   Duchen 2017/04/19 10:53
  //   //提花图库处理 start Duchen 2016/11/13 10:37 dc161113
  //   m_bTiHuaTuku = FALSE;
  //   //提花图库处理 end   Duchen 2016/11/13 10:37
  //   //#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 start Duchen 2017/10/27 16:26 dc161023
  //   m_bChangeTail = FALSE;
  //   //#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 end   Duchen 2017/10/27 16:26
  //   //#6050 夹色成型 start Duchen 2017/11/17 15:57 dc171117
  //   m_bDaShenJiaSe = FALSE;
  //   //#6050 夹色成型 end   Duchen 2017/11/17 15:57

  //   //ZB-273 3D转制版：大身夹色时，平收色码取的引塔夏色码错误 start Duchen 2018/06/05 16:11 dc180604
  //   m_bDaShenJiaSeNoCreateZuZhiTu = FALSE; //是大身夹色，但不生成新的组织图数据
  //   //ZB-273 3D转制版：大身夹色时，平收色码取的引塔夏色码错误 end   Duchen 2018/06/05 16:11

  //   //ZB-253 成型增加接口：借用之前的数据（Duc知道）实现成型后组织图有指定数据（数据由Chenjw给出，Duc知道），指定组织图不套图，指定位置贴上数据 start Duchen 2018/05/04 10:11 dc180308
  //   m_bInaNoAdditionColor = FALSE;
  //   //ZB-253 成型增加接口：借用之前的数据（Duc知道）实现成型后组织图有指定数据（数据由Chenjw给出，Duc知道），指定组织图不套图，指定位置贴上数据 end   Duchen 2018/05/04 10:11

  //   //ZB-905 工艺组织利用TXT转制版增加左右边上不循环的有边的收针之间的色码处理等 start Duchen 2020/07/03 12:21 dc200629
  //   m_bEdgeNeedleFix = FALSE; //有边收针边缘固定
  //   //ZB-905 工艺组织利用TXT转制版增加左右边上不循环的有边的收针之间的色码处理等 end   Duchen 2020/07/03 12:21
   }
   ~CShapeProfileData(){}
public:
   //TYPE_LIST_SHAPE m_LShapeData;                //左侧工艺行数据 //[XML][RNF]
   //MAP_CYCLEARTS  m_vectLCycle;                 //左侧工艺行循环数据 //[XML]
   //TYPE_LIST_SHAPE m_RShapeData;                //右侧工艺行数据 //[XML][RNF]
   //MAP_CYCLEARTS  m_vectRCycle;                 //右侧工艺行循环数据 //[XML]
   //TYPE_LIST_SHAPE m_VLShapeData;               //左V领工艺行数据 //[XML][RNF]
   //MAP_CYCLEARTS  m_vectLNCycle;                //左V领工艺行循环数据 //[XML]
   //TYPE_LIST_SHAPE m_VRShapeData;               //右V领工艺行数据 //[XML][RNF]
   //MAP_CYCLEARTS  m_vectRNCycle;                //右V领工艺行循环数据 //[XML]
   ////----------------------------------------------------------
   ////机型相关
   //BOOL     IsZhiXuanZhen;                      //是否直选针机型 //[XML]
   //BOOL     IsBottomExist;                      //是否有起底板 //[XML]
   //ShapeSpace::Sys_Type m_nMachineType;         //单多系统 //[XML]

   ParamSet m_ParamSet;                         //参数值设置 //[XML]
   OtherParamSet m_OtherParamSet;               //高级其他设置 //[XML]
   //ShapeSpace::NeedleTrans_Type  m_nNeedleTrans;//变针距 //[XML]
   //CString  m_CombType;                         //起底板模式 //[XML]
   ////------------------------------------------------------------
   ////轮廓相关（外型选项）
   //UINT     m_iStartWidth;                      //编织起始宽度 //[XML][RNF]
   //int      m_iStartOffset;                     //起始偏移 //[XML][RNF]
   //UINT     m_iNeckStartHeight;                 //开领位 行数 界面需要用(转数 = m_iNeckStartHeight /2)表示 //[XML]
   //BOOL     m_bNeckAutoHeight;                  //是否自动生成V领 //[XML]
   //int      m_iNeckStartWidth;                  //衣领底边宽度 中留针 //[XML][RNF]
   //BOOL     IsBodySymmetry;                     //大身是否对称 //[XML][RNF]
   //BOOL     IsNeckSymmetry;                     //领子是否对称 //[XML][RNF]
   ShapeSpace::Shape_Type m_enShapeType;                    //生成布片 整片、左、右 //[XML][RNF]
   //收针设置
   NeedleSign m_NeedleSigns;                    //收针符号表 //[XML]
   //ShapeSpace::Row_Type m_nNeedleType;          //收针方式 //[XML]
   ////-----------------------------------------------------------
   ////v领选项
   //ShapeSpace::Neck_Type  m_nNeckType;          //衣领模式 圆领 V领 附件 等 --从0开始 //[XML][RNF]
   //BYTE      m_bNeedleSafeNO;                   //V领安全针数 //[XML]
   BYTE      m_bNeckSplit;                      //衣领拆行数 //[XML]
   //int       m_iNeckOffSet;                     //衣领水平偏移 //[XML][RNF]
   BOOL      m_isVneckYTX;                      //是否V领引塔夏 //[XML]
   BOOL      m_isNeckSeparate;                  //是否V领拆行 //[XML]
   BOOL      m_isBottomSeparate;                //是否领底拆行 //[XML]
   ShapeSpace::ENeck_Type m_nEnecktype;         //由高级其他设置转移过来XUYH 圆领底拆行方式 //[XML]
   //BOOL      m_bVNeckCZ;                        //V领铲针 //[XML]
   //BOOL      m_bDeleteCenterLine;					//抽中心线 //[XML][RNF]
   ////删除多余代码 start Duchen 2017/12/06 19:09 dc171205
   ////BOOL      m_bNeckSinYarn;
   ////删除多余代码 end   Duchen 2017/12/06 19:09
   ////----------------------------------------------------------
   ////起底组织部分
   //
   CKDModData m_ModData;                 //起底数据 //[XML][RNF]
   ////----------------------------------------------------------
   ////保留花样
   //CPoint m_ptCenter;               //保留花样的点以画布的左下角为原点坐标，从1开始 //[XML][RNF]
   //CSize  m_sizeCanvas;             //画布大小 //[RNF]
   //std::vector<BYTE> m_vecPatData;  //画布花样数据 //[RNF]
   //std::vector<BYTE> m_vecInaData;  //引塔夏数据
   ////#4168 套图时保留度目图的内容 start Duchen 2017/05/26 9:56 dc160522
   //std::vector<BYTE> m_vecDumuData;  //引塔夏数据
   ////#4168 套图时保留度目图的内容 end   Duchen 2017/05/26 9:56
   ////#4635 套图清边需要保留辅助点记号 start Duchen 2017/04/14 11:15 dc170410
   //std::vector<BYTE> m_vecAssistRegion; //辅助区域或点或线数据,或者轮廓中间挖空部分表示为0 //[RNF]
   ////#4635 套图清边需要保留辅助点记号 end   Duchen 2017/04/14 11:15
   ////ZB-285 成型接口patData里数据1号色的特殊处理（透明透过）导致无法正确设置含有1号色的组织数据（组织图同，需要特殊处理） start Duchen 2018/05/14 16:21 dc180514
   //std::vector<BYTE> m_vec3DPatRegion; //3d花样图小图案数据（但内存占用相当于全底图）
   ////ZB-285 成型接口patData里数据1号色的特殊处理（透明透过）导致无法正确设置含有1号色的组织数据（组织图同，需要特殊处理） end   Duchen 2018/05/14 16:21
   //BOOL IsKeepPattern;              //是否保留花样 //[XML][RNF]
   //BOOL IsKeepIntersia;             //是否保留引塔夏 //[XML][RNF]
   //BOOL IsKeepOpt;                  //是否保留功能线 //[XML]
   ////#4168 套图时保留度目图的内容 start Duchen 2017/05/26 9:56 dc160522
   //BOOL m_bKeepDumu;                //是否度目图 //[XML]
   ////#4168 套图时保留度目图的内容 end   Duchen 2017/05/26 9:56
   //BOOL bGetDataFromCanvas;         //是否从画布上去取数据
   ////#4638 坑条大身与罗纹组织对齐 start Duchen 2017/04/19 10:53 dc170417
   //BOOL m_bQLDataShapeNotFromDitu;     //是否是从rnf直接成型，没有套底图
   ////#4638 坑条大身与罗纹组织对齐 end   Duchen 2017/04/19 10:53
   ////提花图库处理 start Duchen 2016/11/13 10:37 dc161113
   //BOOL m_bTiHuaTuku; //是否是提花图库处理 //[RNF]
   ////提花图库处理 end   Duchen 2016/11/13 10:37
   ////#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 start Duchen 2017/10/27 16:26 dc161023
   //BOOL m_bChangeTail;              //是否是更换结尾
   ////#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 end   Duchen 2017/10/27 16:26
   UINT x_Border_up;                //左右留边(夹边上) //[XML]
   UINT x_Border_down;              //左右留边(夹边下) //[XML]
   UINT y_Border;                   //上下留边 //[XML]
   //#4066 清边时上留边未使用指定色码清边 start Duchen 2016/11/04 15:02 dc161031
   int m_nYNeckBottomBorder;         //领底上留边 //[XML]
 //  //#4066 清边时上留边未使用指定色码清边 end   Duchen 2016/11/04 15:02
   BOOL m_bTiHuaShouZhen;           //提花收针 //[XML]
 //  //清边参数
 //  CClearBorderCData m_ClearBorderPara;   //清边参数 //[XML]

	//// 2012-12-5 xuyh添加棉纱标记
	//CString iMianshaCenterNum ;   //中心记号 //[XML][RNF]
 //  //删除多余代码 start Duchen 2017/12/06 19:09 dc171205
 //  //BOOL m_isSignHorizontal; //记号横向方向
 //  //删除多余代码 end   Duchen 2017/12/06 19:09
	//BOOL bIsMianshaCenter;  //缝盘 //[XML][RNF]

	//ShapeSpace::BODYSIZEFLAG enBodySizeFlag;  //尺码(S,M,L等) //[XML]
	//ShapeSpace::BODYSIZETYPE enBodySizeType;  //尺码表示方式（吊目、挑孔） //[XML]

	//VECT_MOD_INFO  m_vectModuleInfo; //保留完整模块信息 //[XML][RNF]

 //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
 //  enum AttachmentStartType
 //  {
 //     enAttachmentStartTypeNone = 0, //空
 //     enAttachmentStartTypeAfterKongZhuanFirst = 1, //空转后第一行/单面第一行
 //     enAttachmentStartTypeLastKongZhuan = 2,//空转最后一行/单面第二行
 //  };
 //  AttachmentStartType m_enStartType;   //起头方式 //[RNF]
 //  enum AttachmentEndType
 //  {
 //     enAttachmentEndTypeNone = 0, //空
 //     enAttachmentEndTypeLastLine = 1, //不翻单面最后一行放松（空转以转为单位，为最后一转）
 //     enAttachmentEndTypeSecondLastLine = 2, //不翻单面倒数第二行放松（空转以转为单位，为倒数第二转）
 //     enAttachmentEndTypeTransFirstLine = 3, //翻完单面第一行
 //     //ZB-925 翻单面支持翻后只有1行 start Duchen 2020/07/15 13:21 dc200713
 //     enAttachmentEndTypeTransFirstLineSingle = 4, //翻完单面第一行 单行
 //     //ZB-925 翻单面支持翻后只有1行 end   Duchen 2020/07/15 13:21
 //  };
 //  AttachmentEndType m_enEndType;     //末尾方式 //[RNF]
 //  enum AttachmentConnectType
 //  {
 //     enAttachmentConnectTypeNone = 0, //空
 //     enAttachmentConnectTypeLuowenZimaYuanTongSipinJiaJin = 1, //罗纹字码圆筒四平加紧
 //     enAttachmentConnectTypeJinZimaYuanTongSipinJiaJin = 2, //紧字码圆筒四平加紧
 //     enAttachmentConnectTypeSipinJiaJin = 3 //四平加紧
 //  };

 //  AttachmentConnectType m_enConnectType; //衔接方式 //[RNF]
 //  //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52

 //  //ZB-905 工艺组织利用TXT转制版增加左右边上不循环的有边的收针之间的色码处理等 start Duchen 2020/07/03 12:21 dc200629
 //  BOOL m_bEdgeNeedleFix; //有边收针边缘固定
 //  //ZB-905 工艺组织利用TXT转制版增加左右边上不循环的有边的收针之间的色码处理等 end   Duchen 2020/07/03 12:21

	//// 附件工艺相关
	//BOOL  m_IsTrans;                 // 是否翻单面 //[XML][RNF]
	//int   m_iLoopCount;              // 循环次数 //[XML]
	//BOOL  m_TempIsGreet;		         // 是否接边(处理中间数据, 非界面数据，不要保存)
 //  int   m_iOrgLeftWidth;
 //  int   m_iFirstPieceCenter;       //用于计算最后一片的废纱位置，非界面数据，不要保存)
 //  int   m_iLastPieceOffset;       // 用于计算最后一片的废纱位置，非界面数据，不要保存)
 //  //#4213 附件工艺单，编织为2（后编织）时，最后落布错误 start Duchen 2017/02/10 15:56 dc170206
 //  BOOL  m_bTopUseBack;               //封口纱使用背床
 //  BOOL  m_bNoBottomNeckcalulateKnit2; //是否为封口纱无起底处理方式2
 //  //#4213 附件工艺单，编织为2（后编织）时，最后落布错误 end   Duchen 2017/02/10 15:56

 //  //#5651 常见基本组织成型自动生成合适的收针方式 start Duchen 2017/10/19 10:32 dc161016
 //  CString m_sDaShenTypeName;     //大身组织类型名
 //  //#5651 常见基本组织成型自动生成合适的收针方式 end   Duchen 2017/10/19 10:32

 //  //#6050 夹色成型 start Duchen 2017/11/17 15:57 dc171117
 //  BOOL m_bDaShenJiaSe;    //是否大身夹色（工艺转制版底图为夹色）//[RNF]
 //  //#6050 夹色成型 end   Duchen 2017/11/17 15:57

 //  //ZB-273 3D转制版：大身夹色时，平收色码取的引塔夏色码错误 start Duchen 2018/06/05 16:11 dc180604
 //  BOOL m_bDaShenJiaSeNoCreateZuZhiTu; //是大身夹色，但不生成新的组织图数据
 //  //ZB-273 3D转制版：大身夹色时，平收色码取的引塔夏色码错误 end   Duchen 2018/06/05 16:11

 //  //ZB-253 成型增加接口：借用之前的数据（Duc知道）实现成型后组织图有指定数据（数据由Chenjw给出，Duc知道），指定组织图不套图，指定位置贴上数据 start Duchen 2018/05/04 10:11 dc180308
 //  BOOL m_bInaNoAdditionColor; //组织图不添加额外色码，如收针，清边，废纱等，临时设置的flag,默认FALSE
 //  //ZB-253 成型增加接口：借用之前的数据（Duc知道）实现成型后组织图有指定数据（数据由Chenjw给出，Duc知道），指定组织图不套图，指定位置贴上数据 end   Duchen 2018/05/04 10:11

   ////ZB-780 成型增加一些特殊收针类型自动处理 start Duchen 2019/09/02 18:16 dc190902
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
   //   //ZB-831 收针类型自动处理扩展 start Duchen 2020/03/09 10:52 dc20200309
   //   int nLeftPageCount;
   //   int nRightPageCount;
   //   //ZB-831 收针类型自动处理扩展 end   Duchen 2020/03/09 10:52
   //};
   //std::map<CString, NeedlePackageData> m_mapNeedlePackageData; //成型dll内部不做处理
   ////ZB-780 成型增加一些特殊收针类型自动处理 end   Duchen 2019/09/02 18:16

   //CShapeProfileData*       m_pNextPieceData;   //连片编织的下一片数据
   //CShapeProfileData*       m_pPrePieceData;   //连片编织的下一片数据
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
   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） start Duchen 2016/09/05 15:17 dc160905
   //BOOL IsQuanTiHua()
   //{
   //   return (_T("shuangmiantihua") == this->m_ModData.m_strTransType || this->m_bTiHuaShouZhen);
   //}
   ////#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） end   Duchen 2016/09/05 15:17

   ////#5651 常见基本组织成型自动生成合适的收针方式 start Duchen 2017/10/19 10:32 dc161016
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
   ////#5651 常见基本组织成型自动生成合适的收针方式 end   Duchen 2017/10/19 10:32
   ////#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 start Duchen 2017/12/07 14:20 dc171207
   //void ClearCanvasData() //清楚画布相关数据
   //{
   //   m_vecPatData.clear();
   //   m_vecPatData.shrink_to_fit();
   //   m_vecInaData.clear();
   //   m_vecInaData.shrink_to_fit();
   //   m_vecDumuData.clear();
   //   m_vecDumuData.shrink_to_fit();
   //   m_vecAssistRegion.clear();
   //   m_vecAssistRegion.shrink_to_fit();
   //   //ZB-285 成型接口patData里数据1号色的特殊处理（透明透过）导致无法正确设置含有1号色的组织数据（组织图同，需要特殊处理） start Duchen 2018/05/14 16:21 dc180514
   //   m_vec3DPatRegion.clear();
   //   m_vec3DPatRegion.shrink_to_fit();
   //   //ZB-285 成型接口patData里数据1号色的特殊处理（透明透过）导致无法正确设置含有1号色的组织数据（组织图同，需要特殊处理） end   Duchen 2018/05/14 16:21
   //}
   ////#4171 多尺码RNF套针法底图 提示内存不足 导致崩溃 end   Duchen 2017/12/07 14:20
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


