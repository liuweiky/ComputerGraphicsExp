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

CPoint3::~CPoint3()
{
}
