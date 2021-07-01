/********************************************************************
//  作者:           linyp
//  CopyRight(c)    2011 Burnon All Rights Reserved 
//  创建时间:       2011/09/06 19:32
//  类描述:         成型设计命名空间 enum定义
//  修改时间:       
//  修改目的:       
*********************************************************************/
#pragma once
/*
自定义模块配置信息
*/
//自定义模块废纱
#define REFUSEYARN L"RefuseYarn"

//自定义模块 系统自定义模块类型
#define SYSDEFFSTD L"StdModel"
//模块带纱部分定义
#define MODYARNPICK L"起底组织带纱"
//起底部分过度行数据表
#define TRANSTYPE  L"STDTRANS"
//自定义模块 起底板类型
#define COMBMODEL L"COMBMODEL"



namespace ShapeSpace
{
   //机型选项
   enum Sys_Type{
      enSinMachine = 0,       //单系统
      enMultiMachine = 1,         //多系统
      enMachineNull = 2,
   };
   //变针距
   enum NeedleTrans_Type
   {
      enTransNone = 0,          //无变针距
      enTransSin ,              //单数变针
      enTransMuli               //双数变针
   };
   
   /************************************************************/
   //工艺部分枚举定义
   //收针/放针 类型
   enum Needle_Type
   {
       en_Needle_Null = 0,    //平遥 无加收针动作
       en_Needle_Add,         //加针
       en_Needle_Sub,         //收针
       en_Needle_Ps,          //夹边或者平收
       en_Needle_Mark,        //记号
       en_Needle_Hole,        //挑孔
       en_Needle_Cotton,      //棉纱
       en_Needle_LaXian,       //拉线
		 en_Needle_QiJia,        //集加针
       en_Needle_SuoZhen,       //缩针
       en_Needle_KaisPs,       //开衫领底平收
       //ZB-230 新增记号类型粗针拉线 start Duchen 2018/05/08 16:20 dc180507
       en_Needle_CuZhenLaXian,   //粗针拉线 因为要存文件保证兼容性 所以不能插中间改变数值
       //ZB-230 新增记号类型粗针拉线 end   Duchen 2018/05/08 16:20
       //ZB-602 制版新增缩针方式（平均，留中间或留两侧）start Duchen 2018/11/16 10:01 dc181112
       en_Needle_SuoZhen_Average, //缩针(均)
       en_Needle_SuoZhen_Middle, //缩针(中)
       en_Needle_SuoZhen_Side, //缩针(夹)
       //ZB-602 制版新增缩针方式（平均，留中间或留两侧）end   Duchen 2018/11/16 10:01
       //ZB-619 成型新增第四种新打褶，主要给裙子用 start Duchen 2018/11/26 15:23 dc181126
       en_Needle_SuoZhen_Custom, //缩针(用户)
       //ZB-619 成型新增第四种新打褶，主要给裙子用 end   Duchen 2018/11/26 15:23
       //ZB-626 成型新增打褶（底图），底图的移动和打褶色码的排放由底图特殊行色码决定 start Duchen 2018/12/10 15:23 dc181210
       en_Needle_SuoZhen_Basemap, //缩针(底图)
       //ZB-626 成型新增打褶（底图），底图的移动和打褶色码的排放由底图特殊行色码决定 end   Duchen 2018/12/10 15:23
       //ZB-30 多次加针时，选择齐加，处理方式不合理（#6355） start Duchen 2019/02/25 09:35 dc190225
       en_Needle_QiJia2, //齐加2
       //ZB-30 多次加针时，选择齐加，处理方式不合理（#6355） end   Duchen 2019/02/25 09:35
       //ZB-912 增加记号方式，目前只有拉线和粗针拉线 start Duchen 2020/07/08 13:21 dc200706
       en_Needle_LaXian1x4, //拉线1x4
       en_Needle_LaXian2x4, //拉线2x4
       //ZB-912 增加记号方式，目前只有拉线和粗针拉线 end   Duchen 2020/07/08 13:21
       //ZB-897 增加缩针1X1整条缩功能 start Duchen 2020/07/11 12:41 dc200706
       en_Needle_SuoZhen_1x1, //缩针1X1
       //ZB-897 增加缩针1X1整条缩功能 end   Duchen 2020/07/11 12:41
   };
   //平收方式
   enum NeedleFlat_Type
   {
      en_Flat_Simple_1= 0,
      en_Flat_Simple_2,
      en_Flat_Double_1,
      en_Flat_Double_2,
      en_Flat_Space,
	  en_Flat_MainCotton,
	  en_Flat_NewMod,       // 61 71 收针方式
	  en_Flat_WasteCotton,
      enMoldPS1_1,          //平收1-1（1针收）
      enMoldPS1_2,          //平收1-2（1针收）
      enMoldPS1_3,          //平收1-3（1针收）
      enMoldPS1_4,          //平收1-4（1针收）
      enMoldPS1_5,          //平收1-5（1针收）
      enMoldPS1_6,          //平收1-6（1针收）
      enMoldPS2_1,          //平收2-1（2针收）
      enMoldPS2_2,          //平收2-2（2针收）
      enMoldPS2_3,          //平收2-3（2针收）
      enMoldPS2_4,          //平收2-4（2针收）
      enMoldPSLB,           //落布收
      enMoldPS1_7           ////平收1-7（1针收）


   };
   /************************************************************/
   //领子部分
   enum Neck_Type
   {
      en_Neck_Circle,   //圆领
      en_Neck_VNeck,    //v领
      en_Neck_JLLW,     //拉网（假领移针）
      en_Neck_JLDM,     //假领吊目
      en_Neck_Sleeve,   //袖子
	   en_Neck_Attachment,
   };

