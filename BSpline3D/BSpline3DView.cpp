
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
END_MESSAGE_MAP()

// CBSpline3DView 构造/析构

CBSpline3DView::CBSpline3DView() noexcept
{
	// TODO: 在此处添加构造代码

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
