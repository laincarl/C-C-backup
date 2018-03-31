// ImageProcessingView.cpp : implementation of the CImageProcessingView class
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

//���ò���ͷ�ļ�
#include "ImageCYDlg.h"
//������ʾֱ��ͼͷ�ļ�
#include "ImageZFTDlg.h"
#include "math.h"

//����ƽ��ͷ�ļ�
#include "ImagePYDlg.h"

//������תͷ�ļ�
#include "ImageXZDlg.h"

//��������ͷ�ļ�
#include "ImageSFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	//{{AFX_MSG_MAP(CImageProcessingView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_SHOW_TWO, OnShowTwo)
	ON_COMMAND(ID_SHOW_HD, OnShowHd)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_LH_2, OnLh2)
	ON_COMMAND(ID_LH_4, OnLh4)
	ON_COMMAND(ID_LH_8, OnLh8)
	ON_COMMAND(ID_LH_16, OnLh16)
	ON_COMMAND(ID_LH_32, OnLh32)
	ON_COMMAND(ID_LH_64, OnLh64)
	ON_COMMAND(ID_CY, OnCy)
	ON_COMMAND(ID_ZFT_YT, OnZftYt)
	ON_COMMAND(ID_DYS_XXJX, OnDysXxjx)
	ON_COMMAND(ID_DYS_XXQB, OnDysXxqb)
	ON_COMMAND(ID_DYS_XXZQ, OnDysXxzq)
	ON_COMMAND(ID_DYS_XXYD, OnDysXxyd)
	ON_COMMAND(ID_DYS_FXXHS, OnDysFxxhs)
	ON_COMMAND(ID_DYS_FXXPF, OnDysFxxpf)
	ON_COMMAND(ID_DYS_YZBH, OnDysYzbh)
	ON_COMMAND(ID_DYS_JHH, OnDysJhh)
	ON_COMMAND(ID_JHBH_PY, OnJhbhPy)
	ON_COMMAND(ID_JHBH_TXXZ, OnJhbhTxxz)
	ON_COMMAND(ID_JHBH_FZ, OnJhbhFz)
	ON_COMMAND(ID_JHBH_DZ, OnJhbhDz)
	ON_COMMAND(ID_JHBH_SF, OnJhbhSf)
	ON_COMMAND(ID_TXZQ_PTPH1, OnTxzqPtph1)
	ON_COMMAND(ID_TXZQ_PTPH2, OnTxzqPtph2)
	ON_COMMAND(ID_TXZQ_GSPH, OnTxzqGsph)
	ON_COMMAND(ID_TXZQ_ZZLB, OnTxzqZzlb)
	ON_COMMAND(ID_RH_Laplacian, OnRHLaplacian)
	ON_COMMAND(ID_RH_Isotropic, OnRHIsotropic)
	ON_COMMAND(ID_RH_Prewitt, OnRHPrewitt)
	ON_COMMAND(ID_RH_Sobel, OnRHSobel)
	ON_COMMAND(ID_RH_GTMB, OnRhGtmb)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView construction/destruction

CImageProcessingView::CImageProcessingView()
{
	// TODO: add construction code here

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView drawing

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (!pDoc) return;  
	if( EntName.Compare(_T("bmp")) == 0 )      //bmp��ʽ  
	{  
		ReadBmp();
		ShowBitmap(pDC,BmpName);               //��ʾͼƬ  
	}  
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView printing

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView diagnostics

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageProcessingView message handlers

/*************************************************************/
/* numPicture������ʾͼƬ����
/* 0-��ʾ�����δ��ͼƬ 1-��ʾһ��ͼƬ 2-��ʾ����ͼƬ�ʹ���
/*************************************************************/
int numPicture = 0;

/*************************************************************/
/* level������ʾ����Ĵ��������ÿ���������и�ֵ�ñ���
/* 0-��ʾ2��ͼƬ 1-��ʾ�Ҷ�ͼƬ 3-��ʾͼƬ����
/* 2 4 8 16 32 64-��ͬ�����ȼ�����ͼƬ
/*************************************************************/ 
int level = 0;    


/*������ʾͼ������ʱ�ĳ�������*/
int flagSF=0;          //ͼ�񼸺α任���ű任
int m_nDrawWidthSF=0;  //ͼ����ʾ������ź�
int	m_nDrawHeightSF=0; //ͼ����ʾ�߶����ź�

//****************��ʾBMP��ʽͼƬ****************//
void CImageProcessingView::ShowBitmap(CDC *pDC, CString BmpName)
{
	//����bitmapָ�� ���ú���LoadImageװ��λͼ
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
		LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		
	/*************************************************************************/
	/* 1.Ҫװ��OEMͼ������˲���ֵΪ0  OBM_ OEMλͼ OIC_OEMͼ�� OCR_OEM���
	/* 2.BmpNameҪװ��ͼƬ���ļ���                  
	/* 3.װ��ͼ������: 
	/*   IMAGE_BITMAP-װ��λͼ IMAGE_CURSOR-װ�ع�� IMAGE_ICON-װ��ͼ��    
	/* 4.ָ��ͼ���������ؿ�Ⱥͳ��� ������Ϊ��λ    
	/* 5.����ѡ��:
	/*   IR_LOADFROMFILE-ָ����lpszNameָ���ļ��м���ͼ��
	/*   IR_DEFAULTSIZE-ָ��ʹ��ͼ��Ĭ�ϴ�С
	/*   LR_CREATEDIBSECTION-��uType����ΪIMAGE_BITMAPʱ,����һ��DIB��
	/**************************************************************************/

	if( m_bitmap.m_hObject )
	{
		m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ
	}
	m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����
	
	//�߽�
	CRect rect;
	GetClientRect(&rect);

	//ͼƬ��ʾ(x,y)��ʼ����
	int m_showX=0;
	int m_showY=0;
	int m_nWindowWidth = rect.right - rect.left;   //����ͻ������
	int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�
		
	//���岢����һ���ڴ��豸����DC
	CDC dcBmp;
	if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC
		return;
	BITMAP m_bmp;                          //��ʱbmpͼƬ����
	m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��
	CBitmap *pbmpOld = NULL;      
	dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����
	
	//ͼƬ��ʾ���ú���stretchBlt
	pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,
		m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
	
	/*******************************************************************************/
	/* BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC, 
	/*                 int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop );
	/* 1.����x��yλͼĿ��������Ͻ�x��y������ֵ      
	/* 2.nWidth��nHeigthλͼĿ����ε��߼���Ⱥ͸߶�      
	/* 3.pSrcDC��ʾԴ�豸CDCָ��                          
	/* 4.xSrc��ySrc��ʾλͼԴ���ε����Ͻǵ�x��y�߼�����ֵ 
	/* 5.dwRop��ʾ��ʾλͼ�Ĺ�դ������ʽ SRCCOPY����ֱ�ӽ�λͼ���Ƶ�Ŀ�껷����            
	/*******************************************************************************/
	
	dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ
	DeleteObject(&m_bitmap);               //ɾ���ڴ��е�λͼ
	dcBmp.DeleteDC();                      //ɾ��CreateCompatibleDC�õ���ͼƬDC


	/**
	 * �����Ϊ������ʾ�ڶ���ͼƬ
	 */

	if(numPicture==2) {
		//��ʾͼƬ����LoadImage
		HBITMAP m_hBitmapChange;
		if(level==0) //��ʾ2��ͼ BmpNameLinԭͼ
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else
		if(level==1) //�Ҷ�ͼƬ BmpNameLin��ʱͼƬ
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����2
		if(level==2)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����4
		if(level==4)  
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����8
		if(level==8)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����16
		if(level==16)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����32
		if(level==32)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else         //����64
		if(level==64)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else if(level==3) //ͼƬ����
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //ͼ������� ���Ա仯
		if(level==101)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //ͼ�񼸺α任
		if(level==200)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}
		else        //ͼ����ǿ
		if(level==400)
		{
			m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
				LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
		}


		if( m_bitmap.m_hObject ) {
			m_bitmap.Detach();            //m_bitmapΪ������λͼ����
		}
		m_bitmap.Attach(m_hBitmapChange);
		//���岢����һ���ڴ��豸����
		CDC dcBmp;
		if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC
			return;
		BITMAP m_bmp;                          //��ʱbmpͼƬ����
		m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

		//ͼƬ��ʾ���ú���StretchBlt 
		if(flagSF==1)
		{
			CString str;
			str.Format("���ų�=%d ��%d ԭͼ��=%d ��=%d",m_nDrawWidthSF,m_nDrawHeightSF,m_nWidth,m_nHeight);
			AfxMessageBox(str);
			flagSF=0;
			//m_nDrawWidthSF���Ŵ˴����������ڲ�ֵ���и�ֵ
			if(m_nDrawWidthSF<650 && m_nDrawHeightSF<650)   
				pDC->StretchBlt(m_nWindowWidth-m_nDrawWidthSF,0,
					m_nDrawWidthSF,m_nDrawHeightSF,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
			else
				pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
					m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  //��ʾ��СΪ640*640
		}
		else {
			//���ͼƬ̫����ʾ��СΪ�̶�640*640 ������ʾԭͼ��С
			if(m_nDrawWidth<650 && m_nDrawHeight<650)
				pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,
					m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
			else
				pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,
					m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY); 
		}
		//�ָ���ʱDC��λͼ
		dcBmp.SelectObject(pbmpOld);           
	}

}


