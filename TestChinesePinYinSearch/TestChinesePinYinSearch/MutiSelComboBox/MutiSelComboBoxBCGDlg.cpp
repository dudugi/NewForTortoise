#include "stdafx.h"
#include "MutiSelComboBoxBCGDlg.h"
#include <vector>
#include <imm.h>
#include <algorithm>
#include <set>

enum
{
//    BACKGROUND_COLOR = RGB(255, 255, 255),
//    FRAME_COLOR = RGB(130, 135, 144),
//    DELETE_CONFIRM_TEXT_COLOR = RGB(255, 0, 0),
//   LIST_ITEM_HEIGHT = 18,//28,
   //LIST_BOX_TOP_Y = 36,
   LIST_FONT_HEIGHT = 12,//16,
   EDIT_FONT_HEIGHT = 14,
//    HINT_FONT_HEIGHT = 16,
//    BIG_HINT_FONT_HEIGHT = 28,
};

enum
{
   IDC_LIST_CONTENT = 10000,
   IDC_EDIT_SEARCH
};

enum
{
   COMMAND_EDITCHANGE = 10001,
   COMMAND_COMPOSING = 10002
};

WNDPROC CMutiSelComboBoxBCGDlg::m_oldEditProc = 0;

LRESULT CMutiSelComboBoxBCGDlg::MyEditProc(HWND hWnd,  UINT message, WPARAM wParam, LPARAM lParam )
{
   switch(message)
   {
   case WM_KEYDOWN:
      break;
   case WM_IME_ENDCOMPOSITION:
      {
         HWND hWndParent = ::GetParent(hWnd);
         ::PostMessage(hWndParent, WM_COMMAND, COMMAND_EDITCHANGE, 0);
      }
      break;
   case WM_IME_COMPOSITION:
      {
         HWND hWndParent = ::GetParent(hWnd);
         ::PostMessage(hWndParent, WM_COMMAND, COMMAND_COMPOSING, 0);
      }
      break;
   }
   return CallWindowProc(m_oldEditProc, hWnd, message, wParam, lParam);
}

static CString ConvertChineseToShorthand(const wchar_t* chrstr)
{
   const  int pyvalue[] = {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
      -20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,
      -19725,-19715,-19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,
      -19261,-19249,-19243,-19242,-19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,
      -18977,-18961,-18952,-18783,-18774,-18773,-18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,
      -18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,-18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,
      -18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,-17928,-17922,-17759,-17752,-17733,-17730,
      -17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,-17433,-17427,-17417,-17202,
      -17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,-16465,-16459,
      -16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
      -16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,
      -15707,-15701,-15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,
      -15408,-15394,-15385,-15377,-15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,
      -15143,-15141,-15140,-15139,-15128,-15121,-15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,
      -14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,-14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,
      -14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,-14368,-14355,-14353,-14345,-14170,-14159,
      -14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,-14097,-14094,-14092,-14090,
      -14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,-13831,-13658,
      -13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
      -13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,
      -12860,-12858,-12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,
      -12320,-12300,-12120,-12099,-12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,
      -11589,-11536,-11358,-11340,-11339,-11324,-11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,
      -11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,-10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,
      -10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,-10262,-10260,-10256,-10254};
   const char pystr[396][7] = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao",
      "bie","bin","bing","bo","bu","ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen",
      "cheng","chi","chong","chou","chu","chuai","chuan","chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui",
      "cun","cuo","da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan",
      "dui","dun","duo","e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao",
      "ge","gei","gen","geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai","han","hang",
      "hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo","ji","jia","jian",
      "jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
      "keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei",
      "leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv","luan","lue","lun","luo",
      "ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
      "na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong",
      "nu","nv","nuan","nue","nuo","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie",
      "pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong","qiu","qu","quan","que","qun",
      "ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang",
      "sao","se","sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua",
      "shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su","suan","sui","sun","suo","ta","tai",
      "tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo",
      "wa","wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing",
      "xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin","ying","yo","yong","you",
      "yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
      "zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
      "zi","zong","zou","zu","zuan","zui","zun","zuo"};

   int chrasc = 0;         

   char* pcReturnString = NULL;

   //unicode转换为ANSI
   int length = WideCharToMultiByte(CP_ACP, 0, chrstr, -1, 0, 0, 0, 0 ); 
   char* nowchar = new char[length+1];
   memset(nowchar,0,length+1);
   WideCharToMultiByte( CP_ACP, 0, chrstr, -1, nowchar,length, 0, 0 );

   //转换ANSI,字符部分不变，汉字转换成相应的拼音
   char *returnstr = new char[6*length +1];
   memset(returnstr,0,6*length +1);

   int offset = 0; 
   for (int j = 0; j < length;) // 循环处理字节数组
   {
      if (nowchar[j] >= 0 && nowchar[j] < 128) // 非汉字处理
      {
         returnstr[offset] = nowchar[j];
         offset++;
         j++;
         continue;
      }

      // 汉字处理
      chrasc = nowchar[j] * 256 + nowchar[j+1]+256;

      if (chrasc > 0 && chrasc < 160)
      {
         returnstr[offset]= nowchar[j];
         offset++;
         j++;
      }
      else
      {
         for (int i = (sizeof(pyvalue)/sizeof(pyvalue[0]) - 1); i >= 0; i--)
         {
            if (pyvalue[i] <= chrasc)
            {
               returnstr[offset]= pystr[i][0];
               offset++;  
               break;
            }
         }
         j +=2;
      }
   }
   if(strlen(returnstr)>0)
   {
      pcReturnString = new char[strlen(returnstr)+1];
      memset(pcReturnString,0,strlen(returnstr)+1);
      strcpy(pcReturnString,returnstr);
   }
   delete []returnstr;
   delete []nowchar;

   CString strShorthand(pcReturnString);
   delete []pcReturnString;

   return strShorthand;
}

