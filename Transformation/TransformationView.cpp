
// TransformationView.cpp: CTransformationView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Transformation.h"
#endif

#include "TransformationDoc.h"
#include "TransformationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransformationView

IMPLEMENT_DYNCREATE(CTransformationView, CView)

BEGIN_MESSAGE_MAP(CTransformationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MOVE, &CTransformationView::OnMoveClick)
	ON_COMMAND(ID_SCALE, &CTransformationView::OnScaleClick)
	ON_COMMAND(ID_ROTATE, &CTransformationView::OnRotateClick)
	ON_COMMAND(ID_ROTATEAXIS, &CTransformationView::OnRotateaxisClick)
	ON_COMMAND(ID_PROJCENTER, &CTransformationView::OnProjcenterClick)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_PERSPECTIVE, &CTransformationView::OnPerspectiveClick)
	ON_COMMAND(ID_ISOMETRIC, &CTransformationView::OnIsometricClick)
	ON_COMMAND(ID_CABINET, &CTransformationView::OnCabinetClick)
END_MESSAGE_MAP()

// CTransformationView 构造/析构

CTransformationView::CTransformationView() noexcept
{
	// TODO: 在此处添加构造代码
	m_nOpType = 0;
	m_fScale = 1.01;
	m_nRotateAxis = ROTATE_Z;
	m_nViewType = VIEW_PERS;
	m_fPjX = m_fPjY = 0.0;
	m_fPjD = 600.0;

	double left = 200, right = 400;
	double bottom = 200, top = 400;
	double back = 200, front = 400;

	m_LtBkBt = CPoint3(left, back, bottom);
	m_LtBkTp = CPoint3(left, back, top);
	m_LtFtBt = CPoint3(left, front, bottom);
	m_LtFtTp = CPoint3(left, front, top);
	m_RtBkBt = CPoint3(right, back, bottom);
	m_RtBkTp = CPoint3(right, back, top);
	m_RtFtBt = CPoint3(right, front, bottom);
	m_RtFtTp = CPoint3(right, front, top);
}

CTransformationView::~CTransformationView()
{
}

BOOL CTransformationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTransformationView 绘图

void CTransformationView::OnDraw(CDC* /*pDC*/)
{
	CTransformationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	DrawAxis();
	DrawView();
	//DrawProj();
}


// CTransformationView 打印

BOOL CTransformationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTransformationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTransformationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTransformationView 诊断

#ifdef _DEBUG
void CTransformationView::AssertValid() const
{
	CView::AssertValid();
}

void CTransformationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTransformationDoc* CTransformationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransformationDoc)));
	return (CTransformationDoc*)m_pDocument;
}
#endif //_DEBUG


// CTransformationView 消息处理程序


void CTransformationView::DrawRect(CPoint pt1, CPoint pt2, CPoint pt3, CPoint pt4)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	dc.MoveTo(pt1);
	dc.LineTo(pt2);
	dc.LineTo(pt3);
	dc.LineTo(pt4);
	dc.LineTo(pt1);
}


void CTransformationView::DrawProjCubic()
{
	// TODO: 在此处添加实现代码.
	DrawRect(m_pjLtBkBt, m_pjLtBkTp, m_pjLtFtTp, m_pjLtFtBt);
	DrawRect(m_pjRtBkBt, m_pjRtBkTp, m_pjRtFtTp, m_pjRtFtBt);
	DrawRect(m_pjLtBkBt, m_pjLtBkTp, m_pjRtBkTp, m_pjRtBkBt);
	DrawRect(m_pjLtFtBt, m_pjLtFtTp, m_pjRtFtTp, m_pjRtFtBt);
	DrawRect(m_pjLtBkBt, m_pjLtFtBt, m_pjRtFtBt, m_pjRtBkBt);
	DrawRect(m_pjLtBkTp, m_pjLtFtTp, m_pjRtFtTp, m_pjRtBkTp);
}


