#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Golomb.h"
#include <filesystem> /** It needs a compiler that supports the C++17 language standard, which is implemented e.g. on the g++ compiler from the version 8 onwards,
                        but it's recommended a g++ version release 9 or newer for full support. https://gcc.gnu.org/gcc-9/changes.html#cxx **/

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

Mat translateImg(Mat& img, int offsetx, int offsety) {
    Mat trans_mat = (Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
    warpAffine(img, img, trans_mat, img.size());
    return img;
}

void ImageDecoder(string filename){

    std::filesystem::path p = filename, e; /** constructs the path that corresponds to the current file system or OS, from the character sequence
                                            stored on the rfilename attribute **/

    wfilename = filename;
    std::filesystem::path p1 = filename, e1 = "bin";
    file_extension = std::filesystem::path(p1).extension().string();
    p1.replace_extension(e1);
    rfilename = p1.string();


    int length = 7;
    fstream ifs;
    ifs.open(rfilename);
    string hight;
    string width;
    string image_format;
    char * buffer = new char[length];
    ifs.read (buffer, length);
    for (int i = 0; i < length; i++) {
        hight += buffer[i];
    }
    ifs.read(buffer, length);
    for (int i = 0; i < length; i++) {
        width += buffer[i];
    }
    length = 4;
    ifs.read(buffer, length);
    for (int i = 0; i < length; i++) {
        image_format += buffer[i];
    }
    float RHight = stof(hight);
    float CWidth = stof(width);
    RHight = RHight * 100000;
    CWidth = CWidth * 100000;
    cout << "hight = " << RHight << " width = " << CWidth << endl;

    delete[] buffer;

    Golomb gs;
    gs.filename = filename;

    Mat Encoded(RHight, CWidth, CV_8UC1);
    char sample;
    for (int r = 0; r < RHight; r++) {
        for (int c = 0; c < CWidth; c++) {
            ifs.get(sample);
            Encoded.at<char>(r, c) = sample;
        }
    }

     RHight = RHight*3/4; // get the original image height

     int UVHeightRows = RHight/2;
     int UVWidth = CWidth/2;

     Mat YResidual = Mat::zeros(Size(RHight, CWidth), CV_8UC1);
     Mat UResidual = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
     Mat VResidual = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);

     Mat YChannel = Mat::zeros(Size(RHight, CWidth), CV_8UC1);
     Mat UChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);
     Mat VChannel = Mat::zeros(Size(UVHeightRows, UVWidth), CV_8UC1);

     YResidual = Encoded(Range(1, RHight), Range(1, CWidth));
     UResidual = Encoded(Range((RHight)+1, RHight+(RHight/4)), Range(1, CWidth));
     VResidual = Encoded(Range((RHight + (RHight / 4))+1, 1152), Range(1, CWidth));

     UChannel = UResidual.reshape(1, UVHeightRows); // align the rows
     VChannel = VResidual.reshape(1, UVWidth); // align the rows


     /// JPEG mode 6 predictor formula: X = B + ((A − C)/2), onde: X=(r,c); A=(r,c-1); B=(r-1,c) e C=(r-1,c-1)
     ///A=YChannel.at<uint8_t>(r,c-1), B=YChannel.at<uint8_t>(r-1,c) e C=YChannel.at<uint8_t>(r-1,c-1)

     for (int r = 0; r < RHight; r++) {
         for (int c = 0; c < CWidth; c++) {
             if (r == 0) {
                 YChannel.at<short>(r, c) = YResidual.at<short>(r, c);
             }
             if (c == 0) {
                 YChannel.at<short>(r, c) = YResidual.at<short>(r, c);
             }
             else {
                 int ax, bx, cx, x;
                 ax = YResidual.at<short>(r, c - 1);
                 bx = YResidual.at<short>(r - 1, c);
                 cx = YResidual.at<short>(r - 1, c - 1);
                 x = YResidual.at<short>(r, c);
                 YChannel.at<uchar>(r, c) = x + (bx + ((ax - cx) / 2));
             }
         }
     }

     for (int r = 0; r < UVHeightRows; r++) {
         for (int c = 0; c < UVWidth; c++) {
             if (r == 0) {
                 UChannel.at<short>(r, c) = UResidual.at<short>(r, c);
             }
             if (c == 0) {
                 UChannel.at<short>(r, c) = UResidual.at<short>(r, c);
             }
             else {
                 int ax, bx, cx, x;
                 ax = UResidual.at<short>(r, c - 1);
                 bx = UResidual.at<short>(r - 1, c);
                 cx = UResidual.at<short>(r - 1, c - 1);
                 x = UResidual.at<short>(r, c);
                 UChannel.at<uchar>(r, c) = x + (bx + ((ax - cx) / 2));
             }
         }
     }

     for (int r = 0; r < UVHeightRows; r++) {
         for (int c = 0; c < UVWidth; c++) {
             if (r == 0) {
                 VChannel.at<uchar>(r, c) = VResidual.at<short>(r, c);
             }
             if (c == 0) {
                 VChannel.at<uchar>(r, c) = VResidual.at<short>(r, c);
             }
             else {
                 int ax, bx, cx, x;
                 ax = VResidual.at<short>(r, c - 1);
                 bx = VResidual.at<short>(r - 1, c);
                 cx = VResidual.at<short>(r - 1, c - 1);
                 x = VResidual.at<short>(r, c);
                 VChannel.at<uchar>(r, c) = x + (bx + ((ax - cx) / 2));
             }
         }
     }

     resize(UChannel, UChannel, Size(RHight, CWidth), INTER_CUBIC);
     resize(UChannel, UChannel, Size(RHight, CWidth), INTER_CUBIC);

     Mat merged[3] = { YChannel, UChannel, VChannel };
     Mat yuvcolor = Mat::zeros(Size(RHight, CWidth), CV_8UC3);
     merge(merged, 3, yuvcolor);

     Mat original = Mat::zeros(Size(RHight, CWidth), CV_8UC3);
     cvtColor(yuvcolor, original, COLOR_YUV2BGR);

    imwrite(wfilename, original);

}


int main(int argc, char* argv[]){


    ImageDecoder(argv[1]);


    return 0;
}

