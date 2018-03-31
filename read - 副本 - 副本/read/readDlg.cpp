
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMPINFORMATION, m_edShow);
}

BEGIN_MESSAGE_MAP(CreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNOPEN, &CreadDlg::OnBnClickedBtnopen)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CreadDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_SHARP, &CreadDlg::OnBnClickedBtnSharp)
	ON_BN_CLICKED(IDC_BTN_SMOOTH, &CreadDlg::OnBnClickedBtnSmooth)
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
		CopyFile(BmpName, BmpName2, TRUE);//将图片复制到当前目录下
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
//图像处理的几个函数
/**
* 函数名: readBmp
* 参  数: bmpFileName--指向读入bmp文件的文件名指针
* 功  能: 读入一个bmp文件，获得相应数据
*/
bool CreadDlg::readBmp(char* bmpFileName)
{
	
	FILE *fp = fopen(bmpFileName, "rb");    //以二进制读方式打开指定的图像文件
	if (NULL == fp)
	{
		printf("%s is not exist!", bmpFileName);
		return FALSE;
	}
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);   //读取位图头信息放入bmpFileHeader,注:指针也相应移动
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);   //读取位图信息头放入bmpInfoHeader
	width = bmpInfoHeader.biWidth;							//宽
	height = bmpInfoHeader.biHeight;						//高
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);				//读取颜色表放入pColorTable
	//	int bytePerLine = (bmpInfoHeader.biWidth * bmpInfoHeader.biBitCount + 31) / 32 * 4;
	pBmpData = new unsigned char[imgSize = bmpInfoHeader.biSizeImage];
	pNewBmpData = new unsigned char[imgSize];
	memset(pNewBmpData, (BYTE)255, sizeof(char)*imgSize);		//把新的图像信息用255(白色)填充，平移后没有图像的区域就是白色了
	fread(pBmpData, sizeof(char), bmpInfoHeader.biSizeImage, fp);	//读取图像信息放入pBmpData
	fclose(fp);                //记住要关闭文件
	return TRUE;

}

/**
* 函数名: sharpening
* 功  能: 对图像进行锐化处理
*/
void CreadDlg::Laplacian()
{
	int temp[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 };   //Laplacian 模版
	
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //每行像素所占字节数
	//处理是基于原图的，所以原图的数据不能改变，用pNewBmpData存储改变之后的数据
	memcpy(pNewBmpData, pBmpData, imgSize);   //把原图数据复制给pNewBmpData
	//注意边界点不处理，所以i从1到高度-2，j类似
	double temResult;  //中间结果
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			temResult = (double)(*(pBmpData + (i - 1) * lineByte + j - 1) * temp[0]);
			temResult += (double)(*(pBmpData + (i - 1) * lineByte + j) * temp[1]);
			temResult += (double)(*(pBmpData + (i - 1) * lineByte + j + 1) * temp[2]);
			temResult += (double)(*(pBmpData + (i)* lineByte + j - 1) * temp[3]);
			temResult += (double)(*(pBmpData + (i)* lineByte + j) * temp[4]);
			temResult += (double)(*(pBmpData + (i)* lineByte + j + 1) * temp[5]);
			temResult += (double)(*(pBmpData + (i + 1) * lineByte + j - 1) * temp[6]);
			temResult += (double)(*(pBmpData + (i + 1) * lineByte + j) * temp[7]);
			temResult += (double)(*(pBmpData + (i + 1) * lineByte + j + 1) * temp[8]);
			*(pNewBmpData + i * lineByte + j) = temResult;
		}
	}
}

double tem[9] = { 1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0 };
void CreadDlg::smooth()
{
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //每行像素所占字节数
	//处理是基于原图的，所以原图的数据不能改变，用pNewBmpData存储改变之后的数据
	memcpy(pNewBmpData, pBmpData, imgSize);   //把原图数据复制给pNewBmpData
	double sum;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			sum = 0;    //清零
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j - 1)) * tem[0];   //该点左下角
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j)) * tem[1];		//下
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j + 1)) * tem[2];  //右下
			sum += (double)(*(pBmpData + i * lineByte + j - 1)) * tem[3];  //左
			sum += (double)(*(pBmpData + i * lineByte + j)) * tem[4];  //该点位置
			sum += (double)(*(pBmpData + i * lineByte + j + 1)) * tem[5];  //右
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j - 1)) * tem[6];  //左上
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j)) * tem[7];   //上
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j + 1)) * tem[8];  //右上
			*(pNewBmpData + i * lineByte + j) = (unsigned char)(sum / 16.0);
		}
	}
}
/**
* 函数名: writeBmp
* 功  能: 新建一个bmp文件,把平移后的图像信息写入，生成一个新的bmp
*/
void CreadDlg::writeBmp()
{
	char writeBmpName[] = "after.bmp";
	FILE *fp = fopen(writeBmpName, "wb");   //以二进制写方式打开指定的图像文件
	if (NULL == fp)
	{
		cout << "file not exist!";
		return;
	}
	//写入BMP文件数据
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	fwrite(pNewBmpData, sizeof(char), imgSize, fp);
	fclose(fp);
	//释放内存
	delete[]pColorTable;
	delete[]pNewBmpData;
	delete[]pBmpData;


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
	CopyFile(BmpName, BmpName2, TRUE);//将图片复制到指定目录下
	// TODO:  在此添加控件通知处理程序代码
}


void CreadDlg::OnBnClickedBtnSharp()
{
	char readBmpName[] = "before.bmp";
	readBmp(readBmpName);
		//printf("Bmp file reads faliure");
	Laplacian();
	writeBmp();
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

void CreadDlg::OnBnClickedBtnSmooth()
{
	
	char readBmpName[] = "before.bmp";
	readBmp(readBmpName);
	//printf("Bmp file reads faliure");

	smooth();
	writeBmp();

	path_after = _T("after.bmp");
	HBITMAP  hbitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), path_after, IMAGE_BITMAP, 300, 200, LR_LOADFROMFILE);  //装载位图   
	//显示图片2
	CStatic*  pPic2 = (CStatic*)GetDlgItem(IDC_SHOWAFTER);     //得到picture控件的句柄存入CStatic指针类型的pPic中
	ASSERT(pPic2);
	pPic2->SetBitmap(hbitmap);                                  //将位图加载到图像控件上    
	Invalidate();                                              //重绘窗口
	//提示打开成功
	int nLength = m_edShow.SendMessage(WM_GETTEXTLENGTH);
	m_edShow.SetSel(nLength, nLength);//可以用来控制换行
	m_edShow.ReplaceSel(_T("图片处理成功\n"));//以追加的方式增加文本
	// TODO:  在此添加控件通知处理程序代码
}
