#include "OpenCVClasses.h"


namespace pk::OpenCV
{

	struct CContours::CImpl
	{
		std::vector<std::vector<cv::Point> > m_Contours;
		std::vector<cv::Vec4i> m_Hierarchy;
	};

	int CContours::Count() const
	{
		return m_pImpl->m_Contours.size();
	}

	CContour CContours::GetContour(int Index) const
	{
		return CContour(Index, m_pImpl);
	}

	CRect CContours::BoundingBox(int Contour)
	{
		return cv::boundingRect(m_pImpl->m_Contours[Contour]);
	}

	CImage LoadFromFile(const std::string &FileName)
	{
		cv::Mat img = cv::imread(FileName.c_str());
		return { std::move(img) };
	}

	CContours FindContours(CImage& img, CPoint Offset)
	{
		CContours c;
		c.m_pImpl = std::make_shared<CContours::CImpl>();
		auto& ci = *c.m_pImpl;
		cv::findContours(img.Mat(), ci.m_Contours, ci.m_Hierarchy, cv::RetrievalModes::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE, Offset);
		return c;
	}

	void OtzuThreshold(const CImage& src, CImage& dst)
	{
		cv::threshold(src.Mat(), dst.Mat(), 0, 255, cv::THRESH_OTSU);
	}

	pk::OpenCV::CImage CImage::SubImage(CPoint p, CSize s)
	{
		return SubImage({ p, s });
	}

	pk::OpenCV::CImage CImage::SubImage(CRect r)
	{
		cv::Mat res = m_Image(r);
		return res;
	}

	void WaitForKey()
	{
		cv::waitKey(0);
	}

	void ShowImage(const std::string& WinName, const CImage& i)
	{
		cv::imshow(WinName.c_str(), i.Mat());
	}

	pk::OpenCV::CImage ToGrayScale(const CImage& i)
	{
		CImage res;
		cv::cvtColor(i.Mat(), res.Mat(), cv::ColorConversionCodes::COLOR_BGR2GRAY);
		return res;
	}

	CContour::CContour(int i, std::shared_ptr<CContours::CImpl> pi) :
		m_pImpl(pi),
		m_Index(i)
	{
		m_Rect = cv::boundingRect(pi->m_Contours[m_Index]);
	}

}

