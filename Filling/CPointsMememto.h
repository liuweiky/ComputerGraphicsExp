#pragma once
#include <afx.h>
class CPointsMememto :
	public CObject
{
public:
	CPointsMememto();
	~CPointsMememto();
	CArray<CPoint, CPoint&> points;
};

