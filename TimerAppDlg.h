
// TimerAppDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "TimerStore.h"
#include "DesktopTimer.h"

// CTimerAppDlg dialog
class CTimerAppDlg : public CDialog
{
// Construction
public:
	CTimerAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMERAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTimerStore m_Store;
	CList<CDesktopTimer *> m_TimerWindows;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox m_TimerList;
	afx_msg void OnBnClickedNewTimer();
	afx_msg void OnLbnDblclkTimerList();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMoveRight();
	afx_msg void OnSelchangeTimerList();
	void EnableArrows(bool bEnable);
	afx_msg void OnBnClickedMoveDown();
	afx_msg void OnBnClickedMoveUp();
	afx_msg void OnBnClickedMoveLeft();
};
