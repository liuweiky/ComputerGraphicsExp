
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
END_MESSAGE_MAP()

// CDynamicBezierView 构造/析构

CDynamicBezierView::CDynamicBezierView() noexcept
{
	// TODO: 在此处添加构造代码

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
