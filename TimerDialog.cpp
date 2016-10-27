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
	, m_TimerName(_T(""))
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
	DDX_Text(pDX, IDC_TIMER_NAME, m_TimerName);
}


BEGIN_MESSAGE_MAP(CTimerDialog, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT_FONT, &CTimerDialog::OnBnClickedSelectFont)
	ON_BN_CLICKED(IDC_SELECT_COLOR, &CTimerDialog::OnBnClickedSelectColor)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COUNT_TYPE, &CTimerDialog::OnCbnSelchangeCountType)
	ON_EN_CHANGE(IDC_TIMER_NAME, &CTimerDialog::OnEnChangeTimerName)
END_MESSAGE_MAP()


// TimerDialog message handlers


BOOL CTimerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TimeUnit.SetCurSel(0);
	m_CountType.SetCurSel(0);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	// The item data represents number of seconds the the time unit.
	m_TimeUnit.SetItemData(0, 60 * 60);		// Hours
	m_TimeUnit.SetItemData(1, 60);			// Minutes
	m_TimeUnit.SetItemData(2, 1);			// Seconds

	CClientDC dc(this);
	memset(&m_TimerFont, 0, sizeof(LOGFONT));
	m_TimerFont.lfHeight = -MulDiv(24, dc.GetDeviceCaps(LOGPIXELSY), 72);
	m_TimerFont.lfQuality = CLEARTYPE_QUALITY;
	_tcscpy_s(m_TimerFont.lfFaceName, LF_FACESIZE, _T("Verdana"));

	UpdateFont(&m_TimerFont);
	UpdateColor(m_FontColor);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTimerDialog::OnBnClickedSelectFont()
{
	UpdateData();

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


void CTimerDialog::OnOK()
{
	UpdateData();

	m_Timer.name = m_TimerName;
	m_Timer.color = m_FontColor;
	m_Timer.font = m_TimerFont;
	m_Timer.type = static_cast<CTimerProps::Type>(m_CountType.GetCurSel());
	// Convert value to seconds
	m_Timer.unit = m_TimeUnit.GetCurSel();
	m_Timer.value = m_TimerValue * m_TimeUnit.GetItemData(m_Timer.unit);

	CDialogEx::OnOK();
}


void CTimerDialog::OnEnChangeTimerName()
{
	CString TimerName;
	GetDlgItemText(IDC_TIMER_NAME, TimerName);
	GetDlgItem(IDOK)->EnableWindow(TimerName.IsEmpty() ? FALSE : TRUE);
}
