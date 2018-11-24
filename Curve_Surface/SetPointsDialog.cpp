// SetPointsDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Curve_Surface.h"
#include "SetPointsDialog.h"
#include "afxdialogex.h"


// SetPointsDialog 对话框

IMPLEMENT_DYNAMIC(SetPointsDialog, CDialogEx)

SetPointsDialog::SetPointsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POINTSDIALOG, pParent)
	, p11x(-300), p11y(-300), p11z(0)
	, p12x(-300), p12y(-100), p12z(100)
	, p13x(-300), p13y(100), p13z(100)
	, p14x(-300), p14y(300), p14z(0)

	, p21x(-100), p21y(-300), p21z(25)
	, p22x(-100), p22y(-100), p22z(300)
	, p23x(-100), p23y(100), p23z(300)
	, p24x(-100), p24y(300), p24z(25)

	, p31x(100), p31y(-300), p31z(25)
	, p32x(100), p32y(-100), p32z(300)
	, p33x(100), p33y(100), p33z(300)
	, p34x(100), p34y(300), p34z(25)

	, p41x(300), p41y(-300), p41z(0)
	, p42x(300), p42y(-100), p42z(100)
	, p43x(300), p43y(100), p43z(100)
	, p44x(300), p44y(300), p44z(0)
{

}

SetPointsDialog::~SetPointsDialog()
{
}

void SetPointsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT11x, p11x); DDX_Text(pDX, IDC_EDIT11y, p11y); DDX_Text(pDX, IDC_EDIT11z, p11z);
	DDX_Text(pDX, IDC_EDIT12x, p12x); DDX_Text(pDX, IDC_EDIT12y, p12y); DDX_Text(pDX, IDC_EDIT12z, p12z);
	DDX_Text(pDX, IDC_EDIT13x, p13x); DDX_Text(pDX, IDC_EDIT13y, p13y); DDX_Text(pDX, IDC_EDIT13z, p13z);
	DDX_Text(pDX, IDC_EDIT14x, p14x); DDX_Text(pDX, IDC_EDIT14y, p14y); DDX_Text(pDX, IDC_EDIT14z, p14z);

	DDX_Text(pDX, IDC_EDIT21x, p21x); DDX_Text(pDX, IDC_EDIT21y, p21y); DDX_Text(pDX, IDC_EDIT21z, p21z);
	DDX_Text(pDX, IDC_EDIT22x, p22x); DDX_Text(pDX, IDC_EDIT22y, p22y); DDX_Text(pDX, IDC_EDIT22z, p22z);
	DDX_Text(pDX, IDC_EDIT23x, p23x); DDX_Text(pDX, IDC_EDIT23y, p23y); DDX_Text(pDX, IDC_EDIT23z, p23z);
	DDX_Text(pDX, IDC_EDIT24x, p24x); DDX_Text(pDX, IDC_EDIT24y, p24y); DDX_Text(pDX, IDC_EDIT24z, p24z);

	DDX_Text(pDX, IDC_EDIT31x, p31x); DDX_Text(pDX, IDC_EDIT31y, p31y); DDX_Text(pDX, IDC_EDIT31z, p31z);
	DDX_Text(pDX, IDC_EDIT32x, p32x); DDX_Text(pDX, IDC_EDIT32y, p32y); DDX_Text(pDX, IDC_EDIT32z, p32z);
	DDX_Text(pDX, IDC_EDIT33x, p33x); DDX_Text(pDX, IDC_EDIT33y, p33y); DDX_Text(pDX, IDC_EDIT33z, p33z);
	DDX_Text(pDX, IDC_EDIT34x, p34x); DDX_Text(pDX, IDC_EDIT34y, p34y); DDX_Text(pDX, IDC_EDIT34z, p34z);

	DDX_Text(pDX, IDC_EDIT41x, p41x); DDX_Text(pDX, IDC_EDIT41y, p41y); DDX_Text(pDX, IDC_EDIT41z, p41z);
	DDX_Text(pDX, IDC_EDIT42x, p42x); DDX_Text(pDX, IDC_EDIT42y, p42y); DDX_Text(pDX, IDC_EDIT42z, p42z);
	DDX_Text(pDX, IDC_EDIT43x, p43x); DDX_Text(pDX, IDC_EDIT43y, p43y); DDX_Text(pDX, IDC_EDIT43z, p43z);
	DDX_Text(pDX, IDC_EDIT44x, p44x); DDX_Text(pDX, IDC_EDIT44y, p44y); DDX_Text(pDX, IDC_EDIT44z, p44z);
}


BEGIN_MESSAGE_MAP(SetPointsDialog, CDialogEx)
END_MESSAGE_MAP()


// SetPointsDialog 消息处理程序
