
// BSpline3DView.h: CBSpline3DView 类的接口
//

#pragma once

#include "COpPoint.h"

#define MAX_N 102400
#define K 4
#define LINE_POINTS 2500

class CBSpline3DView : public CView
{
protected: // 仅从序列化创建
	CBSpline3DView() noexcept;
	DECLARE_DYNCREATE(CBSpline3DView)

// 特性
public:
	CBSpline3DDoc* GetDocument() const;

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
	virtual ~CBSpline3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:

	CArray<COpPoint, COpPoint&> m_ptControlPoints;
	COpPoint m_StartPoint;
	COpPoint m_EndPoint;

	COLORREF m_cRGB[3];

	double m_fKnot[MAX_N + K + 1];
	bool m_bLButtonDown;
	bool m_bHasInputFinished;

	void Clear();

	CArray<COpPoint, COpPoint&>& GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points);
	COpPoint Deboor(CArray<COpPoint, COpPoint&>& control, double u, int j);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void ReDraw();
	void DrawSymmetry();
};

#ifndef _DEBUG  // BSpline3DView.cpp 中的调试版本
inline CBSpline3DDoc* CBSpline3DView::GetDocument() const
   { return reinterpret_cast<CBSpline3DDoc*>(m_pDocument); }
#endif

