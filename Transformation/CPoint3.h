#pragma once
#include <afx.h>
class CPoint3 :
	public CObject
{
public:
	double x, y, z;
	CPoint3();
	CPoint3(double initX, double initY, double initZ);
	~CPoint3();
};

