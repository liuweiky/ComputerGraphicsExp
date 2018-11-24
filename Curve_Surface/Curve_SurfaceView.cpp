
// Curve_SurfaceView.cpp: CCurveSurfaceView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Curve_Surface.h"
#endif

#include "Curve_SurfaceDoc.h"
#include "Curve_SurfaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCurveSurfaceView

IMPLEMENT_DYNCREATE(CCurveSurfaceView, CView)

BEGIN_MESSAGE_MAP(CCurveSurfaceView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_HERMITE, &CCurveSurfaceView::OnButtonHermiteClick)
	ON_COMMAND(ID_BUTTON_BEZIER, &CCurveSurfaceView::OnButtonBezierClick)
	ON_COMMAND(ID_BUTTON_BSPLINE, &CCurveSurfaceView::OnButtonBsplineClick)
	ON_COMMAND(ID_BUTTON_BZSURFACE, &CCurveSurfaceView::OnButtonBzsurface)
END_MESSAGE_MAP()

// CCurveSurfaceView 构造/析构

CCurveSurfaceView::CCurveSurfaceView() noexcept
{
	// TODO: 在此处添加构造代码
	type = new Hermite(this);
	// type = new Bezier(this);
	// type = new BSpline(this);
	// type = new BezierSurface(this);
}

CCurveSurfaceView::~CCurveSurfaceView()
{
}

BOOL CCurveSurfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCurveSurfaceView 绘图

void CCurveSurfaceView::OnDraw(CDC* /*pDC*/)
{
	CCurveSurfaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	type->ReDraw();
}


// CCurveSurfaceView 打印

BOOL CCurveSurfaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCurveSurfaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCurveSurfaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCurveSurfaceView 诊断

#ifdef _DEBUG
void CCurveSurfaceView::AssertValid() const
{
	CView::AssertValid();
}

void CCurveSurfaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCurveSurfaceDoc* CCurveSurfaceView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurveSurfaceDoc)));
	return (CCurveSurfaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CCurveSurfaceView 消息处理程序


void CCurveSurfaceView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	type->OnLButtonDown(nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}


void CCurveSurfaceView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	type->OnLButtonUp(nFlags, point);
	CView::OnLButtonUp(nFlags, point);
}


void CCurveSurfaceView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	type->OnMouseMove(nFlags, point);
	CView::OnMouseMove(nFlags, point);
}


void CCurveSurfaceView::OnButtonHermiteClick()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NULL)
	{
		delete type;
	}
	type = new Hermite(this);
	Clear();
}


void CCurveSurfaceView::OnButtonBezierClick()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NULL)
	{
		delete type;
	}
	type = new Bezier(this);
	Clear();
}


void CCurveSurfaceView::OnButtonBsplineClick()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NULL)
	{
		delete type;
	}
	type = new BSpline(this);
	Clear();
}


void CCurveSurfaceView::OnButtonBzsurface()
{
	// TODO: 在此添加命令处理程序代码
	if (type != NULL)
	{
		delete type;
	}
	type = new BezierSurface(this);
	Clear();
	SetPointsDialog dialog;
	BezierSurface* bs = (BezierSurface*)type;
	if (dialog.DoModal() == IDOK)
	{
		bs->m_ptControlPoints[0] = CPoint3(dialog.p11x, dialog.p11y, dialog.p11z);
		bs->m_ptControlPoints[1] = CPoint3(dialog.p12x, dialog.p12y, dialog.p12z);
		bs->m_ptControlPoints[2] = CPoint3(dialog.p13x, dialog.p13y, dialog.p13z);
		bs->m_ptControlPoints[3] = CPoint3(dialog.p14x, dialog.p14y, dialog.p14z);

		bs->m_ptControlPoints[4] = CPoint3(dialog.p21x, dialog.p21y, dialog.p21z);
		bs->m_ptControlPoints[5] = CPoint3(dialog.p22x, dialog.p22y, dialog.p22z);
		bs->m_ptControlPoints[6] = CPoint3(dialog.p23x, dialog.p23y, dialog.p23z);
		bs->m_ptControlPoints[7] = CPoint3(dialog.p24x, dialog.p24y, dialog.p24z);

		bs->m_ptControlPoints[8] = CPoint3(dialog.p31x, dialog.p31y, dialog.p31z);
		bs->m_ptControlPoints[9] = CPoint3(dialog.p32x, dialog.p32y, dialog.p32z);
		bs->m_ptControlPoints[10] = CPoint3(dialog.p33x, dialog.p33y, dialog.p33z);
		bs->m_ptControlPoints[11] = CPoint3(dialog.p34x, dialog.p34y, dialog.p34z);

		bs->m_ptControlPoints[12] = CPoint3(dialog.p41x, dialog.p41y, dialog.p41z);
		bs->m_ptControlPoints[13] = CPoint3(dialog.p42x, dialog.p42y, dialog.p42z);
		bs->m_ptControlPoints[14] = CPoint3(dialog.p43x, dialog.p43y, dialog.p43z);
		bs->m_ptControlPoints[15] = CPoint3(dialog.p44x, dialog.p44y, dialog.p44z);
	}
	type->ReDraw();
}


void CCurveSurfaceView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}
