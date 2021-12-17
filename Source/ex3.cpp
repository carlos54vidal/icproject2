#include <iostream>
#include "sndfile.h"

int main(int argc, char* argv[]){






  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();

  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++)
    {
      audioFileOut.samples[c][i] = audioFile.samples[c][i];
    }
  }

  audioFile.save (argv[2], AudioFileFormat::Wave);

  return 0;
}