void CTransformationView::From3DTo2D()
{
	// TODO: 在此处添加实现代码.

	double h;

	m_pjLtBkBt.x = m_LtBkBt.x * m_pjMatrix[0][0] + m_LtBkBt.y * m_pjMatrix[0][1] + m_LtBkBt.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjLtBkBt.y = m_LtBkBt.x * m_pjMatrix[1][0] + m_LtBkBt.y * m_pjMatrix[1][1] + m_LtBkBt.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_LtBkBt.x * m_pjMatrix[3][0] + m_LtBkBt.y * m_pjMatrix[3][1] + m_LtBkBt.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjLtBkBt.x /= h;
	m_pjLtBkBt.y /= h;

	m_pjLtBkTp.x = m_LtBkTp.x * m_pjMatrix[0][0] + m_LtBkTp.y * m_pjMatrix[0][1] + m_LtBkTp.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjLtBkTp.y = m_LtBkTp.x * m_pjMatrix[1][0] + m_LtBkTp.y * m_pjMatrix[1][1] + m_LtBkTp.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_LtBkTp.x * m_pjMatrix[3][0] + m_LtBkTp.y * m_pjMatrix[3][1] + m_LtBkTp.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjLtBkTp.x /= h;
	m_pjLtBkTp.y /= h;

	m_pjLtFtBt.x = m_LtFtBt.x * m_pjMatrix[0][0] + m_LtFtBt.y * m_pjMatrix[0][1] + m_LtFtBt.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjLtFtBt.y = m_LtFtBt.x * m_pjMatrix[1][0] + m_LtFtBt.y * m_pjMatrix[1][1] + m_LtFtBt.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_LtFtBt.x * m_pjMatrix[3][0] + m_LtFtBt.y * m_pjMatrix[3][1] + m_LtFtBt.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjLtFtBt.x /= h;
	m_pjLtFtBt.y /= h;
	
	m_pjLtFtTp.x = m_LtFtTp.x * m_pjMatrix[0][0] + m_LtFtTp.y * m_pjMatrix[0][1] + m_LtFtTp.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjLtFtTp.y = m_LtFtTp.x * m_pjMatrix[1][0] + m_LtFtTp.y * m_pjMatrix[1][1] + m_LtFtTp.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_LtFtTp.x * m_pjMatrix[3][0] + m_LtFtTp.y * m_pjMatrix[3][1] + m_LtFtTp.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjLtFtTp.x /= h;
	m_pjLtFtTp.y /= h;

	m_pjRtBkBt.x = m_RtBkBt.x * m_pjMatrix[0][0] + m_RtBkBt.y * m_pjMatrix[0][1] + m_RtBkBt.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjRtBkBt.y = m_RtBkBt.x * m_pjMatrix[1][0] + m_RtBkBt.y * m_pjMatrix[1][1] + m_RtBkBt.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_RtBkBt.x * m_pjMatrix[3][0] + m_RtBkBt.y * m_pjMatrix[3][1] + m_RtBkBt.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjRtBkBt.x /= h;
	m_pjRtBkBt.y /= h;
	
	m_pjRtBkTp.x = m_RtBkTp.x * m_pjMatrix[0][0] + m_RtBkTp.y * m_pjMatrix[0][1] + m_RtBkTp.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjRtBkTp.y = m_RtBkTp.x * m_pjMatrix[1][0] + m_RtBkTp.y * m_pjMatrix[1][1] + m_RtBkTp.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_RtBkTp.x * m_pjMatrix[3][0] + m_RtBkTp.y * m_pjMatrix[3][1] + m_RtBkTp.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjRtBkTp.x /= h;
	m_pjRtBkTp.y /= h;
	
	m_pjRtFtBt.x = m_RtFtBt.x * m_pjMatrix[0][0] + m_RtFtBt.y * m_pjMatrix[0][1] + m_RtFtBt.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjRtFtBt.y = m_RtFtBt.x * m_pjMatrix[1][0] + m_RtFtBt.y * m_pjMatrix[1][1] + m_RtFtBt.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_RtFtBt.x * m_pjMatrix[3][0] + m_RtFtBt.y * m_pjMatrix[3][1] + m_RtFtBt.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjRtFtBt.x /= h;
	m_pjRtFtBt.y /= h;
	
	m_pjRtFtTp.x = m_RtFtTp.x * m_pjMatrix[0][0] + m_RtFtTp.y * m_pjMatrix[0][1] + m_RtFtTp.z * m_pjMatrix[0][2] + m_pjMatrix[0][3];
	m_pjRtFtTp.y = m_RtFtTp.x * m_pjMatrix[1][0] + m_RtFtTp.y * m_pjMatrix[1][1] + m_RtFtTp.z * m_pjMatrix[1][2] + m_pjMatrix[1][3];
	h = m_RtFtTp.x * m_pjMatrix[3][0] + m_RtFtTp.y * m_pjMatrix[3][1] + m_RtFtTp.z * m_pjMatrix[3][2] + m_pjMatrix[3][3];
	m_pjRtFtTp.x /= h;
	m_pjRtFtTp.y /= h;
}


