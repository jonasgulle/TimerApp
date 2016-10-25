#pragma once
#include "afxwin.h"


// TimerDialog dialog

class CTimerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTimerDialog)

public:
	CTimerDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimerDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_CountDown;
	CComboBox m_TimeUnit;
	virtual BOOL OnInitDialog();
};
