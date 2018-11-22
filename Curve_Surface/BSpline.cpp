#include "stdafx.h"
#include "BSpline.h"


BSpline::BSpline(CView* view) : DrawType::DrawType(view)
{
	m_bLButtonDown = false;
	for (int i = 0; i < K + BSN + 1; i++)
	{
		m_fKnot[i] = i;
	}
}


BSpline::~BSpline()
{
}

void BSpline::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButtonDown = true;
	m_ptControlPoints.Add(COpPoint(point));
	m_StartPoint = COpPoint(point);
	m_EndPoint = COpPoint(point);
}

void BSpline::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_ptControlPoints.GetSize() == BSN + 1)
	{
		m_bLButtonDown = false;
		CArray<COpPoint, COpPoint&> points;
		GetPoints(LINE_POINTS, m_ptControlPoints, points);

		CClientDC dc(m_pView);
		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = dc.SelectObject(&pen);
		dc.MoveTo(points.GetAt(0));
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

void BSpline::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void BSpline::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void BSpline::OnMouseMove(UINT nFlags, CPoint point)
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

void BSpline::ReDraw()
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


CArray<COpPoint, COpPoint&>& BSpline::GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points)
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处插入 return 语句
	double u, delta;
	delta = (m_fKnot[BSN + 1] - m_fKnot[K - 1]) / (double)n;
	int j = K - 1;
	u = m_fKnot[K - 1];
	for (int i = 0; i <= n; i++)
	{
		while (j < BSN && u > m_fKnot[j + 1])
		{
			j ++;
		}

		points.Add(Deboor(control, u, j));
		u += delta;
	}
	return points;
}


COpPoint BSpline::Deboor(CArray<COpPoint, COpPoint&>& control, double u, int j)
{
	// TODO: 在此处添加实现代码.
	double denom, alpha;
	COpPoint* P = new COpPoint[K];
	const double epsilon = 0.0005;
	for (int i = 0; i < K; i++)
		P[i] = control.GetAt(j - K + 1 + i);
	for (int r = 1; r < K; r++)
	{
		for (int i = K - 1; i >= r; i--)
		{
			denom = m_fKnot[i - r + j + 1] - m_fKnot[i + j - K + 1];
			if (fabs(denom) < epsilon)
				alpha = 0;
			else
				alpha = (u - m_fKnot[i + j - K + 1]) / denom;
			P[i] = P[i - 1] * (1 - alpha) + P[i] * alpha;
		}
	}
	return P[K - 1];
}
