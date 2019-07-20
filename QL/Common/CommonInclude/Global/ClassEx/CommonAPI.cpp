#include "StdAfx.h"
#include "CommonAPI.h"
#include <vector>
#include <Strsafe.h>
#include <windows.h>
#include <nb30.h>
#pragma comment(lib, "Netapi32.lib")
CCommonAPI::CCommonAPI(void)
{
}

CCommonAPI::~CCommonAPI(void)
{
}

BOOL CCommonAPI::MakeDirByCheck( CString strDir )
{
	BOOL bRet = TRUE;

	strDir.Trim();
	if (strDir.IsEmpty())
	{
		bRet = FALSE;
	}
	else
	{
		if (!PathFileExists(strDir))
		{
			strDir.Replace('/','\\');//Windows下路径统一转换
			CStringArray arrTemp;
			CString strTemp;
			strTemp = strDir;
			arrTemp.Add(strTemp);
			int pos = strTemp.ReverseFind('\\');
			for (int i=0;pos>0;)
			{
				arrTemp.Add(strTemp.Left(pos));
				strTemp = strTemp.Left(pos);
				pos = strTemp.ReverseFind('\\');
			}
			CString strPos = _T("");
			for(int j=arrTemp.GetSize();j>0;j--)
			{
				strPos = arrTemp.GetAt(j-1);
				if (!PathFileExists(strPos))
				{
					if (!::CreateDirectory(strPos,NULL))
					{
						bRet = FALSE;
						break;
					}
				}		
			}
		}
	}
	return bRet;
}

BOOL CCommonAPI::DeleteDirectory( const CString &strPath )
{
	ASSERT(!strPath.IsEmpty());

	CFileFind tempFind;
	TCHAR sTempFileFind[MAX_PATH] = { 0 };

	wsprintf(sTempFileFind, _T("%s\\*.*"), strPath);
	BOOL IsFinded = tempFind.FindFile(sTempFileFind);

	while (IsFinded)
	{
		IsFinded = tempFind.FindNextFile();

		if (!tempFind.IsDots())
		{
			TCHAR sFoundFileName[200] = { 0 };
			_tcscpy(sFoundFileName, tempFind.GetFileName().GetBuffer(200));

			if (tempFind.IsDirectory())
			{
				TCHAR sTempDir[200] = { 0 };
				wsprintf(sTempDir, _T("%s\\%s"),strPath, sFoundFileName);
				DeleteDirectory(sTempDir);
			} 
			else
			{
				TCHAR sTempFileName[200] = { 0 };
				wsprintf(sTempFileName, _T("%s\\%s"), strPath, sFoundFileName);
				DeleteFile(sTempFileName);
			}
		}
	}
	tempFind.Close();

	if(!RemoveDirectory(strPath))
		return false;
	return true;
}

void CCommonAPI::GetIniKeyValue( CString strSection,CString strKeyName,CString &strKeyValue,CString strPathFile )
{
	strPathFile.Trim();
	if (strPathFile.IsEmpty())
	{
		return;
	}

	TCHAR temp[MAX_PATH];
	GetPrivateProfileString(strSection,strKeyName,_T(""),temp,MAX_PATH,strPathFile);
	strKeyValue.Format(_T("%s"),temp);
	strKeyValue.Trim();
}

void CCommonAPI::SetIniKeyValue( CString strSection,CString strKeyName,CString strKeyValue,CString strPathFile)
{
	strPathFile.Trim();
	if (strPathFile.IsEmpty())
	{
		return;
	}

	strKeyValue.Trim();
	WritePrivateProfileString(strSection,strKeyName,strKeyValue,strPathFile);
}

