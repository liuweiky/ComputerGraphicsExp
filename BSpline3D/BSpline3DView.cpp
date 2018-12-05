
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
	ON_COMMAND(ID_BUTTONBSPLINE, &CBSpline3DView::OnButtonBSplineClick)
	ON_COMMAND(ID_BUTTONSYMMETRY, &CBSpline3DView::OnButtonSymmetryClick)
	ON_COMMAND(ID_BUTTON3D, &CBSpline3DView::OnButton3dClick)
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
	m_nType = TYPE_INPUT;
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
	switch (m_nType)
	{
	case TYPE_BSPLINE:
		DrawBSpline();
		break;
	case TYPE_SYMMETRY:
		DrawSymmetry();
		break;
	case TYPE_ROTATE:
		DrawCabinet();
		break;
	default:
		break;
	}
}



void CBSpline3DView::DrawSymmetry()
{
	// TODO: 在此处添加实现代码.
	Clear();
	if (m_ptControlPoints.GetSize() < 1)
		return;
	CClientDC dc(this);

	dc.MoveTo(m_ptControlPoints.GetAt(0));
	for (int i = 1; i < m_ptControlPoints.GetSize(); i++)
	{
		dc.LineTo(m_ptControlPoints.GetAt(i));
	}
	dc.MoveTo(m_ptControlPoints.GetAt(0));
	for (int i = 1; i < m_ptControlPoints.GetSize(); i++)
	{
		COpPoint sp = CPoint(2 * m_ptControlPoints.GetAt(0).x - m_ptControlPoints.GetAt(i).x, m_ptControlPoints.GetAt(i).y);
		dc.LineTo(sp);
	}

	CArray<COpPoint, COpPoint&> pts;
	CArray<COpPoint, COpPoint&> ptSymmetry;
	GetPoints(LINE_POINTS, m_ptControlPoints, pts);
	for (int i = 0; i < pts.GetSize(); i++)
	{
		COpPoint p = pts.GetAt(i);
		COpPoint sp = CPoint(2 * m_ptControlPoints.GetAt(0).x - p.x, p.y);
		sp.color = p.color;
		ptSymmetry.Add(sp);
	}
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
	dc.MoveTo(ptSymmetry.GetAt(0));
	for (int i = 1; i < LINE_POINTS; i++)
	{
		COpPoint point = ptSymmetry.GetAt(i);
		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 2, m_cRGB[point.color]);
		oldPen = dc.SelectObject(&pen);
		dc.LineTo((CPoint)point);
		dc.SelectObject(oldPen);
	}
	
}

void CBSpline3DView::DrawCabinet()
{
	// TODO: 在此处添加实现代码.
	Clear();
	if (m_ptControlPoints.GetSize() < 1)
		return;
	double theta = 1.107;
	double l = 0.5;
	m_pjMatrix[0][0] = 1; m_pjMatrix[0][1] = 0; m_pjMatrix[0][2] = l * cos(theta);	m_pjMatrix[0][3] = 0;
	m_pjMatrix[1][0] = 0; m_pjMatrix[1][1] = 1; m_pjMatrix[1][2] = l * sin(theta);	m_pjMatrix[1][3] = 0;
	m_pjMatrix[2][0] = 0; m_pjMatrix[2][1] = 0; m_pjMatrix[2][2] = 0;				m_pjMatrix[2][3] = 0;
	m_pjMatrix[3][0] = 0; m_pjMatrix[3][1] = 0; m_pjMatrix[3][2] = 0;				m_pjMatrix[3][3] = 1;
	Get3DPointsSet();
	DrawProjPoints();
}

void CBSpline3DView::Get2DPointsSet()
{
	for (int i = 0; i < DIVISION; i++)
	{
		for (int j = 0; j < LINE_POINTS; j++)
		{
			double h;
			CPoint point;
			CPoint3 point3D = m_pt3DPointsSet[i][j];
			point.x = point3D.x * m_pjMatrix[0][0] + point3D.y * m_pjMatrix[0][1] + point3D.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
			point.y = point3D.x * m_pjMatrix[1][0] + point3D.y * m_pjMatrix[1][1] + point3D.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
			h = point3D.x * m_pjMatrix[3][0] + point3D.y * m_pjMatrix[3][1] + point3D.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
			point.x /= h;
			point.y /= h;
			m_pt2DPointsSet[i][j] = point;
		}
	}
}

void CBSpline3DView::Get3DPointsSet()
{
	CArray<COpPoint, COpPoint&> pts;
	GetPoints(LINE_POINTS, m_ptControlPoints, pts);
	for (int j = 0; j < LINE_POINTS; j++)
	{
		CPoint3 point;
		point.x = pts.GetAt(j).x;
		point.y = pts.GetAt(j).y;
		point.z = 0;
		m_pt3DPointsSet[0][j] = point;
	}
	
	for (int i = 1; i < DIVISION; i++)
	{
		double theta = 2 * 3.14159265 / DIVISION * i;

		for (int j = 0; j < LINE_POINTS; j++)
		{
			CPoint3 point;
			m_pt3DPointsSet[0][j].x -= m_ptControlPoints.GetAt(0).x;
			point.z = m_pt3DPointsSet[0][j].z * cos(theta) - m_pt3DPointsSet[0][j].x * sin(theta);
			point.x = m_pt3DPointsSet[0][j].z * sin(theta) + m_pt3DPointsSet[0][j].x * cos(theta);
			point.y = m_pt3DPointsSet[0][j].y;
			m_pt3DPointsSet[i][j] = point;
			m_pt3DPointsSet[i][j].x += m_ptControlPoints.GetAt(0).x;
			m_pt3DPointsSet[0][j].x += m_ptControlPoints.GetAt(0).x;
		}
	}

}

void CBSpline3DView::DrawProjPoints()
{
	Get2DPointsSet();
	for (int i = 0; i < DIVISION; i++)
	{
		CClientDC dc(this);
		dc.MoveTo(m_pt2DPointsSet[i][0]);
		for (int j = 0; j < LINE_POINTS; j++)
		{
			dc.LineTo(m_pt2DPointsSet[i][j]);
		}
	}

	CClientDC dc(this);
	dc.MoveTo(m_pt2DPointsSet[0][0]);

	for (int i = 0; i <= DIVISION; i++)
	{
	
		dc.LineTo(m_pt2DPointsSet[i % DIVISION][0]);
	}

	dc.MoveTo(m_pt2DPointsSet[0][LINE_POINTS - 1]);

	for (int i = 0; i <= DIVISION; i++)
	{

		dc.LineTo(m_pt2DPointsSet[i % DIVISION][LINE_POINTS - 1]);
	}
}

void CBSpline3DView::DrawBSpline()
{
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


void CBSpline3DView::OnButtonBSplineClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nType = TYPE_BSPLINE;
	ReDraw();
}


void CBSpline3DView::OnButtonSymmetryClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nType = TYPE_SYMMETRY;
	ReDraw();
}


void CBSpline3DView::OnButton3dClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nType = TYPE_ROTATE;
	ReDraw();
}
