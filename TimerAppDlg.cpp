
// TimerAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerApp.h"
#include "TimerAppDlg.h"
#include "TimerDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickGithubLink(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_GITHUB_LINK, &CAboutDlg::OnNMClickGithubLink)
END_MESSAGE_MAP()


// CTimerAppDlg dialog



CTimerAppDlg::CTimerAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TIMERAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIMER_LIST, m_TimerList);
}

BEGIN_MESSAGE_MAP(CTimerAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTimerAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_NEW_TIMER, &CTimerAppDlg::OnBnClickedNewTimer)
	ON_LBN_DBLCLK(IDC_TIMER_LIST, &CTimerAppDlg::OnLbnDblclkTimerList)
END_MESSAGE_MAP()


// CTimerAppDlg message handlers

BOOL CTimerAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimerAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimerAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CTimerAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimerAppDlg::OnBnClickedOk()
{
	int answer = MessageBox(TEXT("Do you want to exit the application?"), TEXT("Exit?"), MB_YESNO | MB_ICONEXCLAMATION);
	if (answer == IDYES)
		CDialog::OnOK();
}

void CTimerAppDlg::OnBnClickedNewTimer()
{
	CTimerDialog dlg;
	INT_PTR result = dlg.DoModal();

	CDesktopTimer *wnd = new CDesktopTimer();
	wnd->CreateEx(
		WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED,
		_T("STATIC"),
		_T("09:59:12"),
		WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 150, 100),
		GetDesktopWindow(),
		65535
	);

	wnd->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	wnd->SetLayeredWindowAttributes(RGB(255, 255, 255), 255, LWA_COLORKEY | LWA_ALPHA);
	//wnd->ShowWindow(SW_NORMAL);
	//wnd->SetWindowPos(&wndTopMost, 0, 0, 100, 100, )

	if (result == IDOK)
	{
		CTimerProps Timer = dlg.GetTimer();
		m_Store.AddTimer(Timer);
		m_TimerList.AddString(Timer.name);
	}
}

void CAboutDlg::OnNMClickGithubLink(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString url;
	GetDlgItemText(IDC_GITHUB_LINK, url);
	url.Replace(TEXT("<a>"), TEXT(""));
	url.Replace(TEXT("</a>"), TEXT(""));
	::ShellExecute(NULL, NULL, url, NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}


void CTimerAppDlg::OnLbnDblclkTimerList()
{
	int TimerIndex = m_TimerList.GetCurSel();
	CTimerProps *Timer = m_Store.GetTimer(TimerIndex);
	OutputDebugString(Timer->name);
}
