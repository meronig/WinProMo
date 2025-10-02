#ifndef _DOUBLEPOINT_H_
#define _DOUBLEPOINT_H_

class AFX_EXT_CLASS CDoublePoint : public CObject
{
public:
	CDoublePoint();
	CDoublePoint(const CPoint& pt);
	CDoublePoint(const double& x, const double& y);
	CDoublePoint(const CDoublePoint& other);

    CDoublePoint& operator=(const CDoublePoint& other);

	CPoint ToCPoint() const;

	void SetPoint(const CPoint& pt);
	void SetPoint(const double& x, const double& y);

	//member variables are public to ensure efficiency and compatibility with CPoint
	double x;
	double y;
	
};

#endif // _DOUBLEPOINT_H_