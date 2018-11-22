#pragma once
#include "DrawType.h"
#include "COpPoint.h"

#define BSN 4
#define K 4
#define LINE_POINTS 2500

class BSpline :
	public DrawType
{
public:
	BSpline(CView* view);
	~BSpline();

	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void ReDraw();

	CArray<COpPoint, COpPoint&> m_ptControlPoints;
	COpPoint m_StartPoint;
	COpPoint m_EndPoint;

	double m_fKnot[BSN + K + 1];

	bool m_bLButtonDown;

	CObArray m_HistoryPointSets;
	CArray<COpPoint, COpPoint&>& GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points);
	COpPoint Deboor(CArray<COpPoint, COpPoint&>& control, double u, int j);
};