   /************************************************************/
   //其他参数
   enum KnitPara_Type{
      enParaNone = 0,   //无参数
      enParaDefined,    //自定义参数
      enParaMold1       //参数模式1
   };

	enum Add_Type{
		enAdd_Yarn,
		enAdd_One1,
		enAdd_One2,
		enAdd_Two
      //#4621 成型加针增加完全偷吃选项 start Duchen 2017/04/18 11:15 dc170417
      ,enAdd_All1
      ,enAdd_All2
      //#4621 成型加针增加完全偷吃选项 end   Duchen 2017/04/18 11:15
	};
	enum CANCEL_TYPE{
		en_Cancel_NON = 0,
		en_Cancel_1N,
		en_Cancel_2N,
	};
   enum ENeck_Type{
      enENeckKnit,                    //编织（前）
      enENeckMainYarn1,               //主纱落布1
      enENeckMainYarn2,               //主纱落布2      
      enENeckScrapYarn,               //废纱落布
      enENeckSimpleNeedle_one,        //单针（1）
      enENeckSimpleNeedle_double,     //单针(2) 
      //#6266 领底平收也要有双针1选项 start Duchen 2018/01/04 18:06 dc180104
      enENeckDoubleNeedle2,            //双针2(2) 
      //enENeckDoubleNeedle,            //双针2(2) 
      //#6266 领底平收也要有双针1选项 end   Duchen 2018/01/04 18:06
      enENeckSeperateNeedle,           //隔针 
      enENeckScrapYarn_LX,             //废纱落布（定制）
      enENeckKnitBack                //编织（前） 
      //#4120 成型新增双面提花落布方式【废纱落布2】 start Duchen 2016/12/26 18:05 dc161226
      ,enENeckScrapYarn2               //废纱落布2
      //#4120 成型新增双面提花落布方式【废纱落布2】 end   Duchen 2016/12/26 18:05
      //#6266 领底平收也要有双针1选项 start Duchen 2018/01/04 18:06 dc180104
      ,enENeckDoubleNeedle1            //双针2(1)
      //#6266 领底平收也要有双针1选项 end   Duchen 2018/01/04 18:06
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

   //布片设定
   enum Shape_Type
   {
      en_Shape_All,  //整片
      en_Shape_Left, //左片
      en_Shape_Right //右片
   };

   //面包底包数据
   enum FroBkNeedle
   {
      enFrontBkNull,    //无
      enFrontKnit1,     //面1支包
      enFrontKnit2,     //面2支包
      enFrontKnit3,     //面3支包
      enBackKnit1,      //底1支包
      enBackKnit2,      //底2支包
      enBackKnit3,      //底3支包
      //ZB-928 罗纹排不出斜一支， 制版这边成型出来不对没有排除斜一支（工艺+制版卡梅特可以 start Duchen 2020/08/11 13:17 dc200810
      enObliqueKnit1,   //斜一支包
      enObliqueKnit2,   //斜二支包
      enObliqueKnit3,   //斜三支包
      //ZB-928 罗纹排不出斜一支， 制版这边成型出来不对没有排除斜一支（工艺+制版卡梅特可以 end   Duchen 2020/08/11 13:17
   };
   //落布设定
   enum QHLuoBu
   {
      enModLbQLB = 0,         //落布 前落布
      enModLbHLB = 1,         //罗布 后落布
      enModPTBZ = 2,          //普通编织后编织
      enModQBZ = 3,           //  前编织
      //ZB-924 过斜梭，恒强可以选择自动成型（制版） start Duchen 2020/08/03 13:17 dc200803
      enModDmGXSQ = 4,        //单面过斜梭(前)
      enModDmGXSH = 5         //单面过斜梭(后)
      //ZB-924 过斜梭，恒强可以选择自动成型（制版） end   Duchen 2020/08/03 13:17
   };
   enum{
      enUnionLine = 0,        //同行
      enStaggerLine           //分行
   };
   enum Row_Type{
      enUnionState = 0,       //同行状态
      enStaggerState,         //分行状态
      enStaggerState_Right,         //分行状态
   };

