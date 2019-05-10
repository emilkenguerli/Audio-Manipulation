#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <memory>
#include "Audio.h"
#include "Audio.cpp"


using namespace std;


static void show_usage(std::string name)
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
  if (argc < 9 || argc > 11) {

    KNGEMI002::Audio <int> myobject (100, 75);
    cout << myobject.getmax() << endl;

    show_usage(argv[0]);
   return 1;
  }

int sampleRate = 0;
int sampleSize = 0;
int numberChannels = 0;
std::string OutputFileName;
std::string InputFileName1;
std::string InputFileName2;

  if (argv[1] == "-r") { // get sample rate
    sampleRate = stoi(argv[2]);
  }
  else {
    cout << "Sample rate not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (argv[3] == "-b") { // get sample size
    sampleSize = stoi(argv[4]);
  }
  else {
    cout << "Sample size not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (argv[5] == "-c") { // get number of channels
    numberChannels = stoi(argv[6]);
  }
  else {
    cout << "Number of channels not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if (argv[7] == "-o") { // get output file name
    OutputFileName = argv[8];
  }
  else {
    cout << "Output file not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
// Get <ops> parameters
  if (argv[9] == "-add") { // get output file name
	if(argv[11] != "") {
		InputFileName2 = argv[11];
	}
	else{
		cout << "Second input file not provided" << endl;
		show_usage(argv[0]);
		return 1;
	}
  }
  else if (argv[9] == "-cut") {
  }
  else if (argv[9] == "-radd") {
  }
  else if (argv[9] == "-cat") {
  }
  else if (argv[9] == "-v") {
  }
  else if (argv[9] == "-rev") {
  }
  else if (argv[9] == "-rms") {
  }
  else if (argv[9] == "-norm") {
  }
  else if (argv[9] == "-fadein") {
  }
  else if (argv[9] == "-fadeout") {
  }
  else {
    cout << "<ops> parameters not defined" << endl;
    show_usage(argv[0]);
    return 1;
  }
  if(argv[10] != ""){
	InputFileName1 = argv[10];
  }
  else{
	cout << "Input file not given" << endl;
	show_usage(argv[0]);
    return 1;
  }

  return 0;
}

