
// readDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CreadDlg 对话框
class CreadDlg : public CDialogEx
{
// 构造
public:
	CreadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_READ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnopen();
	int biWidth;  //图像宽
	int biHeight;  //图像高
	int biBitCount; //图像类型，每像素位数
	//RGBQUAD *pColorTable;  //颜色表指针
	unsigned char *pBmpBuf;  //存储图像数据
	int lineByte;         //图像数据每行字节数
	//bool CreadDlg::readBmp(char *bmpName);
	//bool CreadDlg::saveBmp(char *bmpName);
	//void CreadDlg::work();
//图像处理
	BITMAPFILEHEADER bmpFileHeader;      //位图文件头
	BITMAPINFOHEADER bmpInfoHeader;		 //位图信息头
	RGBQUAD *pColorTable = new RGBQUAD[256];  //颜色表指针
	unsigned char *pBmpData;             //图像数据指针    
	unsigned char *pNewBmpData;          //锐化后图像数据指针
	unsigned char *pTemp, *pTemp1;		 //临时指针	
	int width, height, imgSize;            //图像宽，高，实际大小,imgSize必须为4的倍数,bmp格式文件结构规定
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
