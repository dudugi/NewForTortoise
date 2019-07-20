#pragma once
#include "Stock.h"
#include <list>

using namespace MsgBus;
template <class T>
class CSubscriber
{
public:

	CSubscriber() {
		m_spStorge = alloc_subscriber_ex(CSubscriber<T>::Update, T, this);
	}

	virtual void OnEvent(T* pEvent) = 0;

	void Update(IMsg* pArgs) {
		if (Indentify((T*)pArgs)) {
			OnEvent((T*)pArgs);
		}
	}

protected:

	bool Indentify(T *pMsg) {
		return (bool)!(pMsg->GetIndentity());
	}


private:

   SP_STORGE  m_spStorge;
};


template <class T>
class CAsyncSubscriber
{
public:

	virtual void OnAsyncEvent(T* pEvent) = 0;

	SP_STORGE SubscribeAsync()
	{
		return alloc_subscriber_ex(CAsyncSubscriber<T>::Update, T, this, call_on_anythread);
	}

	void Update(IMsg* pArgs) {
		if (Indentify((T*)pArgs)) {
			OnAsyncEvent((T*)pArgs);
		}
	}

protected:

	bool Indentify(T *pMsg) {
		return (bool)!(pMsg->GetIndentity());
	}
};

template <class T>
class CIndentitySubscriber
{
public:
   CIndentitySubscriber() {
      m_spStorge = alloc_subscriber_ex(CIndentitySubscriber<T>::Update, T, this);
	}

	virtual void      OnEvent(T* pEvent)      = 0;

	virtual typename T::id_type   GetIndentity(T* pEvent)/*->decltype(typename T::id_type)*/ = 0;

protected:

	bool Indentify(T *pMsg) {
		Indentity* pIndentity = pMsg->GetIndentity();
		auto id = GetIndentity((T*)pMsg);
		if (pIndentity
			&& pIndentity->Indentify<T::id_type>(id)) {
			return true;
		}
		return false;
	}

	void Update(IMsg* pArgs) {
		if (Indentify((T*)pArgs)) {
			OnEvent((T*)pArgs);
		}
	}

private:

	SP_STORGE  m_spStorge;
};


template <class T>
class CIndentityAsyncSubscriber
{
public:

	virtual void      OnAsyncEvent(T* pEvent) = 0;

	virtual typename T::id_type   GetIndentity(T* pEvent)/*->decltype(typename T::id_type)*/ = 0;

	SP_STORGE SubscribeAsync()
	{
		return alloc_subscriber_ex(CIndentityAsyncSubscriber<T>::Update, T, this, call_on_anythread);
	}

protected:

	bool Indentify(T *pMsg) {
		Indentity* pIndentity = pMsg->GetIndentity();
		auto id = GetIndentity((T*)pMsg);
		if (pIndentity
			&& pIndentity->Indentify<T::id_type>(id)) {
			return true;
      }
      return false;
	}

	void Update(IMsg* pArgs) {
		if (Indentify((T*)pArgs)) {
			OnAsyncEvent((T*)pArgs);
		}
	}
};


#define DECLARE_ASYNC_STOCK_LIST std::list<SP_STORGE> m_listStorge;

#define REG_ASYNC_STOCK(msg_type) \
	m_listStorge.push_back(CAsyncSubscriber<msg_type>::SubscribeAsync());

#define REG_ASYNC_IND_STOCK(msg_type) \
	m_listStorge.push_back(CIndentityAsyncSubscriber<msg_type>::SubscribeAsync());