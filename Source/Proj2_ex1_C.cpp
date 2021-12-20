#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;



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




int main(string rfilename){
	
	Mat img =  imread(rfilename, IMREAD_UNCHANGED); // Loads the image file to the memory matrix "img"

	if (img.empty()){
    		cout << "Error : Image cannot be loaded..!!" << endl;
    		return -1;
  	}
	
	int nch = img.channels(); // get the number of channels of the original image
	
	int iHeight = img.size[0];
	int iWidth = img.size[1];

	Mat yuv = Mat::zeros(Size(img.rows, img.cols), CV_8UC3); //creates a new matrix for the yuv color scheme
	
	cvtColor(img, yuv, COLOR_BGR2YUV); // converts RGB color values to YUV color

	
	Scalar_<uint8_t> yuvPixel;
	
	
/* the next sampling can aldo be done with the next method, which is suposed to be safer, and iteract with each value using the * operator:
	            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it]
*/			    
	
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


		
		
	
	
	
	return 0;
}