void CTransformationView::Clear()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);

	/*CDC* pDC = GetDC();

	pDC->MoveTo(5, 5);
	pDC->LineTo(window.Width(), 5);
	pDC->MoveTo(5, 5);
	pDC->LineTo(5, window.Height());

	CRect rec = CRect(1200, 10, 1220, 30);

	pDC->DrawText(CString("x"), &rec, DT_CENTER);

	rec = CRect(10, 600, 30, 620);

	pDC->DrawText(CString("y"), &rec, DT_CENTER);*/

	DrawAxis();

}


void CTransformationView::DrawPerspective()
{
	// TODO: 在此处添加实现代码.

	Clear();
	//double x0 = 2, y0 = 2;	// 投影中心
	//double d = 5;	// z0
	m_pjMatrix[0][0] = 1; m_pjMatrix[0][1] = 0; m_pjMatrix[0][2] = m_fPjX / m_fPjD;	m_pjMatrix[0][3] = 0;
	m_pjMatrix[1][0] = 0; m_pjMatrix[1][1] = 1; m_pjMatrix[1][2] = m_fPjY / m_fPjD;	m_pjMatrix[1][3] = 0;
	m_pjMatrix[2][0] = 0; m_pjMatrix[2][1] = 0; m_pjMatrix[2][2] = 0;				m_pjMatrix[2][3] = 0;
	m_pjMatrix[3][0] = 0; m_pjMatrix[3][1] = 0; m_pjMatrix[3][2] = 1.0 / m_fPjD;	m_pjMatrix[3][3] = 1;
	From3DTo2D();
	DrawProjCubic();
}


void CTransformationView::DrawIsom()
{
	// TODO: 在此处添加实现代码.

	Clear();
	m_pjMatrix[0][0] = 0.707107;	m_pjMatrix[0][1] = 0.707107;	m_pjMatrix[0][2] = 0;			m_pjMatrix[0][3] = 0;
	m_pjMatrix[1][0] = -0.408248;	m_pjMatrix[1][1] = 0.408248;	m_pjMatrix[1][2] = 0.816497;	m_pjMatrix[1][3] = 0;
	m_pjMatrix[2][0] = 0;			m_pjMatrix[2][1] = 0;			m_pjMatrix[2][2] = 0;			m_pjMatrix[2][3] = 0;
	m_pjMatrix[3][0] = 0;			m_pjMatrix[3][1] = 0;			m_pjMatrix[3][2] = 0;			m_pjMatrix[3][3] = 1;
	From3DTo2D();
	DrawProjCubic();
}


void CTransformationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (m_nOpType)
	{
	case TYPE_MOVE:
		MoveTransformation(nChar);
		break;
	case TYPE_SCALE:
		ScaleTransformation(nChar);
		break;
	case TYPE_ROTATE:
		RotateTransformation(nChar);
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTransformationView::OnMoveClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nOpType = TYPE_MOVE;
}