//****************���ļ�****************//
void CImageProcessingView::OnFileOpen() 
{
	//���ָ�ʽ���ļ���bmp gif
    CString filter;  
    filter="�����ļ�(*.bmp,*.jpg,*.gif)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);            
  
    //����ȷ����ť dlg.DoModal() ������ʾ�Ի���  
    if( dlg.DoModal() == IDOK )  
    {  
        BmpName = dlg.GetPathName();     //��ȡ�ļ�·����   ��D:\pic\abc.bmp  
        BmpNameLin = "picture.bmp";      //��ʱ������
		numPicture=1;                    //��ʾһ��ͼƬ
		EntName = dlg.GetFileExt();      //��ȡ�ļ���չ��  
        EntName.MakeLower();             //���ļ���չ��ת��Ϊһ��Сд�ַ�  
        Invalidate();                    //���øú����ͻ����OnDraw�ػ滭ͼ  
    }  	
}

//***************��ȡͼƬ����*************//
bool CImageProcessingView::ReadBmp()
{
	//ͼƬ�����洢���еĶ���
	FILE *fp = fopen(BmpName,"rb");
	if(fp==0)
	{		
		AfxMessageBox("�޷����ļ�!",MB_OK,0);
		return 0; 
	}
	//��ȡ�ļ�ͷ ���BMP��ʽ���õķ���
	fread(&bfh.bfType,sizeof(WORD),1,fp);
	fread(&bfh.bfSize,sizeof(DWORD),1,fp);
	fread(&bfh.bfReserved1,sizeof(WORD),1,fp);
	fread(&bfh.bfReserved2,sizeof(WORD),1,fp);
	fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);
	//ͼ���ļ������ֽ���
	m_nSize = bfh.bfSize;
	//�ж��Ƿ���bmp��ʽͼƬ
	if(bfh.bfType!=0x4d42)   //'BM'
	{
		AfxMessageBox("����BMP��ʽͼƬ!",MB_OK,0);
		return 0;
	}
	//��ȡ��Ϣͷ
	fread(&bih.biSize,sizeof(DWORD),1,fp);
	fread(&bih.biWidth,sizeof(LONG),1,fp);
	fread(&bih.biHeight,sizeof(LONG),1,fp);
	fread(&bih.biPlanes,sizeof(WORD),1,fp);
	fread(&bih.biBitCount,sizeof(WORD),1,fp);
	fread(&bih.biCompression,sizeof(DWORD),1,fp);
	fread(&bih.biSizeImage,sizeof(DWORD),1,fp);
	fread(&bih.biXPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biYPelsPerMeter,sizeof(LONG),1,fp);
	fread(&bih.biClrUsed,sizeof(DWORD),1,fp);
	fread(&bih.biClrImportant,sizeof(DWORD),1,fp);
	if(bih.biSize!=sizeof(bih))
	{
		AfxMessageBox("���ṹ��ռ���ֽ������ִ���");
		return 0;
	}
	//λͼѹ�����ͣ������� 0����ѹ���� 1��BI_RLE8ѹ�����ͣ���2��BI_RLEѹ�����ͣ�֮һ
	if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("λͼ��ѹ��!");
		return 0;
	}
	//��ȡͼ��߿��ÿ��������ռλ��
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //ÿ��������ռλ��
	//����ͼ��ÿ��������ռ���ֽ�����������32�ı�����
	m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;
	//ͼƬ��С ����ϵͳ�Դ����ļ�ͷ BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//������ BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;Ҫ m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//λͼʵ��ʹ�õ���ɫ���е���ɫ�� biClrUsed
	m_nPalette = 0;                       //��ʼ��
	if(bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//����λͼ�ռ� ��СΪλͼ��С m_nImage
	//mallocֻ������4�ֽڵĿռ� ��δ֪��
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fp);
	fclose(fp);
	return true;
}

//****************�����ļ�****************//
bool CImageProcessingView::SaveBmp(LPCSTR lpFileName) //lpFileNameΪλͼ�ļ���
{
	//����bmp��ʽͼƬ дͼƬ���� ֻ����24���ص�ͼƬ ��ͼƬ�޵�ɫ��
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(lpFileName,"wb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//mallocֻ������4�ֽڵĿռ� ��δ֪��
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	return true;
}

//******************�ļ�����*****************//
void CImageProcessingView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CString filter;
	filter="�����ļ�(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";
	//�ص�: 1-�ļ��� 0-�ļ�����
	CFileDialog dlg(0,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);   
	//����ȷ����ť
	if( dlg.DoModal() == IDOK ) {
		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //��ȡ�ļ���·��
		filename = dlg.GetFileTitle();     //��ȡ�ļ���
		int nFilterIndex=dlg.m_ofn.nFilterIndex;
		if( nFilterIndex == 2 )            //���û�ѡ���ļ�������Ϊ".BMP"ʱ
		{
			str = str + ".bmp";	           //�Զ�����չ��.bmp
			SaveBmp(str);                  //����bmpͼƬ ����һ��д��ͼƬ�Ĺ��� 
			AfxMessageBox("ͼƬ����ɹ�",MB_OK,0);
		}
	}
}

//****************��ʾ����ͼƬ****************//
void CImageProcessingView::OnShowTwo() 
{
	//���û�е���ͼƬֱ�ӵ��˫�� ��ʾ����
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ�������ʾ2��ͼƬ!");
		return;
	}
	AfxMessageBox("��ʾ����ͼƬ!",MB_OK,0);
	numPicture = 2;    //ȫ�ֱ��� ��ʾ��ͼ
	level =0;          //level=0˫��
	Invalidate();      //����Invalidate ÿ�����һ��OnDraw��ͼ
}


/********************************************************************************************/
/* ���http://blog.csdn.net/xiakq/article/details/2956902����ϸ�ĻҶ��㷨                   
/* ����24λ��ͼƬ�Ҷ�ʱ,���������㷨:                                                       
/* 1.ƽ��ֵ�㷨 R=G=B=(R+G+B)/3                                                              
/* 2.�����㷨 R=G=B=(R+G+B+128)/4>>2                                                          
/* 3.��Ȩƽ��ֵ�㷨 ���ݹ����������,��ʵ��ȷ�ĻҶȹ�ʽӦ����R=G=B=R*0.299+G*0.587+B0.144   
/*   Ϊ������ٶ�������һ����ȫ���Խ��ܵĽ��ƣ���ʽ�������� R=G=B=(R*3+G*6+B)/10            
/* 4.��ȷ��Ȩƽ��ֵ�㷨 R=G=B=R*0.299+G*0.587+B0.144                                        
/********************************************************************************************/

//**�Ҷ�ͼ����� R=G=B��Ϊ���ߵ�1/3 level=1ʱ�Ҷ�ͼ��**//
void CImageProcessingView::OnShowHd() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ����ܻҶ�ͼƬ!",MB_OK,0);
		return;
	}
	AfxMessageBox("�Ҷ�ͼ��!",MB_OK,0);
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;

	/********************************************************************/
	/* ע�⣺ԭ���������в�������for( i=0; i<m_nWidth*m_nHeight; i++ )  */
	/* �������ͼƬ���һ��û��������һ�����ݣ������ͼ��������   */
	/* ��ͼ���������Ϊm_nImage�������m_nImage/3�Ϳ��Ա�֤�������ض��� */
	/********************************************************************/

	for(int i=0; i < m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		color=(red+green+blue)/3;
		red=color;
		green=color;  
		blue=color;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=1;
	Invalidate();
}


//****************���� �����ȼ�Ϊ2****************//
void CImageProcessingView::OnLh2() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=2!",MB_OK,0);
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//mallocֻ������4�ֽڵĿռ�
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//�ȼ�2����
	for(int i=0; i<m_nImage; i++ ) {
		//24λ��Ϊ��ɫ��Ϊ���ͼ Red Green Blue Ϊ3�ֽ� 
		//�����ȼ�Ϊ2ȡ�м�ֵΪ 64 �� 192
		if(m_pImage[i]<128) { 
			m_pImage[i]=0;
		}
		else if(m_pImage[i]>=128) {
			m_pImage[i]=128;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=2;
	Invalidate();
}

//****************���� �����ȼ�Ϊ4****************//
void CImageProcessingView::OnLh4() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=4!",MB_OK,0);
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//�ȼ�4����
	for(int i=0; i<m_nImage; i++ ) {
		if(m_pImage[i]<64) {
			m_pImage[i]=0;
		}
		else if( (m_pImage[i]>=64) && (m_pImage[i]<128) ) {
			m_pImage[i]=64;
		}
		else if( (m_pImage[i]>=128) && (m_pImage[i]<192) ) {
			m_pImage[i]=128;
		}
		else if(m_pImage[i]>=192) {
			m_pImage[i]=192;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=4;
	Invalidate();
}

//****************���� �����ȼ�Ϊ8****************//
void CImageProcessingView::OnLh8() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=8!",MB_OK,0);
	//����ʱ��ͼƬ ��ȡ�ļ�
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//mallocֻ������4�ֽڵĿռ� ��δ֪��
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//�ȼ�8����
	for(int i=0; i<m_nImage; i++ ) {
		if(m_pImage[i]<32) {
			m_pImage[i]=0;
		}
		else if( (m_pImage[i]>=32) && (m_pImage[i]<64) ) {
			m_pImage[i]=32;
		}
		else if( (m_pImage[i]>=64) && (m_pImage[i]<96) ) {
			m_pImage[i]=64;
		}
		else if( (m_pImage[i]>=96) && (m_pImage[i]<128) ) {
			m_pImage[i]=96;
		}
		else if( (m_pImage[i]>=128) && (m_pImage[i]<160) ) {
			m_pImage[i]=128;
		}
		else if( (m_pImage[i]>=160) && (m_pImage[i]<192) ) {
			m_pImage[i]=160;
		}
		else if( (m_pImage[i]>=192) && (m_pImage[i]<224) ) {
			m_pImage[i]=192;
		}
		else if(m_pImage[i]>=224) {
			m_pImage[i]=224;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=8;
	Invalidate();
}

//****************���� �����ȼ�Ϊ16****************//
void CImageProcessingView::OnLh16() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=16!",MB_OK,0);
	int i,j;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	for( i=0; i<m_nImage; i++ ) {
		j=16;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<16) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-16;
				break;
			}
			else j+=16;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=16;
	Invalidate();
}

//****************���� �����ȼ�Ϊ32****************//
void CImageProcessingView::OnLh32() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=32!",MB_OK,0);
	int i,j;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//�ȼ�32��
	for( i=0; i<m_nImage; i++ )
	{
		j=8;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<8) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-8;
				break;
			}
			else j+=8;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=32;
	Invalidate();
}

