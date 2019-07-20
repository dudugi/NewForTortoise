#pragma once
#include <functional>
#include <memory>

using namespace std::placeholders;

#define  new_nothrow new(std::nothrow)

namespace MsgBus
{
	enum call_mode
	{
		call_only_on_mainthread,
		call_on_anythread,
	};

	typedef std::function<void(IMsg*)> FUN_UPDATE;

	class MSGBUS_API subscriber_storge : public std::enable_shared_from_this<subscriber_storge>
	{
	public:
		subscriber_storge(FUN_UPDATE &funupdate, const std::string &strMsgName, call_mode mode);

		static void deleteAndRemoveFromBus(subscriber_storge* stock);

		static std::shared_ptr<subscriber_storge> alloc_stock(FUN_UPDATE &funupdate, const std::string &strMsgName, call_mode mode = call_only_on_mainthread);

      static std::shared_ptr<subscriber_storge> alloc_stored_stock(FUN_UPDATE &funupdate, const std::string &strMsgName, call_mode mode = call_only_on_mainthread);

		call_mode getcallmode(){ return _call_mode; };

		FUN_UPDATE& getupdate(){ return _update_fun; };

		std::string& GetName(){ return _msg_name; };


	private:
		FUN_UPDATE _update_fun;

		std::string _msg_name;

		call_mode   _call_mode;
	};

	typedef std::weak_ptr<subscriber_storge> WP_STOCK;
	typedef std::shared_ptr<subscriber_storge> SP_STORGE;

   //typedef stock_callback subscriber_storge;

#define subscribe(fun, msg,...) \
   MsgBus::subscriber_storge::alloc_stored_stock(FUN_UPDATE(fun), type_name(msg), ##__VA_ARGS__)

#define subscribe_ex(fun, msg,obj,...) \
   MsgBus::subscriber_storge::alloc_stored_stock(FUN_UPDATE(std::bind(&fun, obj, _1)), type_name(msg), ##__VA_ARGS__)

#define alloc_subscriber(fun, msg,...) MsgBus::subscriber_storge::alloc_stock(FUN_UPDATE(fun), type_name(msg), ##__VA_ARGS__)

#define alloc_subscriber_ex(fun, msg, obj,...) MsgBus::subscriber_storge::alloc_stock(FUN_UPDATE(std::bind(&fun, obj, _1)), type_name(msg), ##__VA_ARGS__)
}
