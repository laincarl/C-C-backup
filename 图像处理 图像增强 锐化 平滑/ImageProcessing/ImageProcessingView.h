// ImageProcessingView.h : interface of the CImageProcessingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_)
#define AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageProcessingView : public CView
{
protected: // create from serialization only
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// Attributes
public:
	CImageProcessingDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageProcessingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	//��ӳ�Ա����
	void ShowBitmap(CDC* pDC,CString BmpName); //��ʾλͼ����
	bool ReadBmp();                            //������ȡbmp���ֻ�ͼƬ
	bool SaveBmp(LPCSTR lpFileName);           //��������bmp��ʽͼƬ

	//��ӳ�Ա����
	CString EntName;     //ͼ���ļ���չ��
	CString BmpName;     //ͼ���ļ�����
	CBitmap m_bitmap;    //����λͼ����

	int	m_nWidth;		//ͼ��ʵ�ʿ��
	int	m_nHeight;		//ͼ��ʵ�ʸ߶�
	int	m_nDrawWidth;	//ͼ����ʾ���
	int	m_nDrawHeight;	//ͼ����ʾ�߶�
	DWORD m_nImage;		//ͼ�����ݵ��ֽ��� ֻ��λͼ
	DWORD m_nSize;      //ͼ���ļ���С
	int m_nLineByte;    //ͼ��һ����ռ�ֽ���
	int	m_nBitCount;    //ͼ��ÿ��������ռλ��
	int	m_nPalette;     //λͼʵ��ʹ�õ���ɫ���е���ɫ��
	
	BYTE *m_pImage;         //����ͼƬ���ݺ��ָ��
	BITMAPFILEHEADER bfh;   //ȫ�ֱ����ļ�ͷ
	BITMAPINFOHEADER bih;   //ȫ�ֱ�����Ϣͷ
	RGBQUAD m_pPal;         //��ɫ��ָ��

	CBitmap m_bitmaplin;   //������ʱλͼ������д���
	CString BmpNameLin;    //����ͼ�񸱱��ļ�

	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageProcessingView)
	afx_msg void OnFileOpen();
	afx_msg void OnShowTwo();
	afx_msg void OnShowHd();
	afx_msg void OnFileSave();
	afx_msg void OnLh2();
	afx_msg void OnLh4();
	afx_msg void OnLh8();
	afx_msg void OnLh16();
	afx_msg void OnLh32();
	afx_msg void OnLh64();
	afx_msg void OnCy();
	afx_msg void OnZftYt();
	afx_msg void OnDysXxjx();
	afx_msg void OnDysXxqb();
	afx_msg void OnDysXxzq();
	afx_msg void OnDysXxyd();
	afx_msg void OnDysFxxhs();
	afx_msg void OnDysFxxpf();
	afx_msg void OnDysYzbh();
	afx_msg void OnDysJhh();
	afx_msg void OnJhbhPy();
	afx_msg void OnJhbhTxxz();
	afx_msg void OnJhbhFz();
	afx_msg void OnJhbhDz();
	afx_msg void OnJhbhSf();
	afx_msg void OnTxzqPtph1();
	afx_msg void OnTxzqPtph2();
	afx_msg void OnTxzqGsph();
	afx_msg void OnTxzqZzlb();
	afx_msg void OnRHLaplacian();
	afx_msg void OnRHIsotropic();
	afx_msg void OnRHPrewitt();
	afx_msg void OnRHSobel();
	afx_msg void OnRhGtmb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageProcessingView.cpp
inline CImageProcessingDoc* CImageProcessingView::GetDocument()
   { return (CImageProcessingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROCESSINGVIEW_H__2E589CAF_6BCD_4586_8B07_F024B9B6D16E__INCLUDED_)
