#include <iostream>
#include <fstream>
#include <stdint.h>
#include <limits>
#include "AudioFile/AudioFile.h"
#include "BitStreamV2.h"
#include "Golomb.h"

using namespace std;

double mid_sample;
double side_sample;
double mid_sample1;
double side_sample1;
double left_sample;
double rigt_sample;
double residual;


int main(){

  BitStream teste("teste.wav","d",0);

    teste.Read_file_tbits();

      if (c%2 != 0){
       left_sample = audioFile.samples[c][i];
       else
            rigt_sample = audioFile.samples[c][i];
       }
/*
    M/S stereo coding:
    M/S stereo coding transforms the left and right channels into a mid channel and a side channel.
    The mid channel is the sum of the left and right channels, or M = L + R.
    The side channel is the difference of the left and right channels, or S = L − R .
    To reconstruct the original signal, the channels are either added  L = M + S or subtracted R = M − S.
*/
        mid_sample = (left_sample + rigt_sample)/2;
        side_sample =  left_sample - rigt_sample;
    }
//Fixed Linear and
//Finite Impulse Response linear
/* Polynomial interpolation:
P0 = 0
P1 = X(n-1)
P2 = 2X(n-1) - x(n-2)
P3 = 3X(n-1) - 3x(n-2) + x(n-3)
P4 = 4X(n-1) - 6x(n-2) + 4X(n-3) - x(n-4)
The most eficient way to implemet this is with a circula buffer 
*/



    for (i>4){

        mid_sample4 = mid_sample3;
        side_sample4 = side_sample3;
        mid_sample3 = mid_sample2;
        side_sample3 = side_sample2;
        mid_sample2 = mid_sample1;
        side_sample2 = side_sample1;
        mid_sample1 = mid_sample;
        side_sample1 = side_sample;

        mid_residual = mid_sample - ((mid_sample1*3) - (mid_sample2*3) + mid_sample3;
        side_residual = side_sample - ((side_sample1*3) - (side_sample2*3) + side_sample3;
    }

    for (i=4){

        mid_sample3 = mid_sample2;
        side_sample3 = side_sample2;
        mid_sample2 = mid_sample1;
        side_sample2 = side_sample1;
        mid_sample1 = mid_sample;
        side_sample1 = side_sample;

        mid_residual = mid_sample - ((mid_sample1*2) - mid_sample2);
        side_residual = side_sample - ((side_sample1*2) - side_sample2);
    }

    for (i=3){


        mid_sample2 = mid_sample1;
        side_sample2 = side_sample1;
        mid_sample1 = mid_sample;
        side_sample1 = side_sample;

        mid_residual = mid_sample - (mid_sample1 + mid_sample2)/2;
        side_residual = side_sample - (side_sample1 + side_sample2)/2;



 //       rbuffer = mid_sample;
 //       rbuffer = side_sample1;
    }

    for (i=2){

        mid_sample1 = mid_sample;
        side_sample1 = side_sample;

        mid_residual = mid_sample1/2;
        side_residual = side_sample/2;

    }

  }

  audioFile.save (teste.wfilename, AudioFileFormat::Wave);

  return 0;
}

