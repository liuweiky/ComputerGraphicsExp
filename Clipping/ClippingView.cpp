
// ClippingView.cpp: CClippingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Clipping.h"
#endif

#include "ClippingDoc.h"
#include "ClippingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClippingView

IMPLEMENT_DYNCREATE(CClippingView, CView)

BEGIN_MESSAGE_MAP(CClippingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CClippingView 构造/析构

CClippingView::CClippingView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = m_bRButtonDown = false;

}

CClippingView::~CClippingView()
{
}

BOOL CClippingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CClippingView 绘图

void CClippingView::OnDraw(CDC* /*pDC*/)
{
	CClippingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (m_HistoryPoints.GetSize() != 0)
	{
		CClientDC dc(this);
		dc.Rectangle(m_RectLtTp.x, m_RectLtTp.y, m_RectRtBt.x, m_RectRtBt.y);
	}

	for (int i = 0; i < m_HistoryPoints.GetSize(); i++)
	{
		CArray<CPoint, CPoint&>* points = (CArray<CPoint, CPoint&>*)m_HistoryPoints.GetAt(i);
		DrawView(*points);
	}
}


// CClippingView 打印

BOOL CClippingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CClippingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CClippingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CClippingView 诊断

#ifdef _DEBUG
void CClippingView::AssertValid() const
{
	CView::AssertValid();
}

void CClippingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClippingDoc* CClippingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClippingDoc)));
	return (CClippingDoc*)m_pDocument;
}
#endif //_DEBUG


// CClippingView 消息处理程序


void CClippingView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}


void CClippingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	Clear();
	m_PolygonPoints.RemoveAll();
	m_HistoryPoints.RemoveAll();
	m_bLButtonDown = true;
	m_RectLtTp = point;
	CView::OnLButtonDown(nFlags, point);
}


void CClippingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLButtonDown)
	{
		ReleaseCapture();
		Clear();
		m_RectRtBt = point;
		CClientDC dc(this);
		dc.Rectangle(m_RectLtTp.x, m_RectLtTp.y, m_RectRtBt.x, m_RectRtBt.y);
		m_bLButtonDown = false;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CClippingView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bRButtonDown)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(m_StartPoint);
		dc.LineTo(m_EndPoint);

		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

		CDC* pDC = GetDC();
		CPen* oldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(m_StartPoint);
		pDC->LineTo(point);

		pDC->SelectObject(oldPen);

		m_EndPoint = point;
		m_PolygonPoints.Add(point);
		m_StartPoint = point;
		m_EndPoint = point;
	}
	else
	{
		SetCapture();
		m_bRButtonDown = true;
		m_PolygonPoints.RemoveAll();
		m_PolygonPoints.Add(point);
		m_StartPoint = point;
		m_EndPoint = point;
	}
	CView::OnRButtonDown(nFlags, point);
}


void CClippingView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonUp(nFlags, point);
}


void CClippingView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bRButtonDown)
	{
		ReleaseCapture();
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

		CDC* pDC = GetDC();
		CPen* oldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(m_PolygonPoints.GetAt(m_PolygonPoints.GetSize() - 1));
		pDC->LineTo(m_PolygonPoints.GetAt(0));

		pDC->SelectObject(oldPen);
		
		m_bRButtonDown = false;
		DrawView(m_PolygonPoints);
		CArray<CPoint, CPoint&>* points = new CArray<CPoint, CPoint&>();
		points->Append(m_PolygonPoints);
		m_HistoryPoints.Add(points);
	}
	CView::OnRButtonDblClk(nFlags, point);
}


void CClippingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLButtonDown)
	{
		Clear();
		m_RectRtBt = point;
		CClientDC dc(this);
		dc.Rectangle(m_RectLtTp.x, m_RectLtTp.y, m_RectRtBt.x, m_RectRtBt.y);
	}
	else if (m_bRButtonDown)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(m_StartPoint);
		dc.LineTo(m_EndPoint);
		dc.MoveTo(m_StartPoint);
		dc.LineTo(point);
		m_EndPoint = point;
	}
	CView::OnMouseMove(nFlags, point);
}