void CTransformationView::OnScaleClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nOpType = TYPE_SCALE;
}


void CTransformationView::OnRotateClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nOpType = TYPE_ROTATE;
}


void CTransformationView::MoveTransformation(UINT nChar)
{
	// TODO: 在此处添加实现代码.
	Clear();
	double step = 2;
	switch (nChar)
	{
	case 'Q':
		m_LtBkBt.x -= step;
		m_LtBkTp.x -= step;
		m_LtFtBt.x -= step;
		m_LtFtTp.x -= step;
		m_RtBkBt.x -= step;
		m_RtBkTp.x -= step;
		m_RtFtBt.x -= step;
		m_RtFtTp.x -= step;
		break;
	case 'W':
		m_LtBkBt.x += step;
		m_LtBkTp.x += step;
		m_LtFtBt.x += step;
		m_LtFtTp.x += step;
		m_RtBkBt.x += step;
		m_RtBkTp.x += step;
		m_RtFtBt.x += step;
		m_RtFtTp.x += step;
		break;
	case 'E':
		m_LtBkBt.y -= step;
		m_LtBkTp.y -= step;
		m_LtFtBt.y -= step;
		m_LtFtTp.y -= step;
		m_RtBkBt.y -= step;
		m_RtBkTp.y -= step;
		m_RtFtBt.y -= step;
		m_RtFtTp.y -= step;
		break;
	case 'R':
		m_LtBkBt.y += step;
		m_LtBkTp.y += step;
		m_LtFtBt.y += step;
		m_LtFtTp.y += step;
		m_RtBkBt.y += step;
		m_RtBkTp.y += step;
		m_RtFtBt.y += step;
		m_RtFtTp.y += step;
		break;
	case 'T':
		m_LtBkBt.z -= step;
		m_LtBkTp.z -= step;
		m_LtFtBt.z -= step;
		m_LtFtTp.z -= step;
		m_RtBkBt.z -= step;
		m_RtBkTp.z -= step;
		m_RtFtBt.z -= step;
		m_RtFtTp.z -= step;
		break;
	case 'Y':
		m_LtBkBt.z += step;
		m_LtBkTp.z += step;
		m_LtFtBt.z += step;
		m_LtFtTp.z += step;
		m_RtBkBt.z += step;
		m_RtBkTp.z += step;
		m_RtFtBt.z += step;
		m_RtFtTp.z += step;
		break;
	default:
		break;
	}
	//From3DTo2D();
	DrawView();
	//DrawProj();
}


