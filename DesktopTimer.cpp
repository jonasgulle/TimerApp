// DesktopTimer.cpp : implementation file
//

#include "stdafx.h"
#include "TimerApp.h"
#include "DesktopTimer.h"

// CDesktopTimer

IMPLEMENT_DYNAMIC(CDesktopTimer, CStatic)

CDesktopTimer::CDesktopTimer(CTimerProps Timer) :
	m_Timer(Timer)
{

}

CDesktopTimer::~CDesktopTimer()
{
}


BEGIN_MESSAGE_MAP(CDesktopTimer, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CDesktopTimer message handlers



BOOL CDesktopTimer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	pDC->SetTextColor(m_Timer.color);
	//pDC->SetBkColor(RGB(255, 255, 255));
	return CStatic::OnEraseBkgnd(pDC);
}


HBRUSH CDesktopTimer::CtlColor(CDC* pDC, UINT nCtlColor)
{
	//pDC->SetTextColor(m_Timer.color);
	/*pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetBkMode(TRANSPARENT);*/
	return static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
}


int CDesktopTimer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	CFont *font = new CFont();
	font->CreateFontIndirect(&m_Timer.font);
	SetFont(font);

	SetTimer(0, 100, NULL);
	m_StartTime = time(0);

	DrawNewTime();

	return 0;
}


void CDesktopTimer::OnTimer(UINT_PTR nIDEvent)
{
	DrawNewTime();
	CStatic::OnTimer(nIDEvent);
}


void CDesktopTimer::OnDestroy()
{
	CStatic::OnDestroy();

	CFont *font = GetFont();
	font->DeleteObject();
	delete font;
}


void CDesktopTimer::DrawNewTime()
{
	time_t Delta = time(0) - m_StartTime;
	time_t TimeLeft = m_Timer.value - Delta;

	if (TimeLeft < 0)
	{
		KillTimer(0);
		DestroyWindow();
		return;
	}

	time_t h, m, s;
	h = TimeLeft / 3600;
	m = (TimeLeft / 60) % 60;
	s = TimeLeft % 60;

	CString TimeStr;
	TimeStr.Format(_T("%02d:%02d:%02d"), h, m, s);
	if (m_OldTimeStr == TimeStr)
		return;

	CClientDC dc(this);
	CFont *Font = GetFont();

	//dc.SetDCBrushColor(m_Timer.color);
	dc.SelectObject(Font);

	/*SetTextColor(dc, m_Timer.color);
	dc.SetTextColor(m_Timer.color);*/

	/*SetBkColor(dc, RGB(0, 0, 0));
	SetBkMode(dc, TRANSPARENT);*/

	CSize sz = dc.GetTextExtent(TimeStr, TimeStr.GetLength());
	SetWindowPos(0, 0, 0, sz.cx, sz.cy, SWP_NOMOVE | SWP_NOZORDER);
	SetWindowText(TimeStr);
	m_OldTimeStr = TimeStr;

	Invalidate();
}


HBRUSH CDesktopTimer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	//pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(m_Timer.color);
	return hbr;
}