static CString ConvertChineseUnicodeToPyt(const wchar_t* chrstr)
{
   const  int pyvalue[] = {-20319,-20317,-20304,-20295,-20292,-20283,-20265,-20257,-20242,-20230,-20051,-20036,-20032,-20026,
      -20002,-19990,-19986,-19982,-19976,-19805,-19784,-19775,-19774,-19763,-19756,-19751,-19746,-19741,-19739,-19728,
      -19725,-19715,-19540,-19531,-19525,-19515,-19500,-19484,-19479,-19467,-19289,-19288,-19281,-19275,-19270,-19263,
      -19261,-19249,-19243,-19242,-19238,-19235,-19227,-19224,-19218,-19212,-19038,-19023,-19018,-19006,-19003,-18996,
      -18977,-18961,-18952,-18783,-18774,-18773,-18763,-18756,-18741,-18735,-18731,-18722,-18710,-18697,-18696,-18526,
      -18518,-18501,-18490,-18478,-18463,-18448,-18447,-18446,-18239,-18237,-18231,-18220,-18211,-18201,-18184,-18183,
      -18181,-18012,-17997,-17988,-17970,-17964,-17961,-17950,-17947,-17931,-17928,-17922,-17759,-17752,-17733,-17730,
      -17721,-17703,-17701,-17697,-17692,-17683,-17676,-17496,-17487,-17482,-17468,-17454,-17433,-17427,-17417,-17202,
      -17185,-16983,-16970,-16942,-16915,-16733,-16708,-16706,-16689,-16664,-16657,-16647,-16474,-16470,-16465,-16459,
      -16452,-16448,-16433,-16429,-16427,-16423,-16419,-16412,-16407,-16403,-16401,-16393,-16220,-16216,-16212,-16205,
      -16202,-16187,-16180,-16171,-16169,-16158,-16155,-15959,-15958,-15944,-15933,-15920,-15915,-15903,-15889,-15878,
      -15707,-15701,-15681,-15667,-15661,-15659,-15652,-15640,-15631,-15625,-15454,-15448,-15436,-15435,-15419,-15416,
      -15408,-15394,-15385,-15377,-15375,-15369,-15363,-15362,-15183,-15180,-15165,-15158,-15153,-15150,-15149,-15144,
      -15143,-15141,-15140,-15139,-15128,-15121,-15119,-15117,-15110,-15109,-14941,-14937,-14933,-14930,-14929,-14928,
      -14926,-14922,-14921,-14914,-14908,-14902,-14894,-14889,-14882,-14873,-14871,-14857,-14678,-14674,-14670,-14668,
      -14663,-14654,-14645,-14630,-14594,-14429,-14407,-14399,-14384,-14379,-14368,-14355,-14353,-14345,-14170,-14159,
      -14151,-14149,-14145,-14140,-14137,-14135,-14125,-14123,-14122,-14112,-14109,-14099,-14097,-14094,-14092,-14090,
      -14087,-14083,-13917,-13914,-13910,-13907,-13906,-13905,-13896,-13894,-13878,-13870,-13859,-13847,-13831,-13658,
      -13611,-13601,-13406,-13404,-13400,-13398,-13395,-13391,-13387,-13383,-13367,-13359,-13356,-13343,-13340,-13329,
      -13326,-13318,-13147,-13138,-13120,-13107,-13096,-13095,-13091,-13076,-13068,-13063,-13060,-12888,-12875,-12871,
      -12860,-12858,-12852,-12849,-12838,-12831,-12829,-12812,-12802,-12607,-12597,-12594,-12585,-12556,-12359,-12346,
      -12320,-12300,-12120,-12099,-12089,-12074,-12067,-12058,-12039,-11867,-11861,-11847,-11831,-11798,-11781,-11604,
      -11589,-11536,-11358,-11340,-11339,-11324,-11303,-11097,-11077,-11067,-11055,-11052,-11045,-11041,-11038,-11024,
      -11020,-11019,-11018,-11014,-10838,-10832,-10815,-10800,-10790,-10780,-10764,-10587,-10544,-10533,-10519,-10331,
      -10329,-10328,-10322,-10315,-10309,-10307,-10296,-10281,-10274,-10270,-10262,-10260,-10256,-10254};
   const char pystr[396][7] = {"a","ai","an","ang","ao","ba","bai","ban","bang","bao","bei","ben","beng","bi","bian","biao",
      "bie","bin","bing","bo","bu","ca","cai","can","cang","cao","ce","ceng","cha","chai","chan","chang","chao","che","chen",
      "cheng","chi","chong","chou","chu","chuai","chuan","chuang","chui","chun","chuo","ci","cong","cou","cu","cuan","cui",
      "cun","cuo","da","dai","dan","dang","dao","de","deng","di","dian","diao","die","ding","diu","dong","dou","du","duan",
      "dui","dun","duo","e","en","er","fa","fan","fang","fei","fen","feng","fo","fou","fu","ga","gai","gan","gang","gao",
      "ge","gei","gen","geng","gong","gou","gu","gua","guai","guan","guang","gui","gun","guo","ha","hai","han","hang",
      "hao","he","hei","hen","heng","hong","hou","hu","hua","huai","huan","huang","hui","hun","huo","ji","jia","jian",
      "jiang","jiao","jie","jin","jing","jiong","jiu","ju","juan","jue","jun","ka","kai","kan","kang","kao","ke","ken",
      "keng","kong","kou","ku","kua","kuai","kuan","kuang","kui","kun","kuo","la","lai","lan","lang","lao","le","lei",
      "leng","li","lia","lian","liang","liao","lie","lin","ling","liu","long","lou","lu","lv","luan","lue","lun","luo",
      "ma","mai","man","mang","mao","me","mei","men","meng","mi","mian","miao","mie","min","ming","miu","mo","mou","mu",
      "na","nai","nan","nang","nao","ne","nei","nen","neng","ni","nian","niang","niao","nie","nin","ning","niu","nong",
      "nu","nv","nuan","nue","nuo","o","ou","pa","pai","pan","pang","pao","pei","pen","peng","pi","pian","piao","pie",
      "pin","ping","po","pu","qi","qia","qian","qiang","qiao","qie","qin","qing","qiong","qiu","qu","quan","que","qun",
      "ran","rang","rao","re","ren","reng","ri","rong","rou","ru","ruan","rui","run","ruo","sa","sai","san","sang",
      "sao","se","sen","seng","sha","shai","shan","shang","shao","she","shen","sheng","shi","shou","shu","shua",
      "shuai","shuan","shuang","shui","shun","shuo","si","song","sou","su","suan","sui","sun","suo","ta","tai",
      "tan","tang","tao","te","teng","ti","tian","tiao","tie","ting","tong","tou","tu","tuan","tui","tun","tuo",
      "wa","wai","wan","wang","wei","wen","weng","wo","wu","xi","xia","xian","xiang","xiao","xie","xin","xing",
      "xiong","xiu","xu","xuan","xue","xun","ya","yan","yang","yao","ye","yi","yin","ying","yo","yong","you",
      "yu","yuan","yue","yun","za","zai","zan","zang","zao","ze","zei","zen","zeng","zha","zhai","zhan","zhang",
      "zhao","zhe","zhen","zheng","zhi","zhong","zhou","zhu","zhua","zhuai","zhuan","zhuang","zhui","zhun","zhuo",
      "zi","zong","zou","zu","zuan","zui","zun","zuo"};

   int chrasc = 0;         

   char* pcReturnString = NULL;

   //unicode转换为ANSI
   int length = WideCharToMultiByte(CP_ACP, 0, chrstr, -1, 0, 0, 0, 0 ); 
   char* nowchar = new char[length+1];
   memset(nowchar,0,length+1);
   WideCharToMultiByte( CP_ACP, 0, chrstr, -1, nowchar,length, 0, 0 );

   //转换ANSI,字符部分不变，汉字转换成相应的拼音
   char *returnstr = new char[6*length +1];
   memset(returnstr,0,6*length +1);

   int offset = 0; 
   for (int j = 0; j < length;) // 循环处理字节数组
   {
      if (nowchar[j] >= 0 && nowchar[j] < 128) // 非汉字处理
      {

         returnstr[offset] = nowchar[j];
         offset++;
         j++;
         continue;
      }

      // 汉字处理
      chrasc = nowchar[j] * 256 + nowchar[j+1]+256;

      if (chrasc > 0 && chrasc < 160)
      {
         returnstr[offset]= nowchar[j];
         offset++;
         j++;
      }
      else
      {
         for (int i = (sizeof(pyvalue)/sizeof(pyvalue[0]) - 1); i >= 0; i--)
         {
            if (pyvalue[i] <= chrasc)
            {
               strcpy(returnstr+offset ,pystr[i]);

               offset +=strlen(pystr[i]);  
               break;
            }
         }
         j +=2;
      }
   }
   if(strlen(returnstr)>0)
   {
      pcReturnString = new char[strlen(returnstr)+1];
      memset(pcReturnString,0,strlen(returnstr)+1);
      strcpy(pcReturnString,returnstr);
   }
   delete []returnstr;
   delete []nowchar;

   CString strPy(pcReturnString);
   delete []pcReturnString;

   return strPy;
}

