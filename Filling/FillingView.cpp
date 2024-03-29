
// FillingView.cpp: CFillingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Filling.h"
#endif

#include "FillingDoc.h"
#include "FillingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFillingView

IMPLEMENT_DYNCREATE(CFillingView, CView)

BEGIN_MESSAGE_MAP(CFillingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_SETCOLOR, &CFillingView::OnMenuSetcolorClick)
	ON_COMMAND(ID_MENU_CLEARSCREEN, &CFillingView::OnMenuClearscreenClick)
END_MESSAGE_MAP()

// CFillingView 构造/析构

CFillingView::CFillingView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bHasLButtonDown = false;
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			m_nMask[i][j] = false;
	m_nR = m_nG = m_nB = 0;
}

CFillingView::~CFillingView()
{
}

BOOL CFillingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFillingView 绘图

void CFillingView::OnDraw(CDC* /*pDC*/)
{
	CFillingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	for (int i = 0; i < m_ptMememto.GetSize(); i++)
	{
		CPointsMememto* m = (CPointsMememto*)m_ptMememto.GetAt(i);
		if (m->points.GetSize() != 0)
		{
			CDC* pDC = GetDC();
			pDC->MoveTo(m->points.GetAt(0));
			for (int j = 1; j <= m->points.GetSize(); j++)
				pDC->LineTo(m->points.GetAt(j % m->points.GetSize()));
			EdgeMarkFill(m->points, RGB(m_nR, m_nG, m_nB));
		}
		
	}
}


// CFillingView 打印

BOOL CFillingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFillingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFillingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CFillingView 诊断

#ifdef _DEBUG
void CFillingView::AssertValid() const
{
	CView::AssertValid();
}

void CFillingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFillingDoc* CFillingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFillingDoc)));
	return (CFillingDoc*)m_pDocument;
}
#endif //_DEBUG


// CFillingView 消息处理程序


//void CFillingView::DDALine(CDC* pDC, CPoint spnt, CPoint epnt, COLORREF color)
//{
//	// TODO: 在此处添加实现代码.
//	int x1 = spnt.x;
//	int x2 = epnt.x;
//	int y1 = spnt.y;
//	int y2 = epnt.y;
//
//	double dx, dy, e, x, y;
//
//	dx = x2 - x1;
//	dy = y2 - y1;
//
//	e = max(fabs(dx), fabs(dy));
//
//	dx /= e;
//	dy /= e;
//	x = x1;
//	y = y1;
//
//	for (int i = 0; i <= e; i++)
//	{
//		pDC->SetPixel(CPoint((int)(x + 0.5), (int)(y + 0.5)), color);
//		x += dx;
//		y += dy;
//	}
//}


void CFillingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	m_bHasLButtonDown = true;
	m_StartPoint = point;
	m_EndPoint = point;
	m_PolygonPoints.Add(point);

	CView::OnLButtonDown(nFlags, point);
}


void CFillingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);
}


void CFillingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bHasLButtonDown)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(m_StartPoint);
		pDC->LineTo(m_EndPoint);
		pDC->MoveTo(m_StartPoint);
		pDC->LineTo(point);

		pDC = GetDC();
		pDC->MoveTo(m_PolygonPoints.GetAt(m_PolygonPoints.GetSize() - 1));
		pDC->LineTo(m_PolygonPoints.GetAt(0));
		ReleaseCapture();

		m_bHasLButtonDown = false;

		CPointsMememto* mememto = new CPointsMememto();
		mememto->points.Append(m_PolygonPoints);
		m_ptMememto.Add(mememto);
		EdgeMarkFill(m_PolygonPoints, RGB(m_nR, m_nG, m_nB));

		m_PolygonPoints.RemoveAll();

	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CFillingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bHasLButtonDown)
	{
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(m_StartPoint);
		pDC->LineTo(m_EndPoint);
		pDC->MoveTo(m_StartPoint);
		pDC->LineTo(point);

		m_EndPoint = point;
	}

	CView::OnMouseMove(nFlags, point);
}


void CFillingView::EdgeMarkFill(CArray<CPoint, CPoint&>& points, COLORREF color)
{
	// TODO: 在此处添加实现代码.

	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			m_nMask[i][j] = false;

	int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;

	for (int i = 0; i < points.GetSize(); i++)
	{
		if (minx > points.GetAt(i).x)
			minx = points.GetAt(i).x;
		else if (maxx < points.GetAt(i).x)
			maxx = points.GetAt(i).x;

		if (miny > points.GetAt(i).y)
			miny = points.GetAt(i).y;
		else if (maxy < points.GetAt(i).y)
			maxy = points.GetAt(i).y;
	}

	for (int i = 0; i < points.GetSize(); i++)
	{
		CPoint pt0 = points.GetAt((i + points.GetSize() - 1) % points.GetSize());

		CPoint pt1 = points.GetAt(i);
		CPoint pt2 = points.GetAt((i + 1) % points.GetSize());

		double dxs, dys, xs, ys;
		xs = pt1.x;
		dxs = (double)(pt2.x - pt1.x) / (pt2.y - pt1.y);
		dys = fabs((pt2.y - pt1.y)) / (pt2.y - pt1.y);

		for (ys = pt1.y; ys != pt2.y; ys += dys)
		{
			m_nMask[(int)ys][(int)(xs + 0.5)] = !m_nMask[(int)ys][(int)(xs + 0.5)];
			xs += (dxs * dys);
		}

		// 直接把顶点去掉，防止拖尾
		if ((pt1.y <= pt0.y && pt1.y <= pt2.y) || (pt1.y >= pt0.y && pt1.y >= pt2.y))
		{
			m_nMask[pt1.y][pt1.x] = false;
		}
	}

	CDC* pDC = GetDC();

	int bitmap[BKG_ROW_NUM][BKG_COL_NUM] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	};

	int x, y;
	for (y = 0; y < MAX_Y; y++)
	{
		bool inside = false;
		int ptscnt = 0;

		for (x = 0; x < MAX_X; x++)
		{
			if (m_nMask[y][x])
				inside = !inside;
			if (inside && bitmap[y % BKG_ROW_NUM][x % BKG_COL_NUM])
				pDC->SetPixel(x, y, color);
		}
	}
}


void CFillingView::OnMenuSetcolorClick()
{
	// TODO: 在此添加命令处理程序代码
	SetColorDialog dialog;
	if (dialog.DoModal() == IDOK)
	{
		m_nR = dialog.m_nR;
		m_nG = dialog.m_nG;
		m_nB = dialog.m_nB;
		Clear();

		for (int i = 0; i < m_ptMememto.GetSize(); i++)
		{
			CPointsMememto* m = (CPointsMememto*)m_ptMememto.GetAt(i);
			if (m->points.GetSize() != 0)
			{
				CDC* pDC = GetDC();
				pDC->MoveTo(m->points.GetAt(0));
				for (int j = 1; j <= m->points.GetSize(); j++)
					pDC->LineTo(m->points.GetAt(j % m->points.GetSize()));
				EdgeMarkFill(m->points, RGB(m_nR, m_nG, m_nB));
			}

		}
	}
	
}


void CFillingView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}


void CFillingView::OnMenuClearscreenClick()
{
	// TODO: 在此添加命令处理程序代码
	Clear();
	m_ptMememto.RemoveAll();
	m_PolygonPoints.RemoveAll();
}
