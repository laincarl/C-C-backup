#pragma once


// CTEXT 对话框

class CTEXT : public CDialogEx
{
	DECLARE_DYNAMIC(CTEXT)

public:
	CTEXT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTEXT();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