BEGIN_MESSAGE_MAP(CMyBCGEditBrowseCtrl, CMFCEditBrowseCtrl)
   ON_WM_CTLCOLOR_REFLECT()
   ON_CONTROL_REFLECT_EX(EN_CHANGE, &CMyBCGEditBrowseCtrl::OnEditchange)
   ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


void CMyBCGEditBrowseCtrl::ShowScrollBarIfNecessary()
{
   if (!::IsWindow(GetSafeHwnd()))
      return;
   int nLine = GetLineCount();
   auto *pFont = GetFont();
   LONG lHeight = 14;
   if (pFont)
   {
      LOGFONT font;
      pFont->GetLogFont(&font);
      lHeight = abs(font.lfHeight);
   }
   int nPerLineHeight = lHeight + 1;
   int nHeight = nLine * nPerLineHeight;
   CRect Rect;
   GetRect(&Rect);

   if (Rect.Height() >= nHeight)
   {
      ShowScrollBar(SB_VERT, FALSE);
   }
   else
   {
      ShowScrollBar(SB_VERT, TRUE);
   }
}

BOOL CMyBCGEditBrowseCtrl::OnEditchange()
{
   ShowScrollBarIfNecessary();
   return FALSE;
}

HBRUSH CMyBCGEditBrowseCtrl::CtlColor(CDC* pDC, UINT nCtlColor)
{
   // TODO: Change any attributes of the DC here
   CClientDC dc(this); //获取画布对象
   CRect rect;
   GetClientRect(rect); //获取客户区域
   rect.InflateRect(1,1,1,1);//将客户区域增大一个像素

   CBrush brush(RGB(255,255,255));//创建画刷
   dc.FrameRect(rect,&brush);//绘制边框

   CBrush brush2(RGB(171,193,222));//创建画刷
   rect.InflateRect(1,1,1,1);//将客户区域增大一个像素
   dc.FrameRect(rect,&brush2);//绘制边框

   GetWindowRect(rect);
   ScreenToClient(&rect);
   dc.FrameRect(rect, &brush2);

   // TODO: Return a non-NULL brush if the parent's handler should not be called
   return NULL;
}

void CMyBCGEditBrowseCtrl::OnBrowse()
{
   if (m_funcOnBrowse)
      m_funcOnBrowse();
}

void CMyBCGEditBrowseCtrl::OnKillFocus(CWnd* pNewWnd)
{
   CMFCEditBrowseCtrl::OnKillFocus(pNewWnd);
   if (m_funcOnKillFocus && pNewWnd != this)
   {
      m_funcOnKillFocus(pNewWnd);
   }
}

BEGIN_MESSAGE_MAP(CMutiSelComboBoxBCGDlg, CDialogEx)
   ON_WM_ACTIVATE()
   ON_LBN_SELCHANGE(IDC_LIST_CONTENT, &CMutiSelComboBoxBCGDlg::OnLbnSelchangeListContent)
   ON_EN_CHANGE(IDC_EDIT_SEARCH, &CMutiSelComboBoxBCGDlg::OnEnChangeEditSearch)
   ON_COMMAND(COMMAND_EDITCHANGE, &CMutiSelComboBoxBCGDlg::OnCbnCommandEditchange)
   ON_COMMAND(COMMAND_COMPOSING, &CMutiSelComboBoxBCGDlg::OnCbnCommandEditComposing)
   ON_WM_SETFOCUS()
   ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CMutiSelComboBoxBCGDlg, CDialogEx)

CMutiSelComboBoxBCGDlg::CMutiSelComboBoxBCGDlg()
   :m_nMaxCount(100), m_bDropUp(FALSE), m_nListItemHeight(18), m_bAutoHide(FALSE)
{

}

void CMutiSelComboBoxBCGDlg::OnSetFocus( CWnd* p)
{
   CDialogEx::OnSetFocus(p);
   m_editSearch.SetFocus();
}

void CMutiSelComboBoxBCGDlg::OnCbnCommandEditchange()
{
   OnEnChangeEditSearch();
}

CString CMutiSelComboBoxBCGDlg::GetImmStringFromEdit()
{
   //auto hIMC = ImmGetContext(m_editSearch.GetSafeHwnd());
   //std::vector<char> vecbyBuf(1, 0);
   //LONG BufSize = ImmGetCompositionStringA(hIMC, GCS_COMPSTR, vecbyBuf.data(), 0); //统一用多字节的A后缀接口

   //if (BufSize > 0)
   //{
   //   vecbyBuf.assign(BufSize + 1, 0);
   //   LONG lRet = ImmGetCompositionStringA(hIMC, GCS_COMPSTR, vecbyBuf.data(), BufSize);
   //   if (IMM_ERROR_NODATA == lRet)
   //   {
   //      ASSERT(0);
   //      return _T("");
   //   }

   //   if (IMM_ERROR_GENERAL == lRet)
   //   {
   //      ASSERT(0);
   //      return _T("");
   //   }
   //}

   //CStringA str = vecbyBuf.data();
   //CString sImmString;
   //int nLen = str.GetLength();
   //for(int i = 0; i < nLen; i++)
   //{
   //   if (str[i] != _T('\''))
   //   {
   //      sImmString.AppendChar(str[i]);
   //   }
   //}

   //TRACE(_T("sImmString：%s\n"), sImmString);
   //sImmString.Trim();

   //ImmReleaseContext(m_editSearch.GetSafeHwnd(), hIMC);

   //return sImmString;
   return _T("");
}