//****************���� �����ȼ�Ϊ64****************//
void CImageProcessingView::OnLh64() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ���������!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ȼ�Level=64!",MB_OK,0);
	int i,j;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	m_pImage=(BYTE*)malloc(m_nImage);
	fread(m_pImage,m_nImage,1,fpo);
	//�ȼ�64����
	for( i=0; i<m_nImage; i++ )
	{
		j=4;
		while(j<=256)
		{
			if(m_pImage[i]<j) 
			{
				if(m_pImage[i]<16) 
					m_pImage[i]=0;
				else 
					m_pImage[i]=j-4;
				break;
			}
			else j+=4;
		}
	}
	fwrite(m_pImage,m_nImage,1,fpw);
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=64;
	Invalidate();
}

//****************ͼƬ����****************//
void CImageProcessingView::OnCy() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܲ���!",MB_OK,0);
		return;
	}
	CImageCYDlg dlg;     //��������Ի���
	//��ʾ�Ի���
	if( dlg.DoModal()==IDOK ) {
		//�����������ΪͼƬ����������
		if( dlg.m_xPlace==0 || dlg.m_yPlace==0 ) {
			AfxMessageBox("����ͼƬ���ز���Ϊ0!",MB_OK,0);
			return;
		}
		if( dlg.m_xPlace>m_nWidth || dlg.m_yPlace>m_nHeight ) {
			AfxMessageBox("ͼƬ���ز���Ϊ����ԭͼ����!",MB_OK,0);
			return;
		}
		AfxMessageBox("ͼƬ����!",MB_OK,0);
		//����ʱ��ͼƬ ��ȡ�ļ�
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);
	
		/*ͼƬ����*/
		int numWidth,numHeight;     //ͼƬ������ȡ��ͬ�����ص�
		int numSYWidth,numSYHeight; //ʣ���ڼ����� 

		/*********************************************************/
		/* ��ʾnumWidth*numHeightΪһ������ ��������ɫ��ͬ       */
		/* �� 512/512=1 512/512=1 1*1Ϊһ������                  */
		/* dlg.m_xPlace*dlg.m_yPlace ��ʾ�µģ�x,y������         */
		/* numSYWidth��ʾʣ��ռ� ������ͳһΪһ����ɫ           */
		/*********************************************************/

		numWidth=m_nWidth/dlg.m_xPlace;        
		numHeight=m_nHeight/dlg.m_yPlace;      
		numSYWidth=m_nWidth%dlg.m_xPlace;     
		numSYHeight=m_nHeight%dlg.m_yPlace;   
		int Y,X;
		int i,j,m,n;
		unsigned char red,green,blue;  //�洢������ɫ
	
		/* ��((m_xPlace * m_yPlace)+ ʣ������ )��С���� */
		for( i=0; i<dlg.m_yPlace; i++ )       //�߶�
		{
			Y=numHeight*i;                    //��ȡY����
			for( j=0; j<dlg.m_yPlace; j++ )   //���
			{
				X=numWidth*j;                 //��ȡX����
				/*��ȡ�����ɫ*/
				red=m_pImage[(X+Y*m_nWidth)*3];
				green=m_pImage[(X+Y*m_nWidth)*3+1];
				blue=m_pImage[(X+Y*m_nWidth)*3+2];
				/*���ͼ��ѭ�� С�����еĳ���ѭ��*/
				for( n=0; n<numHeight; n++ )
				{
					for( m=0; m<numWidth*3; )
					{
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=red;
						m++;
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=green;
						m++;
						m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=blue;
						m++;
					}
				}
			}
		}
		fwrite(m_pImage,m_nImage,1,fpw);
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=3;
		Invalidate();
	}
}



/*ȫ�ֱ�����TestZFTDlg.cpp������ ��extern*/
int Red[256],Green[256],Blue[256];

/**************************************************/
/* ���ֱ��ͼ��ʾ���ܣ�����ֱ��ͼ�·���ʾ�����Ϣ 
/* ��ƽ���Ҷȡ���ֵ�Ҷȡ���׼�����������         
/* ID_ZFT_YT:ֱ��ͼԭͼ��ʾ                       
/**************************************************/
void CImageProcessingView::OnZftYt() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�������ʾԭͼֱ��ͼ!",MB_OK,0);
		return;
	}
	AfxMessageBox("��ʾԭͼֱ��ͼ!",MB_OK,0);
	CImageZFTDlg dlg;

	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	
	int i,j;
	for(j=0;j<256;j++) { //�������鲢����
		Red[j]=0;
		Green[j]=0;
		Blue[j]=0;
	}
	
	//����4������
	unsigned char red,green,blue;
	int IntRed,IntGreen,IntBlue;                  //ǿ��ת��
	double sumRedHD=0,sumGreenHD=0,sumBlueHD=0;   //��¼�����ܵĻҶ�ֵ��
	for(i=0; i<m_nImage/3; i++ ) 
	{
		fread(&red,sizeof(char),1,fpo);
		IntRed=int(red);
		sumRedHD=sumRedHD+IntRed;
		if( IntRed>=0 && IntRed<256 ) Red[IntRed]++; //����0-255֮��
		
		fread(&green,sizeof(char),1,fpo);
		IntGreen=int(green);
		sumGreenHD=sumGreenHD+IntGreen;
		if( IntGreen>=0 && IntGreen<256 ) Green[IntGreen]++;
		
		fread(&blue,sizeof(char),1,fpo);
		IntBlue=int(blue);
		sumBlueHD=sumBlueHD+IntBlue;
		if( IntBlue>=0 && IntBlue<256 ) Blue[IntBlue]++;
	}
	fclose(fpo);
	
	//����:int��ת��ΪCString�� 
	dlg.m_redXS.Format("%d",m_nImage);
	dlg.m_greenXS.Format("%d",m_nImage);
	dlg.m_blueXS.Format("%d",m_nImage);
	
	//ƽ���Ҷ�ֵ:����24λbmpͼƬ�ĻҶ�ֵ,���Ǽ�¼RGB�е�����ƽ��ֵ	
	float pinRedHD,pinGreenHD,pinBlueHD; 
	pinRedHD=sumRedHD*3/m_nImage;
	pinGreenHD=sumGreenHD*3/m_nImage;     //ƽ���Ҷ�=�ܻҶ�/������
	pinBlueHD=sumBlueHD*3/m_nImage;
	
	dlg.m_redPJHD.Format("%.2f",pinRedHD);
	dlg.m_greenPJHD.Format("%.2f",pinGreenHD);
	dlg.m_bluePJHD.Format("%.2f",pinBlueHD);
	
	/****************************************************************/
	/* ��ֵ�Ҷ�:�㷨�ص�(�ƿ������ṩ)                              
	/* ��ֵ�Ҷ�:���������е���λ��,Ӧ���������������ҵ��м�ĻҶ�ֵ 
	/* �㷨:num[256]��¼���Ҷȳ��ִ���,sum+=num[i],�ҵ�sum=������/2 
	/****************************************************************/
	int sumRedZZHD=0,sumGreenZZHD=0,sumBlueZZHD=0;
	int redZZHD,greenZZHD,blueZZHD;
	for(i=0;i<256;i++)
	{
		sumRedZZHD=sumRedZZHD+Red[i];
		if(sumRedZZHD>=m_nImage/6)          //m_nImage���ֳ�3��RGB����sum=������/2
		{
			redZZHD=i;
			break;
		}
	}
	for(i=0;i<256;i++)
	{
		sumGreenZZHD=sumGreenZZHD+Green[i];
		if(sumGreenZZHD>=m_nImage/6)          //m_nImage���ֳ�3��RGB����sum=������/2
		{
			greenZZHD=i;
			break;
		}
	}
	for(i=0;i<256;i++)
	{
		sumBlueZZHD=sumBlueZZHD+Blue[i];
		if(sumBlueZZHD>=m_nImage/6)          //m_nImage���ֳ�3��RGB����sum=������/2
		{
			blueZZHD=i;
			break;
		}
	}
	
	dlg.m_redZZHD.Format("%d",redZZHD);
	dlg.m_greenZZHD.Format("%d",greenZZHD);
	dlg.m_blueZZHD.Format("%d",blueZZHD);
	
	/******************************************************************/
	/*��׼��:��׼��=���������ƽ����                                   
	/*       ����s^2=[(x1-x)^2+(x2-x)^2+......(xn-x)^2]/n             
	/* �㷨:���ÿ�m_nImage������м��� ��num[256]��������             
	/* ����=(ƽ���Ҷ�-i)*(ƽ���Ҷ�-i)*Red[i]  ��Red[i]���Ҷ�ֵΪi���� 
	/******************************************************************/
	float redBZC,greenBZC,blueBZC;       //��׼��
	double redFC=0,greenFC=0,blueFC=0;    //����
	for(i=0;i<256;i++)
	{
		redFC=redFC+(pinRedHD-i)*(pinRedHD-i)*Red[i];   //��Red[i]������i
		greenFC=greenFC+(pinGreenHD-i)*(pinGreenHD-i)*Green[i];
		blueFC=blueFC+(pinBlueHD-i)*(pinBlueHD-i)*Blue[i];
	}
	
	redBZC=sqrt(redFC*3/m_nImage);
	greenBZC=sqrt(greenFC*3/m_nImage);
	blueBZC=sqrt(blueFC*3/m_nImage);
	
	dlg.m_redBZC.Format("%.2lf",redBZC);
	dlg.m_greenBZC.Format("%.2lf",greenBZC);
	dlg.m_blueBZC.Format("%.2lf",blueBZC);
	

	//�ص������Ӹ������ܵ����Ի���
	if(dlg.DoModal()==IDOK)
	{

	}
	
}


