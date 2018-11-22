#include "stdafx.h"
#include "Hermite.h"


Hermite::Hermite(CView* view) : DrawType::DrawType(view)
{
}


Hermite::~Hermite()
{
}

void Hermite::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ptControlPoints.Add(COpPoint(point));
	m_StartPoint = COpPoint(point);
	m_EndPoint = COpPoint(point);
}

void Hermite::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_ptControlPoints.GetSize() == N + 1)
	{
		CClientDC dc(m_pView);
		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = dc.SelectObject(&pen);
		CArray<COpPoint, COpPoint&> points;
		GetPoints(2000, m_ptControlPoints, points);
		dc.MoveTo(m_ptControlPoints.GetAt(0));
		for (int i = 1; i < 2000; i++)
		{
			COpPoint point = points.GetAt(i);
			dc.LineTo((CPoint)point);

		}
		dc.SelectObject(oldPen);
		// 保存到历史点，便于重画
		CArray<COpPoint, COpPoint&>* history = new CArray<COpPoint, COpPoint&>();
		history->Append(m_ptControlPoints);
		m_HistoryPointSets.Add(history);
		m_ptControlPoints.RemoveAll();
	}
}

void Hermite::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void Hermite::OnRButtonUp(UINT nFlags, CPoint point)
{
}

void Hermite::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_ptControlPoints.GetSize() % 2 == 1)
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

void Hermite::ReDraw()
{
	for (int i = 0; i < m_HistoryPointSets.GetSize(); i++)
	{
		CArray<COpPoint, COpPoint&>* points = (CArray<COpPoint, COpPoint&>*) m_HistoryPointSets.GetAt(i);
		CClientDC dc(m_pView);

		for (int j = 0; j < N;)
		{
			dc.MoveTo((CPoint)points->GetAt(j++));
			dc.LineTo((CPoint)points->GetAt(j++));
			dc.MoveTo((CPoint)points->GetAt(j++));
			dc.LineTo((CPoint)points->GetAt(j++));
		}

		CPen pen, *oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = dc.SelectObject(&pen);
		CArray<COpPoint, COpPoint&> pts;
		GetPoints(2000, *points, pts);
		dc.MoveTo(points->GetAt(0));
		for (int i = 1; i < 2000; i++)
		{
			COpPoint point = pts.GetAt(i);
			dc.LineTo((CPoint)point);

		}
		dc.SelectObject(oldPen);
	}
}

// 输入 Hermite 矩阵和控制点相乘的多项式矩阵 poly，获得曲线在 u 处的坐标
COpPoint Hermite::DoHermite(COpPoint poly[], double u)
{
	// TODO: 在此处添加实现代码.
	COpPoint point;
	double us[N + 1];
	us[N] = 1;
	point = poly[N];
	for (int i = N - 1; i >= 0; i--)
	{
		us[i] = us[i + 1] * u;
		point += poly[i] * us[i];
	}
	return point;
}

// 将区间分为 n 等分，获得每个离散点坐标数组
CArray<COpPoint, COpPoint&>& Hermite::GetPoints(int n, CArray<COpPoint, COpPoint&>& control, CArray<COpPoint, COpPoint&>& points)
{
	// TODO: 在此处添加实现代码.

	double u, delta;
	COpPoint P[N + 1], V[N + 1];
	delta = 1 / (double)n;
	u = 0;
	P[0] = control.GetAt(0);
	P[1] = control.GetAt(2);
	P[2] = control.GetAt(1) - control.GetAt(0);
	P[3] = control.GetAt(3) - control.GetAt(2);

	V[0] = P[0] * 2 - P[1] * 2 + P[2] + P[3];
	V[1] = P[0] * (-3) + P[1] * 3 - P[2] * 2 - P[3];
	V[2] = P[2];
	V[3] = P[0];

	for (int i = 0; i <= n; i++)
	{
		points.Add(DoHermite(V, u));
		u += delta;
	}
	return points;
}
