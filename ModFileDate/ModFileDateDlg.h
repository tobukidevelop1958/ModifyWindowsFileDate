
// ModFileDateDlg.h : header file
//

#pragma once


// CModFileDateDlg dialog
class CModFileDateDlg : public CDialogEx
{
// Construction
public:
	CModFileDateDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODFILEDATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CListBox m_List;
	CDateTimeCtrl m_CreateDate;
	CDateTimeCtrl m_CreateTime;
	CDateTimeCtrl m_ModifiedDate;
	CDateTimeCtrl m_ModifiedTime;
	CDateTimeCtrl m_AccessDate;
	CDateTimeCtrl m_AccessTime;
	CString m_File;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton1();
};