/**********************************************************************/
/* ͼ������� 4�����Ա仯ֱ��ͼ��                                                
/* ID_DYS_XXYD:��ʾ���ԻҶȱ仯�ƶ� D(B)=D(A)+50  �Ҷ�ֵ��������        
/* ID_DYS_XXZQ:��ʾ���ԻҶȱ仯��ǿ D(B)=1.5*D(A) ͼ��Աȶ���ǿ       
/* ID_DYS_XXJX:��ʾ���ԻҶȱ仯��С D(B)=0.8*D(A) ͼ��Աȶȼ�С       
/* ID_DYS_XXQB:��ʾ���ԻҶ��� D(B)=-1*D(A)+255  ͼ��������,�����䰵 
/**********************************************************************/

// 1.������ ���ԻҶȱ仯�ƶ� D(B)=D(A)+50
void CImageProcessingView::OnDysXxyd() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ��������ԻҶ�����!",MB_OK,0);
		return;
	}
	AfxMessageBox("���ԻҶ�ֱ��ͼ-�Ҷȱ仯�ƶ� D(B)=D(A)+50!",MB_OK,0);
	int i;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red+50 >255 )
			red=255;
		else
			red=(int)red+50;

		if( (int)green+50>255 )
			green=255;
		else
			green=(int)green+50;  

		if( (int)blue+50>255 )
			blue=255;
		else
			blue=(int)blue+50;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}

	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;       //��ֵ101��ShowBitmap�е�����ʾ������ͼƬ
	Invalidate();
}

// 2.������ ���ԻҶȱ仯��ǿ D(B)=1.5*D(A)
void CImageProcessingView::OnDysXxzq() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ��������ԻҶ�����!",MB_OK,0);
		return;
	}
	AfxMessageBox("���ԻҶ�ֱ��ͼ-�Ҷȱ仯��ǿ D(B)=1.5*D(A)!",MB_OK,0);
	int i;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red*1.5 >255 )
			red=255;
		else
			red=(int)red*1.5;

		if( (int)green*1.5>255 )
			green=255;
		else
			green=(int)green*1.5;  
		
		if( (int)blue*1.5>255 )
			blue=255;
		else
			blue=(int)blue*1.5;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;      //���Ա仯 ShowBitmap�е���
	Invalidate();
}

// 3.������ ���ԻҶȱ仯��СD(B)=0.8*D(A)
void CImageProcessingView::OnDysXxjx() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ��������ԻҶȴ���!",MB_OK,0);
		return;
	}
	AfxMessageBox("���ԻҶ�ֱ��ͼ-�Ҷȼ�С D(B)=0.8*D(A)!",MB_OK,0);
	int i;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*0.8;
		green=(int)green*0.8;  
		blue=(int)blue*0.8;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// 4.������ ���ԻҶ��� D(B)=-1*D(A)+255
void CImageProcessingView::OnDysXxqb() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ��������ԻҶȴ���!",MB_OK,0);
		return;
	}
	AfxMessageBox("���ԻҶ�ֱ��ͼ-�Ҷ��� D(B)=-1*D(A)+255!",MB_OK,0);
	int i;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*(-1)+255;
		green=(int)green*(-1)+255;  
		blue=(int)blue*(-1)+255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}




/************************************************************************/
/* 2�ַ����Ա仯ֱ��ͼ��                                                
/* ID_DYS_FXXPF:��ʾ������ƽ���Ҷȱ仯,D(B)=D(A)*D(A)/255                
/* ID_DYS_FXXHS:��ʾ�����Ժ����Ҷȱ仯,D(B)=D(A)+0.8*D(A)*(255-D(A))/255 
/************************************************************************/

// ������ƽ���Ҷȱ仯 D(B)=D(A)*D(A)/252
void CImageProcessingView::OnDysFxxpf() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ����ܷ����ԻҶȴ���!",MB_OK,0);
		return;
	}
	AfxMessageBox("�����ԻҶȱ仯 D(B)=D(A)*D(A)/255!",MB_OK,0);
	int i;
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	//��ȡ�ļ�
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//�Ҷ�ͼ��
	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=(int)red*(int)red/255;
		green=(int)green*(int)green/255;
		blue=(int)blue*(int)blue/255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// �����Ժ����Ҷȱ仯 D(B)=D(A)+0.8*D(A)*(255-D(A))/255
