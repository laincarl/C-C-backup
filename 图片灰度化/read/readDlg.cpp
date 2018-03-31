
// readDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "read.h"
#include "readDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include <fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//定义几个全局的变量
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
int bmpclrused;//实际使用的颜色数
float rx=0.30;
float gx=0.59;
float bx=0.11;
RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//每个像素的位数 


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CreadDlg 对话框



CreadDlg::CreadDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CreadDlg::IDD, pParent)
, m_sharp(FALSE)
, m_smooth(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMPINFORMATION, m_edShow);
	DDX_Radio(pDX, IDC_SHARP_HARD, m_sharp);
	DDX_Control(pDX, IDC_SHARP_HARD, m_group_sharp);
	
}

BEGIN_MESSAGE_MAP(CreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, &CreadDlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CreadDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_SHARP, &CreadDlg::OnBnClickedBtnSharp)

	ON_BN_CLICKED(IDC_SHARP_MIDDLE, &CreadDlg::OnBnClickedSharpMiddle)

END_MESSAGE_MAP()


// CreadDlg 消息处理程序

BOOL CreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_sharp = 0;
	m_smooth = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/**
* 函数名: readBmp
* 参  数: bmpName -- bmp文件名
* 功  能: 读入bmp文件，并获取相应的信息
*/
void CreadDlg::OnBnClickedBtnopen()
{
	CString filter;
	filter = "Bmp  files(*.bmp)|*.bmp|";

	CFileDialog  dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	if (dlg.DoModal())
	{

		CString BmpName2 = _T("before.bmp");
		CString BmpName = dlg.GetPathName();             //得到路径名
		CopyFile(BmpName, BmpName2, FALSE);//将图片复制到当前目录下
		//调整图片大小，保留比例
		//先获取图片的长和宽
		path_before = BmpName;
		//定义变量存储图片信息
		BITMAPINFO *pBmpInfo;       //记录图像细节
		BYTE *pBmpData;             //图像数据
		BITMAPFILEHEADER bmpHeader; //文件头
		BITMAPINFOHEADER bmpInfo;   //信息头
		CFile bmpFile;              //记录打开文件

		//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
		if (!bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
			return;
		if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
			return;
		if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
			return;
		pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
		//为图像数据申请空间
		memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
		DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
		pBmpData = (BYTE*)new char[dataBytes];
		bmpFile.Read(pBmpData, dataBytes);
		bmpFile.Close();
		//根据比例显示图片
		float a = 4 / 3;
		float b = bmpInfo.biWidth / bmpInfo.biHeight;
		int setwidth, setheight;
		if (a >= b)
		{
			setwidth = 280;
			setheight = bmpInfo.biHeight / (bmpInfo.biWidth / 210);

		}
		else
		{
			setheight = 210;
			setwidth = bmpInfo.biWidth / (bmpInfo.biHeight / 210);
		}

		//picture控件显示图片
		HBITMAP  hbitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), BmpName, IMAGE_BITMAP, setwidth, setheight, LR_LOADFROMFILE);  //装载位图   
		//显示图片1
		CStatic*  pPic = (CStatic*)GetDlgItem(IDC_SHOWBEFORE);     //得到picture控件的句柄存入CStatic指针类型的pPic中
		ASSERT(pPic);
		pPic->SetBitmap(hbitmap);                                  //将位图加载到图像控件上    
		//显示图片2
		CStatic*  pPic2 = (CStatic*)GetDlgItem(IDC_SHOWAFTER);     //得到picture控件的句柄存入CStatic指针类型的pPic中
		ASSERT(pPic2);
		pPic2->SetBitmap(hbitmap);                                  //将位图加载到图像控件上    
		Invalidate();                                              //重绘窗口


		//提示打开成功
		int nLength = m_edShow.SendMessage(WM_GETTEXTLENGTH);
		m_edShow.SetSel(nLength, nLength);//可以用来控制换行
		m_edShow.ReplaceSel(_T("图片打开成功\n"));//以追加的方式增加文本
		//显示图片信息
		CString showwidth;
		CString showheight;
		showwidth.Format(TEXT("%d"), setwidth);
		showheight.Format(TEXT("%d"), setheight);
		int nLength2 = m_edShow.SendMessage(WM_GETTEXTLENGTH);
		m_edShow.SetSel(nLength2, nLength2);//可以用来控制换行
		m_edShow.ReplaceSel(_T("图片显示宽度：") + showwidth + _T("\n"));//以追加的方式增加文本
		int nLength3 = m_edShow.SendMessage(WM_GETTEXTLENGTH);
		m_edShow.SetSel(nLength3, nLength3);//可以用来控制换行
		m_edShow.ReplaceSel(_T("图片显示高度：") + showheight + _T("\n"));//以追加的方式增加文本
		// TODO:  在此添加控件通知处理程序代码
	}
}

