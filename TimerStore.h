#pragma once
#include "TimerProps.h"

class CTimerStore
{
public:
	CTimerStore();
	virtual ~CTimerStore();

	void Save(void);
	void Load(void);

	void AddTimer(CTimerProps Timer);
	CTimerProps *GetTimer(INT_PTR Index) { return &m_Timers.GetAt(Index); }

private:
	CString m_AppPath;
	CArray<CTimerProps> m_Timers;
};