void CImageProcessingView::OnDysFxxhs() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ����ܷ����ԻҶȴ���!",MB_OK,0);
		return;
	}
	AfxMessageBox("���ԻҶ�ֱ��ͼ-�Ҷȱ仯��ǿ D(B)=D(A)+0.8*D(A)*(255-D(A))/255!",MB_OK,0);
	int i;

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);	
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);

	unsigned char color;
	unsigned char red,green,blue;
	for( i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( ((int)red+0.8*(int)red*(255-(int)red)/255) > 255 )
			red=255;
		else
			red=(int)red+0.8*(int)red*(255-(int)red)/255;

		if( ((int)green+0.8*(int)green*(255-(int)green)/255) > 255 )
			green=255;
		else
			green=(int)green+0.8*(int)green*(255-(int)green)/255;  
		
		if( ((int)blue+0.8*(int)blue*(255-(int)blue)/255) > 255 )
			blue=255;
		else
			blue=(int)blue+0.8*(int)blue*(255-(int)blue)/255;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

/**************************************************************/
/* ID_DYS_YZBH:��ʾ��������ֵ�任 Ҳ�����Ҷ�����                   
/* �˴��������ǣ���ֵ��(thresholding)���Կ�����������һ������ 
/* ֻҪ�������е�g1old=g2old��ʵ������ֵ����                  
/* ��ֵ������ż�����������ǰף�����С���Ǻ�,��ֵ            
/**************************************************************/

void CImageProcessingView::OnDysYzbh() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ����ܵ�������ֵ������!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ���������ֵ������!",MB_OK,0);
	//��д�ļ�
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	//����
	unsigned char color;
	unsigned char red,green,blue;
	for(int i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		if( (int)red > 128 )
			red=255;
		else
			red=0;

		if( (int)green > 128 )
			green=255;
		else
			green=0;  
		
		if( (int)blue > 128 )
			blue=255;
		else
			blue=0;

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();
}

// ID_DYS_JHH:��ʾͼ����⻯ ����㷨
void CImageProcessingView::OnDysJhh() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�����ͼ����⻯!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����⻯!",MB_OK,0);

    //��һ��:��ȡͼ���������Ϣ
	//�˲��������ڴ�ͼƬʱ�ͽ��� ��ֱ��ͼ����(ZFTCY)��Ҳ�иô���
	FILE *fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

	int i,j,k;
	for(j=0;j<256;j++) { //�������鲢����
		Red[j]=0;
		Green[j]=0;
		Blue[j]=0;
	}
	
	//����4������
	unsigned char red,green,blue;
	int IntRed,IntGreen,IntBlue;                  //ǿ��ת��
	double sumRedHD=0,sumGreenHD=0,sumBlueHD=0;   //��¼�����ܵĻҶ�ֵ��
	for(i=0; i<m_nImage/3; i++ )
	{
		fread(&red,sizeof(char),1,fpo);
		IntRed=int(red);
		sumRedHD=sumRedHD+IntRed;
		if( IntRed>=0 && IntRed<256 ) Red[IntRed]++;
		
		fread(&green,sizeof(char),1,fpo);
		IntGreen=int(green);
		sumGreenHD=sumGreenHD+IntGreen;
		if( IntGreen>=0 && IntGreen<256 ) Green[IntGreen]++;
		
		fread(&blue,sizeof(char),1,fpo);
		IntBlue=int(blue);
		sumBlueHD=sumBlueHD+IntBlue;
		if( IntBlue>=0 && IntBlue<256 ) Blue[IntBlue]++;
	}
	fclose(fpo);

	/*****************************************************************/
	/* ͼ����⻯����                                                
	/* ����ȫ�ֱ��� Red[256] Blue[256] Green[256]                    
	/* ��һ��:��3������Count..��¼0-255�Ҷȳ��ֵĸ��ʣ���            
	/*        ����=�ûҶȳ��ִ���*3/�ܵ����� (��Ϊ�ֳ�3����RGB)      
	/* �ڶ���:i��1��ʼ����s[i]=s[i]+s[i-1] ��¼�¸�����              
	/* ������:��һ������L��¼�µĵ�ɫ������ֵ����                    
	/*        L[i]=s[i]��(256-1)�����������2.8��Ϊ3                 
	/* ���Ĳ�:���ϵ�����ֵ��Ӧ�ĸ��ʺϲ�����Ϊ��Ӧ���µ�����ֵ�ĸ��� 
	/*   1.ԭ��������ֵ0,1����Ӧ���µ�����ֵ0����Ҷ�����ֵΪ0�ĸ��� 
	/*     ΪP0+P1=0.03                                              
	/*   2.�µ�����ֵ3��7�Ҳ����ϵ�����ֵ��֮��Ӧ��������Q3��Q7Ϊ0   
	/*****************************************************************/

	//��¼���ֵĸ���,��ӵ�1 ������ӵ���ɫ��
	float CountRed[256],CountGreen[256],CountBlue[256];      
	//��¼ԭʼ����,������ӵ�1 ���ڼ����»Ҷȸ���
	float CountRedLin[256],CountGreenLin[256],CountBlueLin[256];   

	for( k=0 ; k<256 ; k++ )
	{
		CountRed[k]=(float)(Red[k])*3/m_nImage;
		CountRedLin[k]=CountRed[k];
		CountGreen[k]=(float)(Green[k])*3/m_nImage;
		CountGreenLin[k]=CountGreen[k];
		CountBlue[k]=(float)(Blue[k])*3/m_nImage;
		CountBlueLin[k]=CountBlue[k];
	}
	
	for( k=1 ; k<256 ; k++ )
	{ 
		CountRed[k]=CountRed[k]+CountRed[k-1];
		CountGreen[k]=CountGreen[k]+CountGreen[k-1];
		CountBlue[k]=CountBlue[k]+CountBlue[k-1];
	}

	/****************************************************/
	/* �˴��ٶȵ�һ���������븡���͵��㷨:              
	/* float a=3.456;   ������С�������λ              
	/* float b=(int)((a * 100) + 0.5) / 100.0;          
	/* output b=3.46                                    
	/****************************************************/

	int LRed[256],LGreen[256],LBlue[256];   //��¼��ɫ��
	for( k=0 ; k<256 ; k++ )
	{
		LRed[k]=(int)(CountRed[k]*(256-1)+0.5);
		LGreen[k]=(int)(CountGreen[k]*(256-1)+0.5);
		LBlue[k]=(int)(CountBlue[k]*(256-1)+0.5);
	}

	//������:������⻯ͼ��д�� ����ʱ��ͼƬ
	fpo = fopen(BmpName,"rb");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

	FILE *fpw = fopen(BmpNameLin,"wb+");
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);

	//m_nWidth*m_nHeight ��ȡͼƬ���һ�в�Ϊm_nWidthʱ�ᱨ�� ��Ϊm_nImage/3
	for( i=0; i<m_nImage/3 ; i++ )
	{	
		fread(&red,sizeof(char),1,fpo);
		fread(&green,sizeof(char),1,fpo);
		fread(&blue,sizeof(char),1,fpo);

		red=LRed[int(red)];
		green=LGreen[int(green)];
		blue=LBlue[int(blue)];

		fwrite(&red,sizeof(char),1,fpw);
		fwrite(&green,sizeof(char),1,fpw);
		fwrite(&blue,sizeof(char),1,fpw);
	}
	fclose(fpw);
	numPicture = 2;
	level=101;
	Invalidate();	
}


/********************************************************/
/* ͼ��ռ伸�α任��ͼ��ƽ�� ID_JHBH_PY(���α任-ƽ��) 
/* ʹ��ƽ�ƶԻ���CImagePYDlg dlg                     
/* �㷨��f(x,y)=f(x+x0,y+y0)ͼ�����е�ƽ�ƣ��յĲ���'0' 
/* ע���ͼ��ƽ�Ʒ���ֻ�Ǵ����Ͻ�(0,0)����ʼƽ��        
/* ��������ԭ����ͬ �Լ�ȥʵ��                           
/********************************************************/

void CImageProcessingView::OnJhbhPy() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܿռ�ƽ��!",MB_OK,0);
		return;
	}
	//��������Ի���Ҳ�������ռ�任ƽ�Ƶ�����
	CImagePYDlg dlg;     
	if( dlg.DoModal()==IDOK ) //��ʾ�Ի���
	{
		//�����������ΪͼƬ����������
		if( dlg.m_xPY>m_nWidth || dlg.m_yPY>m_nHeight ) {
			AfxMessageBox("ͼƬƽ�Ʋ���Ϊ����ԭͼ����!",MB_OK,0);
			return;
		}
		AfxMessageBox("ͼƬ�ռ�任-ƽ��!",MB_OK,0);

		//����ʱ��ͼƬ ��д�ļ�
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);

		int num;            //��¼ÿ�ж����ͼ����������
		int sfSize;         //������ͼ���С
		//�ص�:ͼ���ÿ�����ض�������4�ı�����1*1��ͼ��Ϊ r g b 00H 
		if(m_nWidth*3%4!=0)
		{
			num=(4-m_nWidth*3%4);
			sfSize=(m_nWidth*3+num)*m_nHeight; //ÿ�ж�number��
		}
		else
		{
			num=0;
			sfSize=m_nWidth*m_nHeight*3;
		}
		//ע��:�������һ�����ز���,��Ĭ�ϴ���Ϊ������һ��,���㲹00H
		//��֮������ͼ������m*n��Ϊ4����,ÿ�ж���������

		/*�����ļ�ͷ��Ϣ ������ʱ�ļ�ͷ�ṹ����*/
		BITMAPFILEHEADER bfhsf;
		BITMAPINFOHEADER bihsf;       
		bfhsf=bfh;
		bihsf=bih;
		bfhsf.bfSize=sfSize+54;		
		fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);

		CString str;
		str.Format("����=%d",num);
		AfxMessageBox(str);

		/*��ʱ�����洢��������sfSize��ͬ new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�*/
		unsigned char *ImageSize;      
	    ImageSize=new unsigned char[sfSize];  

		int Place;                    //������ʱ���� ��¼��ʼ����(0,0)ƽ�ƹ�����λ��  
        int m_pImagePlace;            //ԭʼͼ��ƽ��Ϊ(0,0) ͼ�����ƽ�Ƶ�Placeλ��  
        unsigned char black=0;        //����ɫ='0'  
		unsigned char other=0;        //����00H='\0'

		Place=dlg.m_yPY*(m_nWidth*3+num); //ǰm_yPY�ж�Ҫ���Ϊ��ɫ          
		m_pImagePlace=0;                  //ͼ����λ��Ϊ(0,0),�Ѹõ�����ƽ�ƹ�ȥ 
		int countWidth=0;                 //��¼ÿ�е����ظ���,����ʱ���0
		int number=0;                     //���ּ�¼ʹ�õ���������,ƽ��ʱʹ��

		for(int i=0 ; i<sfSize ; i++ )  
        {  
            /*��һ���֣���ƽ�ƺ�����λ��ǰ����������ص㸳ֵΪ��ɫ*/  
            if(i<Place) 
			{  
                ImageSize[i]=black;     //��ֵΪ��ɫ  
                continue;  
            }  
              
            /*�ڶ����֣�ƽ���������߲��ָ�ֵΪ��ɫ*/  
            else if(i>=Place && countWidth<dlg.m_xPY*3)  //RGB��3
			{   
                ImageSize[i]=black;     //��ֵΪ��ɫ  
                countWidth++;  
                continue;  
            }  
          
            /*�������֣�ͼ������ƽ������*/  
            else if(i>=Place && countWidth>=dlg.m_xPY*3)  
            {  
                ImageSize[i]=m_pImage[m_pImagePlace];       
                m_pImagePlace++;  
                countWidth++;  
                if(countWidth==m_nWidth*3)  
                {  
					if(num==0)
					{
						countWidth=0;
						number++;  
						m_pImagePlace=number*m_nWidth*3; 
					}
					else //numΪ��0
					{
						for(int j=0;j<num;j++)
						{
							i++;
							ImageSize[i]=other;
						}
						countWidth=0;
						number++;  
						m_pImagePlace=number*(m_nWidth*3+num); 
					}
                }  
            }  
        }  
          
        fwrite(ImageSize,sfSize,1,fpw);    
        fclose(fpo);  
        fclose(fpw);  
        numPicture = 2;  
        level=200;        //200��ʾ���α任  
        Invalidate();  
    }     
}

