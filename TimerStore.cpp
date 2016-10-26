#include "stdafx.h"
#include "TimerStore.h"


CTimerStore::CTimerStore() :
	m_AppPath('\0', MAX_PATH)
{
	// Get path for each computer, non-user specific and non-roaming data.
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, m_AppPath.GetBuffer())))
	{
		// Append product-specific path
		PathAppend(m_AppPath.GetBuffer(), _T("\\Gulles\\Timer App\\1.0\\"));
	}
}

CTimerStore::~CTimerStore()
{
	Save();
}

void CTimerStore::Save(void)
{
	for (INT_PTR i = 0; i < m_Timers.GetCount(); i++)
	{
		const CTimerProps &t = m_Timers.ElementAt(i);
	}
}

void CTimerStore::Load(void)
{
	CFileFind ff;
	for (BOOL more = ff.FindFile(_T("*.timer")); more; more = ff.FindNextFile())
	{

	}
}

void CTimerStore::AddTimer(CTimerProps Timer)
{
	m_Timers.Add(Timer);
}