void CTransformationView::ScaleTransformation(UINT nChar)
{
	// TODO: 在此处添加实现代码.
	Clear();

	CPoint3 center;
	center.x = (m_LtBkBt.x + m_RtFtBt.x) / 2;
	center.y = (m_LtBkBt.y + m_RtFtBt.y) / 2;
	center.z = (m_LtBkBt.z + m_LtFtTp.z) / 2;

	m_LtBkBt.x -= center.x; m_LtBkBt.y -= center.y; m_LtBkBt.z -= center.z;
	m_LtBkTp.x -= center.x; m_LtBkTp.y -= center.y; m_LtBkTp.z -= center.z;
	m_LtFtBt.x -= center.x; m_LtFtBt.y -= center.y; m_LtFtBt.z -= center.z;
	m_LtFtTp.x -= center.x; m_LtFtTp.y -= center.y; m_LtFtTp.z -= center.z;
	m_RtBkBt.x -= center.x; m_RtBkBt.y -= center.y; m_RtBkBt.z -= center.z;
	m_RtBkTp.x -= center.x; m_RtBkTp.y -= center.y; m_RtBkTp.z -= center.z;
	m_RtFtBt.x -= center.x; m_RtFtBt.y -= center.y; m_RtFtBt.z -= center.z;
	m_RtFtTp.x -= center.x; m_RtFtTp.y -= center.y; m_RtFtTp.z -= center.z;

	switch (nChar)
	{
	case VK_UP:
		m_LtBkBt.x *= m_fScale; m_LtBkBt.y *= m_fScale; m_LtBkBt.z *= m_fScale;
		m_LtBkTp.x *= m_fScale; m_LtBkTp.y *= m_fScale; m_LtBkTp.z *= m_fScale;
		m_LtFtBt.x *= m_fScale; m_LtFtBt.y *= m_fScale; m_LtFtBt.z *= m_fScale;
		m_LtFtTp.x *= m_fScale; m_LtFtTp.y *= m_fScale; m_LtFtTp.z *= m_fScale;
		m_RtBkBt.x *= m_fScale; m_RtBkBt.y *= m_fScale; m_RtBkBt.z *= m_fScale;
		m_RtBkTp.x *= m_fScale; m_RtBkTp.y *= m_fScale; m_RtBkTp.z *= m_fScale;
		m_RtFtBt.x *= m_fScale; m_RtFtBt.y *= m_fScale; m_RtFtBt.z *= m_fScale;
		m_RtFtTp.x *= m_fScale; m_RtFtTp.y *= m_fScale; m_RtFtTp.z *= m_fScale;
		break;
	case VK_DOWN:
		m_LtBkBt.x /= m_fScale; m_LtBkBt.y /= m_fScale; m_LtBkBt.z /= m_fScale;
		m_LtBkTp.x /= m_fScale; m_LtBkTp.y /= m_fScale; m_LtBkTp.z /= m_fScale;
		m_LtFtBt.x /= m_fScale; m_LtFtBt.y /= m_fScale; m_LtFtBt.z /= m_fScale;
		m_LtFtTp.x /= m_fScale; m_LtFtTp.y /= m_fScale; m_LtFtTp.z /= m_fScale;
		m_RtBkBt.x /= m_fScale; m_RtBkBt.y /= m_fScale; m_RtBkBt.z /= m_fScale;
		m_RtBkTp.x /= m_fScale; m_RtBkTp.y /= m_fScale; m_RtBkTp.z /= m_fScale;
		m_RtFtBt.x /= m_fScale; m_RtFtBt.y /= m_fScale; m_RtFtBt.z /= m_fScale;
		m_RtFtTp.x /= m_fScale; m_RtFtTp.y /= m_fScale; m_RtFtTp.z /= m_fScale;
	default:
		break;
	}

	m_LtBkBt.x += center.x; m_LtBkBt.y += center.y; m_LtBkBt.z += center.z;
	m_LtBkTp.x += center.x; m_LtBkTp.y += center.y; m_LtBkTp.z += center.z;
	m_LtFtBt.x += center.x; m_LtFtBt.y += center.y; m_LtFtBt.z += center.z;
	m_LtFtTp.x += center.x; m_LtFtTp.y += center.y; m_LtFtTp.z += center.z;
	m_RtBkBt.x += center.x; m_RtBkBt.y += center.y; m_RtBkBt.z += center.z;
	m_RtBkTp.x += center.x; m_RtBkTp.y += center.y; m_RtBkTp.z += center.z;
	m_RtFtBt.x += center.x; m_RtFtBt.y += center.y; m_RtFtBt.z += center.z;
	m_RtFtTp.x += center.x; m_RtFtTp.y += center.y; m_RtFtTp.z += center.z;

	DrawView();
}


