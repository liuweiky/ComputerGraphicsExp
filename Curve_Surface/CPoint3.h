#pragma once
#include <afx.h>
class CPoint3 :
	public CObject
{
public:
	double x, y, z;
	CPoint3();
	CPoint3(double initX, double initY, double initZ);
	CPoint3(double s);
	CPoint3(const CPoint3& p);
	//CPoint3 & operator=(const CPoint3& pt);
	~CPoint3();

	//CPoint3 operator=(int i);

	CPoint3 operator=(CPoint3 p);

	CPoint3 operator+=(CPoint3 p);

	CPoint3 operator-=(CPoint3 p);

	CPoint3 operator*=(double s);

	CPoint3 operator+(CPoint3 p);
	CPoint3 operator-(CPoint3 p);

	CPoint3 operator*(double s);
	CPoint3 operator/(double s);

	friend CPoint3 operator*(double s, CPoint3 p);
};

