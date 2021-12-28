#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <fstream>
#include <string>
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it's recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

#include "Dependencies/opencv2/core/core.hpp"
#include "Dependencies/opencv2/highgui/highgui.hpp"
#include "Dependencies/opencv2/imgproc.hpp"


using namespace cv;
using namespace std;

string rfilename; // argument for the original image filename (and path)
string file_extension;
using sample_type = uint8_t;
Mat YUVResidual;

Mat translateImg(Mat& img, int offsetx, int offsety) {
    Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img, img, trans_mat, img.size());
    return img;
}

void ImageEncode(string rfilename){

  //  rfilename = "tulips.ppm"; // pass the first argument into the attribute that stores the original image filename (and path)

    std::filesystem::path p = rfilename, e; /* constructs the path that corresponds to the current file system or OS, from the character sequence
                                            stored on the rfilename attribute */
    file_extension = std::filesystem::path(p).extension().string();
    cout << file_extension << endl;
	
    double minVal, maxVal;
    Point minLoc;
    Point maxLoc;

    Mat original = imread(rfilename, cv::IMREAD_UNCHANGED); // Loads the image file to the memory matrix "original"

	if (original.empty()){ // if the file is not loaded prints a message on the terminal console or command prompt
    		cout << "Error : Image on " << std::filesystem::absolute(p) << " can't be loaded..!!" << endl;
    //		return -1; // exits the aplication
  	}

	int nch = original.channels(); // get the number of channels of the original image

	int iHeightRows = original.rows; // get the original image height
	int iWidth = original.cols; // get the original image width
	int UVHeightRows = iHeightRows/2; // set the U and V channel height for a 4:2:0 downsampling
    int UVWidth = iWidth/2; // set the U and V channel width for a 4:2:0 downsampling

//	imshow("Original Image", original);

	Mat yuvcolor = Mat::zeros(Size(original.rows, original.cols), CV_8UC3);//creates a new matrix for the yuv color scheme with 3 channels

	cvtColor(original, yuvcolor, COLOR_BGR2YUV); // converts RGB color values to YUV color and loads the values on the yuv matrix

    cout << "YRES " << iWidth << endl;
    cout << "UVRES " << UVWidth << endl;

 //   imshow("YUV Image", yuvcolor);

///split the channels of the yuvcolor matrix:
    
    Mat splitChannels[3];

    split(yuvcolor, splitChannels);

    minMaxLoc(splitChannels[2], &minVal, &maxVal, &minLoc, &maxLoc);
    cout << "yuv = " << maxVal << endl;

   minMaxLoc(splitChannels[2], &minVal, &maxVal, &minLoc, &maxLoc);

   if (maxVal >= 256){
       using sample_type = int;
    }

    Mat resized_down; // creates a matrix for UV channel downsampling

    resize(yuvcolor, resized_down, Size(UVHeightRows, UVWidth), INTER_CUBIC); // downsamples the YUV matrix with the bicubic 4x4 interpolation

//    imshow("Resized Down by defining height and width", resized_down);

    yuvcolor.release();
    original.release();

    Mat rd_splitChannels[3]; // creates a matrix for 3 separate channels

	split(resized_down, rd_splitChannels); // separates the 3 YUV channels from the downsapled matrix and loads them to the rd_splitChannels matrix

    Mat UChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
    Mat VChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
    Mat YChannel = Mat::zeros(Size(iHeightRows, iWidth), CV_8UC1);

    UChannel = rd_splitChannels[1].clone() /*.reshape(1, UVHeight / 2)*/; // apply reshape if needed
    VChannel = rd_splitChannels[0].clone() /*.reshape(1, UVHeight/2)*/; // apply reshape if needed
    YChannel = splitChannels[2].clone();

 
// JPEG mode 6 predictor formula: X = B + ((A − C)/2), onde: X=(r,c); A=(r,c-1); B=(r-1,c) e C=(r-1,c-1)
//A=YChannel.at<uint8_t>(r,c-1), B=YChannel.at<uint8_t>(r-1,c) e C=YChannel.at<uint8_t>(r-1,c-1)

    Mat YResidual = Mat::zeros(Size(iHeightRows, iWidth), CV_16SC1);
 
    using sample_type = int;

    for (int r = 0; r < iHeightRows; r++){
        for (int c = 0; c < iWidth; c++){
            if (r==0){
                YResidual.at<short>(r,c) = YChannel.at<uchar>(r,c);
            }
            if (c==0) {
                YResidual.at<short>(r,c) = YChannel.at<uchar>(r,c);
            }
            else{
                int ax, bx, cx, x;
                ax = YChannel.at<uchar>(r, c - 1);
                bx = YChannel.at<uchar>(r - 1, c);
                cx = YChannel.at<uchar>(r - 1, c - 1);
                x = YChannel.at<uchar>(r, c);
                YResidual.at<short>(r, c) = x - (bx + ((ax - cx) / 2));
            }
        }        
    }


    minMaxLoc(YResidual, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << "YR = " << maxVal << endl;
    
    Mat UResidual = Mat::zeros(Size(UVHeightRows, UVWidth), CV_16SC1);

    for (int r = 0; r < UVHeightRows; r++){
        for (int c = 0; c < UVWidth; c++){
            if (r==0){
                UResidual.at<short>(r,c) = UChannel.at<uchar>(r,c);
            }
            if (c==0) {
                UResidual.at<short>(r,c) = UChannel.at<uchar>(r,c);
            }
            else{
                int ax, bx, cx, x;
                ax = UChannel.at<uchar>(r,c-1);
                bx = UChannel.at<uchar>(r-1,c);
                cx = UChannel.at<uchar>(r - 1, c - 1);
                x = UChannel.at<uchar>(r, c);
                UResidual.at<short>(r,c) = x-(bx+((ax-cx)/2));
            }
         }
    }
    minMaxLoc(UResidual, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << "UR = " << maxVal << endl;

    Mat VPredict = Mat::zeros(Size(UVHeightRows, UVWidth), CV_16SC1);
    Mat A = VChannel.clone();
    Mat C = VChannel.clone();
    Mat B = VChannel.clone();

    translateImg(C, 0, 1);
    translateImg(B, 0, 1);
    A -= C;
    translateImg(A, 1, 0);
    addWeighted(B, 1, A, 0.5, 0.0, VPredict);    

    Mat VResidual = Mat::zeros(Size(UVHeightRows, UVWidth), CV_16SC1);
    subtract(VChannel, VPredict, VResidual);

    translateImg(VResidual, -1, -1);
    translateImg(VResidual, 1, 1);

    Mat vc = VChannel.clone();
    translateImg(vc, -1, -1);
    translateImg(vc, 1, 1);
    Mat CR11 = Mat::zeros(Size(UVHeightRows, UVWidth), CV_16SC1);
    subtract(VChannel, vc, CR11);
    VResidual += CR11;

    YResidual.convertTo(YResidual, CV_8UC1);
    UResidual.convertTo(UResidual, CV_8UC1);
    VResidual.convertTo(VResidual, CV_8UC1);

    minMaxLoc(YResidual, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << maxVal << endl;
         
 //   imshow("YR", VResidual);


    UResidual = UResidual.reshape(1, UResidual.rows / 2); // align the uneven rows right of the even ones
    VResidual = VResidual.reshape(1, VResidual.rows / 2); // align the uneven rows right of the even ones
      
    vconcat(YResidual, UResidual, YUVResidual);
    vconcat(YUVResidual, VResidual, YUVResidual);
    YUVResidual = YUVResidual.clone();

    string wfilename = "compressed.png";
    
 //   imwrite(wfilename, YUVResidual);

    std::fstream ofs; /// the object name for the output stream.

    ofs.open(wfilename, std::fstream::app | std::fstream::binary);    // para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
    uchar sample;
    float Hight = YUVResidual.rows;
    float Width = YUVResidual.cols;
    ofs << Hight/100000;
    ofs << Width/100000;
    ofs << file_extension;
    for (int r = 0; r < YUVResidual.rows; r++) {
        for (int c = 0; c < YUVResidual.cols; c++) {
            sample = YUVResidual.at<uchar>(r, c);
            ofs.put(sample);
            }
        }
    ofs.close();

    cout << "Width = " << Width << "Hight = " << Hight << endl;

 //   imwrite("compressed.ras", YUVResidual);

 //      imshow("YUV 4:2:0", YUVResidual);

 //   waitKey();

 //   destroyAllWindows();


}


int main(){

    ImageEncode("tulips.ppm");


    return 0;
}