void CMutiSelComboBoxBCGDlg::OnCbnCommandEditComposing()
{
   std::vector<TCHAR> vecTChar(512);
   ::GetWindowText(m_editSearch.GetSafeHwnd(), vecTChar.data(), vecTChar.size());

   int nStart = 0;
   int nEnd = 0;
   m_editSearch.GetSel(nStart, nEnd);

   CString sImmString = GetImmStringFromEdit();
   sImmString.MakeLower();

   TRACE(_T("nStart %d nEnd %d Composing %s\n"), nStart, nEnd, sImmString);

   CString strTest;
   m_editSearch.GetWindowText(strTest);

//#ifdef _UNICODE
   int nStrLen = strTest.GetLength();

   if (nStart == nEnd && nStart == nStrLen)
   {
      std::vector<CString> vecResults;
      FilterWithImm(strTest, sImmString, m_vecContents, &vecResults);
      //ChangeDropDownContents(vecResults);
   }
}

void CMutiSelComboBoxBCGDlg::OnLbnSelchangeListContent()
{
   CString sText;
   for (int i = 0; i < m_lstBox.GetCount(); ++i)
   {
      if (m_lstBox.GetSel(i) > 0)
      {
         CString sSelString;
         m_lstBox.GetText(i, sSelString);
         if (!sText.IsEmpty())
            sText.Append(_T("|"));
         sText.Append(sSelString);
      }
   }
   m_editSearch.SetWindowText(sText);SetWindowText(sText);
   return;

   int nCurSel = m_lstBox.GetCurSel();
   if (nCurSel < 0)
      return;
   CString sSelString;
   m_lstBox.GetText(nCurSel, sSelString);
   m_bDisableEnChangeEvent = TRUE;
   m_editSearch.SetWindowText(sSelString);SetWindowText(sSelString);
   m_editSearch.ShowScrollBarIfNecessary();
   m_editSearch.SetSel(0, -1);
   m_bDisableEnChangeEvent = FALSE;
   if (m_bAutoHide)
      ShowWindow(SW_HIDE);
   if (m_funcSelString)
      m_funcSelString(sSelString);
}

void CMutiSelComboBoxBCGDlg::OnEnChangeEditSearch()
{
   if (m_bDisableEnChangeEvent)
   {
      return;
   }

   CString sEditText;
   m_editSearch.GetWindowText(sEditText);
   std::vector<CString> vecTemp;

   Filter(sEditText, m_vecContents, &vecTemp);
   if (m_bAutoHide && vecTemp.empty())
   {
      ShowWindow(SW_HIDE);
      return;
   }

   //ChangeDropDownContents(vecTemp);
   SetWindowText(sEditText);
   if (m_funcEditChange)
   {
      m_funcEditChange(sEditText);
   }
   return;
}

void CMutiSelComboBoxBCGDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialogEx::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST_CONTENT, m_lstBox);
   DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
}

void CMutiSelComboBoxBCGDlg::SetAutoHide(BOOL bHide)
{
   m_bAutoHide = bHide;
}

