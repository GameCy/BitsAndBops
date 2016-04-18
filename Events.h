#pragma once
#include <vector>
#include "delegates.h"

class EventArgs
{
public:
	EventArgs()
		:Data(0), ReturnValue(0) {}

	EventArgs(std::string typeName, void* data)
		: TypeName(typeName), Data(data)
	{
	}

	std::string TypeName;
	void*		Data;
	void*		ReturnValue;
};

typedef std::vector<EventArgs>	EventArgsVec;

class EventDispatcher;

class Event
{
public:
	Event(void);
	Event(Event*);
	~Event(void);

	void Subscribe(Delegate* observer);
	void Unsubscribe(Delegate* observer);

	void Notify(EventArgs args, float delay=0);
	void NotifyNow(EventArgs args);
	EventArgsVec CollectResponses(EventArgs args);

	DelegateList	mSubscribers;

	void SetDispatcher(EventDispatcher* dsp) { dispatcher = dsp; }
	void SetDispatcherMain();
	void ClearDispatcher() { dispatcher = 0; }

private:
	EventDispatcher* dispatcher;
};

class ExpiringEvent : public Event
{
public:
    ExpiringEvent()
    {
        SetDispatcherMain();
    }

    void Start(float duration)
    {
        Notify(EventArgs("ExpireEvent",0), duration);
    }
};

