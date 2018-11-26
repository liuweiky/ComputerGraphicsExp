
// DynamicBezierView.h: CDynamicBezierView 类的接口
//

#pragma once

#include "COpPoint.h"

#define N 3
#define LINE_POINTS 200

class CDynamicBezierView : public CView
{
protected: // 仅从序列化创建
	CDynamicBezierView() noexcept;
	DECLARE_DYNCREATE(CDynamicBezierView)

// 特性
public:
	CDynamicBezierDoc* GetDocument() const;

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
	virtual ~CDynamicBezierView();
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

public:
	CArray<COpPoint, COpPoint&> m_ptControlPoints;
	CArray<int, int> m_nDir;
	COpPoint m_StartPoint;
	COpPoint m_EndPoint;

	bool m_bLButtonDown;
	bool m_bHasInputFinished;
	
	void Clear();
	void RefreshView();

	CArray<COpPoint, COpPoint&>& GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points);
	// 根据控制点 control，获得 t 处坐标值
	COpPoint Decas(CArray<COpPoint, COpPoint&>& control, double t);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonStartClick();
	afx_msg void OnButtonPauseClick();
};

#ifndef _DEBUG  // DynamicBezierView.cpp 中的调试版本
inline CDynamicBezierDoc* CDynamicBezierView::GetDocument() const
   { return reinterpret_cast<CDynamicBezierDoc*>(m_pDocument); }
#endif

