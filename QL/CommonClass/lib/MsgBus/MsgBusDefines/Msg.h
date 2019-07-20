#pragma once

#define type_name(T) typeid(T).name()

class Indentity
{
public:

	template<class THEIRS_ID_TYPE>
	bool Indentify(const THEIRS_ID_TYPE &id){
		if (testType(type_name(THEIRS_ID_TYPE)))
		{
			CIndentity<THEIRS_ID_TYPE> obj;
			obj.SetIdentity(id);
			return Equal(&obj);
		}
		return false;
	}

protected:

	virtual bool Equal(const Indentity* pIndentity) = 0;

	virtual bool testType(const char* pszTypeName) = 0;

};

template <class ID_TYPE>
class CIndentity : public Indentity
{
public:

	typedef typename ID_TYPE id_type;

	ID_TYPE& GetIdentity() {
		return m_tID;
	}

	void SetIdentity(ID_TYPE id) {
		m_tID = id;
	}
private:

	virtual bool Equal(const Indentity* pIndentity) override {
		CIndentity<ID_TYPE>* pTypeIndentity = (CIndentity<ID_TYPE>*)pIndentity;
		if (this->GetIdentity() == pTypeIndentity->GetIdentity())
		{
			return true;
		}
		return false;
	}

	virtual bool testType(const char* pszTypeName) override {
		return (bool)!(strcmp(pszTypeName, type_name(ID_TYPE)));
	}

	ID_TYPE m_tID;
};

class MSGBUS_API IMsg
{
public:

	virtual ~IMsg(){};

	virtual Indentity* GetIndentity() = 0;

	virtual IMsg* Clone() = 0;

	virtual const char* Name() = 0;

	void Send();

	void Post();

	void PostInBackground();
};

template <class T>
class CMsg : public IMsg
{
public:
	virtual ~CMsg(){};

	virtual Indentity* GetIndentity() override{
		return nullptr; 
	}

	virtual IMsg* Clone() override{
		return new T(*(T*)this);
	}

	virtual const char* Name() override{
		return type_name(T);
	}
};

template <class T, typename ID_TYPE>
class CIndentityMsg : public IMsg
{
public:

	virtual ~CIndentityMsg(){};

	typedef typename ID_TYPE id_type;

	virtual Indentity* GetIndentity() {
		return &m_indentity;
	}

	virtual void SendWithIndentity(ID_TYPE id) {
		m_indentity.SetIdentity(id);
		__super::Send();
	}

   virtual void PostWithIndentity(ID_TYPE id) {
      m_indentity.SetIdentity(id);
      __super::Post();
   }

	virtual void PostInBackgroundWithIndentity(ID_TYPE id) {
		m_indentity.SetIdentity(id);
		__super::PostInBackground();
	}

	virtual IMsg* Clone() override{
		return new T(*(T*)this);
	};

	virtual const char* Name() override{
		return type_name(T);
	}

   template<typename SOMETYPE>
   bool Indentify(SOMETYPE &id) {
      return m_indentity.Indentify((id_type)id);
   }
private:

	CIndentity<ID_TYPE>  m_indentity;
};