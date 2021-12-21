#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <string>
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it´s recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

#include "Dependencies/opencv2/core/core.hpp"
#include "Dependencies/opencv2/highgui/highgui.hpp"
#include "Dependencies/opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

string rfilename; // argument for the original image filename (and path)

int main(int argc, char* argv[]){

    rfilename = argv[1]; // pass the first argument into the attribute that stores the original image filename (and path)
    std::filesystem::path p = rfilename; /* constructs the path that corresponds to the current file system or OS, from the character sequence
                                            stored on the rfilename attribute */

	Mat original = imread("./tulips.ppm", cv::IMREAD_COLOR); // Loads the image file to the memory matrix "original"

	if (original.empty()){ // if the file is not loaded prints a message on the terminal console or command prompt
    		cout << "Error : Image on " << std::filesystem::absolute(p) << " can't be loaded..!!" << endl;
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

    Mat resized_down; // creates a matrix for UV channel downsampling

    resize(yuvcolor, resized_down, Size(UVWidth, UVHeight), INTER_CUBIC); // downsamples the YUV matrix with the bicubic 4x4 interpolation

//    imshow("Resized Down by defining height and width", resized_down);

	Mat rd_splitChannels[3]; // creates a matrix for 3 separate channels

	split(resized_down, rd_splitChannels); // separates the 3 YUV channels from the downsapled matrix and loads them to the rd_splitChannels matrix

    Mat Ueven, Uuneven, Veven, Vuneven; /* creates matrixes for storing even and uneven rows of the U and V channels, in order to later stack them
                                        side by side and fill the with of the original image */

// Fill the U and V matrixes with even and uneven rows:
    for (int i=0; i<resized_down.rows; i+=2){
        Ueven.push_back(rd_splitChannels[1].row(i));
        Veven.push_back(rd_splitChannels[2].row(i));
    }
     for (int i=1; i<resized_down.rows; i+=2){
        Uuneven.push_back(rd_splitChannels[1].row(i));
        Vuneven.push_back(rd_splitChannels[2].row(i));
    }

     resized_down.release(); //free some memory because resized_down matrix is no longer needed

     Mat Uchannel, Vchannel, YUV420_1, YUV420; /* create matrixes to merge previous uneven rows to the right of the even rows and the matrix for
                                                the final YUV420 formated image */

    hconcat(Ueven, Uuneven, Uchannel); /* load the downsapled image with the U values, to the Uchannel matrix. Previous even rows on the right and
                                        uneven rows on the left side */
    hconcat(Veven, Vuneven, Vchannel); /* load the downsapled image with the V values, to the Vchannel matrix. Previous even rows on the right and
                                        uneven rows on the left side */
// Free some memory:
    Ueven.release();
    Uuneven.release();
    Veven.release();
    Vuneven.release();

//split the channels of the yuvcolor matrix:
    Mat splitChannels[3];
    split(yuvcolor, splitChannels);

// Join the Y channel (original size) with the U channel (half size) followed by the V channel, vertically:
    vconcat(splitChannels[0], Uchannel, YUV420_1);
    vconcat(YUV420_1, Vchannel, YUV420);

// Free some memory:
    Uchannel.release();
    Vchannel.release();
    YUV420_1.release();


    imshow("YUV 4:2:0", YUV420);

    waitKey();

    destroyAllWindows();


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