BOOL CMutiSelComboBoxBCGDlg::CreateDlgIndirect(CWnd* pParent, int nStyle, int nListItemHeight, BOOL bChildWindow)
{
   if (GetSafeHwnd())
      return FALSE;

   std::vector<WORD> vecTemplate(sizeof(DLGTEMPLATE)/sizeof(WORD), 0);
   DLGTEMPLATE *pTemplate = (DLGTEMPLATE *)vecTemplate.data();
   if (bChildWindow)
      pTemplate->style =  DS_SETFONT | DS_FIXEDSYS | WS_CHILD | WS_SYSMENU;
   else
      pTemplate->style = DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_SYSMENU;
   pTemplate->x = 0;
   pTemplate->y = 0;
   pTemplate->cx = 275;
   pTemplate->cy = 170;
   pTemplate->cdit = 2;
   vecTemplate.push_back(0); // 菜单
   vecTemplate.push_back(0); // class
   vecTemplate.push_back(0); // Caption

   //MS Shell Dlg(8)
   vecTemplate.push_back(8);

   USES_CONVERSION;
   WCHAR *p = T2W(_T("MS Shell Dlg"));
   while (*p != 0)
   {
      vecTemplate.push_back(*p);
      ++p;
   }
   vecTemplate.push_back(0);

   //Align
   if (vecTemplate.size() % 2 != 0)
      vecTemplate.push_back(0);

   { //edit
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = nStyle | WS_VISIBLE;//WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER ; //NOT WS_BORDER
      item.id = IDC_EDIT_SEARCH;
      item.dwExtendedStyle = WS_EX_TRANSPARENT;
      item.x = 0;
      item.y = 0;
      item.cx = 229;
      item.cy = 14;
//       vecItemTemplate.push_back(0xFFFF);
//       vecItemTemplate.push_back(0x0081);
      WCHAR sName[] = L"MfcEditBrowse";
      vecItemTemplate.insert(vecItemTemplate.end(), sName, sName + wcslen(sName) + 1);

      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data //"MfcEditBrowse"

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   { //list
      std::vector<WORD> vecItemTemplate(sizeof(DLGITEMTEMPLATE)/sizeof(WORD), 0);
      DLGITEMTEMPLATE *pItem = (DLGITEMTEMPLATE *)vecItemTemplate.data();
      DLGITEMTEMPLATE &item = *pItem;
      item.style = WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_SORT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | 
         LBS_MULTIPLESEL | WS_VSCROLL | WS_TABSTOP;
      item.id = IDC_LIST_CONTENT;
      item.dwExtendedStyle = 0;
      item.x = 0;
      item.y = 15;
      item.cx = 275;
      item.cy = 136;
      vecItemTemplate.push_back(0xFFFF);
      vecItemTemplate.push_back(0x0083);
      vecItemTemplate.push_back(0); //title
      vecItemTemplate.push_back(0); //data

      vecTemplate.insert(vecTemplate.end(), vecItemTemplate.begin(), vecItemTemplate.end());
      if (vecTemplate.size() % 2 != 0)
         vecTemplate.push_back(0);
   }

   m_nListItemHeight = nListItemHeight;

   if (!CreateIndirect((DLGTEMPLATE *)vecTemplate.data(), pParent))
      return FALSE;
   if (nStyle & ES_MULTILINE)
   {
      m_lstBox.SetMultipleLine(TRUE);
   }
   m_lstBox.m_funcOnKillFocus = [this](CWnd *pWnd)
   {
      if (pWnd != &m_editSearch)
      {
         if (m_funcKillFocus)
         {
            m_funcKillFocus(pWnd);
         }
      }
   };
   m_editSearch.m_funcOnKillFocus = [this](CWnd *pWnd)
   {
      if (pWnd != &m_lstBox)
      {
         if (m_funcKillFocus)
         {
            m_funcKillFocus(pWnd);
         }
      }
   };
   return TRUE;
}

BOOL CMutiSelComboBoxBCGDlg::ChangeDropDownContents(const std::vector<CString> &vecContents)
{
   m_lstBox.ResetContent();
   for (auto Iter = vecContents.begin(); Iter != vecContents.end(); ++Iter)
   {
      m_lstBox.InsertString(-1, *Iter);
   }

   int nCount = m_lstBox.GetCount();

   if (nCount > m_nTmpMaxCount)
      nCount = m_nTmpMaxCount;

   CRect &EditRect = m_EditRect;

   if (!m_bDropUp)
   {
      if (nCount > 0)
         SetWindowPos(NULL, 0, 0, EditRect.Width(), EditRect.Height() + m_nListItemHeight * nCount + 5, SWP_NOMOVE | SWP_NOZORDER);
      else
         SetWindowPos(NULL, 0, 0, EditRect.Width(), EditRect.Height(), SWP_NOMOVE | SWP_NOZORDER);

      //编辑框处理
      //m_editSearch.SetWindowPos(NULL, 0, 0, EditRect.Width(), EditRect.Height(),  /*SWP_NOMOVE |*/ SWP_NOZORDER | SWP_NOREDRAW);

      m_lstBox.SetWindowPos(NULL, 0, 0, EditRect.Width(), EditRect.Height() + m_nListItemHeight * nCount + 4, SWP_NOMOVE | SWP_NOZORDER);
      Invalidate();
   }
   else
   {
      int nFloatHeight;
      if (nCount > 0)
         nFloatHeight = EditRect.Height() + m_nListItemHeight * nCount + 5;
      else
         nFloatHeight = EditRect.Height();

      //浮窗坐标设置
      if (nCount > 0)
         SetWindowPos(NULL, EditRect.left, EditRect.bottom - nFloatHeight,
            EditRect.Width(), nFloatHeight, SWP_NOREDRAW | SWP_NOZORDER);
      else
         SetWindowPos(NULL, EditRect.left, EditRect.top,
            EditRect.Width(), nFloatHeight, SWP_NOREDRAW | SWP_NOZORDER);

      m_lstBox.SetWindowPos(NULL, 0, 0, EditRect.Width(), /*EditRect.Height() + */m_nListItemHeight * nCount + 4, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
      //编辑框处理
      m_editSearch.SetWindowPos(NULL, 0, nFloatHeight - EditRect.Height(), EditRect.Width(), EditRect.Height(), /*SWP_NOMOVE |*/ SWP_NOZORDER | SWP_NOREDRAW);

      Invalidate();
   }

   return TRUE;
}

BOOL CMutiSelComboBoxBCGDlg::FilterWithImm(const CString &sOrgTest, const CString &sImmString, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents)
{
   if (!pvecResultContents)
      return FALSE;

   CString sInputText = sOrgTest + sImmString;
   CString sInputTextLower = sInputText;
   sInputTextLower.MakeLower();

   std::vector<CString> vecTemp;

   for (auto it = vecTotalContents.begin(); it != vecTotalContents.end(); ++it)
   {
      if (0 == it->m_sOrg.Find(sInputText)) //最开头包含子串
      {
         vecTemp.push_back(it->m_sOrg);
      }
      else if (0 == it->m_sPinYin.Find(sInputTextLower))
      {
         vecTemp.push_back(it->m_sOrg);
      }
      else if (0 == it->m_sShortHand.Find(sInputTextLower))
      {
         vecTemp.push_back(it->m_sOrg);
      }
      else if (!sImmString.IsEmpty() && !sOrgTest.IsEmpty() && 0 == it->m_sOrg.Find(sOrgTest))
      {
         CStringW strW = sOrgTest;
         CString sOldBefore = ConvertChineseUnicodeToPyt(strW);
         CString sOldBeforeShort = ConvertChineseToShorthand(strW);
       
         int nOldBeforeLen = sOldBefore.GetLength();
         int nOldBeforeShortLen = sOldBeforeShort.GetLength();
       
         if (it->m_sPinYin.Mid(nOldBeforeLen, it->m_sPinYin.GetLength() - nOldBeforeLen).Find(sImmString) == 0)
         {
            vecTemp.push_back(it->m_sOrg);
         }
         else if (it->m_sShortHand.Mid(nOldBeforeShortLen, it->m_sShortHand.GetLength() - nOldBeforeShortLen).Find(sImmString) == 0)
         {
            vecTemp.push_back(it->m_sOrg);
         }
      }
   }

   pvecResultContents->swap(vecTemp);
   return TRUE;
}

BOOL CMutiSelComboBoxBCGDlg::Filter(const CString &sInputText, const std::vector<ComboItem> &vecTotalContents, std::vector<CString> *pvecResultContents)
{
   if (!sInputText.IsEmpty())
      return Filter(_T(""), vecTotalContents, pvecResultContents);

   if (!pvecResultContents)
      return FALSE;

   std::vector<CString> vecTemp;
   CString sInputTextLower = sInputText;
   sInputTextLower.MakeLower();
   
   for (auto it = vecTotalContents.begin(); it != vecTotalContents.end(); ++it)
   {
      if (0 == it->m_sOrg.Find(sInputText)) //最开头包含子串
      {
         vecTemp.push_back(it->m_sOrg);
      }
      else if (0 == it->m_sPinYin.Find(sInputTextLower))
      {
         vecTemp.push_back(it->m_sOrg);
      }
      else if (0 == it->m_sShortHand.Find(sInputTextLower))
      {
         vecTemp.push_back(it->m_sOrg);
      }
//       else if (!strImmString.IsEmpty() && !strOrgTest.IsEmpty() && 0 == it->m_sOrg.Find(strOrgTest))
//       {
//          CStringW strW = strOrgTest;
//          CString sOldBefore = ConvertChineseUnicodeToPyt(strW);
//          CString sOldBeforeShort = ConvertChineseToShorthand(strW);
// 
//          int nOldBeforeLen = sOldBefore.GetLength();
//          int nOldBeforeShortLen = sOldBeforeShort.GetLength();
// 
//          if (it->m_sPinYin.Mid(nOldBeforeLen, it->m_sPinYin.GetLength() - nOldBeforeLen).Find(strImmString) == 0)
//          {
//             vecFileredString.push_back(it->m_sOrg);
//          }
//          else if (it->m_sShortHand.Mid(nOldBeforeShortLen, it->m_sShortHand.GetLength() - nOldBeforeShortLen).Find(strImmString) == 0)
//          {
//             vecFileredString.push_back(it->m_sOrg);
//          }
//       }
   }

   pvecResultContents->swap(vecTemp);
   return TRUE;
}

void CMutiSelComboBoxBCGDlg::AddString(LPCTSTR lpszString)//添加item
{
   CString sText(lpszString);
   ComboItem item;
   item.m_sOrg = sText;
   CStringW sOrgWide(sText);
   item.m_sPinYin = ConvertChineseUnicodeToPyt(sOrgWide);
   item.m_sShortHand = ConvertChineseToShorthand(sOrgWide);
   m_vecContents.push_back(item);
}

void CMutiSelComboBoxBCGDlg::GetLBText(int nIndex, CString &rString)
{
   if (nIndex >= 0 && nIndex <= (int)m_vecContents.size())
   {
      rString = m_vecContents[nIndex].m_sOrg;
   }
}

int CMutiSelComboBoxBCGDlg::DeleteString(UINT nIndex)
{
   if (nIndex >= m_vecContents.size())
      return CB_ERR;
   auto Iter = std::next(m_vecContents.begin(), nIndex);
   m_vecContents.erase(Iter);
   return (int)m_vecContents.size();
}

void CMutiSelComboBoxBCGDlg::ResetContent()
{
   m_vecContents.clear();
}

int CMutiSelComboBoxBCGDlg::GetCount() const
{
   return (int)m_vecContents.size();
}

void CMutiSelComboBoxBCGDlg::GetLBText(int nIndex, CString &rString) const
{
   if (nIndex < 0 || nIndex >= (int)m_vecContents.size())
   {
      return;
   }
   rString = m_vecContents[nIndex].m_sOrg;
}

HBITMAP CMutiSelComboBoxBCGDlg::GetButtonBitmap()
{
   static CBitmap bitmap;
   if (bitmap.GetSafeHandle())
   {
      return (HBITMAP)bitmap.GetSafeHandle();
   }
   int nX = 18;
   int nY = 22;
   int cb = ((nX + 3) & (-4)) * nY;

   std::vector<BYTE> bufBmpInfo;
   bufBmpInfo.resize(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

   LPBITMAPINFO lpbi = (LPBITMAPINFO)&bufBmpInfo[0];
   lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   lpbi->bmiHeader.biWidth = nX;
   lpbi->bmiHeader.biHeight = nY;
   lpbi->bmiHeader.biPlanes = 1;
   lpbi->bmiHeader.biBitCount = 8;
   lpbi->bmiHeader.biCompression = BI_RGB;
   lpbi->bmiHeader.biSizeImage = (DWORD)cb;
   lpbi->bmiHeader.biXPelsPerMeter = 0;
   lpbi->bmiHeader.biYPelsPerMeter = 0;
   lpbi->bmiHeader.biClrUsed = 0;
   lpbi->bmiHeader.biClrImportant = 0;

   RGBQUAD tmp;
   tmp.rgbBlue = 0;
   tmp.rgbGreen = 0;
   tmp.rgbRed = 0;
   tmp.rgbReserved = 0;
   std::vector<RGBQUAD> vecRgbQuad(256, tmp);

   vecRgbQuad[1].rgbBlue = 255;
   vecRgbQuad[1].rgbGreen = 255;
   vecRgbQuad[1].rgbRed = 255;
   vecRgbQuad[1].rgbReserved = 0;

   memcpy(&bufBmpInfo[sizeof(BITMAPINFOHEADER)], vecRgbQuad.data(), sizeof(RGBQUAD)*256);

   BYTE* pBmpBits = NULL;

   HBITMAP hbmp = CreateDIBSection(/*dc.GetSafeHdc()*/NULL, lpbi, DIB_RGB_COLORS, (void **)&pBmpBits, NULL, 0);
   ASSERT(hbmp);

   BYTE bits[20*22] = 
   {
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,
      1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
      1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   };

   memcpy(pBmpBits, bits, 20*22);
   bitmap.Attach(hbmp);
   return (HBITMAP)bitmap.GetSafeHandle();
}

std::set<CStringW> SplitStrW(const CStringW &strOrg, const WCHAR *delim)
{
   std::vector<WCHAR> vecProcessTCHAR(strOrg.GetLength() + 1);

   memcpy(vecProcessTCHAR.data(), (LPCWSTR)strOrg, strOrg.GetLength() * sizeof(WCHAR));
   WCHAR *pTUploadChar = ::wcstok(vecProcessTCHAR.data(), delim);

   std::set<CStringW> setResultString;

   while(pTUploadChar != NULL)
   {
      CStringW strExt;

      strExt = pTUploadChar;


      setResultString.insert(strExt);
      pTUploadChar = ::wcstok(NULL, delim);
   }
   return setResultString;
}

int CMutiSelComboBoxBCGDlg::Init(const CRect &EditRect,
   const CString &sEditText, int nEditSelStart, int nEditSelEnd, BOOL bInitialFilter,
   BOOL bShowBrowserButton, const CRect &RectParent)
{
   std::vector<CString> vecTemp;
   if (!bInitialFilter)
   {
      Filter(_T(""), m_vecContents, &vecTemp);
   }
   else
   {
      CString sImmString = GetImmStringFromEdit();
      sImmString.MakeLower();

      if (nEditSelStart == nEditSelEnd && nEditSelStart == sEditText.GetLength())
      { //暂定只允许中文后接拼音
         FilterWithImm(sEditText, sImmString, m_vecContents, &vecTemp);
      }
      else
      {
         Filter(sEditText, m_vecContents, &vecTemp);
      }
   }

   if (vecTemp.empty() && (0 == (GetStyle() & WS_CHILD)))
   {
      return 0;
   }

   m_bHided = FALSE;
   m_EditRect = EditRect;

   ////生成候选项的结构体数组
   //std::vector<ComboItem> vecContents;
   //vecContents.reserve(vecContent.size());
   //for (auto Iter = vecContent.begin(); Iter != vecContent.end(); ++Iter)
   //{
   //   ComboItem item;
   //   item.m_sOrg = *Iter;
   //   CStringW sOrgWide(*Iter);
   //   item.m_sPinYin = ConvertChineseUnicodeToPyt(sOrgWide);
   //   item.m_sShortHand = ConvertChineseToShorthand(sOrgWide);
   //   vecContents.push_back(item);
   //}
   //m_vecContents.swap(vecContents);

   m_lstBox.ResetContent();

   //CFrequentlyChatContentFile ContentFile;
   //if (!m_sSettingFilePath.IsEmpty())
   //   ContentFile.ReadFile(m_sSettingFilePath);

   //m_deqContents.assign(ContentFile.m_vecContent.begin(), ContentFile.m_vecContent.end());
   
  
   for (auto Iter = vecTemp.begin(); Iter != vecTemp.end(); ++Iter)
   {
      m_lstBox.InsertString(-1, *Iter);
   }

   auto vec = SplitStrW(sEditText, _T("|"));

   for (auto Iter = vec.begin(); Iter != vec.end(); ++Iter)
   {
      auto nFindRet = m_lstBox.FindStringExact(-1, *Iter);

      if (nFindRet != CB_ERR)
      {
         m_lstBox.SetSel(nFindRet, 1);
      }
   }

   int nScreenHeight = RectParent.bottom;
   //CWnd *pParent = GetParent();
   //if (pParent)
   //{
   //   CRect rtParent;
   //   pParent->GetWindowRect(&rtParent);
   //   nScreenHeight = rtParent.Height();
   //}

   int nMaxDropCount = m_vecContents.size();
   if (nMaxDropCount > m_nMaxCount)
      nMaxDropCount = m_nMaxCount;

   int nMaxDropHeight = EditRect.Height() + m_nListItemHeight * nMaxDropCount + 5;

   m_nTmpMaxCount = m_nMaxCount;

   if (nMaxDropCount == 0) //没有候选项
   {
      m_bDropUp = FALSE; //往下弹(无所谓哪边弹)
   }
   else if (EditRect.top + nMaxDropHeight > nScreenHeight) //下面放不下
   {
      if (EditRect.bottom - nMaxDropHeight < 0) //上面也放不下
      {
         //m_bDropUp = FALSE;
         if (EditRect.top > nScreenHeight - EditRect.bottom) // 臣
         { //上面空间大
            int nTmpMaxCount = (EditRect.top - 2) / m_nListItemHeight;
            if (nTmpMaxCount < m_nTmpMaxCount)
            {
               m_nTmpMaxCount = nTmpMaxCount;
            }
            m_bDropUp = TRUE; //往上弹
         }
         else
         { //下面空间大
            int nTmpMaxCount = (nScreenHeight - EditRect.bottom - 2) / m_nListItemHeight;
            if (nTmpMaxCount < m_nTmpMaxCount)
            {
               m_nTmpMaxCount = nTmpMaxCount;
            }
            m_bDropUp = FALSE; //往下弹
         }
      }
      else
      {
         m_bDropUp = TRUE; //往上弹
      }
   }
   else
   {
      m_bDropUp = FALSE; //往下弹
   }

   int nCount = m_lstBox.GetCount();

   if (nCount > m_nTmpMaxCount)
      nCount = m_nTmpMaxCount;

   //int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

   int nFloatHeight;
   if (nCount > 0)
      nFloatHeight = EditRect.Height() + m_nListItemHeight * nCount + 5;
   else
      nFloatHeight = EditRect.Height();

   //浮窗大小设置
   SetWindowPos(NULL, 0, 0, EditRect.Width(), nFloatHeight, SWP_NOMOVE | SWP_NOZORDER);

   //编辑框处理
   m_bDisableEnChangeEvent = TRUE;
   m_editSearch.SetWindowText(sEditText);SetWindowText(sEditText);
   m_editSearch.ShowScrollBarIfNecessary();
   m_bDisableEnChangeEvent = FALSE;
   m_editSearch.SetSel(nEditSelStart, nEditSelEnd);

   if (bShowBrowserButton)
   {
      m_editSearch.EnableBrowseButton(TRUE);
      auto hBmp = GetButtonBitmap();
      m_editSearch.SetBrowseButtonImage(hBmp, FALSE);
   }

   m_editSearch.SetFocus();

   if (m_bDropUp)
   {
      //编辑框处理
      m_editSearch.SetWindowPos(NULL, 0, nFloatHeight - EditRect.Height(), EditRect.Width(), EditRect.Height(), /*SWP_NOMOVE |*/ SWP_NOZORDER);

      //listbox大小设置
      CRect ListBoxRect;
      m_lstBox.GetWindowRect(&ListBoxRect);
      m_lstBox.SetWindowPos(NULL, 0, 0, EditRect.Width(), m_nListItemHeight * nCount + 4, /*SWP_NOMOVE |*/ SWP_NOZORDER);

      //浮窗坐标设置
      if (nCount > 0)
         ::SetWindowPos(GetSafeHwnd(), 0, EditRect.left, EditRect.bottom - nFloatHeight,
            EditRect.Width(), EditRect.Height() + m_nListItemHeight * nCount + 5, SWP_NOZORDER);
      else
         ::SetWindowPos(GetSafeHwnd(), 0, EditRect.left, EditRect.top,
            EditRect.Width(), EditRect.Height(), SWP_NOZORDER);
   }
   else
   {
      //编辑框处理
      m_editSearch.SetWindowPos(NULL, 0, 0, EditRect.Width(), EditRect.Height(), /*SWP_NOMOVE |*/ SWP_NOZORDER);

      //m_editSearch.SetRectNP()

      //listbox大小设置
      CRect ListBoxRect;
      m_lstBox.GetWindowRect(&ListBoxRect);
      m_lstBox.SetWindowPos(NULL, 0, EditRect.Height(), EditRect.Width(), m_nListItemHeight * nCount + 4, /*SWP_NOMOVE |*/ SWP_NOZORDER);

      //浮窗坐标设置
      if (nCount > 0)
         ::SetWindowPos(GetSafeHwnd(), 0, EditRect.left, EditRect.top,
            EditRect.Width(), EditRect.Height() + m_nListItemHeight * nCount + 5, SWP_NOZORDER);
      else
         ::SetWindowPos(GetSafeHwnd(), 0, EditRect.left, EditRect.top,
            EditRect.Width(), EditRect.Height(), SWP_NOZORDER);
   }

   m_editSearch.ShowScrollBarIfNecessary();

   Invalidate();

   return (int)vecTemp.size();
}

BOOL CMutiSelComboBoxBCGDlg::OnInitDialog()
{
   CDialogEx::OnInitDialog();

   //参数初始化
   m_bDisableEnChangeEvent = FALSE;
   m_bHided = TRUE;

   //事件初始化
   m_editSearch.m_funcOnBrowse = [this]()
   {
      if (m_bAutoHide)
         this->ShowWindow(SW_HIDE);
      if (m_funcOnHide)
      {
         CString sEditString;
         m_editSearch.GetWindowText(sEditString);
         int nStartChar = 0;
         int nEndChar = 0;
         m_editSearch.GetSel(nStartChar, nEndChar);
         m_funcOnHide(sEditString, nStartChar, nEndChar, 0, 0);
      }
      if (m_funcReturn)
      {
         CString sEditString;
         m_editSearch.GetWindowText(sEditString);
         m_funcReturn(sEditString);
      }
   };

   //修改编辑框窗口过程
   auto oldEditProc = (WNDPROC)SetWindowLong(m_editSearch.GetSafeHwnd(), GWL_WNDPROC, (LONG)MyEditProc); 
   if (m_oldEditProc == 0)
   {
      m_oldEditProc = oldEditProc;
   }

   // TODO:  在此添加额外的初始化

   m_lstBox.SetItemHeight(0, m_nListItemHeight);

   m_ListFont.CreateFont(LIST_FONT_HEIGHT,0,0,0,FW_DONTCARE,FALSE,FALSE,0, 1,
      OUT_DEFAULT_PRECIS, 
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, 
      DEFAULT_PITCH|FF_SWISS,
      _T("宋体"));

   m_lstBox.SetFont(&m_ListFont);

   auto funcEditItem = [this](int nItem)
   {
       int nCount = m_lstBox.GetCount();
       if (nItem < nCount && nItem >= 0)
       {
          CString sText;
          m_lstBox.GetText(nItem, sText);
          if (m_funcDeleteStringCheck)
          {
             if (!m_funcDeleteStringCheck(sText))
                return;
          }
          this->DeleteString(nItem);
          //if (m_bAutoHide)
          //  this->ShowWindow(SW_HIDE);
          if (m_funcDeleteString)
          {
             m_funcDeleteString(sText);
          }
		  
		  auto FuncFind = [sText](const ComboItem &ItemText)->bool
		  {
			  return ItemText.m_sOrg == sText;
		  };
		  
		  auto Iter = std::find_if(m_vecContents.begin(), m_vecContents.end(), FuncFind);
		  if (Iter != m_vecContents.end())
		  {
			 m_vecContents.erase(Iter);
		  }

		  std::vector<CString> vecTemp;
		  CString sTextItem;
		  int nCount = m_lstBox.GetCount();
		  for (int i = 0; i < nCount; ++i)
		  {
			  m_lstBox.GetText(i, sTextItem);
			  if (sTextItem == sText)
				  continue;
			  vecTemp.push_back(sTextItem);
		  }
		  
		  ChangeDropDownContents(vecTemp);

        CString sEdit;
        m_editSearch.GetWindowText(sEdit);
        auto vec = SplitStrW(sEdit, _T("|"));

        for (auto Iter = vec.begin(); Iter != vec.end(); ++Iter)
        {
           auto nFindRet = m_lstBox.FindStringExact(-1, *Iter);

           if (nFindRet != CB_ERR)
           {
              m_lstBox.SetSel(nFindRet, 1);
           }
        }
       }
   };

   m_lstBox.m_funcOnClickItemButton = funcEditItem;

   if (m_EditFont.GetSafeHandle())
      m_editSearch.SetFont(&m_EditFont);

   return TRUE;
}

CString CMutiSelComboBoxBCGDlg::GetPreviousString(const CString &sOrgText)
{
   for (auto it = m_vecContents.rbegin(); it != m_vecContents.rend(); ++it)
   {
      if (it->m_sOrg == sOrgText)
      {
         auto IterNext = it;
         ++IterNext;
         if (IterNext == m_vecContents.rend())
         {
            return sOrgText;
         }
         return IterNext->m_sOrg;
      }
   }

   //找不到

   if (m_vecContents.empty())
      return sOrgText;
   else
      return m_vecContents.back().m_sOrg;
}

CString CMutiSelComboBoxBCGDlg::GetNextString(const CString &sOrgText)
{
   for (auto it = m_vecContents.begin(); it != m_vecContents.end(); ++it)
   {
      if (it->m_sOrg == sOrgText)
      {
         auto IterNext = it;
         ++IterNext;
         if (IterNext == m_vecContents.end())
         {
            return sOrgText;
         }
         return IterNext->m_sOrg;
      }
   }
   
   if (m_vecContents.empty())
      return sOrgText;
   else
      return m_vecContents.front().m_sOrg;
}

void CMutiSelComboBoxBCGDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
   CDialogEx::OnActivate(nState, pWndOther, bMinimized);

   // TODO: 在此处添加消息处理程序代码

   if (m_bAutoHide && nState == WA_INACTIVE && !m_bHided)
   {
      m_bHided = TRUE;
      ShowWindow(SW_HIDE);
      if (m_funcOnHide)
      {
         CString sEditString;
         m_editSearch.GetWindowText(sEditString);
         int nStartChar = 0;
         int nEndChar = 0;
         m_editSearch.GetSel(nStartChar, nEndChar);
         m_funcOnHide(sEditString, nStartChar, nEndChar, 0, 0);
      }
   }
}

BOOL CMutiSelComboBoxBCGDlg::PreTranslateMessage(MSG* pMsg)
{
   if (pMsg->message == WM_KEYDOWN)
   {
      if (pMsg->wParam == VK_UP)
      {
         if (m_lstBox.GetSafeHwnd())
         {
            int nCount = m_lstBox.GetCount();
            if (nCount > 0)
            {
               auto nSel = m_lstBox.GetCurSel();
               if (nSel < 0)
               {
                  m_lstBox.SetCurSel(nCount - 1);
               }
               else
               {
                  --nSel;
                  if (nSel >= 0)
                  {
                     m_lstBox.SetCurSel(nSel);
                  }
               }
            }
         }
         return TRUE;
      }
      else if (pMsg->wParam == VK_DOWN)
      {
         if (m_lstBox.GetSafeHwnd())
         {
            int nCount = m_lstBox.GetCount();
            if (nCount > 0)
            {
               auto nSel = m_lstBox.GetCurSel();
               if (nSel < 0)
               {
                  m_lstBox.SetCurSel(0);
               }
               else
               {
                  ++nSel;
                  if (nSel < nCount)
                  {
                     m_lstBox.SetCurSel(nSel);
                  }
               }
            }
         }
         return TRUE;
      }
      else if (pMsg->wParam == VK_RETURN && GetKeyState(VK_CONTROL) >= 0)
      {
         /*if (m_lstBox.GetSafeHwnd())
         {
            int nCount = m_lstBox.GetCount();
            if (nCount > 0)
            {
               auto nSel = m_lstBox.GetCurSel();
               if (nSel >= 0)
               {
                  CString sText;
                  m_lstBox.GetText(nSel, sText);
                  m_bDisableEnChangeEvent = TRUE;
                  m_editSearch.SetWindowText(sText);SetWindowText(sText);
                  m_editSearch.ShowScrollBarIfNecessary();
                  m_editSearch.SetSel(0, -1);
                  m_bDisableEnChangeEvent = FALSE;
                  if (m_bAutoHide)
                     ShowWindow(SW_HIDE);
                  if (m_funcSelString)
                     m_funcSelString(sText);
                  return TRUE;
               }
            }
            if (m_bAutoHide)
               ShowWindow(SW_HIDE);
            if (m_funcOnHide)
            {
               CString sText;
               m_editSearch.GetWindowText(sText);
               SetWindowText(sText);
               m_funcOnHide(sText, 0, 0, pMsg->message, pMsg->wParam);
            }
         }*/
         if (m_funcReturn)
         {
            CString sText;
            m_editSearch.GetWindowText(sText);
            SetWindowText(sText);
            m_funcReturn(sText);
         }
         return TRUE;
      }
      else if (pMsg->wParam == VK_TAB)
      {
         if (m_bAutoHide)
            ShowWindow(SW_HIDE);
         return TRUE;
      }
   }
   if (pMsg->message == WM_MOUSEWHEEL)
   {
      pMsg->hwnd = m_lstBox.GetSafeHwnd();
   }
   return CDialogEx::PreTranslateMessage(pMsg);
}

void CMutiSelComboBoxBCGDlg::NewPutChar(WPARAM nChar)
{
   if (m_editSearch.GetSafeHwnd())
   {
      //m_editSearch.SetWindowText(_T(""));
      m_editSearch.SendMessage(WM_CHAR, (WPARAM)nChar);
   }
}

void CMutiSelComboBoxBCGDlg::OnKillFocus(CWnd* pNewWnd)
{
   CDialogEx::OnKillFocus(pNewWnd);
}