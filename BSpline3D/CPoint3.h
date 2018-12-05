#pragma once
#include <afx.h>
class CPoint3 :
	public CObject
{
public:
	double x, y, z;
	CPoint3();
	CPoint3(double initX, double initY, double initZ);
	CPoint3(const CPoint3& pt);
	CPoint3 operator=(const CPoint3& pt);
	~CPoint3();
};