void CTransformationView::RotateTransformation(UINT nChar)
{
	// TODO: 在此处添加实现代码.

	CPoint3 center;

	// 用 8 个点计算体心坐标，提高计算精度

	center.x = (m_LtBkBt.x + m_LtBkTp.x + m_LtFtBt.x + m_LtFtTp.x + m_RtBkBt.x + m_RtBkTp.x + m_RtFtBt.x + m_RtFtTp.x) / 8;
	center.y = (m_LtBkBt.y + m_LtBkTp.y + m_LtFtBt.y + m_LtFtTp.y + m_RtBkBt.y + m_RtBkTp.y + m_RtFtBt.y + m_RtFtTp.y) / 8;
	center.z = (m_LtBkBt.z + m_LtBkTp.z + m_LtFtBt.z + m_LtFtTp.z + m_RtBkBt.z + m_RtBkTp.z + m_RtFtBt.z + m_RtFtTp.z) / 8;

	double theta = 0.05;

	m_LtBkBt.x -= center.x; m_LtBkBt.y -= center.y; m_LtBkBt.z -= center.z;
	m_LtBkTp.x -= center.x; m_LtBkTp.y -= center.y; m_LtBkTp.z -= center.z;
	m_LtFtBt.x -= center.x; m_LtFtBt.y -= center.y; m_LtFtBt.z -= center.z;
	m_LtFtTp.x -= center.x; m_LtFtTp.y -= center.y; m_LtFtTp.z -= center.z;
	m_RtBkBt.x -= center.x; m_RtBkBt.y -= center.y; m_RtBkBt.z -= center.z;
	m_RtBkTp.x -= center.x; m_RtBkTp.y -= center.y; m_RtBkTp.z -= center.z;
	m_RtFtBt.x -= center.x; m_RtFtBt.y -= center.y; m_RtFtBt.z -= center.z;
	m_RtFtTp.x -= center.x; m_RtFtTp.y -= center.y; m_RtFtTp.z -= center.z;

	switch (nChar)
	{
	case VK_UP:
		Clear();
		break;
	case VK_DOWN:
		Clear();
		theta = -theta;
		break;
	default:
		m_LtBkBt.x += center.x; m_LtBkBt.y += center.y; m_LtBkBt.z += center.z;
		m_LtBkTp.x += center.x; m_LtBkTp.y += center.y; m_LtBkTp.z += center.z;
		m_LtFtBt.x += center.x; m_LtFtBt.y += center.y; m_LtFtBt.z += center.z;
		m_LtFtTp.x += center.x; m_LtFtTp.y += center.y; m_LtFtTp.z += center.z;
		m_RtBkBt.x += center.x; m_RtBkBt.y += center.y; m_RtBkBt.z += center.z;
		m_RtBkTp.x += center.x; m_RtBkTp.y += center.y; m_RtBkTp.z += center.z;
		m_RtFtBt.x += center.x; m_RtFtBt.y += center.y; m_RtFtBt.z += center.z;
		m_RtFtTp.x += center.x; m_RtFtTp.y += center.y; m_RtFtTp.z += center.z;
		return;
		break;
	}

	double ct = cos(theta);
	double st = sin(theta);

	double x, y, z;

	switch (m_nRotateAxis)
	{
	case ROTATE_X:
		y = m_LtBkBt.y; z = m_LtBkBt.z; m_LtBkBt.y = y * ct - z * st; m_LtBkBt.z = y * st + z * ct;
		y = m_LtBkTp.y; z = m_LtBkTp.z; m_LtBkTp.y = y * ct - z * st; m_LtBkTp.z = y * st + z * ct;
		y = m_LtFtBt.y; z = m_LtFtBt.z; m_LtFtBt.y = y * ct - z * st; m_LtFtBt.z = y * st + z * ct;
		y = m_LtFtTp.y; z = m_LtFtTp.z; m_LtFtTp.y = y * ct - z * st; m_LtFtTp.z = y * st + z * ct;
		y = m_RtBkBt.y; z = m_RtBkBt.z; m_RtBkBt.y = y * ct - z * st; m_RtBkBt.z = y * st + z * ct;
		y = m_RtBkTp.y; z = m_RtBkTp.z; m_RtBkTp.y = y * ct - z * st; m_RtBkTp.z = y * st + z * ct;
		y = m_RtFtBt.y; z = m_RtFtBt.z; m_RtFtBt.y = y * ct - z * st; m_RtFtBt.z = y * st + z * ct;
		y = m_RtFtTp.y; z = m_RtFtTp.z; m_RtFtTp.y = y * ct - z * st; m_RtFtTp.z = y * st + z * ct;
		break;
	case ROTATE_Y:
		z = m_LtBkBt.z; x = m_LtBkBt.x; m_LtBkBt.z = z * ct - x * st; m_LtBkBt.x = z * st + x * ct;
		z = m_LtBkTp.z; x = m_LtBkTp.x; m_LtBkTp.z = z * ct - x * st; m_LtBkTp.x = z * st + x * ct;
		z = m_LtFtBt.z; x = m_LtFtBt.x; m_LtFtBt.z = z * ct - x * st; m_LtFtBt.x = z * st + x * ct;
		z = m_LtFtTp.z; x = m_LtFtTp.x; m_LtFtTp.z = z * ct - x * st; m_LtFtTp.x = z * st + x * ct;
		z = m_RtBkBt.z; x = m_RtBkBt.x; m_RtBkBt.z = z * ct - x * st; m_RtBkBt.x = z * st + x * ct;
		z = m_RtBkTp.z; x = m_RtBkTp.x; m_RtBkTp.z = z * ct - x * st; m_RtBkTp.x = z * st + x * ct;
		z = m_RtFtBt.z; x = m_RtFtBt.x; m_RtFtBt.z = z * ct - x * st; m_RtFtBt.x = z * st + x * ct;
		z = m_RtFtTp.z; x = m_RtFtTp.x; m_RtFtTp.z = z * ct - x * st; m_RtFtTp.x = z * st + x * ct;
		break;
	case ROTATE_Z:
		x = m_LtBkBt.x; y = m_LtBkBt.y; m_LtBkBt.x = x * ct - y * st; m_LtBkBt.y = x * st + y * ct;
		x = m_LtBkTp.x; y = m_LtBkTp.y; m_LtBkTp.x = x * ct - y * st; m_LtBkTp.y = x * st + y * ct;
		x = m_LtFtBt.x; y = m_LtFtBt.y; m_LtFtBt.x = x * ct - y * st; m_LtFtBt.y = x * st + y * ct;
		x = m_LtFtTp.x; y = m_LtFtTp.y; m_LtFtTp.x = x * ct - y * st; m_LtFtTp.y = x * st + y * ct;
		x = m_RtBkBt.x; y = m_RtBkBt.y; m_RtBkBt.x = x * ct - y * st; m_RtBkBt.y = x * st + y * ct;
		x = m_RtBkTp.x; y = m_RtBkTp.y; m_RtBkTp.x = x * ct - y * st; m_RtBkTp.y = x * st + y * ct;
		x = m_RtFtBt.x; y = m_RtFtBt.y; m_RtFtBt.x = x * ct - y * st; m_RtFtBt.y = x * st + y * ct;
		x = m_RtFtTp.x; y = m_RtFtTp.y; m_RtFtTp.x = x * ct - y * st; m_RtFtTp.y = x * st + y * ct;
		break;
	default:
		break;
	}

	m_LtBkBt.x += center.x; m_LtBkBt.y += center.y; m_LtBkBt.z += center.z;
	m_LtBkTp.x += center.x; m_LtBkTp.y += center.y; m_LtBkTp.z += center.z;
	m_LtFtBt.x += center.x; m_LtFtBt.y += center.y; m_LtFtBt.z += center.z;
	m_LtFtTp.x += center.x; m_LtFtTp.y += center.y; m_LtFtTp.z += center.z;
	m_RtBkBt.x += center.x; m_RtBkBt.y += center.y; m_RtBkBt.z += center.z;
	m_RtBkTp.x += center.x; m_RtBkTp.y += center.y; m_RtBkTp.z += center.z;
	m_RtFtBt.x += center.x; m_RtFtBt.y += center.y; m_RtFtBt.z += center.z;
	m_RtFtTp.x += center.x; m_RtFtTp.y += center.y; m_RtFtTp.z += center.z;

	DrawView();
}


