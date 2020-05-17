#include "Gridlet.h"

namespace pk::Griddlers
{


	inline bool ComparePoints(const CPoint& p1, const CPoint& p2)
	{
		if (p1.x != p2.x)
			return p1.x < p2.x;
		return p1.y < p2.y;
	}


	void SortContours(vector<CContour>& Contours)
	{
		sort(Contours.begin(), Contours.end(),
			[](const CContour& c1, const CContour& c2) { return ComparePoints(ComputeCenterPoint(c1), ComputeCenterPoint(c2)); }
		);
	}
	
	CGridlet FindGridlet(const CContours& c)
	{
		vector<CContour> Contours;
		for (int i = 0; i < c.Count(); ++i)
		{
			Contours.push_back(c.GetContour(i));
		}

		return CGridlet(move(Contours));
	}

}

