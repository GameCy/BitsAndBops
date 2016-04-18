#pragma once
#include <list>
#include "Events.h"
#include "s3eThread.h"

using namespace std;

struct Dispatch
{
	float tstamp;
	Event toRaise;
	EventArgs args;
};

typedef list<Dispatch>			DispatchList;
typedef	DispatchList::iterator	DispatchListItr;

class EventDispatcher
{
public:
	EventDispatcher(void);
	~EventDispatcher(void);

	void	Process();

	void	QueueNotify(float delay, Event evt, EventArgs args);

private:
	DispatchList			m_triggers;
	//CRITICAL_SECTION	    _cs;
	s3eThreadLock *_lock; 
	void     CreateLock()	{ if (!_lock)  _lock = s3eThreadLockCreate(); }
	void     DestroyLock()	{ if (_lock)  s3eThreadLockDestroy(_lock); }
	void	Lock()			{ if (_lock)  s3eThreadLockAcquire(_lock, -1); }
	void	Unlock()		{ if (_lock)  s3eThreadLockRelease(_lock); }
};

extern EventDispatcher *gEventDispatcher;
