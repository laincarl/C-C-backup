#pragma once


// CTEXT �Ի���

class CTEXT : public CDialogEx
{
	DECLARE_DYNAMIC(CTEXT)

public:
	CTEXT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTEXT();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
