#include "stdafx.h"
#include "CPoint3.h"


CPoint3::CPoint3()
{
	x = y = z = 0.0;
}

CPoint3::CPoint3(double initX, double initY, double initZ)
{
	x = initX; y = initY; z = initZ;
}

CPoint3::CPoint3(double s)
{
	x = y = z = s;
}

CPoint3::CPoint3(const CPoint3 & p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

/*CPoint3 & CPoint3::operator=(const CPoint3 & pt)
{
	// TODO: 在此处插入 return 语句
	x = pt.x;
	y = pt.y;
	z = pt.z;
	return *this;
}*/

CPoint3::~CPoint3()
{
}

/*CPoint3 CPoint3::operator=(int i)
{
	x = y = z = i;
	return *this;
}*/

CPoint3 CPoint3::operator=(CPoint3 p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
}

CPoint3 CPoint3::operator+=(CPoint3 p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

CPoint3 CPoint3::operator-=(CPoint3 p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

CPoint3 CPoint3::operator*=(double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

CPoint3 CPoint3::operator+(CPoint3 p)
{
	CPoint3 point;
	point.x = x + p.x;
	point.y = y + p.y;
	point.z = z + p.z;
	return point;
}

CPoint3 CPoint3::operator-(CPoint3 p)
{
	CPoint3 point;
	point.x = x - p.x;
	point.y = y - p.y;
	point.z = z - p.z;
	return point;
}

CPoint3 CPoint3::operator*(double s)
{
	CPoint3 point;
	point.x = x * s;
	point.y = y * s;
	point.z = z * s;
	return point;
}

CPoint3 CPoint3::operator/(double s)
{
	CPoint3 point;
	point.x = x / s;
	point.y = y / s;
	point.z = z / s;
	return point;
}

CPoint3 operator*(double s, CPoint3 p)
{
	CPoint3 t;
	t.x = p.x * s;
	t.y = p.y * s;
	t.z = p.z * s;
	return t;
}
