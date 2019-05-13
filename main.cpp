#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include "Audio.h"
#include "Audio.cpp"


using namespace std;


static void show_usage(string name)
{
  cerr << "Usage: " << name << " <options> <ops>" << endl
       << "options:" << endl
       << "\t-h,--help\t\tshow this help message\n"
       << "\t-r <samples per sec>\tnumber of samples per second of the audio file(s)" << endl
       << "\t-b <sample size>\tsize (in bits) of each sample" << endl
       << "\t-c <number of channels>\tnumber of channels in the audio file(s)" << endl
       << "\t-o outFileName\t\tthe name of the newly created sound clip" << endl
       << "ops:" << endl
       << "\t-add: add soundFile1 and soundFile2" << endl
       << "\t-cut r1 r2: remove samples over range [r1,r2] (inclusive)" << endl
       << "\t-radd r1 r2 s1 s2 : add soundFile1 and soundFile2 over sub-ranges indicated" << endl
       << "\t-cat: concatenate soundFile1 and soundFile2" << endl
       << "\t-v r1 r2: volume factor for left/right audio (def=1.0/1.0)" << endl
       << "\t-rev: reverse sound file (assumes one sound file only)" << endl
       << "\t-rms: prints out the RMS of the sound file" << endl
       << "\t-norm r1 r2: normalize file for left/right audio" << endl
       << "\t-fadein n: n - number of seconds to slowly increase the volume" << endl
       << "\t-fadeout n: n - number of seconds to slowly decrease the volume" << endl
       << endl;
}