void CCommonAPI::WriteLocalLogData(const char * strFilePath,const char * strContent,BOOL bEnter /*= FALSE*/)
{
	ASSERT(0 != strcmp(strFilePath,""));

	FILE *fp;
	if((fp=fopen(strFilePath,"a"))!=NULL)
	{
		CString strTime = COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M"));
	
		char szTime[MAX_PATH] = {0};

#ifdef _UNICODE
		WCharToMByte(strTime,szTime,sizeof(szTime)/sizeof(szTime[0]));
#else
		strncpy_s(szTime,(LPSTR)(LPCTSTR)strTime, sizeof(szTime) - 1);
#endif // _UNICODE

		fprintf(fp,"Time : %s \n %s\n",szTime,strContent);
		if (bEnter)
		{
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
}

CString CCommonAPI::GetWorkPath()
{
	TCHAR szPath[MAX_PATH];
	CString strAppFilePath;	//文件全路径

	GetModuleFileName(NULL, szPath, MAX_PATH);  //获取到完整路径 eg：E:\Tools\qq.exe
	strAppFilePath = szPath;

	CString strRet = strAppFilePath.Left(strAppFilePath.ReverseFind('\\'));
	return strRet;
}

BOOL CCommonAPI::WCharToMByte( LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize )
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return TRUE;
}

BOOL CCommonAPI::MByteToWChar( LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize )
{
	// Get the required size of the buffer that receives the Unicode
	// string.
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);

	if(dwSize < dwMinSize)
	{
		return FALSE;
	}

	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize); 
	return TRUE;
}
void CCommonAPI::SetCboselByNameAssociateMatch(CComboBox *pCbo,CString strName,BOOL bMatchUpperLower/*=TRUE*/)
{
	ASSERT(pCbo != NULL);

	strName.Trim();

	int nSel = -1;
	if (strName.IsEmpty())
	{
		pCbo->SetCurSel(nSel);
	}
	else
	{
		BOOL bMatch = FALSE;
		int nCount = pCbo->GetCount();
		CString strTmp = _T("");
		for (int i=0;i<nCount;i++)
		{
			pCbo->GetLBText(i,strTmp);
			if (strTmp == strName)
			{
				nSel = i;
				bMatch = TRUE;

				break;
			}
		}

		if (bMatch)
		{
			pCbo->SetCurSel(nSel);

			return;
		}
		

		if (!bMatchUpperLower)
		{
			strName.MakeUpper();
			int nCount = pCbo->GetCount();
			CString strTmp = _T("");
			for (int i=0;i<nCount;i++)
			{
				pCbo->GetLBText(i,strTmp);
				strTmp.MakeUpper(); 
				if (-1 != strTmp.Find(strName))
				{
					nSel = i;
					pCbo->SetCurSel(nSel);
					
					return;
				}
			}	
		}
		else
		{
			int nCount = pCbo->GetCount();
			CString strTmp = _T("");
			for (int i=0;i<nCount;i++)
			{
				pCbo->GetLBText(i,strTmp);
				if (-1 != strTmp.Find(strName))
				{
					nSel = i;
					pCbo->SetCurSel(nSel);

					return;
				}
			}	
		}
	}

	pCbo->SetCurSel(nSel);
}

void CCommonAPI::SetCboselByName( CComboBox *pCbo,CString strName,BOOL bMatchUpperLower/*=TRUE*/ )
{
	ASSERT(pCbo != NULL);

	strName.Trim();
/*  不根据风格设置显示字符 wangzl 2017-09-06
	DWORD dwStyle = pCbo->GetStyle();
	if(CBS_DROPDOWNLIST == (dwStyle &  CBS_DROPDOWNLIST))//2017/08/10 zhangt 根据风格设置显示字符
	{*/
		int nSel = -1;
		if (strName.IsEmpty())
		{
			pCbo->SetCurSel(nSel);
		}
		else
		{
			BOOL bMatch = FALSE;
			int nCount = pCbo->GetCount();
			CString strTmp = _T("");
			for (int i=0;i<nCount;i++)
			{
				pCbo->GetLBText(i,strTmp);
				if (strTmp == strName)
				{
					nSel = i;
					bMatch = TRUE;

					break;
				}
			}

			pCbo->SetCurSel(nSel);
			
			if (!bMatchUpperLower
				&&!bMatch)
			{
				strName.MakeUpper();
				int nCount = pCbo->GetCount();
				CString strTmp = _T("");
				for (int i=0;i<nCount;i++)
				{
					pCbo->GetLBText(i,strTmp);
					strTmp.MakeUpper(); 
					if (strTmp == strName)
					{
						nSel = i;
						break;
					}
				}

				pCbo->SetCurSel(nSel);
			}
			
		}
	/*}
	else
	{
		pCbo->SetWindowText(strName);
	}*/
}