/* ���α任 ͼ��ת���Լ���������ܱȽϸ���Ȥ,����ͼ��ת */
void CImageProcessingView::OnJhbhFz() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܿռ䷴ת!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼƬ�ռ�任-��תͼ��!",MB_OK,0);

	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);
	
	/*new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�*/
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];    
	int countWidth=0;        //��¼ÿ�е����ظ���,����ʱ���0
	int Place;               //��¼ͼ��ÿ�е�λ��,����ͼ��ת
	int number=0;            //���ּ�¼ʹ�õ���������
	Place=m_nWidth*3-1;

	//��ת����: y=y0 x=width-x0-1
	for(int i=0 ; i<m_nImage ; i++ )
	{
		if(countWidth==m_nWidth*3)
		{
			countWidth=0;
		}
		ImageSize[i]=m_pImage[Place]; //(0,0)��ֵ(0,width*3-1)����
		Place--;
		countWidth++;
		if(countWidth==m_nWidth*3)
		{
			number++;
			Place=number*m_nWidth*3-1;
		}
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=200;                      
	Invalidate();
}

/* ���α任 ͼ��ת */
void CImageProcessingView::OnJhbhDz() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܿռ䷴ת!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼƬ�ռ�任-��תͼ��!",MB_OK,0);

	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);
	
	/*new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�*/
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];    
	int countWidth=0;                   //��¼ÿ�����ظ���,����ʱ���0
	int Place;                          //ÿ��λ��
	int number=0;                       //��������
	Place=(m_nWidth*3)*(m_nHeight-1-1); //0�д洢

	//��ת����: x=x0 y=height-y0-1 
	for(int i=0 ; i<m_nImage ; i++ )
	{
		ImageSize[i]=m_pImage[Place]; //(0,0)��ֵ(0,0)����
		Place++;
		countWidth++;
		if(countWidth==m_nWidth*3)
		{
			countWidth=0;
			number++;
			Place=(m_nWidth*3)*(m_nHeight-number-1);
		}
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=200;                      
	Invalidate();
	
}

/**********************************************************/
/* ���α任��ͼƬ��ת                                 
/* ����ӶԻ���:IDD_JHBH_TXXZ(ͼ����ת),��������CImageXZDlg  
/* �������������:m_xzds Member variables Ϊint 0-360�� 
/**********************************************************/

void CImageProcessingView::OnJhbhTxxz() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܿռ���ת!",MB_OK,0);
		return;
	}
	
	//����Ի��򲢵��öԻ���
	CImageXZDlg dlg;    
	if( dlg.DoModal()==IDOK ) //��ʾ�Ի���
	{
		AfxMessageBox("ͼƬ�ռ�任-��תͼ��!",MB_OK,0);
		//��д�ļ�
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
		fread(m_pImage,m_nImage,1,fpo);
		
		/*new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�*/
		unsigned char *ImageSize;      
		ImageSize=new unsigned char[m_nImage];    
		int Place;          //��¼ͼ��ÿ�е�λ��,����ͼ����ת

		/*����PA=3.14ʱʹ�õķ�����arcsin(1.0/2)*6��Ϊ��*/
		double PA;
		PA=asin(0.5)*6;
		
		/*�������0-360������������ת��Ϊ�Ƕ�,30��=��/6*/
		double degree; 
		degree=PA*dlg.m_xzds/180;   //����dlg.m_xzds(��ת����)
		
		//��Ӧ�Ķ�ά���� ע��ͼ���������½ǿ�ʼ���� ������Ҫת����һά�洢
		int X,Y;               //ͼ��任ǰͨ��һά����ת��Ϊ��ά
		int XPlace,YPlace;

		//���ת��Ϊ�ĽǶ�
		CString str;
		str.Format("ת����ĽǶ�=%f",degree);
		AfxMessageBox(str);

		//ͼ����ת����
		for(int i=0 ; i<m_nImage ; i++ )
		{
			//ԭͼ��һά����ת��Ϊ��ά����
			X=(i/3)%m_nWidth;
			Y=(i/3)/m_nWidth;
			//ע�����X=i/m_nHeight Y=i%m_nWidth; ֻ������1/3

			//ͼ����תΪ��a(x,y)=x*cos-y*sin b(x,y)=x*sin+y*cos
			XPlace=(int)(X*cos(degree)-Y*sin(degree));
			YPlace=(int)(X*sin(degree)+Y*cos(degree));
			
			//��ת��Ϊһάͼ�����
			if( (XPlace>=0 && XPlace<=m_nWidth) && (YPlace>=0 && YPlace<=m_nHeight) )
			{
				Place=YPlace*m_nWidth*3+XPlace*3;
				//��ͼ��Χ�ڸ�ֵΪ������
				if(Place+2<m_nImage) 
				{
					ImageSize[i]=m_pImage[Place];
					i++;
					ImageSize[i]=m_pImage[Place+1];
					i++;
					ImageSize[i]=m_pImage[Place+2];
				}
				//����ֵΪ��ɫ
				else 
				{
					ImageSize[i]=0; 
					i++;
					ImageSize[i]=0;
					i++;
					ImageSize[i]=0;
				}
			}
			//����ֵΪ��ɫ
			else
			{
				ImageSize[i]=0;
				i++;
				ImageSize[i]=0;
				i++;
				ImageSize[i]=0;
			}
		}
	
		fwrite(ImageSize,m_nImage,1,fpw);  
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=200;        //���α任              
		Invalidate();
	}
}


/*******************************************************************/
/* ID_JHBH_SF: ��������-����-����ڲ�ֵ�㷨               
/* �㷨˼��:���ͼ��ĻҶȵ���������ӳ��λ�����������ͼ��ĻҶ�ֵ 
/* �ȼ�����Ŵ���С��ĳ���������������ԭͼ�еĵ�Ҷȣ���������  
/*******************************************************************/

void CImageProcessingView::OnJhbhSf() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ����ܼ�������ͼ��!",MB_OK,0);
		return;
	}

	CImageSFDlg dlg;           //�������ŶԻ���
	if( dlg.DoModal()==IDOK )
	{
		//�����������ΪͼƬ����������  m_sfbs(���ű���)
		if( dlg.m_sfbs==0 ) {
			AfxMessageBox("����ͼƬ���ű�������Ϊ0!",MB_OK,0);
			return;
		}
		
		FILE *fpo = fopen(BmpName,"rb");
		FILE *fpw = fopen(BmpNameLin,"wb+");
		fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
		fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
		
		/*�������ź�ĳ���*/
		int sfWidth,sfHeight;                            //���ź�ĳ���
		int sfSize;                                      //���ź��ͼ���С
		sfWidth=(int)(m_nWidth*(dlg.m_sfbs*1.0)/100);    //24λͼ��RGB������3�ı��� ѭ���ж�ȡʱΪR G B
		sfHeight=(int)(m_nHeight*(dlg.m_sfbs*1.0)/100);
		int number;                                      //��¼ÿ�ж����ͼ����������

		//�ص�:ͼ���ÿ�����ض�������4�ı�����1*1��ͼ��Ϊ r g b 00H 
		if(sfWidth*3%4!=0) {
			number=(4-sfWidth*3%4);
			sfSize=(sfWidth*3+(4-sfWidth*3%4))*sfHeight;
		}
		else {
			number=0;
			sfSize=sfWidth*sfHeight*3;
		}
		//ע��:�������һ�����ز���,��Ĭ�ϴ���Ϊ������һ��,���㲹00H
		//��֮������ͼ������m*n��Ϊ4����,ÿ�ж���������
	
		/*�����ļ�ͷ��Ϣ ������ʱ�ļ�ͷ�ṹ����*/
		BITMAPFILEHEADER bfhsf;
		BITMAPINFOHEADER bihsf;                //����(sf)
		bfhsf=bfh;
		bihsf=bih;

		bfhsf.bfSize=sfSize+54;		
		bihsf.biWidth=sfWidth;
		bihsf.biHeight=sfHeight;

		//��ʾ����m_nDrawWidth<650��ʾԭͼ,������ʾ
		flagSF=1;                         //ͼ������Ϊ1��ʶ����
		m_nDrawWidthSF=sfWidth;
		m_nDrawHeightSF=sfHeight;

		fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);
		fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);

		fread(m_pImage,m_nImage,1,fpo);	
		
		unsigned char red,green,blue;
		unsigned char other=0;                       //����00H='\0'
		int placeX;                                  //��¼��ԭͼ�еĵڼ��е�λ��
		int placeY;									 //��¼��ԭͼ�е�λ��(x,y)
		int placeBH;                                 //��¼�任���ڱ任ͼ�е�λ��

		/*new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�*/
		unsigned char *ImageSize;      
		ImageSize=new unsigned char[sfSize]; 

		/*��ȡ�ļ�������Ϣ ����ע��:1.������Ҷ� 2.�������뷨(�㷨+0.5)*/
		for(int i=0; i<sfHeight ; i++ )                  //��
		{
			placeX=(int)(i/(dlg.m_sfbs*1.0/100)+0.5)*bih.biWidth*3;
			for(int j=0; j<sfWidth ; j++ )               //��
			{
				red=green=blue=0;
				//�Ŵ���Ϊ(dlg.m_sfbs*1.0/100)
				placeY=placeX+(int)(j/(dlg.m_sfbs*1.0/100)+0.5)*3;    
				//�ص���:number*i����00H,�����numerͼ��ᱻ�г�2��
				placeBH=(i*sfWidth*3+number*i)+j*3;                  
				if(placeY+2<m_nImage)
				{
					ImageSize[placeBH]=m_pImage[placeY];
					ImageSize[placeBH+1]=m_pImage[placeY+1];
					ImageSize[placeBH+2]=m_pImage[placeY+2];
				}
				else
				{
					ImageSize[placeBH]=0;
					ImageSize[placeBH+1]=0;
					ImageSize[placeBH+2]=0;
				}
			}
		}
		
		fwrite(ImageSize,sfSize,1,fpw);
		fclose(fpo);
		fclose(fpw);
		numPicture = 2;
		level=200;
		Invalidate();
	}
}



