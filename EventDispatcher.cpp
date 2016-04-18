#include ".\EventDispatcher.h"
#include <stdarg.h>
#include <stdio.h>
#include "Timer.h"


EventDispatcher *gEventDispatcher;

EventDispatcher::EventDispatcher(void)
	: _lock(0)
{
    //CreateLock(); // now it runs single thread, just uncomment to make it safe
}

EventDispatcher::~EventDispatcher(void)
{
    DestroyLock();
}

void	EventDispatcher::Process()
{
	if (m_triggers.size()==0)	return;
	float t = gTimerObj->m_Time;
	DispatchList	pending;

	Unlock();
	DispatchListItr itr=m_triggers.begin();
	while(itr!=m_triggers.end())
	{
		if (itr->tstamp<=t)
		{
			pending.push_back(*itr);
			itr = m_triggers.erase(itr);
		}
		else	itr++;
	}
	Lock();

	for( itr = pending.begin(); itr!=pending.end(); ++itr)
	{
		itr->toRaise.NotifyNow(itr->args);
	}
}

void	EventDispatcher::QueueNotify(float delay, Event evt, EventArgs args)
{
	Dispatch		ti;
	ti.tstamp	= gTimerObj->m_Time + delay;
	ti.toRaise = evt;
	ti.args = args;

	Lock();
		m_triggers.push_back(ti);
	Unlock();
}

