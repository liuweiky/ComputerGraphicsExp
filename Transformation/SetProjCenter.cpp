// SetProjCenter.cpp: 实现文件
//

#include "stdafx.h"
#include "Transformation.h"
#include "SetProjCenter.h"
#include "afxdialogex.h"


// SetProjCenter 对话框

IMPLEMENT_DYNAMIC(SetProjCenter, CDialogEx)

SetProjCenter::SetProjCenter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGPROJ, pParent)
	, m_fX(0)
	, m_fY(0)
	, m_fZ(0)
{

}

SetProjCenter::~SetProjCenter()
{
}

void SetProjCenter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fX);
	DDX_Text(pDX, IDC_EDIT2, m_fY);
	DDX_Text(pDX, IDC_EDIT3, m_fZ);
}


BEGIN_MESSAGE_MAP(SetProjCenter, CDialogEx)
END_MESSAGE_MAP()


// SetProjCenter 消息处理程序
