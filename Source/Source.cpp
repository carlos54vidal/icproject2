#include "Dependencies/opencv2/opencv.hpp"
#include <stdint.h>
#include <iostream>
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

int main() {

    rfilename = "tulips.ppm";

    Mat original = imread(rfilename, cv::IMREAD_UNCHANGED);

    int orows = original.rows;

    original = original.reshape(1, original.rows / 2); // align the uneven rows right of the even ones

    imshow("original/2", original);

    original = original.reshape(1, orows); // align the uneven rows right of the even ones

    imshow("original?", original);

    retur 0;
}








