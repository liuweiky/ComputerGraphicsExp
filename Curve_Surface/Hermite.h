#pragma once
#include "DrawType.h"
#include "COpPoint.h"

#define N 3
#define LINE_POINTS 2500

class Hermite :
	public DrawType
{
public:
	Hermite(CView* view);
	virtual ~Hermite();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void ReDraw();

	CArray<COpPoint, COpPoint&> m_ptControlPoints;
	COpPoint m_StartPoint;
	COpPoint m_EndPoint;
	COpPoint DoHermite(COpPoint poly[], double u);
	CArray<COpPoint, COpPoint&>& GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points);

	CObArray m_HistoryPointSets;
};

