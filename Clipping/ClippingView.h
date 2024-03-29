
// ClippingView.h: CClippingView 类的接口
//

#pragma once


class CClippingView : public CView
{
protected: // 仅从序列化创建
	CClippingView() noexcept;
	DECLARE_DYNCREATE(CClippingView)

// 特性
public:
	CClippingDoc* GetDocument() const;

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
	virtual ~CClippingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	bool m_bLButtonDown;
	bool m_bRButtonDown;
	CPoint m_RectLtTp;
	CPoint m_RectRtBt;
	void Clear();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	CArray<CPoint, CPoint&> m_PolygonPoints;
	CObArray m_HistoryPoints;
	CPoint m_StartPoint;
	CPoint m_EndPoint;
	void CutTop(CArray<CPoint, CPoint&>& points);
	void CutRight(CArray<CPoint, CPoint&>& points);
	void CutBottom(CArray<CPoint, CPoint&>& points);
	void CutLeft(CArray<CPoint, CPoint&>& points);
	void SutherlandHodgman(const CArray<CPoint, CPoint&>& points);
	void FillRect(const CArray<CPoint, CPoint&>& points, COLORREF color);
	void DrawView(const CArray<CPoint, CPoint&>& points);
	void DrawPolyLine(const CArray<CPoint, CPoint&>& points, int width, COLORREF color);
};

#ifndef _DEBUG  // ClippingView.cpp 中的调试版本
inline CClippingDoc* CClippingView::GetDocument() const
   { return reinterpret_cast<CClippingDoc*>(m_pDocument); }
#endif