void CTransformationView::OnRotateaxisClick()
{
	// TODO: 在此添加命令处理程序代码
	SelectAxisDialog dialog;
	if (dialog.DoModal() == IDOK)
	{
		m_nRotateAxis = dialog.m_nRotateAxis;
	}
}


void CTransformationView::OnProjcenterClick()
{
	// TODO: 在此添加命令处理程序代码
	SetProjCenter dialog;
	if (dialog.DoModal() == IDOK)
	{
		m_fPjX = dialog.m_fX;
		m_fPjY = dialog.m_fY;
		m_fPjD = dialog.m_fZ;
	}
	Clear();
	DrawView();
}


void CTransformationView::DrawAxis()
{
	// TODO: 在此处添加实现代码.
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	int height = rect.Height();
	int width = rect.Width();
	int i;

	//画顶部的坐标轴
	//在最顶部画一条直线，作为坐标轴线
	pDC->MoveTo(0, 0);
	pDC->LineTo(width, 0);
	//画坐标轴刻度
	for (i = 0; i < width; i += 10)
	{
		//坐标距离为100像素的，刻度竖线长度为50像素
		if (i % 100 == 0)
		{
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 50);
		}
		//坐标距离为50像素的，刻度竖线长度为25像素
		else if (i % 50 == 0)
		{
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 25);
		}
		//坐标距离为10像素的，刻度竖线长度为10像素
		else
		{
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 10);
		}

	}

	//画左部的坐标轴
	//在最左部画一条直线，作为坐标轴线
	pDC->MoveTo(0, height);
	pDC->LineTo(0, 0);
	//画坐标轴刻度
	for (i = 50; i < height; i += 10)
	{
		//坐标距离为100像素的，刻度竖线长度为50像素
		if (i % 100 == 0)
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(50, i);
		}
		//坐标距离为50像素的，刻度竖线长度为25像素
		else if (i % 50 == 0)
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(25, i);
		}
		//坐标距离为10像素的，刻度竖线长度为10像素
		else
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(10, i);
		}
	}
}


