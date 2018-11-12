
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
END_MESSAGE_MAP()

// CClippingView 构造/析构

CClippingView::CClippingView() noexcept
{
	// TODO: 在此处添加构造代码

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
