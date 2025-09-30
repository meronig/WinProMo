#ifndef _DOUBLERECT_H_
#define _DOUBLERECT_H_

class AFX_EXT_CLASS CDoubleRect 
{

public:
	CDoubleRect();
	CDoubleRect(CRect rect);
	CDoubleRect(double left, double top, double right, double bottom);

	double Width() const;
	double Height() const;
	double Ratio() const;

	CRect ToCRect() const;

	void SetRect(CRect rect);
	void SetRect(double left, double top, double right, double bottom);

	//member variables are public to ensure efficiency and compatibility with CRect
	double top;
	double bottom;
	double left;
	double right;
};

#endif //_DOUBLERECT_H_

