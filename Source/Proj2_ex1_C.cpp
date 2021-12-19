#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat image =  imread("0001.png");
int iHeight = image.size[0];
int iWidth = image.size[1];

Mat yuv;
cvtColor(image, yuv, COLOR_BGR2YUV_I420);

int bufLen = iWidth * iHeight * 3 / 2;
unsigned char* pYuvBuf = new unsigned char[bufLen];

File * pFileYuv;
fopen_s(&pFileYuv, "0001.yuv", "wb");

fwrite(yuv.data, sizeof(unsigned char), bufLen, pFileYuv);fclose(pFileYuv);

pFileYuv = NULL;
delete [] pYuvBuf;

/*//sample input and output
float data[3][1] = { 98,76,88 };
Mat input( 1, 1, CV_32FC3, data) ;
Mat output( 1, 1, CV_32FC3 );

//iterate over all pixels
for(int i = 0; i < input.rows; i++) {
    for(int j = 0; j < input.cols; j++) {
        //get bgr pixel
        Vec3f bgrPixel = input.at<Vec3f>(i, j);

        float B = bgrPixel[0];
        float G = bgrPixel[1];
        float R = bgrPixel[2];

        //actual conversion from BGR to YCrCb
        float delta = 0.5f;
        float Y  = 0.299f * R + 0.587f * G + 0.114f * B;
        float Cb = (B - Y) * 0.564f + delta;
        float Cr = (R - Y) * 0.713f + delta;

        //store into result image
        Vec3f yCrCbPixel( Y, Cr, Cb );
        output.at<Vec3f>(i, j) = yCrCbPixel;
    }
}*/

/*
//equations for RGB to YUV conversion
 Y' = 0.299 R + 0.587 G + 0.114  B
 U = -0.147 R - 0.289 G + 0.436  B
 V = 0.615  R - 0.515 G - 0.100  B.
 */




int main(int argc, char* argv[])
{
	Mat img = imread(argv[1]);

	if (img.empty())
  {
    cout << "Error : Image cannot be loaded..!!" << endl;
    return -1;
  }

	Mat img2 = Mat::zeros(Size(img.rows, img.cols), CV_8UC3);

	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			img2.at<Vec3b>(r,c) = img.at<Vec3b>(r,c);
		}
	}
	imwrite(argv[2], img2);
	return 0;
}
