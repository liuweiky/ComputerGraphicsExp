#pragma once
#include "DrawType.h"
#include "COpPoint.h"

#define N 3
#define LINE_POINTS 2500

class Bezier :
	public DrawType
{
public:
	Bezier(CView* view);
	~Bezier();

	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void ReDraw();

	CArray<COpPoint, COpPoint&> m_ptControlPoints;
	COpPoint m_StartPoint;
	COpPoint m_EndPoint;

	bool m_bLButtonDown;

	CObArray m_HistoryPointSets;
	CArray<COpPoint, COpPoint&>& GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points);
	// 根据控制点 control，获得 t 处坐标值
	COpPoint Decas(CArray<COpPoint, COpPoint&>& control, double t);
};

