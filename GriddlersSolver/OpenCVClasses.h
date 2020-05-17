#pragma once

#include <string>


#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui.hpp>

namespace pk::OpenCV
{
	using CSize = cv::Size;
	using CPoint = cv::Point;
	using CRect = cv::Rect;

	struct CImage
	{
		CImage() = default;

		CImage(cv::Mat m) : m_Image(m)
		{

		}

		CSize Size() const
		{
			return { Width(), Height() };
		}

		int Width() const
		{
			return m_Image.cols;
		}

		int Height() const
		{
			return m_Image.rows;
		}

		cv::Mat& Mat()
		{
			return m_Image;
		}

		const cv::Mat& Mat() const
		{
			return m_Image;
		}

		CImage SubImage(CPoint p, CSize s);
		CImage SubImage(CRect r);

		CImage Clone() const
		{
			return { m_Image.clone() };
		}


	private:
		cv::Mat m_Image;
	};
	struct CContour;
	struct CContours
	{
		int Count() const;
		CContour GetContour(int Index) const;
		CRect BoundingBox(int Contour);
	private:
		struct CImpl;
		std::shared_ptr<CImpl> m_pImpl;
		friend CContours FindContours(CImage& i, CPoint Offset);
		friend struct CContour;
	};

	struct CContour
	{
		CContour() : m_Index(-1) {}
		CContour(int i, std::shared_ptr<CContours::CImpl> pi);

		const CRect &Box() const
		{
			return m_Rect;
		}
	private:
		CRect m_Rect;
		int m_Index;
		std::shared_ptr<CContours::CImpl> m_pImpl;
	};

	CImage LoadFromFile(const std::string& FileName);

	CContours FindContours(CImage &i, CPoint Offset);

	void OtzuThreshold(const CImage &src, CImage& dst);
	inline void Median(const CImage& src, CImage& dst, int Size)
	{
		cv::medianBlur(src.Mat(), dst.Mat(), Size);
	}

	void WaitForKey();

	void ShowImage(const std::string& WinName, const CImage& i);

	CImage ToGrayScale(const CImage& i);

}
