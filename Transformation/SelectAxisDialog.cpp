// SelectAxisDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Transformation.h"
#include "SelectAxisDialog.h"
#include "afxdialogex.h"


// SelectAxisDialog 对话框

IMPLEMENT_DYNAMIC(SelectAxisDialog, CDialogEx)

SelectAxisDialog::SelectAxisDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGAXIS, pParent)
	, m_nRotateAxis(0)
{

}

SelectAxisDialog::~SelectAxisDialog()
{
}

void SelectAxisDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nRotateAxis);
}


BEGIN_MESSAGE_MAP(SelectAxisDialog, CDialogEx)
END_MESSAGE_MAP()


// SelectAxisDialog 消息处理程序
