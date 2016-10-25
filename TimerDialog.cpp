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
	, m_TimerValue(1)
	, m_CurrentFont(_T(""))
	, m_FontColor(RGB(255, 0, 255))
{

}

CTimerDialog::~CTimerDialog()
{
}

void CTimerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIMER_VALUE, m_TimerValue);
	DDX_Control(pDX, IDC_TIME_UNIT, m_TimeUnit);
	DDX_Text(pDX, IDC_CURRENT_FONT, m_CurrentFont);
	DDX_Control(pDX, IDC_COUNT_TYPE, m_CountType);
}


BEGIN_MESSAGE_MAP(CTimerDialog, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT_FONT, &CTimerDialog::OnBnClickedSelectFont)
	ON_BN_CLICKED(IDC_SELECT_COLOR, &CTimerDialog::OnBnClickedSelectColor)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COUNT_TYPE, &CTimerDialog::OnCbnSelchangeCountType)
END_MESSAGE_MAP()


// TimerDialog message handlers


BOOL CTimerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TimeUnit.SetCurSel(0);
	m_CountType.SetCurSel(0);

	// Show the font dialog with 12 point "Times New Roman" as the default font.
	memset(&m_TimerFont, 0, sizeof(LOGFONT));
	m_TimerFont.lfHeight = -16;
	_tcscpy_s(m_TimerFont.lfFaceName, LF_FACESIZE, _T("Times New Roman"));

	UpdateFont(&m_TimerFont);
	UpdateColor(m_FontColor);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTimerDialog::OnBnClickedSelectFont()
{
	CFontDialog dlg(&m_TimerFont);
	if (dlg.DoModal() == IDOK)
	{
		LOGFONT font;
		dlg.GetCurrentFont(&font);
		UpdateFont(&font);
	}
}


void CTimerDialog::UpdateFont(LOGFONT *font)
{
	CClientDC dc(this);
	m_CurrentFont.Format(
		_T("%s (%d px)"),
		m_TimerFont.lfFaceName,
		MulDiv(-m_TimerFont.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY))
	);
	UpdateData(FALSE);
}


void CTimerDialog::UpdateColor(COLORREF color)
{
	m_FontColor = color;
	Invalidate();
}

void CTimerDialog::OnBnClickedSelectColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		UpdateColor(dlg.GetColor());
	}
}


HBRUSH CTimerDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_CURRENT_COLOR)
	{
		pDC->SetBkColor(m_FontColor);
	}

	return hbr;
}


void CTimerDialog::OnCbnSelchangeCountType()
{
	BOOL bEnable = m_CountType.GetCurSel() == 0;
	GetDlgItem(IDC_TIME_UNIT)->EnableWindow(bEnable);
	GetDlgItem(IDC_TIMER_VALUE)->EnableWindow(bEnable);
}
