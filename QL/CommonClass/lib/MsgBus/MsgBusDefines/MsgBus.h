// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MSGBUS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MSGBUS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
