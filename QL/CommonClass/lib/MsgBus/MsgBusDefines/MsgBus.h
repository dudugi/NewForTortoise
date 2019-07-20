// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MSGBUS_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MSGBUS_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef MSGBUS_EXPORTS
#define MSGBUS_API __declspec(dllexport)
#else
#define MSGBUS_API __declspec(dllimport)
#endif


#pragma warning( disable: 4251 )
#include "MsgBusDefines/Msg.h"
#include "MsgBusDefines/Stock.h"
#include "MsgBusDefines/Subscriber.h"

namespace MsgBus
{

	MSGBUS_API void Initialize(HINSTANCE hInstance);

	MSGBUS_API void Finalize();

	MSGBUS_API void RegisterSubscriber(WP_STOCK wpStock);
};