void CClippingView::CutTop(CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	int ty = max(m_RectLtTp.y, m_RectRtBt.y);
	CArray<CPoint, CPoint&> cpts;
	CPoint f, p, s;
	int c1 = 0, c2 = 0;
	for (int i = 0; i < points.GetSize(); i++)
	{
		p = points.GetAt(i);
		if (i != 0)
		{
			c2 = p.y > ty ? -1 : 1;
			if (c1 + c2 == 0)	// 在 top 线异侧
			{
				CPoint pt;
				pt.y = ty;
				pt.x = (p.x - s.x) * (pt.y - s.y) / (p.y - s.y) + s.x;
				cpts.Add(pt);
			}
		}
		else
		{
			f = p;
		}
		s = p;
		if (s.y > ty)	// 第一个点在 top 线不可见一侧（矩形外侧）
		{
			c1 = -1;
		}
		else			// 第一个点在 top 线可见一侧（矩形内侧）
		{
			c1 = 1;
			cpts.Add(p);
		}
	}
	c2 = f.y > ty ? -1 : 1;
	if (c1 + c2 == 0 && c1 !=0 && c2 != 0)
	{
		CPoint pt;
		pt.y = ty;
		pt.x = (f.x - s.x) * (pt.y - s.y) / (f.y - s.y) + s.x;
		cpts.Add(pt);
	}
	points.RemoveAll();
	points.Append(cpts);
}


void CClippingView::CutRight(CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	int rx = max(m_RectLtTp.x, m_RectRtBt.x);
	CArray<CPoint, CPoint&> cpts;
	CPoint f, p, s;
	int c1 = 0, c2 = 0;
	for (int i = 0; i < points.GetSize(); i++)
	{
		p = points.GetAt(i);
		if (i != 0)
		{
			c2 = p.x > rx ? -1 : 1;
			if (c1 + c2 == 0)	// 在 right 线异侧
			{
				CPoint pt;
				pt.x = rx;
				pt.y = (p.y - s.y) * (pt.x - s.x) / (p.x - s.x) + s.y;
				cpts.Add(pt);
			}
		}
		else
		{
			f = p;
		}
		s = p;
		if (s.x > rx)	// 第一个点在 right 线不可见一侧（矩形外侧）
		{
			c1 = -1;
		}
		else			// 第一个点在 right 线可见一侧（矩形内侧）
		{
			c1 = 1;
			cpts.Add(p);
		}
	}
	c2 = f.x > rx ? -1 : 1;
	if (c1 + c2 == 0 && c1 != 0 && c2 != 0)
	{
		CPoint pt;
		pt.x = rx;
		pt.y = (f.y - s.y) * (pt.x - s.x) / (f.x - s.x) + s.y;
		cpts.Add(pt);
	}
	points.RemoveAll();
	points.Append(cpts);
}


void CClippingView::CutBottom(CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	int by = min(m_RectLtTp.y, m_RectRtBt.y);
	CArray<CPoint, CPoint&> cpts;
	CPoint f, p, s;
	int c1 = 0, c2 = 0;
	for (int i = 0; i < points.GetSize(); i++)
	{
		p = points.GetAt(i);
		if (i != 0)
		{
			c2 = p.y < by ? -1 : 1;
			if (c1 + c2 == 0)	// 在 bottom 线异侧
			{
				CPoint pt;
				pt.y = by;
				pt.x = (p.x - s.x) * (pt.y - s.y) / (p.y - s.y) + s.x;
				cpts.Add(pt);
			}
		}
		else
		{
			f = p;
		}
		s = p;
		if (s.y < by)	// 第一个点在 bottom 线不可见一侧（矩形外侧）
		{
			c1 = -1;
		}
		else			// 第一个点在 bottom 线可见一侧（矩形内侧）
		{
			c1 = 1;
			cpts.Add(p);
		}
	}
	c2 = f.y < by ? -1 : 1;
	if (c1 + c2 == 0 && c1 != 0 && c2 != 0)
	{
		CPoint pt;
		pt.y = by;
		pt.x = (f.x - s.x) * (pt.y - s.y) / (f.y - s.y) + s.x;
		cpts.Add(pt);
	}
	points.RemoveAll();
	points.Append(cpts);
}


