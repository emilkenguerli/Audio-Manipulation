#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <math.h>
#include <numeric> 
#include "Audio.h"

namespace KNGEMI002 {

//Default constructor

template<class T> Audio<T>::Audio(){

      no_channels = 1;
      sample_size = 8*sizeof(T);
}

template<class T> Audio<pair<T,T> >::Audio(){

      no_channels = 1;
      sample_size = 8*sizeof(T);
}

//constructor

template<class T> Audio<T>::Audio(int sr, int size, int chan, int samples, vector<T> buffer){

	sample_rate = sr;
    sample_size = size;
    no_channels = chan;
    no_samples = samples;
    sample_data.swap(buffer);

}

template<class T> Audio<pair<T,T> >::Audio(int sr, int size, int chan, int samples, vector<pair<T,T>  > buffer){

	sample_rate = sr;
    sample_size = size;
    no_channels = chan;
    no_samples = samples;
    sample_data.swap(buffer);

}

//Destructor

template<class T> Audio<T>::~Audio(){
	  
	sample_rate = sample_size = no_channels = no_samples = 0;
	sample_data.clear();
}

template<class T> Audio<pair<T,T> >::~Audio(){

    sample_rate = sample_size = no_channels = no_samples = 0;
	sample_data.clear();
}

//Copy constructor

template<class T> Audio<T>::Audio(const Audio<T>& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data = orig_audio.sample_data;

}

template<class T> Audio<pair<T,T> >::Audio(const Audio<pair<T,T> >& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data = orig_audio.sample_data;

}

//Assignment operator

template <class T> Audio<T>& Audio<T>::operator=(const Audio<T>& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data.swap(orig_audio.sample_data);

	return *this;

}

template <class T> Audio<pair<T,T> >& Audio<pair<T,T> >::operator=(const Audio<pair<T,T> >& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data.swap(orig_audio.sample_data);

	return *this;
}

//Move assignment operator

template <class T> Audio<T>& Audio<T>::operator=(Audio<T>&& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data.swap(orig_audio.sample_data);

	orig_audio.sample_rate = orig_audio.sample_size = orig_audio.no_channels = orig_audio.no_samples = 0;
	orig_audio.sample_data.clear();

	return *this;

}

template <class T> Audio<pair<T,T> >& Audio<pair<T,T> >::operator=(Audio<pair<T,T> >&& orig_audio){

	sample_rate = orig_audio.sample_rate;
    sample_size = orig_audio.sample_size;
    no_channels = orig_audio.no_channels;
    no_samples = orig_audio.no_samples;
    sample_data.swap(orig_audio.sample_data);

	orig_audio.sample_rate = orig_audio.sample_size = orig_audio.no_channels = orig_audio.no_samples = 0;
	orig_audio.sample_data.clear();

	return *this;
}

//Loading from file

template <class T> bool Audio<T>::load(string file_name) 
{
  stringstream ss(file_name);
  vector<string> result;
  while(ss.good()) {
    string substr;
    getline(ss, substr, '_');
    result.push_back(substr);
  }
  if (result.size() < 5) {
    cout << "Invalid input file name format: " << file_name << endl;
    return false;
  }
  sample_rate = stoi(result[1]);
  sample_size = stoi(result[3]);
  string token = result[4].substr(0, result[4].find("."));
  if (token == "mono") no_channels = 1;
  else no_channels = 2;

  ifstream in_file;
  in_file.open(file_name, ios::binary|ios::in);
  if (!in_file) {
    cout << "Couldn't open input file" << endl;
    return false;
  }

  in_file.seekg (0, in_file.end);
  long file_length = in_file.tellg();
  in_file.seekg (0, in_file.beg);
  no_samples = file_length/(no_channels*sizeof(T));
  cout << "no_samples = " << no_samples << endl;
  sample_data.resize(no_samples);
  cout << "mono" << endl;
  for(auto i = 0; i < no_samples; i++) {
    in_file.read((char*)&(sample_data[i]), sizeof(T));
  }

  in_file.close();

  return true;
}

template <class T> bool Audio<pair<T,T> >::load(string file_name) 
{
 stringstream ss(file_name);
  vector<string> result;
  while(ss.good()) {
    string substr;
    getline(ss, substr, '_');
    result.push_back(substr);
  }
  if (result.size() < 5) {
    cout << "Invalid input file name format: " << file_name << endl;
    return false;
  }
  sample_rate = stoi(result[1]);
  sample_size = stoi(result[3]);
  string token = result[4].substr(0, result[4].find("."));
  if (token == "mono") no_channels = 1;
  else no_channels = 2;

  ifstream in_file;
  in_file.open(file_name, ios::binary|ios::in);
  if (!in_file) {
    cout << "Couldn't open input file" << endl;
    return false;
  }

  in_file.seekg (0, in_file.end);
  long file_length = in_file.tellg();
  in_file.seekg (0, in_file.beg);
  no_samples = file_length/(no_channels*sizeof(T));
  cout << "no_samples = " << no_samples << endl;
  sample_data.resize(no_samples);
  cout << "stereo" << endl;
  for(int i = 0; i < no_samples; i++) {
    in_file.read((char*)&(sample_data[i].first),sizeof(T));
    in_file.read((char*)&(sample_data[i].second),sizeof(T));
  }

  in_file.close();

  return true;
}

//Saving file

template <class T> bool Audio<T>::save(string file_name) {

  file_name += "_" + to_string(sample_rate) + "_" + to_string(sample_size) + "_mono.raw";

  ofstream out_file(file_name, ios::binary|ios::out);
  if (!out_file) {
    cout << "Couldn't open output file" << endl;
    return false;
  }
  T buffer;  
  cout << "Saving" << endl;        

  for(auto i = sample_data.begin(); i != sample_data.end(); ++i) {
    buffer  = *i;
    out_file.write((char*)&buffer, 1);
  }

  out_file.close();
  return true;
}

template <class T> bool Audio<pair<T,T> >::save(string file_name) {

  file_name += "_" + to_string(sample_rate) + "_" + to_string(sample_size) + "_stereo.raw";

  cout << "Saving" << endl;
  ofstream out_file(file_name, ios::binary|ios::out);
  if (!out_file) {
    cout << "Couldn't open output file" << endl;
    return false;
  }
  pair<T,T> buffer;  
  for(auto i = sample_data.begin(); i != sample_data.end(); ++i) {
    buffer  = *i;
    out_file.write((char*)&buffer.first, sizeof(T));
    out_file.write((char*)&buffer.second, sizeof(T));
  }

  out_file.close();
  return true;
}

//Adding files

template <class T> Audio<T> Audio<T>::operator+(const Audio<T>& rhs) 
{
  if(no_channels != rhs.no_channels || sample_size != rhs.sample_size || sample_rate != rhs.sample_rate){
  	  cerr << "The sampling, sampling size or mono/stereo settings didn't match" << endl;
	  return *this;
  }
   
  auto beg = this->sample_data.begin(), end = this->sample_data.end();
  auto in_beg = rhs.sample_data.begin(), in_end = rhs.sample_data.end();
  int max = (rhs.sample_size == 8) ? INT8_MAX : INT16_MAX;

  while ( beg != end) { 
    int mixed = (int)(*beg + *in_beg);
    if (mixed > max) mixed = max;
    if (mixed < -max) mixed = -max;
    *beg = mixed; 
    ++beg;
    ++in_beg;
  } 

  return *this;
}

template <class T > Audio<pair<T,T> > Audio<pair<T,T> >::operator+(const Audio<pair<T,T> >& rhs) 
{
  if(no_channels != rhs.no_channels || sample_size != rhs.sample_size || sample_rate != rhs.sample_rate){
  	  cerr << "The sampling, sampling size or mono/stereo settings didn't match" << endl;
	  return *this;
  }
   
  auto beg = this->sample_data.begin(), end = this->sample_data.end();
  auto in_beg = rhs.sample_data.begin(), in_end = rhs.sample_data.end();
  int max = (rhs.sample_size == 8) ? INT8_MAX : INT16_MAX;

  while ( beg != end) { 
    int mixed = (int)((*beg).first + (*in_beg).first);
    if (mixed > max) mixed = max;
    if (mixed <- max) mixed = -max;
      (*beg).first = mixed; 

    mixed = (int)((*beg).second + (*in_beg).second);
    if (mixed > max) mixed = max;
    if (mixed <- max) mixed = -max;
    (*beg).second = mixed; 

    ++beg;
    ++in_beg;
  } 
  return *this;
}

//Concatenation of file 1 and 2

template <class T> Audio<T> Audio<T>::operator|(const Audio<T>& rhs){
  if(no_channels != rhs.no_channels || sample_size != rhs.sample_size || sample_rate != rhs.sample_rate){
  	  cerr << "The sampling, sampling size or mono/stereo settings didn't match" << endl;
	  return *this;
  }

  vector<T> buffer(no_samples);
  copy(sample_data.begin(), sample_data.end(), buffer.begin());
  copy(rhs.sample_data.begin(), rhs.sample_data.end(), back_inserter(buffer));
  Audio<T> temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;
  
} 

template <class T> Audio<pair<T,T> > Audio<pair<T,T> >::operator|(const Audio<pair<T,T> >& rhs){
  if(no_channels != rhs.no_channels || sample_size != rhs.sample_size || sample_rate != rhs.sample_rate){
  	  cerr << "The sampling, sampling size or mono/stereo settings didn't match" << endl;
	  return *this;
  }

  vector<pair<T,T> > buffer(no_samples);
 
  copy(sample_data.begin(), sample_data.end(), buffer.begin());
  copy(rhs.sample_data.begin(), rhs.sample_data.end(), back_inserter(buffer));
  Audio<pair<T,T> > temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);
		
