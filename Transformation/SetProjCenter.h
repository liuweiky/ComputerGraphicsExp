#pragma once


// SetProjCenter 对话框

class SetProjCenter : public CDialogEx
{
	DECLARE_DYNAMIC(SetProjCenter)

public:
	SetProjCenter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SetProjCenter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGPROJ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_fX;
	double m_fY;
	double m_fZ;
};
