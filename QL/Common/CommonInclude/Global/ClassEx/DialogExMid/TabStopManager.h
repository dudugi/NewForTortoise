#include <afxstr.h>
#include <map>
#include <deque>
#include <functional>
#include <vector>


//Tab键控件焦点跳转（也可以是其他键），通过读取xml来获取配置信息
//author duc
class CTabStopManager
{
public:
   typedef std::deque<int> CtrlID; //控件ID，如果是嵌套在子窗口里的，则前面放的是子窗口ID（可多层）
   class CCtrlInfo //控件跳转信息
   {
   public:
      CtrlID m_NextCtrlID; //下一个将要获取焦点的空间ID
      CString m_sType;      //控件类型，如：QLBCGGrid
      CString m_sCondition; //XML所写的跳出的条件，如表格的"3,2",表示表格选中第三行第二列时，再次按tab键可以使表格失去焦点
      CString m_sOnEnter; //XML所写的跳入事件，如表格的"3,2",就是表格获取焦点时，选中第3行第2列
   };

   //单实例
   static CTabStopManager &Instance();
   
   //读取xml配置信息, 配置信息包括各种窗口的各种键的焦点跳转顺序
   BOOL ReadFile(const CStringA &sPath);
   //获取下一个要获得焦点的控件信息，失败返回Empty
   CtrlID GetNextTabID(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode=VK_TAB);
   //获取指定控件再某个KEY下的跳转信息
   BOOL GetTabInfo(int nTopParentIDD, CtrlID nControlID, WPARAM uKeyCode, CCtrlInfo *pControlInfo);
   //获取指定窗口需要第一个获取焦点的控件ID，失败返回empty
   CtrlID GetFirstID(int nTopParentIDD); 
   //是否要获取最外层窗口（支持多窗口嵌套）（只有版本号3.0以上才支持）
   BOOL IsUseTopWindow(){return m_dVersion >= 3;}
   //设置指定控件类型的焦点跳出后的处理函数
   BOOL SetCheckFunction(const CString &sControlType, 
      std::function<BOOL(HWND hWnd, const CString &sCondition)> function);
   //设置指定控件的焦点跳入后的处理函数
   BOOL SetEnterEventFunction(const CString &sControlType, 
      std::function<BOOL(HWND hWnd, const CString &sCondition)> function);
   //通过调用之前设置好的处理函数来判断当前控件是否可以跳出（也可以用来执行一段处理，比如展开下拉框）
   BOOL CheckCanLeave(const CString &sType, const CString &sCondition, HWND hControlWnd);
   //通过调用之前设置的处理函数来判断当前控件焦点跳入后需要执行的处理
   BOOL DoOnEnter(const CString &sType, const CString &sCondition, HWND hControlWnd);
   //将delim作为分隔符拆分字符串
   static std::vector<CString> SplitStrW(const CString &strOrg, const WCHAR *delim); 
private:
   CTabStopManager(); //构造函数

   //一个窗口（如果支持多层嵌套的话，就是顶层窗口）里面包含的快捷键焦点跳转信息
   class CTabInOneWindow
   {
   public:
      CtrlID m_nFirstFocusID; //窗口初始化时获得焦点的控件ID
      std::map<WPARAM, std::map<CtrlID, CCtrlInfo>> m_mapKey2ID2ID; //快捷键(WPARAM)到原控件ID到目标控件ID的映射
   };
   std::map<int, CTabInOneWindow> m_mapIDD2ID2NextID; //对话框IDD到原控件ID到目标控件ID的映射

   //函数对象集合
   struct CControlFunction
   {
      //控件失去焦点前的判断
      std::function<BOOL(HWND hWnd, const CString &sCondition)> m_funcCheckCanLeave;
      //控件获得焦点时的处理
      std::function<BOOL(HWND hWnd, const CString &sEnter)> m_funcOnEnter;
   };
   std::map<CString, CControlFunction> m_mapTypeToFunction; //控件类型（type）到函数对象的映射
   BOOL m_bHasReadFile; //已读过xml文件标志
   double m_dVersion; //版本号，比如3.1
};