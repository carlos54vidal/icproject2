#include <iostream>
#include <fstream>
#include <stdint.h>
#include <limits>
#include "AudioFile/AudioFile.h"

using namespace std;



int main(int argc, char* argv[]){

  AudioFile<double> audioFile;
  AudioFile<double> audioFileOut;

  audioFile.load(argv[1]);

  audioFileOut.setNumChannels(audioFile.getNumChannels());
  audioFileOut.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel());

  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();

  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++)
    {
      audioFileOut.samples[c][i] = audioFile.samples[c][i];
/*
    M/S stereo coding

    M/S stereo coding transforms the left and right channels into a mid channel and a side channel. The mid channel is the sum of the left and right channels, or M = L + R. The side channel is the difference of the left and right channels, or S = L − R .
    Unlike intensity stereo coding, M/S coding is a special case of transform coding, and retains the audio perfectly without introducing artifacts.
    Lossless codecs such as FLAC or Monkey's Audio use M/S stereo coding because of this characteristic.
    To reconstruct the original signal, the channels are either added  L = M + S or subtracted R = M − S .This form of coding is also sometimes known as matrix stereo and is used in many different forms of audio processing and recording equipment.
*/

    }
  }

  audioFile.save (argv[2], AudioFileFormat::Wave);

  return 0;
}