void CCommonAPI::SetCtrlString( _In_ HWND hDlg,_In_ int nID, _In_z_ _FormatMessage_format_string_ LPCTSTR pszFormat,... )
{
	CString strContent = _T("");
	va_list argList;
	va_start( argList, pszFormat );
	strContent.FormatV(pszFormat,argList);

	va_end( argList );

	::SetDlgItemText(hDlg,nID,strContent);

}

CString CCommonAPI::ConvertChineseUnicodeToPyt(wchar_t* chrstr)
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

CString CCommonAPI::ConvertChineseToShorthand(wchar_t* chrstr)
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

COleDateTime CCommonAPI::CString2OleDateTime( CString strValue )
{
	if (strValue.IsEmpty())
	{
		return COleDateTime::GetCurrentTime();
	}

	CString strYear,strMonth,strDay,strHour,strMin,strSec;
	strYear = strValue.Mid(0,4);	//截取 年
	strMonth = strValue.Mid(5,2);	//截取 月
	strDay = strValue.Mid(8,2);		//截取 日
	if(strValue.GetLength()>10)
	{
		strHour = strValue.Mid(11,2);	//截取 时
		strMin = strValue.Mid(14,2);	//截取 分
		strSec = strValue.Mid(17,2);	//截取 秒
	}
	else
	{
		strHour = _T("0");
		strMin = _T("0");
		strSec = _T("0");
	}

	COleDateTime TValue(_ttoi(strYear),_ttoi(strMonth),_ttoi(strDay),_ttoi(strHour),_ttoi(strMin),_ttoi(strSec));

	return TValue;
}

void CCommonAPI::GetClipboard(CString &strGet)
{
	strGet.Empty();
	if (OpenClipboard(NULL))//打开剪贴板  
	{  
		if (IsClipboardFormatAvailable(CF_TEXT))//判断格式是否是我们所需要  
		{  
			HANDLE hClip;  
			char* pBuf;  

			//读取数据  
			hClip=GetClipboardData(CF_TEXT);  
			pBuf=(char*)GlobalLock(hClip);  
			GlobalUnlock(hClip);  
			//SetDlgItemText(IDC_EDIT_RECV,pBuf);//讲数据显示在IDC_EDIT_RECV中 
			wchar_t wBuf[MAX_PATH];
			BOOL bRet = MByteToWChar(pBuf,wBuf,MAX_PATH);
			if (bRet)
			{
				strGet = wBuf;
			}

			CloseClipboard();  
		}  
	}  
}
void CCommonAPI::SetClipboard( CString strClicpboardText )
{
	//2017/11//18 zhangt 修复：复制中文字符串出现丢失
#ifdef _UNICODE
	if(!strClicpboardText.IsEmpty())
	{
		int nLength = strClicpboardText.GetLength();
		int nBytes = WideCharToMultiByte(CP_ACP,0,strClicpboardText,nLength,NULL,0,NULL,NULL);
		char* pTemp = new char[ nBytes + 1];
		memset(pTemp,0,nLength + 1);
		WideCharToMultiByte(CP_OEMCP, 0, strClicpboardText, nLength, pTemp, nBytes, NULL, NULL); 

		if( OpenClipboard(NULL) )
		{
			EmptyClipboard();
			HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, nBytes + 1);
			char* buffer = (char*)GlobalLock(clipbuffer);
			memset(buffer,0,nBytes + 1);
			memcpy(buffer,pTemp,nBytes + 1);
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_TEXT,clipbuffer);
			CloseClipboard();
		}
		delete[] pTemp;
	}else
   {//复制空的字符串，清空原有的 yangjr 2018/1/31
      if( OpenClipboard(NULL) )
      {
         EmptyClipboard();
         HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, 1);
         char* buffer = (char*)GlobalLock(clipbuffer);
         memset(buffer,0,1);         
         GlobalUnlock(clipbuffer);
         SetClipboardData(CF_TEXT,clipbuffer);
         CloseClipboard();
      }
   }