   enum
   {
      enModSzfsZYTH = 1,   //左右同行
      enModSzfsZYFH = 2,   //左右分行
      enModSzfsZYFH2 = 3   //左右复合
   };

   enum Body_Type
   {
      //顺序不能变更 只能往后添加,界面相关的段数
      en_UserDefine          =  0,          //为用户定制的数据情况下使用用户数据
      en_BirdEyes_Bottom     =  1,          //鸟眼四平1
      en_FullNeedle          =  2,          //废纱四平2
      en_SplitYarn_Bottom    =  3,          //废纱拆线3
      en_MainYarn            =  4,          //主纱起底4
      en_MainRacing          =  5,          //起底空转5
      en_RibbingKnit         =  6,          //螺纹编织8
      en_Transition          =  7,          //过度行7
      en_Body                =  8,          //大身8
      en_FlatInsert_LEFT     =  9,          //(平收)夹边插行9  左
      en_FlatInsert_RIGHT    =  10,         //(平收)夹边插行 右
      en_AutoInsert          =  11,         //自动插行11
      en_VNeck               =  12,         //领子12
      en_CircleNeckBottom    =  13,         //领底拆行
      en_VNeck_Left          =  14,         //领子左
      en_VNeck_Right         =  15,         //领子右
      en_TransNeedle         =  16,         //翻针17
      en_Doffing1            =  17,         //落布13
      en_Cotton              =  18,         //棉纱16
      en_Doffing2            =  19,         //落布2 15
      en_PPYarnBottom        =  20,         //PP线段数
      en_CombBottom          =  21,         //起底板
      en_FullNeedleComb      =  22,         //废纱四平2
      en_LuowenDxj           =  23,         //底橡筋
      //#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） start Duchen 2016/09/05 15:17 dc160905
      en_Taokou              =  24,         //套口
      en_TaokouFangSong              =  25,         //套口放松
      //#3346 全提花 结束时自动添加翻单面（用主纱做单面编织一转） end   Duchen 2016/09/05 15:17
      //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
      //附件段数-尾放松
      enAttachmentLoosenTail    = 26,
      //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52
      en_BodyType_DaiSha    = 27,       //带纱 主要标记让编译不报浮线过长 yangjr 2020/08/25

      //界面无关的段数，只在成型过程中使用
      //-顺序可以变更区域
      en_TopCotton,                          //废纱
      en_CircleNeckMainYarn,
      en_CircleNeck,                        //圆领14
      en_FlatInsert,
	   en_FlatInseetWaste_Left,
	   en_FlatInseetWaste_Right,
		en_CircleNeckBottom_LastRow,          //圆领最后一行，要求度目与大身度目相同
	   en_FlatDoffing,                       //平收吊针落布
      en_VNeckIntersia,                     //V领引塔夏
      en_ConttonIntersia,                   //棉纱引塔夏
      en_NeckIna_Left_Bottom,
      en_NeckIna_Left_Top,
      en_NeckIna_Right_Bottom,
      en_NeckIna_Right_Top,
      en_CottonIna_Left_Bottom,             //用废纱纱嘴1填充纱嘴 度目速度没加(V领引塔夏时使用)
      en_CottonIna_Left_Top,                //用废纱纱嘴1填充纱嘴 度目速度没加(V领引塔夏时使用)
      en_CottonIna_Right_Bottom,            //用废纱纱嘴2填充纱嘴 度目速度没加(V领引塔夏时使用)
      en_CottonIna_Right_Top,               //用废纱纱嘴2填充纱嘴 度目速度没加(V领引塔夏时使用)
      en_FlatInsertIna_Left,
      en_FlatInsertIna_Right,
      en_FlatInsertSeparate_Left,
      en_FlatInsertSeparate_Right,