  return temp;
	  
}

//Volume factor

template <class T> Audio<T> Audio<T>::operator*(pair<float,float> rhs){
  //float f = rhs.first;
  
  vector<T> buffer(no_samples);
  transform(sample_data.begin(), sample_data.end(), buffer.begin(), [rhs](T value){return (T)(value*rhs.first);});
  Audio<T> temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;
  
} 

template <class T> Audio<pair<T,T> > Audio<pair<T,T> >::operator*(pair<float,float> rhs){
  
  vector<pair<T,T>> buffer(no_samples);
  transform(sample_data.begin(), sample_data.end(), buffer.begin(), [rhs](pair<T,T> value){return make_pair((T)value.first*rhs.first, (T)value.second*rhs.second);});
  Audio<pair<T,T> > temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;
	  
}

//Cut

template <class T> Audio<T> Audio<T>::operator^(pair<int,int> rhs) 
{
  cout << "Hello" << endl;
  vector<T> buffer(rhs.first);
  copy(sample_data.begin(), sample_data.begin() + rhs.first, buffer.begin());
  copy(sample_data.begin() + rhs.second, sample_data.end(), back_inserter(buffer));
  cout << buffer.size() << endl;
  Audio<T> temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);
  

  return temp;
}

template <class T > Audio<pair<T,T> > Audio<pair<T,T> >::operator^(pair<int,int> rhs) 
{
  vector<pair<T,T> > buffer(rhs.first);
  copy(sample_data.begin() , sample_data.begin() + rhs.first, buffer.begin());
  copy(sample_data.begin() + rhs.second, sample_data.end(), back_inserter(buffer));    
  Audio<pair<T,T> > temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;
}