#else
	// Write to shared file (REMEBER: CF_TEXT is ANSI, not UNICODE, so we need to convert)
	CSharedFile sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
	USES_CONVERSION;
	sf.Write(T2A(strClicpboardText.GetBuffer(1)), strClicpboardText.GetLength());
	strClicpboardText.ReleaseBuffer();

	char c = '\0';
	sf.Write(&c, 1);

	DWORD dwLen = (DWORD) sf.GetLength();
	HGLOBAL hMem = sf.Detach();
	if (!hMem)
		return ;

	hMem = ::GlobalReAlloc(hMem, dwLen, GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
	if (!hMem)
		return ;

	COleDataSource* pSource = new COleDataSource();
	pSource->CacheGlobalData(CF_TEXT, hMem);
	if (!pSource)
		return;

	pSource->SetClipboard();
#endif // _UNICODE
	
}

BOOL CCommonAPI::SaveClipboardToBmp(const CString & strFilePath)
{
   BOOL bRet = FALSE;
   if(!OpenClipboard(NULL))
   {
      return bRet;
   }
   if(::IsClipboardFormatAvailable(CF_BITMAP))
   {
      //是图片的格式      获取图片并保存成文件

      HANDLE   hBitmap   =   ::GetClipboardData(CF_BITMAP);
      HDC   hDC   =   ::GetDC(NULL);//获取设备环境句柄
      HDC   hdcMem   =   CreateCompatibleDC(hDC);//创建与设备相关的内存环境
      SelectObject(hdcMem,   hBitmap);   //选择对象
      SetMapMode(hdcMem,   GetMapMode(hDC));//设置映射模式
      BITMAP   bm;   //   得到位图对象   
      GetObject(hBitmap,   sizeof(BITMAP),   &bm);  

      bRet = SaveBitmap(bm,hDC,(HBITMAP)hBitmap,strFilePath);
      ::ReleaseDC(NULL,hDC);//释放设备环境句柄
      DeleteDC(hdcMem);   //   删除内存环境
   }
   CloseClipboard();

   return bRet;
}

BOOL CCommonAPI::SaveClipboardBmpToBuf(std::vector<BYTE> *pvecBuf, int *pnWidth, int *pnHeight)
{
   if (!pvecBuf)
      return FALSE;
   BOOL bRet = FALSE;
   if(!OpenClipboard(NULL))
   {
      return bRet;
   }
   if(::IsClipboardFormatAvailable(CF_BITMAP))
   {
      //是图片的格式      获取图片并保存成文件

      HANDLE   hBitmap   =   ::GetClipboardData(CF_BITMAP);
      HDC   hDC   =   ::GetDC(NULL);//获取设备环境句柄
      HDC   hdcMem   =   CreateCompatibleDC(hDC);//创建与设备相关的内存环境
      SelectObject(hdcMem,   hBitmap);   //选择对象
      SetMapMode(hdcMem,   GetMapMode(hDC));//设置映射模式
      BITMAP   bm;   //   得到位图对象   
      GetObject(hBitmap,   sizeof(BITMAP),   &bm);  
      if (pnWidth)
         *pnWidth = bm.bmWidth;
      if (pnHeight)
         *pnHeight = bm.bmHeight;
      bRet = SaveBitmapToBuf(bm,hDC,(HBITMAP)hBitmap,pvecBuf);
      ::ReleaseDC(NULL,hDC);//释放设备环境句柄
      DeleteDC(hdcMem);   //   删除内存环境
   }
   CloseClipboard();

   return bRet;
}

std::set<CString> CCommonAPI::SplitStrToSet(const CString &strOrg, const TCHAR *delim,BOOL bWithSpot/* = TRUE*/)
{
   std::vector<TCHAR> vecProcessTCHAR(strOrg.GetLength() + 1);

   memcpy(vecProcessTCHAR.data(), (LPCTSTR)strOrg, strOrg.GetLength() * sizeof(TCHAR));
   TCHAR *pTUploadChar = ::_tcstok(vecProcessTCHAR.data(), delim);

   std::set<CString> setResultString;

   while(pTUploadChar != NULL)
   {
      CString strExt = _T("");

      if (bWithSpot)
      {
         strExt = CString(_T(".")) + pTUploadChar;
      }
      else
      {
         strExt =pTUploadChar;
      }

      setResultString.insert(strExt.MakeUpper());
      pTUploadChar = ::_tcstok(NULL, delim);
   }
   return setResultString;
}