      en_FlatInsert_2NdLeft_LEFT,
      en_FlatInsert_2NdLeft_RIGHT,
      en_FlatInsert_2NdLeft_Rev_LEFT,
      en_FlatInsert_2NdLeft_Rev_RIGHT,

      en_Doffing3,                          //无起底板时领子棉纱的落布行
      en_TurnNeedle,                        //翻针行
      en_Cotton_Left,                       //棉纱拆行左
      en_Cotton_right,                      //棉纱拆行右
      en_SplitYarn,                         //废纱拆线3
      en_BirdEyes,                          //鸟眼四平1
      en_TypeSeted,                         //过渡类型
      en_SplitYarnAdd_Right,
      en_SplitYarnAdd_Left_BirdEyes,                 //齐加针左边插入行(用废纱1)   度目速度没加
      en_SplitYarnAdd_Left_FullNeedle,               //齐加针左边插入行(用废纱1)   度目速度没加
      en_SplitYarnAdd_Left_SplitYarn_Bottom,         //齐加针左边插入行(用废纱1)   度目速度没加  
      en_SplitYarnAdd_Left_Doffing,                 //齐加针左边插入行(用废纱1)   度目速度没加      
      en_SplitYarnAdd_Right_BirdEyes,                //齐加针左边插入行(用废纱2)   度目速度没加        
      en_SplitYarnAdd_Right_FullNeedle,              //齐加针左边插入行(用废纱2)   度目速度没加        
      en_SplitYarnAdd_Right_SplitYarn_Bottom,        //齐加针左边插入行(用废纱2)   度目速度没加         
      en_SplitYarnAdd_Right_Doffing,                //齐加针左边插入行(用废纱2)   度目速度没加    
      en_CottonAdd_left,                    //加针编织废纱左
      en_CottonAdd_right,                   //加针编织废纱右
      en_CottonSpec_SplitYarn,              //引塔夏中的废纱拆线
      en_CottonSpec_FullNeedle,             //引塔夏中的废纱四平
      en_CottonSpec_Left_SplitYarn,         //引塔夏中的废纱拆线
      en_CottonSpec_Left_FullNeedle,        //引塔夏中的废纱四平
      en_CottonSpec_Right_SplitYarn,        //引塔夏中的废纱拆线
      en_CottonSpec_Right_FullNeedle,       //引塔夏中的废纱四平
      en_SplitYarnNeckBottom,               //领底拆行废纱
      en_0Zhuan,
      en_MainYarnFstOut,                    // 主纱1带出
      en_MainYarnSecOut,                    // 主纱2带出
      en_bottomCotton,
      en_JiaSi_SendOut,				           //加丝纱嘴带出
      //#2912 成型支持单纱嘴最开领分边织 start Duchen 2016/07/20 10:16 dc160718
      en_AutoInsert_SinYarnSeperateTwoWayMainYarn,               //开领分边织主纱
      en_AutoInsert_SinYarnSeperateTwoWaySplitYarn,               //开领分边织废纱
      //#2912 成型支持单纱嘴最开领分边织 end   Duchen 2016/07/20 10:16
      //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 start Duchen 2016/08/24 16:38 dc160822
      en_SuoZhen,
      //#2393 成型缩针行翻针度目拉力等可以单独设置一段度目 end   Duchen 2016/08/24 16:38
      //#4219 V领成型使用双面提花或者提花套图，两边分配了同一把纱嘴 start Duchen 2016/12/06 11:17 dc161205
      en_TaokouRight,
      //#4219 V领成型使用双面提花或者提花套图，两边分配了同一把纱嘴 end   Duchen 2016/12/06 11:17
      //#4219 V领成型使用双面提花或者提花套图，两边分配了同一把纱嘴 start Duchen 2016/12/06 11:17 dc161205
      en_TaokouIntarsia,
      //#4219 V领成型使用双面提花或者提花套图，两边分配了同一把纱嘴 end   Duchen 2016/12/06 11:17
      //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 start Duchen 2019/09/29 17:52 dc190923
      //附件段数-头放松
      enAttachmentLoosenHead,
      //附件段数-紧圆筒
      enAttachmentTightYuanTong,
      //附件段数-四平
      enAttachmentSiPing,
      //ZB-784 坯布增加头尾放松属性，转制版自动在头尾设置放松度目 end   Duchen 2019/09/29 17:52
      //ZB-859 成型大身最后一行主纱度目放松 start Duchen 2020/04/16 15:13 dc200413
      en_MainYarnFangSong,
      //ZB-859 成型大身最后一行主纱度目放松 end   Duchen 2020/04/16 15:13
      en_End,
   };
   static BOOL isTypeDaShen(const Body_Type &type) //线圈统计大身类型
   {
      if (en_Body == type || //大身8
         en_FlatInsert_LEFT == type  || //(平收)夹边插行9  左
         en_FlatInsert_RIGHT == type||  //(平收)夹边插行 右
         en_AutoInsert == type|| //自动插行11
         en_VNeck  == type|| //领子12
         en_CircleNeckBottom  == type|| //领底拆行
         en_VNeck_Left== type || //领子左
         en_VNeck_Right== type  //领子右
         )
      {
         return TRUE;
      }
      return FALSE;
   }
   static BOOL isTypeLuoWen(const Body_Type &type) //线圈统计螺纹类型
   {
      if (en_MainYarn == type || //主纱起底4
         en_MainRacing == type  || //起底空转5
         en_RibbingKnit == type||  //螺纹编织6
         en_Transition == type //过度行7
         )
      {
         return TRUE;
      }
      return FALSE;
   }    
   static BOOL isTypeNeedWeave(const Body_Type &type) //需要仿真部位数据
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

