#ifndef _DOUBLEPOINT_H_
#define _DOUBLEPOINT_H_

class AFX_EXT_CLASS CDoublePoint
{
public:
	CDoublePoint();
	CDoublePoint(CPoint pt);
	CDoublePoint(double x, double y);

	CPoint ToCPoint() const;

	void SetPoint(CPoint pt);
	void SetPoint(double x, double y);

	//member variables are public to ensure efficiency and compatibility with CPoint
	double x;
	double y;
	
};

#endif // _DOUBLEPOINT_H_