BOOL CCommonAPI::IsFloatEqual(float f1,float f2)
{
#define Epsilon	0.000001

	return fabs(f1 - f2) <= Epsilon;  
	
#undef Epsilon
}

bool CCommonAPI::IsOsVersionVistaOrGreater()
{  
   OSVERSIONINFOEX    ovex;  
   CHAR  szVersionInfo[1024];  
   *szVersionInfo = '\x00';  
   //设置参数的大小，调用并判断是否成功  
   ovex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);  
   if( !GetVersionEx(  (LPOSVERSIONINFO) (&ovex)  )  )  
   {  
      printf("检查系统版本失败\n");  
      return false;  
   }  
   //通过版本号，判断是否是vista及之后版本  
   if(ovex.dwMajorVersion > 5)  
   {  
      return true;   
   }  
   else  
   {  
      return false;  
   }  
}  

bool CCommonAPI::ShellExecuteExOpen(CString appName, CString appPath)
{
   bool bRet = true;
   if(IsOsVersionVistaOrGreater())  
   {  
      SHELLEXECUTEINFO sei={sizeof(SHELLEXECUTEINFO)};  
      sei.fMask  = SEE_MASK_NOCLOSEPROCESS;  
      sei.lpVerb = TEXT("runas");  
      sei.lpFile = appName;  
      sei.lpDirectory = appPath;  
      sei.nShow = SW_SHOWNORMAL;  
      if(!ShellExecuteEx(&sei))  
      {  
         DWORD dwStatus=GetLastError();
         if(dwStatus==ERROR_CANCELLED)
         {  
            TRACE(L"提升权限被用户拒绝\n");
            bRet = false;
         }  
         else if(dwStatus==ERROR_FILE_NOT_FOUND)
         {  
            TRACE(L"所要执行的文件没有找到\n");
            bRet = false;
         }
      }
   }
   else  
   {
      appPath.Replace(_T("\\"),_T("\\\\"));
      HINSTANCE n=ShellExecute(NULL, _T("open"), appName, NULL, appPath, SW_SHOWNORMAL);
      if ((int)n < 32)
      {
         LPVOID lpMsgBuf;
         LPVOID lpDisplayBuf;
         DWORD dw = GetLastError(); 

         FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

         // Display the error message and exit the process

         lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
            (lstrlen((LPCTSTR)lpMsgBuf)  + 40) * sizeof(TCHAR)); 
         StringCchPrintf((LPTSTR)lpDisplayBuf, 
            LocalSize(lpDisplayBuf) / sizeof(TCHAR),
            TEXT("错误信息:%d %s"), 
            dw, lpMsgBuf); 
         ::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("错误"), MB_OK); 

         LocalFree(lpMsgBuf);
         LocalFree(lpDisplayBuf);

         bRet = false;
      }
   }

   return bRet;
}

DWORD CCommonAPI::GetDirSize(CString strDirPath)
{
   CString strFilePath;
   DWORD dwDirSize = 0;

   strFilePath += strDirPath;
   strFilePath += _T("\\*.*");

   int ret;
   CFileFind finder;
   BOOL bFind = finder.FindFile(strFilePath);
   ret=0;
   while (bFind)
   {
      bFind = finder.FindNextFile();
      if (!finder.IsDots())
      {
         CString strTempPath = finder.GetFilePath();
         if (!finder.IsDirectory())
         {
            dwDirSize += finder.GetLength();
         }
         else
         {
            dwDirSize += GetDirSize(strTempPath);
         }

      }
   }
   finder.Close();
   return dwDirSize;
}

