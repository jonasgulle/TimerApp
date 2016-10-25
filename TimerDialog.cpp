// TimerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TimerApp.h"
#include "TimerDialog.h"
#include "afxdialogex.h"


// TimerDialog dialog

IMPLEMENT_DYNAMIC(CTimerDialog, CDialogEx)

CTimerDialog::CTimerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
	, m_CountDown(0)
{

}

CTimerDialog::~CTimerDialog()
{
}

void CTimerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_CountDown);
	DDX_Control(pDX, IDC_TIME_UNIT, m_TimeUnit);
}


BEGIN_MESSAGE_MAP(CTimerDialog, CDialogEx)
END_MESSAGE_MAP()


// TimerDialog message handlers


BOOL CTimerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TimeUnit.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
