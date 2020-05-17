// GriddlersSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "OpenCVClasses.h"
#include "Gridlet.h"

/*

 - OpenCV Image
 - Histogram of black and white - of a center area of image
 - threshold - based on optimal histogram - Otzu ?  - We got monochrome image (white/black)
 - Find n gridlets 
   - FindGridlet: 
     - Find 3 white objects in a row
     - Find 9 white objects in 3x3 
     - Find center point of 9 objects
     - Find 4 corners of square
     - Draw square 
*/

using namespace pk::OpenCV;
using namespace pk::Griddlers;
using namespace std;

CRect ROIForImage(const CImage& i)
{
    CSize Size = i.Size();
    CPoint p{ Size.width / 2, Size.height / 2 };
    CRect r{ p, CSize{Size.width/4, Size.height/4} };
    return r;
}

int main()
{
    
    auto ColorImg = LoadFromFile("../data/2o.png");   
    auto GrayImg = ToGrayScale(ColorImg);
    CImage Img = GrayImg;
    
    Median(GrayImg, Img, 3);        // the size depends on size of the grid ... image resolution

    cout << Img.Width() << "x" << Img.Height() << endl;

    auto roi = ROIForImage(Img);
    auto SubImg = Img.SubImage(roi);
    auto ColorSubImg = ColorImg.SubImage(roi).Clone();
    cout << SubImg.Width() << "x" << SubImg.Height() << endl;
    OtzuThreshold(SubImg, SubImg);

    auto Contours = FindContours(SubImg, { 0,0 });
    cout << "ContoursCount = " << Contours.Count() << endl;


    CGridlet g = FindGridlet(Contours);
    int Count = 0;
    for (const auto& c : g.Contours())
    {
        cv::rectangle(ColorSubImg.Mat(), c.Box(), {255, 0, 0});
        cv::circle(ColorSubImg.Mat(), ComputeCenterPoint(c), 3, { 0, 0, 255 });
    //    if (++Count > 8)
      //      break;
    }

  //  ShowImage("img", Img);
    ShowImage("thr", SubImg);
    ShowImage("color", ColorSubImg);
    WaitForKey();
}

