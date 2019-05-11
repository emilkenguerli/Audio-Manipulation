#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <type_traits>
#include "Audio.h"

namespace KNGEMI002 {

//Default constructor

template<class T> Audio<T>::Audio(){

      no_channels = 1;
      sample_size = 8*sizeof(T);
}

//constructor

template<class T> Audio<T>::Audio(int sr, int size, int chan, int samples, vector<T> buffer){

	sample_rate = sr;
    sample_size = size;
    no_channels = chan;
    no_samples = samples;
    sample_data.reset(buffer);

}

template <class T> bool Audio<T>::Load(string file_name) 
{
  stringstream ss(file_name);
  vector<string> result;

  while(ss.good()) {
    string substr;
    getline(ss, substr, '_');
    result.push_back(substr);
  }
  sample_rate = stoi(result[1]);
  sample_size = stoi(result[3]);
  string token = result[4].substr(0, result[4].find("."));
  if (token == "mono") no_channels = 1;
  else no_channels = 2;

cout << sample_rate << ", " << sample_size << ", " << no_channels << endl;

  ifstream in_file;
  cout << file_name << endl;
  in_file.open(file_name, ios::in|ios::binary);
  if (!in_file) {
    cout << "Couldn't open input file" << endl;
    return false;
  }

  in_file.seekg (0, in_file.end);
  long file_length = in_file.tellg();
  in_file.seekg (0, in_file.beg);
  no_samples = file_length/(no_channels*sizeof(T));
  cout << "no_samples is " << no_samples << endl;

  sample_data.resize(file_length);
  if(no_channels == 1){
	cout << "mono" << endl;
	for(auto i = 0; i < no_samples;i++){
		in_file.read((char*)&(sample_data[i]), sizeof(T));

	}
  }
  else if(no_channels == 2){
	if constexpr (is_same_v<T, pair<T, T> >){
		for(int i = 0; i< no_samples; i++){
			in_file.read((char*)&(sample_data[i].first),sizeof(T));
			in_file.read((char*)&(sample_data[i].second),sizeof(T));
		}
	}
  }
  
  in_file.close();
  cout<<"Done"<<endl;

  return true;
}

//Saves 

template <class T> bool Audio<T>::Save(string file_name) {
  if(no_channels == 1){
		file_name += "_" + to_string(sample_rate) + "_" + to_string(sample_size) + "_mono.raw";
  }
  else{
		file_name += "_" + to_string(sample_rate) + "_" + to_string(sample_size) + "_stereo.raw";
  }

  ofstream out_file(file_name, ios::binary|ios::out);
  if (!out_file) {
    cout << "Couldn't open output file" << endl;
    return false;
  }
  if(no_channels == 1){
	cout << "mono" << endl;
	for(auto i = 0; i < no_samples;i++){
		out_file.write((char*)&(sample_data[i]), sizeof(T));

	}
  }
  else if(no_channels == 2){
	if constexpr (is_same_v<T, pair<T, T> >){
		for(int i = 0; i< no_samples; i++){
			out_file.write((char*)&(sample_data[i].first),sizeof(T));
			out_file.write((char*)&(sample_data[i].second),sizeof(T));
		}
	}
  }


  return true;
}

//Concatenation of file 1 and 2

template <class T> Audio<T> Audio<T>::operator|(const Audio& rhs){
  if(no_channels != rhs.no_channels || sample_size != rhs.sample_size || sample_rate != rhs.sample_rate){
  	  cerr << "The sampling, sampling size or mono/stereo settings didn't match" << endl;
	  return *this;
  }

  vector<T> result(length);
  copy (sample_data.begin(), sample_data.end(), result.begin());
  copy(rhs.sample_data.begin(), rhs.sample_data.end(), back_inserter(result));
  Audio<T> temp(sample_rate, sample_size, no_channels, no_samples, result);

  return temp;
}

// Implement I/O operators for Audio: <<
template <class T> ostream& operator<<(ostream& lhs, const Audio<T>& rhs) 
{

}

//Implement I/O operators for Audio: >>
template <class T> ostream& operator>>(ifstream& lhs, Audio<T>& rhs)
{
} 
}