/**************************************************
  �ھ���--ͼ����ǿ    
  ͼ��ƽ�� ��ͨƽ�� ģ��
 
float H1[3][3]={{1.0/10,1.0/10,1.0/10}, //ģ��һ:ϵ��1/10
			   {1.0/10,2.0/10,1.0/10},
			   {1.0/10,1.0/10,1.0/10}};
		
float H2[3][3]={{1.0/16,2.0/16,1.0/16}, //ģ���:ϵ��1/16
			   {2.0/16,4.0/16,2.0/16},
			   {1.0/16,2.0/16,1.0/16}};

float H3[3][3]={{1.0/8,1.0/8,1.0/8},    //ģ����:ϵ��1/8,�������Ϊ�ѵ�תΪ���ľ���
			   {1.0/8,0.0/8,1.0/8},
			   {1.0/8,1.0/8,1.0/8}};

float H4[3][3]={{0.0,1.0/8,0.0},        //ģ����:ϵ�������ݺ�ľ���
			   {1.0/8,1.0/2,1.0/8},
			   {0.0,1.0/8,0.0}};

/**************************************************/


void CImageProcessingView::OnTxzqPtph1() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(ƽ��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(ƽ��)!ѡȡ��ģ��Ϊ:��ͨƽ�� ģ��һ",MB_OK,0);

	/******************************************************************/
	/* ͼ��ƽ�����㷨��                                               
	/*   1.���峣�õ��ĸ�ģ��,���ǵ�ά����Ϊ3,����ĸ�����Ϊ9������   
	/*   2.����˼���ǰ�һ�����ɢ������Χ��9������,����ʹͼ���ģ��   
	/*   3.ͨ���������Χ�Ƹõ�ľ������غ�,������ƽ��ֵ(��9)��ֵ���� 
	/*   4.ģ�鲻ͬ,������ͼ��Ҳ������ͬ                           
	/******************************************************************/

	/*��һ�����ȶ�������ģ��*/
	int HWS=3;                                //ģ��ά��:���ĸ�ģ���Ϊ3ά��
	float H1[3][3]={{1.0/10,1.0/10,1.0/10},   //ģ��һ:ϵ��1/10
					{1.0/10,2.0/10,1.0/10},
					{1.0/10,1.0/10,1.0/10}};
	
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	float red,green,blue;
	int X,Y;               //һά����ת��Ϊ��ά����
	int TR,TG,TB;          //��¼����������λ��

	//ͼ����ǿ:ƽ�� ��Ҫ��ȡԴͼ����Χ9����ľ������ģ��9����ľ���,��һάͼ��ת��ά
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//ԭͼ��һά����ת��Ϊ��ά����
		X=(i/3)%m_nWidth;    //ͼ����X��
		Y=(i/3)/m_nWidth;    //ͼ����Y��

		//��ֵΪ��ɫ,�൱������
		red=green=blue=0;

		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //��ֹԽ��
				{			
					//ģ��һ ����ģ��ƽ��,�Ѹõ����ط�ɢ������
					TR=j*m_nWidth*3+k*3;	
					red+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H1[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ
		ImageSize[i]=(unsigned char)(red);
		ImageSize[i+1]=(unsigned char)(green);
		ImageSize[i+2]=(unsigned char)(blue);
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

void CImageProcessingView::OnTxzqPtph2() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(ƽ��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(ƽ��)!ѡȡ��ģ��Ϊ:��ͨƽ�� ģ���",MB_OK,0);

	/*��һ�����ȶ�������ģ��*/
	int HWS=3;
	float H2[3][3]={{1.0/8,1.0/8,1.0/8},    //ģ����:ϵ��1/8 �������Ϊ�ѵ�תΪ���ľ���
					{1.0/8,0.0/8,1.0/8},
					{1.0/8,1.0/8,1.0/8}};
	
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	
	//�ص�:ͼ���ÿ�����ض�������4�ı�����1*1��ͼ��Ϊ r g b 00H   
	int num;            //��¼ÿ�ж����ͼ����������  
	int sfSize;         //������ͼ���С  
    if(m_nWidth*3%4!=0) {  
        num=(4-m_nWidth*3%4);  
        sfSize=(m_nWidth*3+num)*m_nHeight; //ÿ�ж�number��  
    }  
    else {  
        num=0;  
        sfSize=m_nWidth*m_nHeight*3;  
    }  
  
    /*�����ļ�ͷ��Ϣ ������ʱ�ļ�ͷ�ṹ����*/  
    BITMAPFILEHEADER bfhsf;  
    BITMAPINFOHEADER bihsf;         
    bfhsf=bfh;  
    bihsf=bih;  
    bfhsf.bfSize=sfSize+54;  
    fwrite(&bfhsf,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bihsf,sizeof(BITMAPINFOHEADER),1,fpw);  
    fread(m_pImage,m_nImage,1,fpo);  

	//new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[sfSize];    
	float red,green,blue;
	int X,Y;               //һά����ת��Ϊ��ά����
	int TR,TG,TB;          //��¼����������λ��  
    int countWidth=0;      //��¼ÿ�е����ظ���,����ʱ���0  
	int place=0;           //������ʱ���� ��¼��ʼ����(0,0)ƽ�ƹ�����λ�� 

	//ͼ����ǿ ƽ��
	for(int i=0; i<m_nImage; )
	{
		//ԭͼһά����ת��Ϊ��ά����
		X=(i/3)%m_nWidth;    //ͼ����X��
		Y=(i/3)/m_nWidth;    //ͼ����Y��

		//��ֵΪ��ɫ,�൱������
		red=green=blue=0;

		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //��ֹԽ��
				{			
					//ģ��� ����ģ��ƽ��,�Ѹõ����ط�ɢ������
					TR=j*m_nWidth*3+k*3;	
					red+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H2[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ
		//ͨ������place��ֵ�任���ͼ�� iʼ��ָ��ԭͼ3�ı��� Ϊ�˲�0�����place����
		ImageSize[place]=(unsigned char)(red);
		i++; place++;
		ImageSize[place]=(unsigned char)(green);
		i++; place++;
		ImageSize[place]=(unsigned char)(blue);
		i++; place++;
		countWidth=countWidth+3;
		
		if(countWidth==m_nWidth*3)    
        {    
			if(num==0)  
            {  
                countWidth=0;    
                place=Y*m_nWidth*3;
            }  
            else //numΪ��0  
            {  
                for(int n=0;n<num;n++)  
                {    
                    ImageSize[place]=0;  
					place++;  
                }  
                countWidth=0;   
                place=Y*(m_nWidth*3+num); //�ص� ���Num  
            }  
		} 
	}
		
	fwrite(ImageSize,sfSize,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture=2;
	level=400;
	Invalidate();
}

//��˹ƽ��
void CImageProcessingView::OnTxzqGsph() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(ƽ��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(ƽ��)!ѡȡ��ģ��Ϊ:��˹ƽ��",MB_OK,0);

	/*��һ�����ȶ�������ģ��*/
	int HWS=3;                                //ģ��ά��Ϊ3ά
	float H[3][3]={{1.0/16,2.0/16,1.0/16},    //��˹ģ�� ϵ��1/16
				   {2.0/16,4.0/16,2.0/16},
				   {1.0/16,2.0/16,1.0/16}};
	
	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	float red,green,blue;
	int X,Y;               //һά����ת��Ϊ��ά����
	int TR,TG,TB;          //��¼����������λ��

	//ͼ����ǿ:ƽ�� 
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//ԭͼ��һά����ת��Ϊ��ά����
		X=(i/3)%m_nWidth;    //ͼ����X��
		Y=(i/3)/m_nWidth;    //ͼ����Y��

		//��ֵΪ��ɫ,�൱������
		red=green=blue=0;

		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //��ֹԽ��
				{			
					//ģ��� ����ģ��ƽ��,�Ѹõ����ط�ɢ������
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ
		ImageSize[i]=(unsigned char)(red);
		ImageSize[i+1]=(unsigned char)(green);
		ImageSize[i+2]=(unsigned char)(blue);
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

//��ֵ�˲�
void CImageProcessingView::OnTxzqZzlb() 
{
	if(numPicture==0) {
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(ƽ��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(ƽ��)!ѡȡ��ģ��Ϊ:��ֵ�˲�",MB_OK,0);

	//����ʱ��ͼƬ
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�
    unsigned char *ImageSize;        
    ImageSize = new unsigned char[m_nImage];    
	int X,Y;               //һά����ת��Ϊ��ά����
	int TR,TG,TB;          //��¼����������λ��

	//ѡȡ��Ϊ���ĵ���Χ9�������أ�ע��һ����ΪRGB��
	int H[9]={0,0,0,0,0,0,0,0,0};    
	int HWS=3;             //ά��Ϊ��ά

	//ͼ����ǿ:ƽ�� ��Ҫ��ȡԴͼ����Χ9����ľ������ģ��9����ľ���,��һάͼ��ת��ά
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		//ԭͼ��һά����ת��Ϊ��ά����
		X=(i/3)%m_nWidth;    //ͼ����X��
		Y=(i/3)/m_nWidth;    //ͼ����Y��
		
		//��һ�� ��һ�� ���һ�� ���һ�� ֱ�Ӹ���
		if(X==0 || Y==0 || X==m_nWidth*3 || Y==m_nHeight) 
		{
			if(i+2>m_nImage) break;
			ImageSize[i] = m_pImage[i];
			ImageSize[i+1] = m_pImage[i+1];
			ImageSize[i+2] = m_pImage[i+2];
			continue;
		}

		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		int num=0;
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )      //��ֹԽ��
				{			
					//��ȡ��ǰλ��Red���� kһ������RGB�������� R=G=B
					TR = j*m_nWidth*3+k*3;	
					H[num] = m_pImage[TR];
					num++;
				}
			}
		}
		//�����ȡ�м�ֵ
		int temp=0;
		for(int x=0;x<9;x++)
		{
			for(int y=x;y<9;y++)
			{
				if(H[x]>=H[y])
				{
					temp=H[x];
					H[x]=H[y];
					H[y]=temp;
				}
			}
		}
		//CString str;
		//str.Format("����:%d %d %d, %d %d %d, %d %d %d",H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7],H[8]);
		//AfxMessageBox(str);

		//����ͼ��ֵ �Ҷ�ͼ��RGB��ͬ
		ImageSize[i]=H[4];
		ImageSize[i+1]=H[4];
		ImageSize[i+2]=H[4];
	}
		
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;
	Invalidate();
}

/*****************************************/
/* ͼ����:����menu�д���5���ӵ�menu    */
/* ��ֹ����ƽ������,һ��ֻ����һ�������� */
/* ID_RH_Laplacian Laplacian������˹���� */
/* ID_RH_Sobel Sobel����                 */
/* ID_RH_Prewitt Prewitt����             */
/* ID_RH_Isotropic Isotropic����         */
/* ID_RH_GTMB ��ͨģ��H2                 */
/*****************************************/

void CImageProcessingView::OnRHLaplacian() 
{
	if(numPicture==0) 
	{
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(��):����������˹(Laplacian)����!");

	//ģ��ά��:���ĸ�ģ���Ϊ3ά��
	int HWS=3;  
	
	int H[3][3]={{0,-1,0},    //ģ��Ϊ������˹����(����Ϊ4��Laplacian)
				{-1,4,-1},
				{0,-1,0}};

	//��д�ļ�
	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	//new��delete��Ч�Ľ��ж�̬�ڴ�ķ�����ͷ�
	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;       //һά����ת��Ϊ��ά����
	int TR,TG,TB;  //��¼����������λ��
	
	//ͼ����ǿ ��
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X��
		Y=(i/3)/m_nWidth;    //Y��
		red=green=blue=0;
		
		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//��ͨģ��
void CImageProcessingView::OnRhGtmb() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(��):���ø�ͨģ��!");

	int HWS=3;                                
	int H[3][3]={{-1,-1,-1},    
				{-1,8,-1},
				{-1,-1,-1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;       
	int TR,TG,TB; 
	
	//ͼ����ǿ ��
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X��
		Y=(i/3)/m_nWidth;    //Y��
		red=green=blue=0;
		
		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		
		//����ͼ��ֵ
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();	
}

//Sobel���Ӳ���PPT�ϵ�d(x) d(y)ģ��
void CImageProcessingView::OnRHSobel() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(��):����Sobel����!");

	int HWS=3;                                
	//ģ��ΪSobel����
	int HX[3][3]={{1,0,-1},{2,0,-2},{1,0,-1}};
	int HY[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);	
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int redX,greenX,blueX;
	int redY,greenY,blueY;
	int X,Y;       
	int TR,TG,TB;  
	
	//ͼ����ǿ ��
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X��
		Y=(i/3)/m_nWidth;    //Y��
		redX=greenX=blueX=0;
		redY=greenY=blueY=0;
		
		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					redX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					redY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					greenX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					greenY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blueX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
					blueY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//s=(d(x)*d(x)+d(y)*d(y))������
		int R,G,B;
		R=(int)(sqrt(redX*redX*1.0+redY*redY*1.0));
		G=(int)(sqrt(greenX*greenX*1.0+greenY*greenY*1.0));
		B=(int)(sqrt(blueX*blueX*1.0+blueY*blueY*1.0));

		if(redX<0 && redY<0) ImageSize[i]=0;
		else if(R>255) ImageSize[i]=255;
		else ImageSize[i]=R;
		
		if(greenX<0 && greenY<0) ImageSize[i+1]=0;
		else if(G>255) ImageSize[i+1]=255;
		else ImageSize[i+1]=G;

		if(blueX<0 && blueY<0) ImageSize[i+2]=0;
		else if(B>255) ImageSize[i+2]=255;
		else ImageSize[i+2]=B;
	}
	
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//Isotropic���Ӳ���PPT�ϵ�d(x)ģ�� d(y)
void CImageProcessingView::OnRHIsotropic() 
{
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(��)!",MB_OK,0);
		return;
	}

	AfxMessageBox("ͼ����ǿ(��):����Isotropic����!");

	int HWS=3;                               
	//ģ��ΪIsotropic����
	float HX[3][3]={{1,0,-1},
					{sqrt(2.0),0,-sqrt(2.0)}, 
					{1,0,-1} };
	float HY[3][3]={{-1,-sqrt(2.0),-1},
					{0,0,0}, 
					{1,sqrt(2.0),1} };

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	float redX,greenX,blueX;
	float redY,greenY,blueY;
	int X,Y;      
	int TR,TG,TB;  
	
	//ͼ����ǿ
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X��
		Y=(i/3)/m_nWidth;    //Y��
		redX=greenX=blueX=0;
		redY=greenY=blueY=0;
		
		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					redX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					redY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					greenX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					greenY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blueX+=HX[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
					blueY+=HY[(j-Y+HWS/2)][(k-X+HWS/2)]*(float)(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ s=(d(x)*d(x)+d(y)*d(y))������
		int R,G,B;
		R=(int)(sqrt(redX*redX*1.0+redY*redY*1.0));
		G=(int)(sqrt(greenX*greenX*1.0+greenY*greenY*1.0));
		B=(int)(sqrt(blueX*blueX*1.0+blueY*blueY*1.0));

		if(redX<0 && redY<0) ImageSize[i]=0;
		else if(R>255) ImageSize[i]=255;
		else ImageSize[i]=R;
		
		if(greenX<0 && greenY<0) ImageSize[i+1]=0;
		else if(G>255) ImageSize[i+1]=255;
		else ImageSize[i+1]=G;

		if(blueX<0 && blueY<0) ImageSize[i+2]=0;
		else if(B>255) ImageSize[i+2]=255;
		else ImageSize[i+2]=B;
	}
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}

//Prewitt���Ӳ���PPT�ϵ�d(x)ģ��,����d(y)
void CImageProcessingView::OnRHPrewitt() 
{
	
	if(numPicture==0)
	{
		AfxMessageBox("����ͼƬ�����ͼ����ǿ(��)!",MB_OK,0);
		return;
	}
	AfxMessageBox("ͼ����ǿ(��):����Prewitt����!");

	int HWS=3;                               
	int H[3][3]={{1,0,-1},    //ģ��ΪPrewitt����
				{1,0,-1},
				{1,0,-1}};

	FILE *fpo = fopen(BmpName,"rb");
	FILE *fpw = fopen(BmpNameLin,"wb+");
	fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);
	fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);
	fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);
	fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);
	fread(m_pImage,m_nImage,1,fpo);

	unsigned char *ImageSize;      
	ImageSize=new unsigned char[m_nImage];  
	int red,green,blue;
	int X,Y;      
	int TR,TG,TB; 
	
	//ͼ����ǿ:ƽ��
	for(int i=0; i<m_nImage ; i=i+3 )
	{
		X=(i/3)%m_nWidth;    //X��
		Y=(i/3)/m_nWidth;    //Y��
		red=green=blue=0;
		
		//��ͼ�����������Ͳ�ȡƽ��ֵ HWSά��
		for(int j=Y-HWS/2 ; j<Y+HWS/2+1 ; j++ )                      //��j��
		{
			for(int k=X-HWS/2 ; k<X+HWS/2+1 ; k++ )                  //��k��
			{
				if( j>=0 && k>=0 && k<m_nWidth && j<m_nHeight )
				{			
					
					TR=j*m_nWidth*3+k*3;	
					red+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TR]);
					TG=j*m_nWidth*3+k*3+1;
					green+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TG]);
					TB=j*m_nWidth*3+k*3+2;
					blue+=H[(j-Y+HWS/2)][(k-X+HWS/2)]*(m_pImage[TB]);
				}
			}
		}
		//����ͼ��ֵ
		if(red>=0 && red<256) ImageSize[i]=red;
		else if(red<0) ImageSize[i]=0;      //ImageSize[i]=-red;
		else ImageSize[i]=0;
		
		if(green>=0 && green<256) ImageSize[i+1]=green;
		else if(green<0) ImageSize[i+1]=0;  //ImageSize[i+1]=-green;
		else ImageSize[i+1]=0;
		
		if(blue>=0 && blue<256) ImageSize[i+2]=blue;
		else if(blue<0) ImageSize[i+2]=0;   //ImageSize[i+2]=-blue;
		else ImageSize[i+2]=0;	
	}
	fwrite(ImageSize,m_nImage,1,fpw);  
	fclose(fpo);
	fclose(fpw);
	numPicture = 2;
	level=400;	
	Invalidate();
}
