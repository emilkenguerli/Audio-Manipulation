// image.h: declaration of audio class.
#ifndef AUDIO_H
#define AUDIO_H

#include <iterator>
#include <memory>
#include <stdint.h>
#include <math.h>

using namespace std;

namespace KNGEMI002 {

  template <class T> class Audio {
    int16_t buf[44100] = {0}; // buffer
    int n;                // buffer index
    double Fs = 44100.0;  // sampling frequency

    T a, b;
    public:
    Audio(T first, T second)
      {a=first; b=second;}
    T getmax();
  };
}

#endif