//readBmp()函数用于读取位图数据
bool CreadDlg::readBmp(char *bmpName)
{

	FILE *fp;//二进制方式打开制定的图像文件
	BITMAPINFOHEADER head;
	int lineByte;
	fp = fopen(bmpName, "rb");
	if (fp == 0)
		return 0;
	//跳过位图的文件头
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head之中

	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//获取图像高，宽，每个像素所占的位数信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	bmpclrused = head.biClrUsed;
	//定义变量，计算图像每行像素所占的字节数
	lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//灰度图像
	if (biBitCount == 8)
	{
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte*bmpHeight];
	//读入数据
	fread(pBmpBuf, 1, lineByte*bmpHeight, fp);
	fclose(fp);
	return 1;
}

//bmp文件的存盘用函数savebmp()
//char *bmpName文件名字及路径
//unsigned char *imgBuf待存盘的文图数据
//int wedth以像素为单位待存盘位图的宽
//int height
//int biBitCount每像素所占的位数
//RGBQUAD *pColorTable颜色表指针
//返回值0为失败，1为成功
bool CreadDlg::saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{
	if (!imgBuf)
		return 0;//位图数据指针为0，则没有数据传入
	int colorTablesize = 0;//颜色表的大小
	if (biBitCount == 8)
		colorTablesize = 1024;//灰度图像颜色表大小为1024
	int lineByte = (width*biBitCount / 8 + 3) / 4 * 4;//每行所占的字节数
	//以二进制方式打开文件
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp的类型
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits是图像文件前三个部分所需要的空间和
	fileHead.bfOffBits = 54 + colorTablesize;
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//如果是灰度图像，有颜色表，需要写入文件
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
	fclose(fp);
	return 1;
}