//Add over subrange

template <class T> bool Audio<T>::cut_range(pair<int,int> r) {
  int lowerbound = r.first*sample_rate;
  int upperbound = r.second*sample_rate;

  vector<T> buffer(sample_data.begin() + lowerbound, sample_data.begin() + upperbound);

  no_samples = buffer.size();
  sample_data.clear();
  sample_data.resize(no_samples);
  for(auto i = 0; i < no_samples; i++) {
    sample_data[i] = buffer[i];
  }
  return true;
}

template <class T> bool Audio<pair<T,T> >::cut_range(pair<int,int> r) {
  int lowerbound = r.first*sample_rate;
  int upperbound = r.second*sample_rate;

  vector<pair<T,T> > buffer(sample_data.begin() + lowerbound, sample_data.begin() + upperbound);

  no_samples = buffer.size();

  sample_data.clear();
  sample_data.resize(no_samples);
  for(auto i = 0; i < no_samples; i++) {
    sample_data[i].first = buffer[i].first;
    sample_data[i].second = buffer[i].second;
  }

  return true;
}


//Reverse

template <class T> Audio<T> Audio<T>::rev(){

  Audio<T> temp(*this); //copy constructor called
  reverse(temp.sample_data.begin(), temp.sample_data.end());
  return temp;

}