CString CCommonAPI::GetMaxCommonSubstrFromStr2(CString strSrc1,CString strSrc2)
{
   CString strRet = _T("");
   if (strSrc2.IsEmpty())
   {
      return strRet;
   }

   //对字符串1中的每一个字符从字符串2中进行查找 找到以后找后续的相应子串
   int nSrc1Len = strSrc1.GetLength();
   int nSrc2Len = strSrc2.GetLength();
   for (int nIndex = 0;nIndex < nSrc1Len;)
   {
      int nFindPos = strSrc2.Find(strSrc1[nIndex]);
      if (-1 != nFindPos)
      {
         CString strCacheStr = _T("");
         int nTmpIndex2 = nFindPos;
         for (;nIndex < nSrc1Len && nTmpIndex2 < nSrc2Len;)
         {
            if (strSrc1[nIndex] == strSrc2[nTmpIndex2])
            {
               strCacheStr.AppendChar(strSrc1[nIndex]);
            }
            else
            {
               break;
            }

            nIndex++;
            nTmpIndex2++;
         }
         if (strRet.GetLength() < strCacheStr.GetLength())
         {
            strRet = strCacheStr;
         }
         continue;
      }
      nIndex++;
   }

   return strRet;
}

BOOL  CCommonAPI::SaveBitmap(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,LPCTSTR szFileName)   
{
   int nBitPerPixel = bm.bmBitsPixel;//获得颜色模式
   int nW = bm.bmWidth;
   int nH = bm.bmHeight;
   int nPalItemC=bm.bmPlanes; //调色板项的个数
   int nBmpInfSize=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nPalItemC;//位图信息的大小
   int nDataSize=(nBitPerPixel*nW+31)/32*4*nH;//位图数据的大小
   //初始化位图信息
   BITMAPFILEHEADER bfh = {0};//位图文件头
   bfh.bfOffBits = sizeof(BITMAPFILEHEADER) +  nBmpInfSize;//sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
   bfh.bfSize = bfh.bfOffBits   +   nDataSize;//文件总的大小
   bfh.bfType  = (WORD)0x4d42;//位图标志
   char * p  = new char[nBmpInfSize+nDataSize];//申请内存位图数据空间(包括信息头)
   memset(p,0,nBmpInfSize);//将信息头的数据初始化为0
   LPBITMAPINFOHEADER pBih = (LPBITMAPINFOHEADER)p;//位图信息头
   pBih->biCompression = BI_RGB;
   pBih->biBitCount = nBitPerPixel;//每个图元像素使用的位数
   pBih->biHeight = nH;//高度
   pBih->biWidth = nW;//宽度
   pBih->biPlanes = 1;
   pBih->biSize = sizeof(BITMAPINFOHEADER);
   pBih->biSizeImage = nDataSize;//图像数据大小
   char   *pData=p+nBmpInfSize;
   //DDB转换为DIB
   ::GetDIBits(hDC,hBitmap,0,nH,pData,(LPBITMAPINFO)pBih,DIB_RGB_COLORS);//获取位图数据
   CFile file;
   BOOL bRet = file.Open(szFileName,CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyWrite);
   if (!bRet)
   {
      delete [] p;
      return FALSE;
   }
   file.Write((const char*)&bfh,  sizeof(BITMAPFILEHEADER));//写入位图文件头
   file.Write((const char*)pBih,  nBmpInfSize);//写入位图信息数据
   file.Write((const char*)pData, nDataSize);//写入位图数据
   delete [] p;
   return TRUE;
}

