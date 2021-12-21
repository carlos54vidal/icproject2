#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <string>

#include "Dependencies/opencv2/core/core.hpp"
#include "Dependencies/opencv2/highgui/highgui.hpp"
#include "Dependencies/opencv2/imgproc.hpp"

using namespace cv;
using namespace std;





int main(){

	Mat original =  imread("tulips.ppm", cv::IMREAD_COLOR); // Loads the image file to the memory matrix "original"

	if (original.empty()){
    		cout << "Error : Image cannot be loaded..!!" << endl;
    		return -1;
  	}

	int nch = original.channels(); // get the number of channels of the original image

	short iHeight = original.size[0];
	short iWidth = original.size[1];
	int UVHeight = iHeight/4;
    int UVWidth = iWidth/4;

	imshow("Original Image", original);

//	Mat yuv = Mat::zeros(Size(original.rows, original.cols), CV_8UC3); //creates a new matrix for the yuv color scheme
    Mat resized_down;

    resize(original, resized_down, Size(UVWidth, UVHeight), INTER_CUBIC);

    imshow("Resized Down by defining height and width", resized_down);

    waitKey();

    destroyAllWindows();

//	Mat splitChannels[3];

//	splitChannels (original, splitChannels);






/*


	Scalar_<uint8_t> yuvPixel;

		for(int i = 0; i < yuv.rows; i++){
    			uint8_t* rowPtr = yuv.row(i);
    			for(int j = 0; j < yuv.cols; j++){
        			yuvPixel.val[0] = rowPtr[j*nch + 0]; // B | Y
       				yuvPixel.val[1] = rowPtr[j*nch + 1]; // G | U -> Divide by 2 to downsample/subsample the channel for loosy data
        			yuvPixel.val[2] = rowPtr[j*nch + 2]; // R | V -> Divide by 2 to downsample/subsample the channel for loosy data

        			// do something with BGR values...

			yuv = yuvPixel; // replaces YUV values with yuvPixel values

			}
		}





*/

	return 0;
}