   //#6002 翻单面领子增加放松的度目段 start Duchen 2016/11/15 16:27 dc161113
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
   //#6002 翻单面领子增加放松的度目段 end   Duchen 2016/11/15 16:27

   //#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 start Duchen 2017/10/27 16:26 dc161023
   static BOOL IsColorTail(const Body_Type &type)
   {
      switch(type)
      {
      case en_Cotton: //棉纱
      case en_FullNeedle: //废纱四平
      case en_SplitYarn_Bottom: //废纱拆线
      case en_Doffing2: //落布2
      case en_BirdEyes_Bottom: //鸟眼四平
      case en_TransNeedle: //翻针
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
   //#5803 使用“更换起头”，结束前的废纱也应该替换，目前只替换来了开始的废纱部分 end   Duchen 2017/10/27 16:26
   enum Yarn_Type
   {
      en_YarnNull,       //无纱嘴
      en_YarnMain1,      //主纱嘴1 = 1
      en_YarnMain2,      //主纱嘴2 =2
      en_YarnSpilt1,     //废纱1  =3
      en_YarnSpilt2,     //废纱2 =4
      en_YarnOrgLuoWen,  //螺纹纱嘴2 =5
      en_YarnNeckSpilt,  //V领废纱 = 6
      en_YarnVIntersia,  //V领引塔夏 = 7
      en_PPYarn,         //pp线纱嘴 = 8
      en_YarnDxj,    //新增底橡胶 = 9 20151221 LINYP
      //#5652 沙嘴和段数增加罗纹沙嘴1 start Duchen 2017/12/05 15:26 dc171205
      en_YarnMainLuoWen, //罗纹沙嘴1 = 10
      //#5652 沙嘴和段数增加罗纹沙嘴1 end   Duchen 2017/12/05 15:26
      en_YarnRubb = 100, //橡筋纱嘴 = 100 一般不做变更 变更后数据库也要相应的修改
      en_YarnSeted,      //已分配纱嘴
	   en_YarnJiaSi,
      
	   en_Yarn255,
   };
   enum Spec_Type
   {
      en_NeckIna = 0x01,       //v领引塔夏
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
      en_KnitMainFirst, // 只用主纱1织 （只用一把纱嘴(纱嘴1=纱嘴2)、V领拆行/V领引塔夏底部、V领/V领引塔夏左边）
      en_KnitMainSec,   // 只用主纱2织 （V领/V领引塔夏右边）  
      en_KnitMainBoth   // 主纱12一起织（两把纱嘴织时的非V领拆行/V领引塔夏底部、非平收处、非领子处）
   };
   //成型清边
   enum CLEARBORDERTYPE
   {
      en_KnitFront,     //前编织
      en_KnitRear,      //后编织
      en_TuckFront,     //前吊目
      en_TuckRear,      //后吊目
      en_Transfer,      //翻针
      en_Custom         // 自定义
   };
	//棉纱尺码标记
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

   //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 start Duchen 2017/08/22 10:00 dc160821
   enum VNECKCHANZHENTYPE
   {
      enBoLiuZhenFirst = 0,
      enZhongLiuZhenFirst,
   };
   //#4629 V领产针时，因产针次数少了一次，造成中留 针变多 end   Duchen 2017/08/22 10:00
}


