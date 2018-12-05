#include "stdafx.h"
#include "COpPoint.h"


COpPoint::COpPoint()
{
	x = y = 0;
	color = 0;
}

COpPoint::~COpPoint()
{
}

COpPoint::COpPoint(double initX, double initY)
{
	x = initX;
	y = initY;
}

COpPoint::COpPoint(CPoint p)
{
	x = p.x;
	y = p.y;
	color = 0;
}

COpPoint::COpPoint(const COpPoint& p)
{
	x = p.x;
	y = p.y;
	color = p.color;
}

COpPoint COpPoint::operator=(COpPoint p)
{
	x = p.x;
	y = p.y;
	color = p.color;
	return *this;
}

COpPoint COpPoint::operator=(CPoint p)
{
	x = p.x;
	y = p.y;
	color = 0;
	return *this;
}

COpPoint COpPoint::operator+=(COpPoint p)
{
	x += p.x;
	y += p.y;
	return *this;
}

COpPoint COpPoint::operator+=(CPoint p)
{
	x += p.x;
	y += p.y;
	return *this;
}

COpPoint COpPoint::operator-=(COpPoint p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}

COpPoint COpPoint::operator-=(CPoint p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}

COpPoint COpPoint::operator*=(double s)
{
	x *= s;
	y *= s;
	return *this;
}

COpPoint COpPoint::operator/=(double s)
{
	x /= s;
	y /= s;
	return *this;
}

COpPoint COpPoint::operator+(COpPoint p)
{
	COpPoint point;
	point.x = x + p.x;
	point.y = y + p.y;
	return point;
}

COpPoint COpPoint::operator+(CPoint p)
{
	COpPoint point;
	point.x = x + p.x;
	point.y = y + p.y;
	return point;
}

COpPoint COpPoint::operator-(COpPoint p)
{
	COpPoint point;
	point.x = x - p.x;
	point.y = y - p.y;
	return point;
}

COpPoint COpPoint::operator-(CPoint p)
{
	COpPoint point;
	point.x = x - p.x;
	point.y = y - p.y;
	return point;
}

COpPoint COpPoint::operator*(double s)
{
	COpPoint point;
	point.x = x * s;
	point.y = y * s;
	return point;
}

COpPoint COpPoint::operator/(double s)
{
	COpPoint point;
	point.x = x / s;
	point.y = y / s;
	return point;
}

COpPoint::operator CPoint()
{
	return CPoint(x, y);
}
