#include <afxstr.h>
#include <map>
#include <deque>
#include <functional>
#include <vector>


//Tab���ؼ�������ת��Ҳ����������������ͨ����ȡxml����ȡ������Ϣ
//author duc
class CTabStopManager
{
public:
   typedef std::deque<int> CtrlID; //�ؼ�ID�������Ƕ�����Ӵ�����ģ���ǰ��ŵ����Ӵ���ID���ɶ�㣩
   class CCtrlInfo //�ؼ���ת��Ϣ
   {
   public:
      CtrlID m_NextCtrlID; //��һ����Ҫ��ȡ����Ŀռ�ID
      CString m_sType;      //�ؼ����ͣ��磺QLBCGGrid
      CString m_sCondition; //XML��д�������������������"3,2",��ʾ���ѡ�е����еڶ���ʱ���ٴΰ�tab������ʹ���ʧȥ����
      CString m_sOnEnter; //XML��д�������¼��������"3,2",���Ǳ���ȡ����ʱ��ѡ�е�3�е�2��
   };

   //��ʵ��
   static CTabStopManager &Instance();
   
   //��ȡxml������Ϣ, ������Ϣ�������ִ��ڵĸ��ּ��Ľ�����ת˳��
   BOOL ReadFile(const CStringA &sPath);
   //��ȡ��һ��Ҫ��ý���Ŀؼ���Ϣ��ʧ�ܷ���Empty
   CtrlID GetNextTabID(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode=VK_TAB);
   //��ȡָ���ؼ���ĳ��KEY�µ���ת��Ϣ
   BOOL GetTabInfo(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode, CCtrlInfo *pControlInfo);
   //��ȡָ��������Ҫ��һ����ȡ����Ŀؼ�ID��ʧ�ܷ���empty
   CtrlID GetFirstID(int nTopParentIDD); 
   //�Ƿ�Ҫ��ȡ����㴰�ڣ�֧�ֶര��Ƕ�ף���ֻ�а汾��3.0���ϲ�֧�֣�
   BOOL IsUseTopWindow(){return m_dVersion >= 3;}
   //����ָ���ؼ����͵Ľ���������Ĵ�����
   BOOL SetCheckFunction(const CString &sControlType, 
      std::function<BOOL(HWND hWnd, const CString &sCondition)> function);
   //����ָ���ؼ��Ľ��������Ĵ�����
   BOOL SetEnterEventFunction(const CString &sControlType, 
      std::function<BOOL(HWND hWnd, const CString &sCondition)> function);
   //ͨ������֮ǰ���úõĴ��������жϵ�ǰ�ؼ��Ƿ����������Ҳ��������ִ��һ�δ�������չ��������
   BOOL CheckCanLeave(const CString &sType, const CString &sCondition, HWND hControlWnd);
   //ͨ������֮ǰ���õĴ��������жϵ�ǰ�ؼ������������Ҫִ�еĴ���
   BOOL DoOnEnter(const CString &sType, const CString &sCondition, HWND hControlWnd);
   //��delim��Ϊ�ָ�������ַ���
   static std::vector<CString> SplitStrW(const CString &strOrg, const WCHAR *delim); 
private:
   CTabStopManager(); //���캯��

   //һ�����ڣ����֧�ֶ��Ƕ�׵Ļ������Ƕ��㴰�ڣ���������Ŀ�ݼ�������ת��Ϣ
   class CTabInOneWindow
   {
   public:
      CtrlID m_nFirstFocusID; //���ڳ�ʼ��ʱ��ý���Ŀؼ�ID
      std::map<WPARAM, std::map<CtrlID, CCtrlInfo>> m_mapKey2ID2ID; //��ݼ�(WPARAM)��ԭ�ؼ�ID��Ŀ��ؼ�ID��ӳ��
   };
   std::map<int, CTabInOneWindow> m_mapIDD2ID2NextID; //�Ի���IDD��ԭ�ؼ�ID��Ŀ��ؼ�ID��ӳ��

   //�������󼯺�
   struct CControlFunction
   {
      //�ؼ�ʧȥ����ǰ���ж�
      std::function<BOOL(HWND hWnd, const CString &sCondition)> m_funcCheckCanLeave;
      //�ؼ���ý���ʱ�Ĵ���
      std::function<BOOL(HWND hWnd, const CString &sEnter)> m_funcOnEnter;
   };
   std::map<CString, CControlFunction> m_mapTypeToFunction; //�ؼ����ͣ�type�������������ӳ��
   BOOL m_bHasReadFile; //�Ѷ���xml�ļ���־
   double m_dVersion; //�汾�ţ�����3.1
};