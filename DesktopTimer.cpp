// DesktopTimer.cpp : implementation file
//

#include "stdafx.h"
#include "TimerApp.h"
#include "DesktopTimer.h"


// CDesktopTimer

IMPLEMENT_DYNAMIC(CDesktopTimer, CStatic)

CDesktopTimer::CDesktopTimer()
{

}

CDesktopTimer::~CDesktopTimer()
{
}


BEGIN_MESSAGE_MAP(CDesktopTimer, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CDesktopTimer message handlers




BOOL CDesktopTimer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return CStatic::OnEraseBkgnd(pDC);
}


HBRUSH CDesktopTimer::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
}
