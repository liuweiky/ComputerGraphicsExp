
// BSpline3DView.cpp: CBSpline3DView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BSpline3D.h"
#endif

#include "BSpline3DDoc.h"
#include "BSpline3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBSpline3DView

IMPLEMENT_DYNCREATE(CBSpline3DView, CView)

BEGIN_MESSAGE_MAP(CBSpline3DView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CBSpline3DView 构造/析构

CBSpline3DView::CBSpline3DView() noexcept
{
	// TODO: 在此处添加构造代码
	m_bLButtonDown = false;
	for (int i = 0; i < K + MAX_N + 1; i++)
	{
		m_fKnot[i] = i;
	}
	m_cRGB[0] = RGB(255, 0, 0);
	m_cRGB[1] = RGB(0, 255, 0);
	m_cRGB[2] = RGB(0, 0, 255);
}

CBSpline3DView::~CBSpline3DView()
{
}

BOOL CBSpline3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBSpline3DView 绘图

void CBSpline3DView::OnDraw(CDC* /*pDC*/)
{
	CBSpline3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	ReDraw();
}


// CBSpline3DView 打印

BOOL CBSpline3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBSpline3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBSpline3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CBSpline3DView 诊断

#ifdef _DEBUG
void CBSpline3DView::AssertValid() const
{
	CView::AssertValid();
}

void CBSpline3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBSpline3DDoc* CBSpline3DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBSpline3DDoc)));
	return (CBSpline3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CBSpline3DView 消息处理程序


void CBSpline3DView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}


void CBSpline3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bLButtonDown)
	{
		m_ptControlPoints.RemoveAll();
		Clear();
	}
	m_bLButtonDown = true;
	m_ptControlPoints.Add(COpPoint(point));
	m_StartPoint = point;
	m_EndPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void CBSpline3DView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLButtonDown = false;
	ReDraw();
	CView::OnLButtonDblClk(nFlags, point);
}


void CBSpline3DView::OnMouseMove(UINT nFlags, CPoint point)
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

CArray<COpPoint, COpPoint&>& CBSpline3DView::GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处插入 return 语句
	double u, delta;
	delta = (m_fKnot[control.GetSize()] - m_fKnot[K - 1]) / (double)n;
	int j = K - 1;
	u = m_fKnot[K - 1];
	for (int i = 0; i <= n; i++)
	{
		while (j < control.GetSize() - 1 && u > m_fKnot[j + 1])	// n 个控制点，最大到Un-1开区间
		{
			j++;
		}

		points.Add(Deboor(control, u, j));
		u += delta;
	}
	return points;
}


COpPoint CBSpline3DView::Deboor(CArray<COpPoint, COpPoint&>& control, double u, int j)
{
	// TODO: 在此处添加实现代码.
	double denom, alpha;
	COpPoint P[K];
	const double epsilon = 0.0005;
	for (int i = 0; i < K; i++)
		P[i] = control.GetAt(j - K + 1 + i);
	for (int r = 1; r < K; r++)
	{
		for (int i = K - 1; i >= r; i--)
		{
			denom = m_fKnot[i - r + j + 1] - m_fKnot[i + j - K + 1];
			if (fabs(denom) < epsilon)
				alpha = 0;
			else
				alpha = (u - m_fKnot[i + j - K + 1]) / denom;
			P[i] = P[i - 1] * (1 - alpha) + P[i] * alpha;
		}
	}
	P[K - 1].color = j % 3;
	return P[K - 1];
}


void CBSpline3DView::ReDraw()
{
	// TODO: 在此处添加实现代码.
	Clear();
	if (m_ptControlPoints.GetSize() >= 4)
	{
		CClientDC dc(this);
		dc.MoveTo(m_ptControlPoints.GetAt(0));
		for (int i = 1; i < m_ptControlPoints.GetSize(); i++)
		{
			dc.LineTo(m_ptControlPoints.GetAt(i));
		}
		
		CArray<COpPoint, COpPoint&> pts;
		GetPoints(LINE_POINTS, m_ptControlPoints, pts);
		dc.MoveTo(pts.GetAt(0));
		for (int i = 1; i < LINE_POINTS; i++)
		{
			COpPoint point = pts.GetAt(i);
			CPen pen, *oldPen;
			pen.CreatePen(PS_SOLID, 2, m_cRGB[point.color]);
			oldPen = dc.SelectObject(&pen);
			dc.LineTo((CPoint)point);
			dc.SelectObject(oldPen);
		}
	}
}


void CBSpline3DView::DrawSymmetry()
{
	// TODO: 在此处添加实现代码.
}
