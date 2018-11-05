// SetColorDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Filling.h"
#include "SetColorDialog.h"
#include "afxdialogex.h"


// SetColorDialog 对话框

IMPLEMENT_DYNAMIC(SetColorDialog, CDialogEx)

SetColorDialog::SetColorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nR(0)
	, m_nG(0)
	, m_nB(0)
{

}

SetColorDialog::~SetColorDialog()
{
}

void SetColorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nR);
	DDX_Text(pDX, IDC_EDIT2, m_nG);
	DDX_Text(pDX, IDC_EDIT3, m_nB);
}


BEGIN_MESSAGE_MAP(SetColorDialog, CDialogEx)
END_MESSAGE_MAP()


// SetColorDialog 消息处理程序