void CClippingView::CutLeft(CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	int lx = min(m_RectLtTp.x, m_RectRtBt.x);
	CArray<CPoint, CPoint&> cpts;
	CPoint f, p, s;
	int c1 = 0, c2 = 0;
	for (int i = 0; i < points.GetSize(); i++)
	{
		p = points.GetAt(i);
		if (i != 0)
		{
			c2 = p.x < lx ? -1 : 1;
			if (c1 + c2 == 0)	// 在 left 线异侧
			{
				CPoint pt;
				pt.x = lx;
				pt.y = (p.y - s.y) * (pt.x - s.x) / (p.x - s.x) + s.y;
				cpts.Add(pt);
			}
		}
		else
		{
			f = p;
		}
		s = p;
		if (s.x < lx)	// 第一个点在 left 线不可见一侧（矩形外侧）
		{
			c1 = -1;
		}
		else			// 第一个点在 left 线可见一侧（矩形内侧）
		{
			c1 = 1;
			cpts.Add(p);
		}
	}
	c2 = f.x < lx ? -1 : 1;
	if (c1 + c2 == 0 && c1 != 0 && c2 != 0)
	{
		CPoint pt;
		pt.x = lx;
		pt.y = (f.y - s.y) * (pt.x - s.x) / (f.x - s.x) + s.y;
		cpts.Add(pt);
	}
	points.RemoveAll();
	points.Append(cpts);
}


void CClippingView::SutherlandHodgman(const CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	CArray<CPoint, CPoint&> tmp_points;
	tmp_points.Append(points);
	CutTop(tmp_points);
	CutRight(tmp_points);
	CutBottom(tmp_points);
	CutLeft(tmp_points);

	//FillRect(tmp_points, RGB(255, 255, 0));
	DrawPolyLine(tmp_points, 4, RGB(0, 255, 0));
}


void CClippingView::FillRect(const CArray<CPoint, CPoint&>& points, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	if (points.GetSize() != 0)
	{
		CClientDC dc(this);
		dc.BeginPath();
		dc.MoveTo(points.GetAt(0));
		for (int i = 1; i <= points.GetSize(); i++)
		{
			/*CPen pen;
			pen.CreatePen(PS_SOLID, 1, color);
			CPen * pOldPen = dc.SelectObject(&pen);*/
			dc.LineTo(points.GetAt(i % points.GetSize()).x, points.GetAt(i % points.GetSize()).y);
			//dc.SelectObject(pOldPen);
		}
		dc.EndPath();
		CRgn rgn;
		CBrush br;
		br.CreateSolidBrush(color);
		rgn.CreateFromPath(&dc);
		dc.InvertRgn(&rgn);
		dc.FillRgn(&rgn, &br);
	}
}


// 根据给定的 points 多边形，绘制多边形本身和被显示区域截取部分
void CClippingView::DrawView(const CArray<CPoint, CPoint&>& points)
{
	// TODO: 在此处添加实现代码.

	DrawPolyLine(points, 2, RGB(255, 0, 0));
	//FillRect(points, RGB(0, 255, 255));
	SutherlandHodgman(points);
}


void CClippingView::DrawPolyLine(const CArray<CPoint, CPoint&>& points, int width, COLORREF color)
{
	// TODO: 在此处添加实现代码.

	if (points.GetSize() == 0)
		return;

	CPen pen;
	pen.CreatePen(PS_SOLID, width, color);

	CDC* pDC = GetDC();
	CPen* oldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(points.GetAt(0));
	for (int i = 1; i <= points.GetSize(); i++)
	{
		pDC->LineTo(points.GetAt(i % points.GetSize()).x, points.GetAt(i % points.GetSize()).y);
	}
	pDC->SelectObject(oldPen);
}
