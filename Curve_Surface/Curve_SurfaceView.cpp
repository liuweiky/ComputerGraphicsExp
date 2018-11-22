
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
END_MESSAGE_MAP()

// CCurveSurfaceView 构造/析构

CCurveSurfaceView::CCurveSurfaceView() noexcept
{
	// TODO: 在此处添加构造代码

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
