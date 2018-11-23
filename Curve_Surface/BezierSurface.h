#pragma once
#include "DrawType.h"
#include "CPoint3.h"

#define N 3
#define npoints 20

class BezierSurface :
	public DrawType
{
public:
	
	BezierSurface(CView* view);
	~BezierSurface();

	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void ReDraw();

	CPoint3 m_ptControlPoints[(N + 1) * (N + 1)];


	void Bezier2Point2D(int n, int np, CPoint3 P[], CPoint3 points[]);
	template<typename T1, typename T2, typename T3> void Product(T1 a[], T2 b[], T3 c[], int ah, int s, int bw);
	template<typename T> void Transpose(T a[], int n);
	CPoint World2View(CPoint3& pt, CPoint3& vLoc, double vz);
	long dtxs(double x);
	int dtys(double y);

};

