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
	private:
		int sample_rate;
		int sample_size;
		int no_channels;
		int no_samples;
		vector<T> sample_data;

		T a, b;
    public:
		Audio();
		Audio(int sr, int size, int chan, int no_samples, T* buffer);
		Audio(T first, T second) {a=first; b=second;}
		bool Load(string file_name);
		bool Save(string file_name);

		Audio operator|(const Audio& rhs);
		friend ostream& operator<<(ostream& lhs, const Audio<T>& rhs); // out stream 
		friend ostream& operator>>(ifstream& lhs, Audio<T>& rhs); // in stream 
  };
}

#endif