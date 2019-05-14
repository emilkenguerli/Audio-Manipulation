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
		//template <class U> friend class Normalise;
		Audio();
		Audio(int sr, int size, int chan, int no_samples, vector<T> buffer);
		Audio(T first, T second) {a=first; b=second;}
		~Audio();
		Audio(const Audio& orig_audio); // Copy constructor
		Audio& operator=(const Audio& orig_audio); // Assignment operator
		Audio& operator=(Audio&& orig_audio); // Move assignment operator

		bool load(string file_name);
		bool save(string file_name);

		Audio operator+(const Audio& rhs);
		Audio operator|(const Audio& rhs);
		Audio operator*(pair<float,float> rhs);
		Audio operator^(pair<int,int> rhs);
		bool cut_range(pair<int,int> r);
		Audio rev();
		double rms();
		Audio norm(pair<double, double> p);

  };

  template <class T> class Normalise {
	public:
		Normalise(double rms1, double rms2) : desired_rms(rms1), current_rms(rms2){}
		T operator()(T rhs);

	private:
		double desired_rms;
		double current_rms;
  };

  template <class T> class Audio<pair<T,T> >{
		private:
		int sample_rate;
		int sample_size;
		int no_channels;
		int no_samples;
		vector<pair<T,T> > sample_data;

		T a, b;
    public:
		//template <class U> friend class Normalise;
		Audio();
		Audio(int sr, int size, int chan, int no_samples, vector<pair<T,T> > buffer);
		Audio(T first, T second) {a=first; b=second;}
		~Audio();
		Audio(const Audio& orig_audio); // Copy constructor
		Audio& operator=(const Audio& orig_audio); // Assignment operator
		Audio& operator=(Audio&& orig_audio); // Move assignment operator

		bool load(string file_name);
		bool save(string file_name);

		Audio operator+(const Audio& rhs);
		Audio operator|(const Audio& rhs);
		Audio operator*(pair<float,float> rhs);
		Audio operator^(pair<int,int> rhs);
		bool cut_range(pair<int,int> r);
		Audio rev();
		pair<double,double> rms();
		Audio norm(pair<double, double> p);


  };

  template <class T> class Normalise<pair<T,T> > {
	public:
		Normalise(pair<double, double> rms1, pair<double, double> rms2) : desired_rms(rms1), current_rms(rms2){}
		pair<T,T> operator()(pair<T,T> rhs);

	private:
		pair<double, double> desired_rms;
		pair<double, double> current_rms;
  };
}

#endif