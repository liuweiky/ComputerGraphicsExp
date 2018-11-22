#pragma once
#include <afx.h>
class DrawType :
	public CObject
{
public:
	DrawType(CView* view);
	virtual ~DrawType();
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnRButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnRButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
	virtual void ReDraw() = 0;

	CView* m_pView;
};

