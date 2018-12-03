
// DynamicBezierView.cpp: CDynamicBezierView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DynamicBezier.h"
#endif

#include "DynamicBezierDoc.h"
#include "DynamicBezierView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDynamicBezierView

IMPLEMENT_DYNCREATE(CDynamicBezierView, CView)

BEGIN_MESSAGE_MAP(CDynamicBezierView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTON_START, &CDynamicBezierView::OnButtonStartClick)
	ON_COMMAND(ID_BUTTON_PAUSE, &CDynamicBezierView::OnButtonPauseClick)
END_MESSAGE_MAP()

// CDynamicBezierView 构造/析构

CDynamicBezierView::CDynamicBezierView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = false;
	m_bHasInputFinished = false;
}

CDynamicBezierView::~CDynamicBezierView()
{
}

BOOL CDynamicBezierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDynamicBezierView 绘图

void CDynamicBezierView::OnDraw(CDC* /*pDC*/)
{
	CDynamicBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RefreshView();
}


// CDynamicBezierView 打印

BOOL CDynamicBezierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDynamicBezierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDynamicBezierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDynamicBezierView 诊断

#ifdef _DEBUG
void CDynamicBezierView::AssertValid() const
{
	CView::AssertValid();
}

void CDynamicBezierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynamicBezierDoc* CDynamicBezierView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDynamicBezierDoc)));
	return (CDynamicBezierDoc*)m_pDocument;
}
#endif //_DEBUG


// CDynamicBezierView 消息处理程序


void CDynamicBezierView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bHasInputFinished)
	{
		m_bLButtonDown = true;
		m_ptControlPoints.Add(COpPoint(point));
		m_nDir.Add(1);
		m_StartPoint = point;
		m_EndPoint = point;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CDynamicBezierView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Clear();
	KillTimer(1);
	m_ptControlPoints.RemoveAll();
	m_nDir.RemoveAll();
	m_bLButtonDown = false;
	m_bHasInputFinished = false;
	CView::OnLButtonUp(nFlags, point);
}


void CDynamicBezierView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bLButtonDown)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		dc.MoveTo((CPoint)m_StartPoint);
		dc.LineTo((CPoint)m_EndPoint);
		m_EndPoint = point;
		dc.MoveTo((CPoint)m_StartPoint);
		dc.LineTo((CPoint)m_EndPoint);
	}
	CView::OnMouseMove(nFlags, point);
}


void CDynamicBezierView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLButtonDown = false;
	m_bHasInputFinished = true;
	RefreshView();
	CView::OnLButtonDblClk(nFlags, point);
}


void CDynamicBezierView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}


void CDynamicBezierView::RefreshView()
{
	// TODO: 在此处添加实现代码.
	Clear();
	CClientDC dc(this);
	if (m_ptControlPoints.GetSize() != 0)
	{
		dc.MoveTo(m_ptControlPoints.GetAt(0));
		for (int i = 1; i <= m_ptControlPoints.GetSize(); i++)
			dc.LineTo(m_ptControlPoints.GetAt(i % m_ptControlPoints.GetSize()));
	}

	for (int i = 0; i < m_ptControlPoints.GetSize(); i++)
	{
		CArray<COpPoint, COpPoint&> controls;
		COpPoint pt1 = m_ptControlPoints.GetAt(i % m_ptControlPoints.GetSize());
		COpPoint pt2 = m_ptControlPoints.GetAt((i + 1) % m_ptControlPoints.GetSize());
		COpPoint pt3 = m_ptControlPoints.GetAt((i + 2) % m_ptControlPoints.GetSize());

		controls.Add((pt1 + pt2) / 2);
		controls.Add(pt2);
		controls.Add((pt2 + pt3) / 2);

		CArray<COpPoint, COpPoint&> points;
		GetPoints(LINE_POINTS, controls, points);

		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = dc.SelectObject(&pen);
		dc.MoveTo(points.GetAt(0));
		for (int i = 1; i < points.GetSize(); i++)
		{
			COpPoint point = points.GetAt(i);
			dc.LineTo((CPoint)point);
		}
		dc.SelectObject(oldPen);
	}
	
}


CArray<COpPoint, COpPoint&>& CDynamicBezierView::GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处插入 return 语句
	double t = 0, delta;
	delta = 1.0 / (double)n;
	for (int i = 0; i <= n; i++)
	{
		points.Add(Decas(control, t));
		t += delta;
	}
	return points;
}


COpPoint CDynamicBezierView::Decas(CArray<COpPoint, COpPoint&>& control, double t)
{
	// TODO: 在此处添加实现代码.
	int m;
	COpPoint *R, *Q, P0;
	R = new COpPoint[control.GetSize()];
	Q = new COpPoint[control.GetSize()];
	for (int i = 0; i < control.GetSize(); i++)
		R[i] = control.GetAt(i);

	for (m = control.GetSize() - 1; m >= 0; m--)
	{
		for (int i = 0; i <= m - 1; i++)
		{
			Q[i] = R[i] + (R[i + 1] - R[i]) * t;
		}

		for (int i = 0; i <= m - 1; i++)
		{
			R[i] = Q[i];
		}
	}

	P0 = R[0];
	delete[] R;
	delete[] Q;
	return P0;
}

void CDynamicBezierView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);

	for (int i = 0; i < m_ptControlPoints.GetSize(); i++)
	{
		COpPoint& point = m_ptControlPoints.GetAt(i);
		if (i % 2 == 1)
		{
			point.y += m_nDir.GetAt(i) * 3 * (i + 1);
			if (point.y >= rect.Height())
			{
				point.y = rect.Height();
				m_nDir.GetAt(i) = -m_nDir.GetAt(i);
			}
			else if (point.y <= 0)
			{
				point.y = 0;
				m_nDir.GetAt(i) = -m_nDir.GetAt(i);
			}
		}
		else
		{
			point.x += m_nDir.GetAt(i) * 3 * (i + 1);
			if (point.x >= rect.Width())
			{
				point.x = rect.Width();
				m_nDir.GetAt(i) = -m_nDir.GetAt(i);
			}
			else if (point.x <= 0)
			{
				point.x = 0;
				m_nDir.GetAt(i) = -m_nDir.GetAt(i);
			}
		}
	}

	RefreshView();

	CView::OnTimer(nIDEvent);
}


void CDynamicBezierView::OnButtonStartClick()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 50, NULL);
}


void CDynamicBezierView::OnButtonPauseClick()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}