void CTransformationView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_nViewType == VIEW_CABI)
		m_nViewType = VIEW_PERS;
	else if (m_nViewType == VIEW_PERS)
		m_nViewType = VIEW_ISOM;
	else
		m_nViewType = VIEW_CABI;
	DrawView();
	CView::OnRButtonDown(nFlags, point);
}


void CTransformationView::DrawView()
{
	// TODO: 在此处添加实现代码.
	switch (m_nViewType)
	{
	case VIEW_ISOM:
		DrawIsom();
		break;
	case VIEW_PERS:
		DrawPerspective();
		break;
	case VIEW_CABI:
		DrawCabinet();
		break;
	default:
		break;
	}
}

void CTransformationView::OnCabinetClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nViewType = VIEW_CABI;
	DrawCabinet();
}

void CTransformationView::OnPerspectiveClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nViewType = VIEW_PERS;
	DrawPerspective();
}

void CTransformationView::OnIsometricClick()
{
	// TODO: 在此添加命令处理程序代码
	m_nViewType = VIEW_ISOM;
	DrawIsom();
}

void CTransformationView::DrawCabinet()
{
	// TODO: 在此处添加实现代码.

	Clear();
	double theta = 1.107;
	double l = 0.5;
	m_pjMatrix[0][0] = 1; m_pjMatrix[0][1] = 0; m_pjMatrix[0][2] = l * cos(theta);	m_pjMatrix[0][3] = 0;
	m_pjMatrix[1][0] = 0; m_pjMatrix[1][1] = 1; m_pjMatrix[1][2] = l * sin(theta);	m_pjMatrix[1][3] = 0;
	m_pjMatrix[2][0] = 0; m_pjMatrix[2][1] = 0; m_pjMatrix[2][2] = 0;				m_pjMatrix[2][3] = 0;
	m_pjMatrix[3][0] = 0; m_pjMatrix[3][1] = 0; m_pjMatrix[3][2] = 0;				m_pjMatrix[3][3] = 1;
	From3DTo2D();
	DrawProjCubic();
}