template <class T> Audio<pair<T,T> > Audio<pair<T,T> >::rev() {

  reverse(sample_data.begin(), sample_data.end());
  return *this;
}

//RMS calculation

template <class T> double Audio<T>::rms(){
  
  double rms = 0;
  double sumsquares = accumulate(sample_data.begin(), sample_data.end(), 0.0, [](double sum, double value){return sum + value*value;});
  rms = sqrt(sumsquares/no_samples);

  return rms;

}

template <class T> pair<double,double> Audio<pair<T,T> >::rms() {

  double rms = 0;
  double sumsquares1 = accumulate(sample_data.begin(), sample_data.end(), 0.0, [](double sum, pair<T,T> value){return sum + ((double)value.first);});
  double sumsquares2 = accumulate(sample_data.begin(), sample_data.end(), 0.0, [](double sum, pair<T,T> value){return sum + ((double)value.second);});

  double rms1 = sqrt(sumsquares1/no_samples/2);
  double rms2 = sqrt(sumsquares2/no_samples/2);
  pair<double,double> rms_samples = make_pair(rms1, rms2);

  return rms_samples;
}

//Normalizing

template <class T> Audio<T> Audio<T>::norm(pair<double, double> p){
  double c_rms= p.first;
  double d_rms = this -> rms();
  vector<T> buffer(no_samples);

  Normalise<T> funct(c_rms, d_rms);
  transform(sample_data.begin(), sample_data.end(), buffer.begin(), funct);
  Audio<T> temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;

}

template <class T> Audio<pair<T,T> > Audio<pair<T,T> >::norm(pair<double, double> p){
  //pair<double, double> c_rms= make_pair(p.first, p.second);
  pair<double, double> d_rms = this -> rms();
  vector<pair<T,T> > buffer(no_samples);

  Normalise<pair<T,T> > funct(p, d_rms);
  transform(sample_data.begin(), sample_data.end(), buffer.begin(), funct);
  Audio<pair<T,T> > temp(sample_rate, sample_size, no_channels, buffer.size(), buffer);

  return temp;
}

template <class T> T Normalise<T>::operator()(T rhs){

  T value = (rhs * desired_rms)/current_rms;
  int max = (8* sizeof(T) == 8) ? INT8_MAX : INT16_MAX;
  if (value > max) value = max;
  if (value < -max) value = -max;

  return value;

} 

template <class T> pair<T,T> Normalise<pair<T,T> >::operator()(pair<T,T> rhs){

  double value1 = (rhs.first * desired_rms.first)/current_rms.first;
  int max = (8* sizeof(T) == 8) ? INT8_MAX : INT16_MAX;
  if (value1 > max) value1 = max;
  if (value1 < -max) value1 = -max;

  double value2 = (rhs.second * desired_rms.second)/current_rms.second;
  if (value2 > max) value2 = max;
  if (value2 < -max) value2 = -max;

  pair<T,T> combined = make_pair((T)value1, (T)value2);

  return combined;

} 



}