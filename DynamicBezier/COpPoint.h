#pragma once
#include <afx.h>
class COpPoint :
	public CObject
{
public:
	double x, y;
	COpPoint();
	~COpPoint();
	COpPoint(double initX, double initY);
	COpPoint(CPoint p);
	COpPoint(const COpPoint& p);

	COpPoint operator=(COpPoint p);
	COpPoint operator=(CPoint p);

	COpPoint operator+=(COpPoint p);
	COpPoint operator+=(CPoint p);

	COpPoint operator-=(COpPoint p);
	COpPoint operator-=(CPoint p);

	COpPoint operator*=(double s);
	COpPoint operator/=(double s);

	COpPoint operator+(COpPoint p);
	COpPoint operator+(CPoint p);
	COpPoint operator-(COpPoint p);
	COpPoint operator-(CPoint p);

	COpPoint operator*(double s);
	COpPoint operator/(double s);

	operator CPoint();
};

