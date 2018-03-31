
// readDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CreadDlg �Ի���
class CreadDlg : public CDialogEx
{
// ����
public:
	CreadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_READ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnopen();
	int biWidth;  //ͼ���
	int biHeight;  //ͼ���
	int biBitCount; //ͼ�����ͣ�ÿ����λ��
	//RGBQUAD *pColorTable;  //��ɫ��ָ��
	unsigned char *pBmpBuf;  //�洢ͼ������
	int lineByte;         //ͼ������ÿ���ֽ���
	//bool CreadDlg::readBmp(char *bmpName);
	//bool CreadDlg::saveBmp(char *bmpName);
	//void CreadDlg::work();
//ͼ����
	BITMAPFILEHEADER bmpFileHeader;      //λͼ�ļ�ͷ
	BITMAPINFOHEADER bmpInfoHeader;		 //λͼ��Ϣͷ
	RGBQUAD *pColorTable = new RGBQUAD[256];  //��ɫ��ָ��
	unsigned char *pBmpData;             //ͼ������ָ��    
	unsigned char *pNewBmpData;          //�񻯺�ͼ������ָ��
	unsigned char *pTemp, *pTemp1;		 //��ʱָ��	
	int width, height, imgSize;            //ͼ����ߣ�ʵ�ʴ�С,imgSize����Ϊ4�ı���,bmp��ʽ�ļ��ṹ�涨
	bool CreadDlg::readBmp(char* bmpFileName);
	void CreadDlg::Laplacian();
	void CreadDlg::smooth();
	void CreadDlg::writeBmp();
	CEdit m_edShow;
	CString path_before;
	CString path_after;
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnSharp();
	afx_msg void OnBnClickedBtnSmooth();
	BOOL m_sharp;
	BOOL m_smooth;
	CButton m_group_sharp;
	CButton m_group_smooth;
	
	afx_msg void OnBnClickedSharpMiddle();
	afx_msg void OnBnClickedSharpWeak();
};