//存个图片到内存
BOOL CCommonAPI::SaveBitmapToBuf(const BITMAP &bm,HDC hDC,HBITMAP hBitmap,std::vector<BYTE> *pvecBuf)
{
   if (!pvecBuf)
      return FALSE;

   int nBitPerPixel = bm.bmBitsPixel;//获得颜色模式
   int nW = bm.bmWidth;
   int nH = bm.bmHeight;
   int nPalItemC=bm.bmPlanes; //调色板项的个数
   int nBmpInfSize=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nPalItemC;//位图信息的大小
   int nDataSize=(nBitPerPixel*nW+31)/32*4*nH;//位图数据的大小
   //初始化位图信息
   BITMAPFILEHEADER bfh = {0};//位图文件头
   bfh.bfOffBits = sizeof(BITMAPFILEHEADER) +  nBmpInfSize;//sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
   bfh.bfSize = bfh.bfOffBits   +   nDataSize;//文件总的大小
   bfh.bfType  = (WORD)0x4d42;//位图标志
   std::vector<char> vecChar;
   vecChar.assign(nBmpInfSize+nDataSize, 0); //申请内存位图数据空间(包括信息头) 将信息头的数据初始化为0
   char * p = vecChar.data();

   LPBITMAPINFOHEADER pBih = (LPBITMAPINFOHEADER)p;//位图信息头
   pBih->biCompression = BI_RGB;
   pBih->biBitCount = nBitPerPixel;//每个图元像素使用的位数
   pBih->biHeight = nH;//高度
   pBih->biWidth = nW;//宽度
   pBih->biPlanes = 1;
   pBih->biSize = sizeof(BITMAPINFOHEADER);
   pBih->biSizeImage = nDataSize;//图像数据大小
   char   *pData=p+nBmpInfSize;
   //DDB转换为DIB
   ::GetDIBits(hDC,hBitmap,0,nH,pData,(LPBITMAPINFO)pBih,DIB_RGB_COLORS);//获取位图数据
   std::vector<BYTE> vecTemp;
   vecTemp.assign(sizeof(BITMAPFILEHEADER) + nBmpInfSize + nDataSize, 0);
   BYTE *pOutput = vecTemp.data();
   memcpy(pOutput, &bfh, sizeof(BITMAPFILEHEADER)); //写入位图文件头
   pOutput += sizeof(BITMAPFILEHEADER);
   memcpy(pOutput, pBih, nBmpInfSize); //写入位图信息数据
   pOutput += nBmpInfSize;
   memcpy(pOutput, pData, nDataSize); //写入位图数据
   pOutput += nDataSize;

   pvecBuf->swap(vecTemp);

   return TRUE;
}

bool CCommonAPI::GetAdapterInfo(int adapterNum, std::string& macOUT)
{
   NCB Ncb;
   memset(&Ncb, 0, sizeof(Ncb));
   Ncb.ncb_command = NCBRESET; // 重置网卡，以便我们可以查询
   Ncb.ncb_lana_num = adapterNum;
   if (Netbios(&Ncb) != NRC_GOODRET)
      return false;

   // 准备取得接口卡的状态块
   memset(&Ncb, sizeof(Ncb), 0);
   Ncb.ncb_command = NCBASTAT;
   Ncb.ncb_lana_num = adapterNum;
   strcpy((char *) Ncb.ncb_callname, "*");
   struct ASTAT
   {
      ADAPTER_STATUS adapt;
      NAME_BUFFER nameBuff[30];
   }adapter;
   memset(&adapter,sizeof(adapter), 0);
   Ncb.ncb_buffer = (unsigned char *)&adapter;
   Ncb.ncb_length = sizeof(adapter);
   if (Netbios(&Ncb) != 0)
      return false;

   char acMAC[32];
   sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
      int (adapter.adapt.adapter_address[0]),
      int (adapter.adapt.adapter_address[1]),
      int (adapter.adapt.adapter_address[2]),
      int (adapter.adapt.adapter_address[3]),
      int (adapter.adapt.adapter_address[4]),
      int (adapter.adapt.adapter_address[5]));
   macOUT = acMAC;
   return true;
}

bool CCommonAPI::GetMacByNetBIOS(CString& strMacOUT)
{
   // 取得网卡列表
   LANA_ENUM adapterList;
   NCB Ncb;
   memset(&Ncb, 0, sizeof(NCB));
   Ncb.ncb_command = NCBENUM;
   Ncb.ncb_buffer = (unsigned char *)&adapterList;
   Ncb.ncb_length = sizeof(adapterList);
   Netbios(&Ncb);

   std::string macOUT = "";
   // 取得MAC
   for (int i = 0; i < adapterList.length; ++i)
   {
      if (GetAdapterInfo(adapterList.lana[i], macOUT))
      {
         CString strText(macOUT.c_str());
         strMacOUT = strText;
         return true;
      }
   }
   return false;
}
