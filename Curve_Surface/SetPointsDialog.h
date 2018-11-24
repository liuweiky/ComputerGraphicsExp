#pragma once


// SetPointsDialog 对话框

class SetPointsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetPointsDialog)

public:
	SetPointsDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SetPointsDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POINTSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int p11x; int p11y; int p11z;
	int p12x; int p12y; int p12z;
	int p13x; int p13y; int p13z;
	int p14x; int p14y; int p14z;

	int p21x; int p21y; int p21z;
	int p22x; int p22y; int p22z;
	int p23x; int p23y; int p23z;
	int p24x; int p24y; int p24z;

	int p31x; int p31y; int p31z;
	int p32x; int p32y; int p32z;
	int p33x; int p33y; int p33z;
	int p34x; int p34y; int p34z;

	int p41x; int p41y; int p41z;
	int p42x; int p42y; int p42z;
	int p43x; int p43y; int p43z;
	int p44x; int p44y; int p44z;
};
