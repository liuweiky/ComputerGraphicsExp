#include "stdafx.h"
#include "BezierSurface.h"

BezierSurface::BezierSurface(CView* view) : DrawType::DrawType(view)
{
	/*m_ptControlPoints[0] = CPoint3(-180, -180, 0);
	m_ptControlPoints[1] = CPoint3(-180, -60, 20);
	m_ptControlPoints[2] = CPoint3(-180, 60, 20);
	m_ptControlPoints[3] = CPoint3(-180, 180, 0);
	m_ptControlPoints[4] = CPoint3(-60, -180, 40);
	m_ptControlPoints[5] = CPoint3(-60, -60, 60);
	m_ptControlPoints[6] = CPoint3(-60, 60, 60);
	m_ptControlPoints[7] = CPoint3(-60, 180, 40);
	m_ptControlPoints[8] = CPoint3(60, -180, 40);
	m_ptControlPoints[9] = CPoint3(60, -60, 60);
	m_ptControlPoints[10] = CPoint3(60, 60, 60);
	m_ptControlPoints[11] = CPoint3(60, 180, 40);
	m_ptControlPoints[12] = CPoint3(180, -180, 0);
	m_ptControlPoints[13] = CPoint3(180, -60, 20);
	m_ptControlPoints[14] = CPoint3(180, 60, 20);
	m_ptControlPoints[15] = CPoint3(180, 180, 0);*/

	m_ptControlPoints[0] = CPoint3(-300, -300, 0);
	m_ptControlPoints[1] = CPoint3(-300, -100, 100);
	m_ptControlPoints[2] = CPoint3(-300, 100, 100);
	m_ptControlPoints[3] = CPoint3(-300, 300, 0);

	m_ptControlPoints[4] = CPoint3(-100, -300, 25);
	m_ptControlPoints[5] = CPoint3(-100, -100, 300);
	m_ptControlPoints[6] = CPoint3(-100, 100, 300);
	m_ptControlPoints[7] = CPoint3(-100, 300, 25);

	m_ptControlPoints[8] = CPoint3(100, -300, 25);
	m_ptControlPoints[9] = CPoint3(100, -100, 300);
	m_ptControlPoints[10] = CPoint3(100, 100, 300);
	m_ptControlPoints[11] = CPoint3(100, 300, 25);

	m_ptControlPoints[12] = CPoint3(300, -300, 0);
	m_ptControlPoints[13] = CPoint3(300, -100, 100);
	m_ptControlPoints[14] = CPoint3(300, 100, 100);
	m_ptControlPoints[15] = CPoint3(300, 300, 0);
}


BezierSurface::~BezierSurface()
{
}

void BezierSurface::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void BezierSurface::OnLButtonUp(UINT nFlags, CPoint point)
{
}

void BezierSurface::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void BezierSurface::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void BezierSurface::OnMouseMove(UINT nFlags, CPoint point)
{
}

// 未进行屏幕 y 坐标颠倒操作
void BezierSurface::ReDraw()
{
	CClientDC dc(m_pView);
	CPoint3 v;
	double vz;
	CPoint3 MeshPoint[(npoints + 1) * (npoints + 1)];	// 逼近曲面网格点坐标
	CPoint PlaneMeshPoint[(npoints + 1) * (npoints + 1)];// 曲面网格点屏幕坐标
	CPoint PlaneCtrlPoint[(npoints + 1) * (npoints + 1)];// 控制网格点屏幕坐标

	int i;
	Bezier2Point2D(N, npoints, m_ptControlPoints, MeshPoint);

	v = CPoint3(400, 400, 600);	// 观察点
	vz = 100;	// 投影平面到原点距离

	for (i = 0; i < (N + 1) * (N + 1); i++)
		PlaneCtrlPoint[i] = World2View(m_ptControlPoints[i], v, vz);	// 控制点转为屏幕坐标
	for (i = 0; i <= N; i++)
		dc.Polyline(&PlaneCtrlPoint[i * (N + 1)], N + 1);	// 一个方向
	Transpose(PlaneCtrlPoint, N + 1);	// 转置
	for (i = 0; i <= N; i++)
		dc.Polyline(&PlaneCtrlPoint[i * (N + 1)], N + 1);	// 另一个方向
	Transpose(PlaneCtrlPoint, N + 1);	// 恢复

	CPen pen, *oldPen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	oldPen = dc.SelectObject(&pen);

	for (i = 0; i < (npoints + 1) * (npoints + 1); i++)		
		PlaneMeshPoint[i] = World2View(MeshPoint[i], v, vz);
	for (i = 0; i <= npoints; i++)
		dc.Polyline(&PlaneMeshPoint[i * (npoints + 1)], npoints + 1);// 一个方向
	Transpose(PlaneMeshPoint, npoints + 1);// 转置
	for (i = 0; i <= npoints; i++)
		dc.Polyline(&PlaneMeshPoint[i * (npoints + 1)], npoints + 1);// 另一个方向
	Transpose(PlaneMeshPoint, npoints + 1);// 恢复

	dc.SelectObject(oldPen);
}


