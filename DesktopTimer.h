#pragma once
#include "TimerProps.h"

// CDesktopTimer

class CDesktopTimer : public CStatic
{
	DECLARE_DYNAMIC(CDesktopTimer)

public:
	CDesktopTimer(CTimerProps Timer);
	virtual ~CDesktopTimer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);

private:
	CTimerProps m_Timer;
	time_t m_StartTime;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
protected:
	void DrawNewTime();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

