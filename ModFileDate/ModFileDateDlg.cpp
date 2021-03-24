
// ModFileDateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModFileDate.h"
#include "ModFileDateDlg.h"
#include "afxdialogex.h"
#include "MyGetFileTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CModFileDateDlg dialog



CModFileDateDlg::CModFileDateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODFILEDATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModFileDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_CreateDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_CreateTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_ModifiedDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_ModifiedTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_AccessDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER6, m_AccessTime);
}

BEGIN_MESSAGE_MAP(CModFileDateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CModFileDateDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CModFileDateDlg message handlers

BOOL CModFileDateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	DragAcceptFiles();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModFileDateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CModFileDateDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CModFileDateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CModFileDateDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	// URL : https://prog-pc.hatenadiary.org/entry/20090521/1242883859
	//
	UINT length = DragQueryFile(hDropInfo, 0, NULL, 0);

	CString csfile;
	DragQueryFile(hDropInfo, 0, csfile.GetBuffer(length + 1), length + 1);
	csfile.ReleaseBuffer();

	// Put File Path in ListBox
	int nIndex;
	int nCount = m_List.GetCount();
	if (nCount > 0) {
		for (nIndex = 0; nIndex < nCount; nIndex++) {
			m_List.DeleteString(nIndex);
		}
	}
	m_List.AddString(csfile);
	m_File = csfile;

	// Get File Create Date & Time
	FILETIME ftC, ftA, ftR, ftl;
	SYSTEMTIME st;

	if (!myGetFileTime((LPCWSTR)csfile,
		&ftC,
		&ftA,
		&ftR)) {
		myDispLastError(_T("Get File Date & Time"));
		return;
	};

	// Display Create Date & Time
	FileTimeToLocalFileTime(&ftC, &ftl);
	FileTimeToSystemTime(&ftl, &st);
	CTime stCreateDate(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	CTime stCreateTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_CreateDate.SetTime(&stCreateDate);
	m_CreateTime.SetTime(&stCreateTime);

	// Display Modified Date & Time
	FileTimeToLocalFileTime(&ftR, &ftl);
	FileTimeToSystemTime(&ftl, &st);
	CTime stModifiedDate(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	CTime stModifiedTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_ModifiedDate.SetTime(&stModifiedDate);
	m_ModifiedTime.SetTime(&stModifiedTime);

	// Display Last Access Date & Time
	FileTimeToLocalFileTime(&ftA, &ftl);
	FileTimeToSystemTime(&ftl, &st);
	CTime stAccessDate(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	CTime stAccessTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_AccessDate.SetTime(&stAccessDate);
	m_AccessTime.SetTime(&stAccessTime);

	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}


void CModFileDateDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	FILETIME ftC, ftA, ftR, ftl;
	SYSTEMTIME stCreateDate, stCreateTime, stModifiedDate, stModifiedTime, stAccessDate, stAccessTime;
	SYSTEMTIME stFileCreateDate, stFileModifiedDate, stFileAccessDate;

	UpdateData(TRUE);

	m_CreateDate.GetTime(&stCreateDate);
	m_CreateTime.GetTime(&stCreateTime);
	m_ModifiedDate.GetTime(&stModifiedDate);
	m_ModifiedTime.GetTime(&stModifiedTime);
	m_AccessDate.GetTime(&stAccessDate);
	m_AccessTime.GetTime(&stAccessTime);

	stFileCreateDate.wYear = stCreateDate.wYear;
	stFileCreateDate.wMonth = stCreateDate.wMonth;
	stFileCreateDate.wDay = stCreateDate.wDay;
	stFileCreateDate.wHour = stCreateTime.wHour;
	stFileCreateDate.wMinute = stCreateTime.wMinute;
	stFileCreateDate.wSecond = stCreateTime.wSecond;
	stFileCreateDate.wDayOfWeek = stCreateDate.wDayOfWeek;
	stFileCreateDate.wMilliseconds = 0;

	stFileModifiedDate.wYear = stModifiedDate.wYear;
	stFileModifiedDate.wMonth = stModifiedDate.wMonth;
	stFileModifiedDate.wDay = stModifiedDate.wDay;
	stFileModifiedDate.wHour = stModifiedTime.wHour;
	stFileModifiedDate.wMinute = stModifiedTime.wMinute;
	stFileModifiedDate.wSecond = stModifiedTime.wSecond;
	stFileModifiedDate.wDayOfWeek = stModifiedDate.wDayOfWeek;
	stFileModifiedDate.wMilliseconds = 0;

	stFileAccessDate.wYear = stAccessDate.wYear;
	stFileAccessDate.wMonth = stAccessDate.wMonth;
	stFileAccessDate.wDay = stAccessDate.wDay;
	stFileAccessDate.wHour = stAccessTime.wHour;
	stFileAccessDate.wMinute = stAccessTime.wMinute;
	stFileAccessDate.wSecond = stAccessTime.wSecond;
	stFileAccessDate.wDayOfWeek = stAccessDate.wDayOfWeek;
	stFileAccessDate.wMilliseconds = 0;

	SystemTimeToFileTime(&stFileCreateDate, &ftl);
	LocalFileTimeToFileTime(&ftl, &ftC);
	SystemTimeToFileTime(&stFileModifiedDate, &ftl);
	LocalFileTimeToFileTime(&ftl, &ftR);
	SystemTimeToFileTime(&stFileAccessDate, &ftl);
	LocalFileTimeToFileTime(&ftl, &ftA);

	// Set File Date & Time
	if (!mySetFileTime((LPCWSTR)m_File,
		&ftC,
		&ftA,
		&ftR)) {
		myDispLastError(_T("Modify File Date & Time"));
		return;
	};

}
