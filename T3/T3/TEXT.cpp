// TEXT.cpp : 实现文件
//

#include "stdafx.h"
#include "T3.h"
#include "TEXT.h"
#include "afxdialogex.h"


// CTEXT 对话框

IMPLEMENT_DYNAMIC(CTEXT, CDialogEx)

CTEXT::CTEXT(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTEXT::IDD, pParent)
{

}

CTEXT::~CTEXT()
{
}

void CTEXT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTEXT, CDialogEx)
END_MESSAGE_MAP()


// CTEXT 消息处理程序
