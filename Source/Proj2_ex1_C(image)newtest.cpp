#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <string>
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it�s recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

#include "Dependencies/opencv2/core/core.hpp"
#include "Dependencies/opencv2/highgui/highgui.hpp"
#include "Dependencies/opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

string rfilename; // argument for the original image filename (and path)

int main(){

    rfilename = "C:/Users/carlo/Documents/GitHub/icproject2/Source/tulips.ppm"; // pass the first argument into the attribute that stores the original image filename (and path)
    
 //   std::filesystem::path p = rfilename; /* constructs the path that corresponds to the current file system or OS, from the character sequence
 //                                           stored on the rfilename attribute */

	Mat original = imread(rfilename, cv::IMREAD_UNCHANGED); // Loads the image file to the memory matrix "original"


	if (original.empty()){ // if the file is not loaded prints a message on the terminal console or command prompt
    		cout << "Error : Image on " << " can't be loaded..!!" << endl;
    		return -1; // exits the aplication
  	}

	int nch = original.channels(); // get the number of channels of the original image

	int iHeight = original.size[0]; // get the original image height
	int iWidth = original.size[1]; // get the original image width
	int UVHeight = iHeight/2; // set the U and V channel height for a 4:2:0 downsampling
    int UVWidth = iWidth/2; // set the U and V channel width for a 4:2:0 downsampling

	imshow("Original Image", original);

	Mat yuvcolor = Mat::zeros(Size(original.rows, original.cols), CV_8UC3);//creates a new matrix for the yuv color scheme with 3 channels

	cvtColor(original, yuvcolor, COLOR_BGR2YUV); // converts RGB color values to YUV color and loads the values on the yuv matrix

    imshow("YUV Image", yuvcolor);

//split the channels of the yuvcolor matrix:
    Mat splitChannels[3];
    split(yuvcolor, splitChannels);

 //   double maxVal;

    Mat resized_down; // creates a matrix for UV channel downsampling

    resize(yuvcolor, resized_down, Size(UVWidth, UVHeight), INTER_CUBIC); // downsamples the YUV matrix with the bicubic 4x4 interpolation

//    imshow("Resized Down by defining height and width", resized_down);

	Mat rd_splitChannels[3]; // creates a matrix for 3 separate channels

	split(resized_down, rd_splitChannels); // separates the 3 YUV channels from the downsapled matrix and loads them to the rd_splitChannels matrix

    Mat UChannel, VChannel;
    
    UChannel = rd_splitChannels[1] /*.reshape(1, UVHeight / 2)*/; // apply reshape if needed
    VChannel = rd_splitChannels[2] /*.reshape(1, UVHeight/2)*/; // apply reshape if needed

    rd_splitChannels[3].release();

        imshow("YUV 4:2:0", VChannel);

    waitKey();

    destroyAllWindows();


	return 0;
}
