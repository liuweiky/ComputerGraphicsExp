
// FillingView.h: CFillingView 类的接口
//

#pragma once

#define BKG_ROW_NUM 24
#define BKG_COL_NUM 48

#define MAX_X 4096
#define MAX_Y 4096

class CFillingView : public CView
{
protected: // 仅从序列化创建
	CFillingView() noexcept;
	DECLARE_DYNCREATE(CFillingView)

	// 特性
public:
	CFillingDoc* GetDocument() const;

	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CFillingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	bool m_nMask[MAX_X][MAX_Y];
	CArray<CPoint, CPoint&> m_PolygonPoints;
	bool m_bHasLButtonDown;
	CPoint m_StartPoint;
	CPoint m_EndPoint;
	//	void DDALine(CDC* pDC, CPoint spnt, CPoint epnt, COLORREF color);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	void EdgeMarkFill(CArray<CPoint, CPoint&>& points, COLORREF color);
};

#ifndef _DEBUG  // FillingView.cpp 中的调试版本
inline CFillingDoc* CFillingView::GetDocument() const
{
	return reinterpret_cast<CFillingDoc*>(m_pDocument);
}
#endif

