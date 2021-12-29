#include <iostream>
#include <fstream>
#include <stdint.h>
#include <limits>
#include "Dependencies/AudioFile/AudioFile.h"
#include "BitStream.h"
#include "Golomb.h"

using namespace std;

double mid_sample;
double side_sample;
double left_sample;
double rigt_sample;
double mid_residual;
double side_residual;

string filename;


int main(int argc, char* argv[]){
	
	

    filename = argv[1];

    AudioFile<double> audioFile;

    audioFile.load(filename);
    double rbuffer{};
    //            rbuffer = static_cast<double>(rbuffer);
    int channels = audioFile.getNumChannels();
    int numSamples = audioFile.getNumSamplesPerChannel();

    double mid_sample4;
    double side_sample4;
    double mid_sample3;
    double side_sample3;
    double mid_sample2;
    double side_sample2;
    double mid_sample1;
    double side_sample1;

    for (int i = 0; i <= numSamples; i++) {
        for (int c = 0; c <= channels; c++) {
            if (c%2 != 0) {
                left_sample = audioFile.samples[c][i];
            }
            else {
                rigt_sample = audioFile.samples[c][i];
            }

            /**
            M/S stereo INTER-CHANNEL DECORRELATION coding:
            M/S stereo coding transforms the left and right channels into a mid channel and a side channel.
            The mid channel is the sum of the left and right channels, or M = L + R.
            The side channel is the difference of the left and right channels, or S = L − R .
            To reconstruct the original signal, the channels are either added  L = M + S or subtracted R = M − S.
            This form of coding is also sometimes known as matrix stereo and is used in many different forms of audio processing and recording equipment.
            **/
            mid_sample = (left_sample + rigt_sample) / 2;
            side_sample = left_sample - rigt_sample;

            ///Linear Predictive Coding (LPC) or Fixed Linear and
            ///Finite Impulse Response linear?

            if (i > 3) {

                mid_sample4 = mid_sample3;  ///mid_sample4 =x[n-4]
                side_sample4 = side_sample3;
                mid_sample3 = mid_sample2;
                side_sample3 = side_sample2;
                mid_sample2 = mid_sample1;
                side_sample2 = side_sample1;
                mid_sample1 = mid_sample;
                side_sample1 = side_sample;
                /// ^x(n)=4x[n-1]-6x[n-2]+4x[n-3]-x[n-4]
                mid_residual = mid_sample - ((mid_sample1 * 4) - (mid_sample2 * 6) + (mid_sample3 * 4) - mid_sample4);
                side_residual = side_sample - ((side_sample1 * 4) - (side_sample2 * 6) + (side_sample3 * 4) - mid_sample4);
            }

            if (i = 3) {
                mid_sample3 = mid_sample2;  ///mid_sample3 =x[n-3]
                side_sample3 = side_sample2;
                mid_sample2 = mid_sample1;
                side_sample2 = side_sample1;
                mid_sample1 = mid_sample;
                side_sample1 = side_sample;
                /// ^x(n)=3x[n-1]-3x[n-2]+x[n-3]
                mid_residual = mid_sample - ((mid_sample1 * 3) - (mid_sample2 * 3) + mid_sample3);
                side_residual = side_sample - ((side_sample1 * 3) - (side_sample2 * 3) + side_sample3);
            }

            if (i = 2) {
                mid_sample2 = mid_sample1;  ///mid_sample2 =x[n-2]
                side_sample2 = side_sample1;
                mid_sample1 = mid_sample;   ///mid_sample2 =x[n-1]
                side_sample1 = side_sample;
                /// ^x(n)=2x[n-1]-x[n-2]
                mid_residual = mid_sample - ((2 * mid_sample2) - mid_sample1);
                side_residual = side_sample - ((2 * side_sample2) - side_sample1);
            }

            if (i = 1) {
                /// ^x(n)=x[n-1]
                mid_sample1 = mid_sample;  ///mid_sample1 =x[n-1]
                side_sample1 = side_sample;

                mid_residual = mid_sample - mid_sample1;
                side_residual = side_sample - side_sample1;
            }

            if (i = 0) {
                /// ^x(n)=0
                mid_residual = mid_sample;
                side_residual = side_sample;
            }

  /// folding:
            if (mid_residual >= 0) {
                mid_residual = (2 * mid_residual);
            }
                else {
                mid_residual = (2 * mid_residual) - 1;
                }
            if (side_residual >= 0) {
                side_residual = 2 * mid_residual;
            }
                else {
                side_residual = (2 * mid_residual) - 1;
                }
/*To do:
FRAMING
An audio frame is preceded by a frame header and trailed by a frame footer. The header starts with a sync code, 
and contains the minimum information necessary for a decoder to play the stream, like sample rate, bits per sample, etc.*/


            Golomb gs;
			
            gs.filename = argv[1];
            gs.G_encoder(mid_residual);
            gs.G_encoder(side_residual);

        }
    }


  return 0;
}

