
// Curve_SurfaceView.h: CCurveSurfaceView 类的接口
//

#pragma once

#include "DrawType.h"
#include "Hermite.h"
#include "Bezier.h"
#include "BSpline.h"


class CCurveSurfaceView : public CView
{
protected: // 仅从序列化创建
	CCurveSurfaceView() noexcept;
	DECLARE_DYNCREATE(CCurveSurfaceView)

// 特性
public:
	CCurveSurfaceDoc* GetDocument() const;

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
	virtual ~CCurveSurfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

private:
	DrawType* type;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Curve_SurfaceView.cpp 中的调试版本
inline CCurveSurfaceDoc* CCurveSurfaceView::GetDocument() const
   { return reinterpret_cast<CCurveSurfaceDoc*>(m_pDocument); }
#endif

