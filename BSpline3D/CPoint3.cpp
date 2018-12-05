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

CPoint3::CPoint3(const CPoint3& pt)
{
	x = pt.x; y = pt.y; z = pt.z;
}

CPoint3 CPoint3::operator=(const CPoint3 & pt)
{
	// TODO: 在此处插入 return 语句
	x = pt.x;
	y = pt.y;
	z = pt.z;
	return *this;
}

CPoint3::~CPoint3()
{
}