int main(int argc, char* argv[])
{
  if (argc < 9 || argc > 14) {
    show_usage(argv[0]);
   return 1;
  }

int sampleRate = 0;
int sampleSize = 0;
int numberChannels = 0;
string OutputFileName;

  if (string(argv[1]) == "-r") { // get sample rate
    sampleRate = stoi(argv[2]);
	
  }
  else {
    cout << "Sample rate not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (string(argv[3]) == "-b") { // get sample size
    sampleSize = stoi(argv[4]);
  }
  else {
    cout << "Sample size not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (string(argv[5]) == "-c") { // get number of channels
    numberChannels = stoi(argv[6]);
  }
  else {
    cout << "Number of channels not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (string(argv[7]) == "-o") { // get output file name
    OutputFileName = argv[8];
  }
  else {
    cout << "Output file not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
// Get <ops> parameters
  string SoundFile1, SoundFIle2; 
  if (string(argv[9]) == "-add") { // get output file name
	SoundFile1 = argv[10];
    SoundFIle2 = argv[11];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			KNGEMI002::Audio <int8_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding" << endl;
			KNGEMI002::Audio<int8_t> sum = a1+a2;
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			KNGEMI002::Audio <int16_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding" << endl;
			KNGEMI002::Audio<int16_t> sum = a1+a2;
			sum.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			KNGEMI002::Audio <pair<int8_t, int8_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding" << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> > sum = a1+a2;
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			KNGEMI002::Audio <pair<int16_t, int16_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding" << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > sum = a1+a2;
			sum.save(OutputFileName);
		}
	}
    
  }
  else if (string(argv[9]) == "-cut") {
	int r1 = stoi(argv[10]);
	int r2 = stoi(argv[11]);
	pair<int, int> range = make_pair(r1,r2);
	SoundFile1 = argv[12];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Cutting" << endl;
			KNGEMI002::Audio<int8_t> cut = a1^range;
			cut.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Cutting" << endl;
			KNGEMI002::Audio<int16_t> cut = a1^range;
			cut.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Cutting" << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> > cut = a1^range;
			cut.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Cutting" << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > cut = a1^range;
			cut.save(OutputFileName);
		}
	}
  }
  else if (string(argv[9]) == "-radd") {
    int r1 = stoi(argv[10]);
	int r2 = stoi(argv[11]);
	pair<int, int> range = make_pair(r1,r2);
	SoundFile1 = argv[12];
    SoundFIle2 = argv[13];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			KNGEMI002::Audio <int8_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding over range " << argv[10] << " to " << argv[11] << endl;
			KNGEMI002::Audio<int8_t> sum = a1.add_ranges(a2, range);
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			KNGEMI002::Audio <int16_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding over range " << argv[10] << " to " << argv[11] << endl;
			KNGEMI002::Audio<int16_t> sum = a1.add_ranges(a2, range);
			sum.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			KNGEMI002::Audio <pair<int8_t, int8_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding over range " << argv[10] << " to " << argv[11] << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> > sum = a1.add_ranges(a2, range);
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			KNGEMI002::Audio <pair<int16_t, int16_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Adding over range " << argv[10] << " to " << argv[11] << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > sum = a1.add_ranges(a2, range);
			sum.save(OutputFileName);
		}
	}
  }
  else if (string(argv[9]) == "-cat") {
	SoundFile1 = argv[10];
    SoundFIle2 = argv[11];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			KNGEMI002::Audio <int8_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Concatenating" << endl;
			KNGEMI002::Audio<int8_t> sum = a1|a2;
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			KNGEMI002::Audio <int16_t> a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Concatenating" << endl;
			KNGEMI002::Audio<int16_t> sum = a1|a2;
			sum.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			KNGEMI002::Audio <pair<int8_t, int8_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Concatenating" << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> > sum = a1|a2;
			sum.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			KNGEMI002::Audio <pair<int16_t, int16_t> > a2;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			if (!a2.load(SoundFIle2)) {
			  cerr << "Couldn't load " << SoundFIle2 << endl;
			  return 0;
			}
			cout << "Concatenating" << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > sum = a1|a2;
			sum.save(OutputFileName);
		}
	}
  }
  else if (string(argv[9]) == "-v") {
	float r1 = stod(argv[10]);
	float r2 = stod(argv[11]);
	pair<float, float> f = make_pair(r1,r2);
	SoundFile1 = argv[12];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Factoring" << endl;
			KNGEMI002::Audio<int8_t> factor = a1*f;
			factor.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Factoring" << endl;
			KNGEMI002::Audio<int16_t> factor = a1*f;
			factor.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Factoring" << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> > factor = a1*f;
			factor.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Factoring" << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > factor = a1*f;
			factor.save(OutputFileName);
		}
	}

  }
  else if (string(argv[9]) == "-rev") {
	SoundFile1 = argv[10];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Reversing" << endl;
			KNGEMI002::Audio<int8_t> reversed = a1.rev();
			reversed.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Reversing" << endl;
			KNGEMI002::Audio<int16_t> reversed = a1.rev();
			reversed.save(OutputFileName);
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Reversing" << endl;
			KNGEMI002::Audio<pair<int8_t, int8_t> >  reversed = a1.rev();
			reversed.save(OutputFileName);
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Reversing" << endl;
			KNGEMI002::Audio<pair<int16_t, int16_t> > reversed = a1.rev();
			reversed.save(OutputFileName);
		}
	}
  }
  else if (string(argv[9]) == "-rms") {
	SoundFile1 = argv[10];
	if(numberChannels == 1){
		if(sampleSize == 8){
			KNGEMI002::Audio <int8_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Calculating RMS" << endl;
			double RMS = a1.rms();
			cout << "RMS is " << RMS << endl;
		}
		else{
			KNGEMI002::Audio <int16_t> a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}
			cout << "Calculating RMS" << endl;
			double RMS = a1.rms();
			cout << "RMS is " << RMS << endl;
		}		
	}
	else{
		if(sampleSize == 8){
			KNGEMI002::Audio <pair<int8_t, int8_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Calculating RMS" << endl;
			pair<double,double> RMS = a1.rms();
			cout << "RMS is for left channel is " << RMS.first << " and for RMS for the right channel is " << RMS.second << endl;
		}
		else{
			KNGEMI002::Audio <pair<int16_t, int16_t> > a1;
			if (!a1.load(SoundFile1)) {
			  cerr << "Couldn't load " << SoundFile1 << endl;
			  return 0;
			}

			cout << "Calculating RMS" << endl;
			pair<double,double> RMS = a1.rms();
			cout << "RMS for the left channel is " << RMS.first << " and RMS for the right channel is " << RMS.second << endl;
		}
	}
  }
  else if (string(argv[9]) == "-norm") {
  }
  else if (string(argv[9]) == "-fadein") {
  }
  else if (string(argv[9]) == "-fadeout") {
  }
  else {
    cout << "<ops> parameters not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  return 0;
}
