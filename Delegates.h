#pragma once
#include <string>
#include <list>

class EventArgs;

// ------------------------------------------------

class Delegate 
{
public:
      virtual void Invoke(EventArgs& args)=0;
protected:
      Delegate(){}
      virtual ~Delegate(){}
}; 

typedef std::list<Delegate*>	DelegateList;
typedef DelegateList::iterator	DelegateListItr;

// ------------------------------------------------

class NonTypeDelegate : public Delegate  
{
public:
   void Invoke(EventArgs& args);
   NonTypeDelegate(void (*pFunc)(EventArgs&));
   virtual ~NonTypeDelegate(){}
private:
   void (*mpFunc)(EventArgs&);
};

// ------------------------------------------------

template <typename T>
class TypeDelegate : public Delegate  
{
public:
   void Invoke(EventArgs& args);
   TypeDelegate(T *obj, void (T::*pfn)(EventArgs&));
   ~TypeDelegate(){}

private:
   T* mObject;
   void (T::*m_pfn)(EventArgs&);
};

template<typename T>
TypeDelegate<T>::TypeDelegate(T *obj, void (T::*pfn)(EventArgs&))
	: mObject(obj), m_pfn(pfn)
{
}

template<typename T>
void TypeDelegate<T>::Invoke(EventArgs& args)
{
   (mObject->*m_pfn)(args);
}

#define NewDelegate(_CLASS_,_METHOD_)	new TypeDelegate<_CLASS_>(this, &_CLASS_::_METHOD_)
