
// Circle_EllipseView.cpp: CCircleEllipseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Circle_Ellipse.h"
#endif

#include "Circle_EllipseDoc.h"
#include "Circle_EllipseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircleEllipseView

IMPLEMENT_DYNCREATE(CCircleEllipseView, CView)

BEGIN_MESSAGE_MAP(CCircleEllipseView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CIRCLE, &CCircleEllipseView::OnCircleClick)
	ON_COMMAND(ID_ELLIPSE, &CCircleEllipseView::OnEllipseClick)
END_MESSAGE_MAP()

// CCircleEllipseView 构造/析构

CCircleEllipseView::CCircleEllipseView() noexcept
{
	// TODO: 在此处添加构造代码
	m_nDrawType = 0;
	m_bHasLButtonDown = false;
}

CCircleEllipseView::~CCircleEllipseView()
{
}

BOOL CCircleEllipseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCircleEllipseView 绘图

void CCircleEllipseView::OnDraw(CDC* /*pDC*/)
{
	CCircleEllipseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCircleEllipseView 打印

BOOL CCircleEllipseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCircleEllipseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCircleEllipseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCircleEllipseView 诊断

#ifdef _DEBUG
void CCircleEllipseView::AssertValid() const
{
	CView::AssertValid();
}

void CCircleEllipseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCircleEllipseDoc* CCircleEllipseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircleEllipseDoc)));
	return (CCircleEllipseDoc*)m_pDocument;
}
#endif //_DEBUG


// CCircleEllipseView 消息处理程序


void CCircleEllipseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//BresenhamCircle(this->GetDC(), 100, CPoint(200, 200), RGB(0, 0, 0));
	//MidPointEllipse(this->GetDC(), CPoint(100, 100), CPoint(150, 200), RGB(50, 50, 50));
	if (m_nDrawType == CIRCLE || m_nDrawType == ELLIPSE)
	{
		this->SetCapture();
		m_StartPoint = point;
		m_EndPoint = point;
		m_bHasLButtonDown = true;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CCircleEllipseView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	m_bHasLButtonDown = false;
	CView::OnLButtonUp(nFlags, point);
}


void CCircleEllipseView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bHasLButtonDown && m_nDrawType == CIRCLE)
	{
		CDC* pDC = this->GetDC();
		pDC->SetROP2(R2_NOT);
		BresenhamCircle(pDC, GetDistance(m_EndPoint, m_StartPoint), m_StartPoint, RGB(0, 0, 0));
		BresenhamCircle(pDC, GetDistance(point, m_StartPoint), m_StartPoint, RGB(0, 0, 0));
	}
	else if (m_bHasLButtonDown && m_nDrawType == ELLIPSE)
	{
		CDC* pDC = this->GetDC();
		pDC->SetROP2(R2_NOT);
		MidPointEllipse(pDC, m_StartPoint, m_EndPoint, RGB(0, 0, 0));
		MidPointEllipse(pDC, m_StartPoint, point, RGB(0, 0, 0));
	}
	m_EndPoint = point;
	CView::OnMouseMove(nFlags, point);
}


void CCircleEllipseView::OnCircleClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = CIRCLE;
}


void CCircleEllipseView::OnEllipseClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = ELLIPSE;
}


void CCircleEllipseView::BresenhamCircle(CDC* pDC, int R, CPoint point, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	int x, y, p;
	x = 0; y = R; p = 3 - 2 * R;
	for (; x <= y; x++)
	{
		pDC->SetPixel(CPoint(x + point.x, y + point.y), color);
		pDC->SetPixel(CPoint(-x + point.x, y + point.y), color);
		pDC->SetPixel(CPoint(x + point.x, -y + point.y), color);
		pDC->SetPixel(CPoint(-x + point.x, -y + point.y), color);
		pDC->SetPixel(CPoint(y + point.x, x + point.y), color);
		pDC->SetPixel(CPoint(-y + point.x, x + point.y), color);
		pDC->SetPixel(CPoint(y + point.x, -x + point.y), color);
		pDC->SetPixel(CPoint(-y + point.x, -x + point.y), color);

		if (p >= 0)
		{
			p += 4 * (x - y) + 10;
			y--;
		}
		else
		{
			p += 4 * x + 6;
		}
	}
}


double CCircleEllipseView::GetDistance(CPoint pnt1, CPoint pnt2)
{
	// TODO: 在此处添加实现代码.
	return sqrt((pnt1.x - pnt2.x) * (pnt1.x - pnt2.x) + (pnt1.y - pnt2.y) * (pnt1.y - pnt2.y));
}


void CCircleEllipseView::MidPointEllipse(CDC* pDC, CPoint pnt1, CPoint pnt2, COLORREF color)
{
	// TODO: 在此处添加实现代码.
	double a = abs(pnt1.x - pnt2.x);
	double b = abs(pnt1.y - pnt2.y);

	CPoint center = CPoint((pnt1.x + pnt2.x) / 2, (pnt1.y + pnt2.y) / 2);

	int x, y;
	double d1, d2;
	x = 0; y = b;

	d1 = b * b + a * a * (-b + 0.25);

	pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
	pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
	pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);

	while (b * b * (x + 1) < a * a * (y - 0.5))
	{
		if (d1 < 0)
		{
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else
		{
			d1 += (b * b * (2 * x + 3) + a * a * (-2 * y + 2));
			x++;
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}

	d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

	while (y > 0)
	{
		if (d2 < 0)
		{
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;
		}
		else
		{
			d2 += a * a * (-2 * y + 3);
			y--;
		}
		pDC->SetPixel(CPoint(x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, y + center.y), color);
		pDC->SetPixel(CPoint(x + center.x, -y + center.y), color);
		pDC->SetPixel(CPoint(-x + center.x, -y + center.y), color);
	}
}
