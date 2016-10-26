#pragma once


// CDesktopTimer

class CDesktopTimer : public CStatic
{
	DECLARE_DYNAMIC(CDesktopTimer)

public:
	CDesktopTimer();
	virtual ~CDesktopTimer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


