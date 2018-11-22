#include "stdafx.h"
#include "Bezier.h"


Bezier::Bezier(CView* view) : DrawType::DrawType(view)
{
	m_bLButtonDown = false;
}


Bezier::~Bezier()
{
}

void Bezier::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButtonDown = true;
	m_ptControlPoints.Add(COpPoint(point));
	m_StartPoint = COpPoint(point);
	m_EndPoint = COpPoint(point);
}

void Bezier::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_ptControlPoints.GetSize() == N + 1)
	{
		m_bLButtonDown = false;
		CArray<COpPoint, COpPoint&> points;
		GetPoints(LINE_POINTS, m_ptControlPoints, points);

		CClientDC dc(m_pView);
		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptControlPoints.GetAt(0));
		for (int i = 1; i < LINE_POINTS; i++)
		{
			COpPoint point = points.GetAt(i);
			dc.LineTo((CPoint)point);

		}
		dc.SelectObject(oldPen);

		CArray<COpPoint, COpPoint&>* history = new CArray<COpPoint, COpPoint&>();
		history->Append(m_ptControlPoints);
		m_HistoryPointSets.Add(history);
		m_ptControlPoints.RemoveAll();
	}
}

void Bezier::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void Bezier::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void Bezier::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButtonDown)
	{
		CClientDC dc(m_pView);
		dc.SetROP2(R2_NOT);
		dc.MoveTo((CPoint)m_StartPoint);
		dc.LineTo((CPoint)m_EndPoint);
		m_EndPoint = point;
		dc.MoveTo((CPoint)m_StartPoint);
		dc.LineTo((CPoint)m_EndPoint);
	}
}

void Bezier::ReDraw()
{
	for (int i = 0; i < m_HistoryPointSets.GetSize(); i++)
	{
		CArray<COpPoint, COpPoint&>* points = (CArray<COpPoint, COpPoint&>*) m_HistoryPointSets.GetAt(i);
		CClientDC dc(m_pView);

		dc.MoveTo((CPoint)points->GetAt(0));

		for (int j = 1; j < points->GetSize(); j++)
		{
			dc.LineTo((CPoint)points->GetAt(j));
		}

		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = dc.SelectObject(&pen);
		CArray<COpPoint, COpPoint&> pts;
		GetPoints(LINE_POINTS, *points, pts);
		dc.MoveTo(points->GetAt(0));
		for (int i = 1; i < LINE_POINTS; i++)
		{
			COpPoint point = pts.GetAt(i);
			dc.LineTo((CPoint)point);
		}
		dc.SelectObject(oldPen);
	}
}


// 将区间分为 n 等分，获得每个离散点坐标数组
CArray<COpPoint, COpPoint&>& Bezier::GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处插入 return 语句
	double t = 0, delta;
	delta = 1.0 / (double)n;
	for (int i = 0; i <= n; i++)
	{
		points.Add(Decas(control, t));
		t += delta;
	}
	return points;
}


// 根据控制点 control，获得 t 处坐标值
COpPoint Bezier::Decas(CArray<COpPoint, COpPoint&>& control, double t)
{
	// TODO: 在此处添加实现代码.
	int m;
	COpPoint *R, *Q, P0;
	R = new COpPoint[control.GetSize()];
	Q = new COpPoint[control.GetSize()];
	for (int i = 0; i < control.GetSize(); i++)
		R[i] = control.GetAt(i);

	for (m = control.GetSize() - 1; m >= 0; m--)
	{
		for (int i = 0; i <= m - 1; i++)
		{
			Q[i] = R[i] + (R[i + 1] - R[i]) * t;
		}

		for (int i = 0; i <= m - 1; i++)
		{
			R[i] = Q[i];
		}
	}

	P0 = R[0];
	delete[] R;
	delete[] Q;
	return P0;
}
