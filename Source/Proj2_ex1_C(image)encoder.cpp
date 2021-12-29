#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <fstream>
#include <string>
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it's recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/
#include "Golomb.h"
#include "Dependencies/opencv2/core/core.hpp"
#include "Dependencies/opencv2/highgui/highgui.hpp"
#include "Dependencies/opencv2/imgproc.hpp"


using namespace cv;
using namespace std;

string rfilename; /// argument for the original image filename (and path)
string file_extension;
using sample_type = uint8_t;
Mat YUVResidual;
string wfilename;


void ImageEncode(string rfilename){

    std::filesystem::path p = rfilename, e; /** constructs the path that corresponds to the current file system or OS, from the character sequence
                                            stored on the rfilename attribute */
    file_extension = std::filesystem::path(p).extension().string();
    cout << file_extension << endl;

    double minVal, maxVal;
    Point minLoc;
    Point maxLoc;

    Mat original = imread(rfilename, cv::IMREAD_UNCHANGED); /// Loads the image file to the memory matrix "original"

	if (original.empty()){ /// if the file is not loaded prints a message on the terminal console or command prompt
    		cout << "Error : Image on " << std::filesystem::absolute(p) << " can't be loaded..!!" << endl;
    //		return -1; // exits the aplication
  	}

	int nch = original.channels(); /// get the number of channels of the original image

	int iHeightRows = original.rows; /// get the original image height
	int iWidth = original.cols; /// get the original image width
	int UVHeightRows = iHeightRows/2; /// set the U and V channel height for a 4:2:0 downsampling
    int UVWidth = iWidth/2; /// set the U and V channel width for a 4:2:0 downsampling


	Mat yuvcolor = Mat::zeros(Size(original.rows, original.cols), CV_8UC3);///creates a new matrix for the yuv color scheme with 3 channels

	cvtColor(original, yuvcolor, COLOR_BGR2YUV); /// converts RGB color values to YUV color and loads the values on the yuv matrix

    Mat splitChannels[3];

    split(yuvcolor, splitChannels);

   minMaxLoc(splitChannels[2], &minVal, &maxVal, &minLoc, &maxLoc);
   if (maxVal >= 256){
       using sample_type = int;
    }

    Mat resized_down; /// creates a matrix for UV channel downsampling

    resize(yuvcolor, resized_down, Size(UVHeightRows, UVWidth), INTER_CUBIC); // downsamples the YUV matrix with the bicubic 4x4 interpolation

    yuvcolor.release();
    original.release();

    Mat rd_splitChannels[3]; /// creates a matrix for 3 separate channels

	split(resized_down, rd_splitChannels); /// separates the 3 YUV channels from the downsapled matrix and loads them to the rd_splitChannels matrix

    Mat UChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
    Mat VChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
    Mat YChannel = Mat::zeros(Size(iHeightRows, iWidth), CV_8UC1);

    UChannel = rd_splitChannels[1].clone(); /// apply reshape if needed
    VChannel = rd_splitChannels[2].clone(); /// apply reshape if needed
    YChannel = splitChannels[0].clone();

    std::filesystem::path p1 = rfilename, we = "dat";
    p1.replace_extension(we);
    rfilename = p1.string();

    std::fstream ofs; /// the object name for the output stream.

    ofs.open(wfilename, std::fstream::app | std::fstream::binary);    /// para adicionar, caso o ficheiro exista usar:  std::ofstream::app . std::ofstream::binary para que o output seja em binário
    uchar sample;
    float Hight = iHeightRows / 100000;
    float Width = iWidth / 100000;
    ofs << Hight;
    ofs << Width;
    ofs << file_extension;
    for (int r = 0; r < YUVResidual.rows; r++) {
        for (int c = 0; c < YUVResidual.cols; c++) {
            sample = YUVResidual.at<uchar>(r, c);
            ofs.put(sample);
        }
    }

    cout << "Width = " << Width << "Hight = " << Hight << endl;

/// JPEG mode 6 predictor formula: X = B + ((A − C)/2), onde: X=(r,c); A=(r,c-1); B=(r-1,c) e C=(r-1,c-1)
///A=YChannel.at<uint8_t>(r,c-1), B=YChannel.at<uint8_t>(r-1,c) e C=YChannel.at<uint8_t>(r-1,c-1)

    uchar residual;
    Golomb gs;
    gs.filename = rfilename;

    for (int r = 0; r < iHeightRows; r++){
        for (int c = 0; c < iWidth; c++){
            if (r==0){
                residual = YChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            if (c==0) {
                residual = YChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            else{
                int ax, bx, cx, x;
                ax = YChannel.at<uchar>(r, c - 1);
                bx = YChannel.at<uchar>(r - 1, c);
                cx = YChannel.at<uchar>(r - 1, c - 1);
                x = YChannel.at<uchar>(r, c);
                residual = x - (bx + ((ax - cx) / 2));
                gs.G_encoder(residual);
            }
        }
    }

    for (int r = 0; r < UVHeightRows; r++){
        for (int c = 0; c < UVWidth; c++){
            if (r==0){
                residual = UChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            if (c==0) {
                residual = UChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            else{
                int ax, bx, cx, x;
                ax = UChannel.at<uchar>(r,c-1);
                bx = UChannel.at<uchar>(r-1,c);
                cx = UChannel.at<uchar>(r - 1, c - 1);
                x = UChannel.at<uchar>(r, c);
                residual = x-(bx+((ax-cx)/2));
                gs.G_encoder(residual);
            }
         }
    }

    for (int r = 0; r < UVHeightRows; r++){
        for (int c = 0; c < UVWidth; c++){
            if (r==0){
                residual = VChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            if (c==0) {
                residual = VChannel.at<uchar>(r,c);
                gs.G_encoder(residual);
            }
            else{
                int ax, bx, cx, x;
                ax = VChannel.at<uchar>(r,c-1);
                bx = VChannel.at<uchar>(r-1,c);
                cx = VChannel.at<uchar>(r - 1, c - 1);
                x = VChannel.at<uchar>(r, c);
                residual = x-(bx+((ax-cx)/2));
                gs.G_encoder(residual);
            }
         }
    }

    ofs.close();

}


int main(int argc, char* argv[]){



    if (argc <= 2 || argv[1] == "/?") {	// indicação da sintaxe de commando
        cout << "Usage: ./program_name ./image_file_name.ppm \a" << endl; // \a toca um som de alerta (byte 0x07 in ASCII encoding)
            }

    ImageEncode(argv[1]);



    return 0;
}
