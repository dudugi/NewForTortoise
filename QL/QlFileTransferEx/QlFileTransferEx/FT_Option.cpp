#include "StdAfx.h"
#include "FT_Option.h"
#include "FileTransData.h"
#include <utility>

FileTransCode vsetopt(struct FileTrans_easy *pData, FileTransOption option, va_list param)
{
  FileTransCode result = FILETRANS_OK;

  switch(option) {
  case FTOPT_ORDER:
     {
        pData->strOrderNo.FormatV(_T("%s"),param);
     }
     break;
  case FTOPT_HWND:
     {
        pData->hProcessWnd = va_arg(param,HWND);
     }
     break;
  case FTOPT_ACTION:
     {
        pData->nAction = va_arg(param,FILETRANSACTION);
     }
     break;
  case FTOPT_ACTION_KEY:
     {
        CString strArg;
        strArg.FormatV(_T("%s"),param);
        if (strArg.IsEmpty())
        {
           return FILETRANS_WRONG_BAD_FUNCTION_ARGUMENT;
        }
        pData->strAction_ParamKey = strArg;
     }
     break;
  case FTOPT_SIZE:
     {
        pData->strSize.FormatV(_T("%s"),param);
     }
     break;
  case FTOPT_VERSION:
     {
        pData->nVersion = va_arg(param,int);
     }
     break;
  case FTOPT_FLAG:
     {
        pData->nFlag = va_arg(param,int);
     }
     break;
  case FTOPT_DELSRC:
     {
        pData->bDelSrcFile = va_arg(param,bool);
     }
     break;
  case FTOPT_TRAVERSINGDIR:
     {
        pData->bTraversingDir = va_arg(param,bool);
     }
     break;
  case FTOPT_STYLE:
     {
        pData->dwStyle = va_arg(param,DWORD);
     }
     break;
  case FTOPT_DST_ORDER:
     {
        pData->strDstOrderNo.FormatV(_T("%s"),param);
     }
     break;
  case FTOPT_DST_ACTION_KEY:
     {
        pData->strDstAction_ParamKey.FormatV(_T("%s"),param);
     }
     break;
  case FTOPT_DST_SIZE:
     {
        pData->strDstSize.FormatV(_T("%s"),param);
     }
     break;
  case FTOPT_DST_VERSION:
     {
        pData->nDstVersion = va_arg(param,int);
     }
     break;
  case FTOPT_VEC_ONEPARAM:
     {
        pData->vec_ActParam_OneParam = va_arg(param,vector<CString>);
     }
     break;
  case FTOPT_VEC_TWOPARAM:
     {
        typedef pair<CString,CString> PAIR_DEF;
        pData->vec_ActParam_TwoParam = va_arg(param,vector<PAIR_DEF>);
     }
     break;
  case FTOPT_FUNC_UPLOAD:
     {
        pData->funcUpload = va_arg(param,File_trans_upload_callback);
     }
     break;
  case FTOPT_FUNC_DELETE:
     {
         pData->funcDelete = va_arg(param,File_trans_delete_callback);
     }
     break;
  case FTOPT_FUNC_BEFORE_DOWNLOAD:
     {
         pData->funcBeforeDownload = va_arg(param,File_trans_before_download_callback);
     }
     break;
  case FTOPT_FUNC_USER_DATA:
     {
        pData->pUserCallBackData = va_arg(param,void *);
     }
     break;
  default:
    /* unknown tag and its companion, just ignore: */
    result = FILETRANS_WRONG_UNKNOWN_OPTION;
    break;
  }

  return result;
}
