#pragma once
#include "afxwin.h"
#include "TimerProps.h"

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
	int m_TimerValue;
	CComboBox m_TimeUnit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSelectFont();
	void UpdateFont(LOGFONT * font);
	CTimerProps GetTimer() const { return m_Timer; }

private:
	void UpdateFont(CFont &font);
	void UpdateColor(COLORREF color);

private:
	CTimerProps m_Timer;
	CString m_CurrentFont;
	LOGFONT m_TimerFont;
	COLORREF m_FontColor;

public:
	afx_msg void OnBnClickedSelectColor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_CountType;
	afx_msg void OnCbnSelchangeCountType();
	virtual void OnOK();
	CString m_TimerName;
	afx_msg void OnEnChangeTimerName();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
