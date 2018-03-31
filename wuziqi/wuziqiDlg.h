// wuziqiDlg.h : header file
//

#if !defined(AFX_WUZIQIDLG_H__9227B4ED_6A57_409A_8398_423DCE7FF21F__INCLUDED_)
#define AFX_WUZIQIDLG_H__9227B4ED_6A57_409A_8398_423DCE7FF21F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWuziqiDlg dialog

class CWuziqiDlg : public CDialog
{
// Construction
public:
	CWuziqiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWuziqiDlg)
	enum { IDD = IDD_WUZIQI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuziqiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWuziqiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUZIQIDLG_H__9227B4ED_6A57_409A_8398_423DCE7FF21F__INCLUDED_)