void CreadDlg::OnBnClickedBtnSave()
{
	CString filter;
	filter = "Bmp  files(*.bmp)|*.bmp|";
	CString path;
	path = "Bmp";
	CString filename;
	filename = "after";
	CFileDialog  dlg(FALSE, path, filename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	dlg.DoModal();
	CString BmpName = _T("after.bmp");
	CString BmpName2 = dlg.GetPathName();             //得到路径名
	CopyFile(BmpName, BmpName2, FALSE);//将图片复制到指定目录下
	// TODO:  在此添加控件通知处理程序代码
}


void CreadDlg::OnBnClickedBtnSharp()
{
	char readBmpName[] = "before.bmp";
	readBmp(readBmpName);
	//printf("Bmp file reads faliure");

	//////////////////////

	BYTE r, g, b;
	int gray;

	//输出图像
	printf("width=%d\nheight=%d\nbiBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
	printf("biclrused=%d\n", bmpclrused);
	//循环变量i，j图像的坐标
	int i, j;
	//每行字节数
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	//将图像数据存盘
	int k;//当图像为彩色图像时，遍历每个像素的三个分量
	//将图像左下角1、4部分置成黑色
	if (biBitCount == 8)//灰度图像
	{
		/*	for(i=0;i<bmpHeight/2;i++)
		for(j=0;j<bmpWidth/2;j++)
		*(pBmpBuf+i*lineByte+j)=0;*/
	}
	else if (biBitCount == 24)
		/*	{
		for(i=0;i<bmpHeight/2;i++)
		for(j=0;j<bmpWidth/2;j++)
		for(k=0;k<3;k++)
		*(pBmpBuf+i*lineByte+j*3+k)=0;
		}*/
		//为24位图时，转换为灰度图像
	{
		for (i = 0; i<bmpHeight; i++)
		for (j = 0; j<bmpWidth; j++)
		{
			b = *(pBmpBuf + i*lineByte + j * 3 + 0);
			g = *(pBmpBuf + i*lineByte + j * 3 + 1);
			r = *(pBmpBuf + i*lineByte + j * 3 + 2);
			//gray=(r+g+b)/3;
			//	gray=100;
			gray = rx*r + gx*g + bx*b;
			*(pBmpBuf + i*lineByte + j * 3 + 0) = (BYTE)gray;
			*(pBmpBuf + i*lineByte + j * 3 + 1) = (BYTE)gray;
			*(pBmpBuf + i*lineByte + j * 3 + 2) = (BYTE)gray;

		}
	}
	//改变灰度图像的颜色表蓝色分量的值
	//256色图像
	if (biBitCount == 8)
	{
		for (i = 0; i<256; i++)
		{
			gray = 0.11*pColorTable[i].rgbBlue + 0.3*pColorTable[i].rgbRed + 0.59*pColorTable[i].rgbGreen;
			pColorTable[i].rgbBlue = (BYTE)gray;
			pColorTable[i].rgbRed = (BYTE)gray;
			pColorTable[i].rgbGreen = (BYTE)gray;
		}
	}
	char writepath[] = "after.bmp";
	saveBmp(writepath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//清除换从去，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;
	path_after = _T("after.bmp");
	//调整图片大小，保留比例
	//先获取图片的长和宽
	//定义变量存储图片信息
	BITMAPINFO *pBmpInfo;       //记录图像细节
	BYTE *pBmpData;             //图像数据
	BITMAPFILEHEADER bmpHeader; //文件头
	BITMAPINFOHEADER bmpInfo;   //信息头
	CFile bmpFile;              //记录打开文件

	//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
	if (!bmpFile.Open(path_after, CFile::modeRead | CFile::typeBinary))
		return;
	if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//为图像数据申请空间
	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData, dataBytes);
	bmpFile.Close();
	//根据比例显示图片
	float a = 4 / 3;
	float c = bmpInfo.biWidth / bmpInfo.biHeight;
	int setwidth, setheight;
	if (a >= c)
	{
		setwidth = 280;
		setheight = bmpInfo.biHeight / (bmpInfo.biWidth / 210);

	}
	else
	{
		setheight = 210;
		setwidth = bmpInfo.biWidth / (bmpInfo.biHeight / 210);
	}

	//picture控件显示图片
	HBITMAP  hbitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path_after, IMAGE_BITMAP, setwidth, setheight, LR_LOADFROMFILE);  //装载位图   
	//显示图片2
	CStatic*  pPic2 = (CStatic*)GetDlgItem(IDC_SHOWAFTER);     //得到picture控件的句柄存入CStatic指针类型的pPic中
	ASSERT(pPic2);
	pPic2->SetBitmap(hbitmap);                                  //将位图加载到图像控件上    
	Invalidate();                                              //重绘窗口
	//提示处理成功
	int nLength = m_edShow.SendMessage(WM_GETTEXTLENGTH);
	m_edShow.SetSel(nLength, nLength);//可以用来控制换行
	m_edShow.ReplaceSel(_T("图片处理成功\n"));//以追加的方式增加文本
	// TODO:  在此添加控件通知处理程序代码


}

void CreadDlg::OnBnClickedSharpMiddle()
{

	rx = 0.33;
	gx = 0.33;
	bx = 0.33;
	UpdateData(true);
	// TODO:  在此添加控件通知处理程序代码
}



