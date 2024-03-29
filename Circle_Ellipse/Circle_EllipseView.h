
// Circle_EllipseView.h: CCircleEllipseView 类的接口
//

#pragma once

#define CIRCLE 1
#define ELLIPSE 2

class CCircleEllipseView : public CView
{
protected: // 仅从序列化创建
	CCircleEllipseView() noexcept;
	DECLARE_DYNCREATE(CCircleEllipseView)

	// 特性
public:
	CCircleEllipseDoc* GetDocument() const;

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
	virtual ~CCircleEllipseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCircleClick();
	afx_msg void OnEllipseClick();

private:
	int m_nDrawType;
	bool m_bHasLButtonDown;
	CPoint m_StartPoint;
	CPoint m_EndPoint;
	void BresenhamCircle(CDC* pDC, int R, CPoint point, COLORREF color);
	double GetDistance(CPoint pnt1, CPoint pnt2);
	void MidPointEllipse(CDC* pDC, CPoint pnt1, CPoint pnt2, COLORREF color);
};

#ifndef _DEBUG  // Circle_EllipseView.cpp 中的调试版本
inline CCircleEllipseDoc* CCircleEllipseView::GetDocument() const
{
	return reinterpret_cast<CCircleEllipseDoc*>(m_pDocument);
}
#endif