void BezierSurface::Bezier2Point2D(int n, int np, CPoint3 P[], CPoint3 points[])
{
	// TODO: 在此处添加实现代码.
	int i, j, k, l;
	double B[(N + 1) * (N + 1)] = { -1, 3, -3, 1, 3, -6, 3, 0, -3, 3, 0, 0, 1, 0, 0, 0 };
	double BT[(N + 1) * (N + 1)];

	CPoint3 temp[(N + 1) * (N + 1)];
	CPoint3 temp1[(N + 1) * (N + 1)];
	CPoint3 temp2[N + 1];

	double uvector[N + 1];
	double wvector[N + 1];

	double u, w, du, dw;

	du = dw = 1 / (double)np;

	memcpy(BT, B, sizeof(B));
	Transpose(BT, N + 1);

	//Product(P, B, temp, N + 1, N + 1, N + 1);
	Product(B, P, temp, N + 1, N + 1, N + 1);

	Product(temp, BT, temp1, N + 1, N + 1, N + 1);

	for (i = 0, u = 0; i <= np; i++, u+=du)
	{
		uvector[N] = 1;
		for (k = N - 1; k >= 0; k--)
			uvector[k] = u * uvector[k + 1];

		//Product(temp1, uvector, temp2, N + 1, 1, N + 1);
		Product(uvector, temp1, temp2, 1, N + 1, N + 1);

		for (j = 0, w = 0; j <= np; j++, w += dw)
		{
			wvector[N] = 1;
			for (l = N - 1; l >= 0; l--)
				wvector[l] = w * wvector[l + 1];
			Product(temp2, wvector, &points[i * (np + 1) + j], 1, N + 1, 1);
		}
	}
}


template<typename T1, typename T2, typename T3>
void BezierSurface::Product(T1 a[], T2 b[], T3 c[], int ah, int s, int bw)
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < ah; i++)
	{
		for (int j = 0; j < bw; j++)
		{
			c[i * bw + j] = 0;
			for (int k = 0; k < s; k++)
			{
				c[i * bw + j] += a[i * s + k] * b[k * bw + j];
			}
		}
	}
}


template<typename T>
void BezierSurface::Transpose(T a[], int n)
{
	// TODO: 在此处添加实现代码.
	T temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			temp = a[i * n + j];
			a[i * n + j] = a[j * n + i];
			a[j * n + i] = temp;
		}
	}

}


CPoint BezierSurface::World2View(CPoint3& pt, CPoint3& vLoc, double vz)
{
	// TODO: 在此处添加实现代码.
	double s = 8;
	CPoint qt;
	double aa, bb, cc, xw, yw, zw, xe, ye, ze, uu, vv;

	xw = pt.x; yw = pt.y; zw = pt.z;
	aa = vLoc.x; bb = vLoc.y; cc = vLoc.z;
	uu = sqrt(aa * aa + bb * bb + cc * cc);
	vv = sqrt(aa * aa + bb * bb);
	if (!uu)
	{
		xe = xw; ye = yw; ze = zw;
	}
	else if (!vv)
	{
		xe = xw; ye = yw; ze = zw + cc;
	}
	else
	{
		xe = -bb * xw / vv + aa * yw / vv;
		ye = -aa * cc * xw / (uu * vv) - bb * cc * yw / (uu * vv) + vv * zw / uu;
		ze = -aa * xw / uu - bb * yw / uu - cc * zw / uu + uu;
	}
	qt.x = (long)dtxs(s * xe * vz / ze);
	qt.y = (long)dtys(s * ye * vz / ze);
	return qt;
}


long BezierSurface::dtxs(double x)
{
	// TODO: 在此处添加实现代码.
	CRect rect;
	m_pView->GetClientRect(&rect);
	return (long)(rect.right / 2 + x);
}


int BezierSurface::dtys(double y)
{
	// TODO: 在此处添加实现代码.
	CRect rect;
	m_pView->GetClientRect(&rect);
	return (long)(rect.bottom / 2 + y);
}
