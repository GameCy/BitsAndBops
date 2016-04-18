#include "Delegates.h"
#include "Events.h"

NonTypeDelegate::NonTypeDelegate(void (*pfn)(EventArgs&))
		: mpFunc(pfn)
{
}

void NonTypeDelegate::Invoke(EventArgs& args)
{
   mpFunc(args);
}

class Boo
{
public:
	Boo() {}

	void example()
	{
		Boo& ref = *this;
		TypeDelegate<Boo>	proxy( this, &Boo::ProxyHandler);
		EventArgs args("ClickEventArgs", (void*) 0);
		proxy.Invoke(args);
	}

	void ProxyHandler(EventArgs& args) {}
};

