#pragma once

#include <vector>
#include "OpenCVClasses.h"

namespace pk::Griddlers
{
	using namespace OpenCV;
	using namespace std;

	inline CPoint ComputeCenterPoint(const CContour& c)
	{
		auto& b = c.Box();
		return { b.x + b.width / 2, b.y + b.height / 2 };
	}

	struct CGridlet
	{
		CGridlet(vector<CContour> Contours) :
			m_Contours(std::move(Contours))
		{

		}

		const vector<CContour>& Contours() const
		{
			return m_Contours;
		}
	private:
		vector<CContour> m_Contours;
	};

	CGridlet FindGridlet(const CContours& c);

}

