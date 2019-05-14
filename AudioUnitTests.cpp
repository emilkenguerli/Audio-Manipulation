#include <iostream>
#include "Audio.h"
#include "Audio.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Test Save", "[SAVE OPERATION]")
{
  // buffer for test audio
  vector<int8_t> buffer_1_8(5);
  buffer_1_8.push_back(1); 
  buffer_1_8.push_back(2); 
  buffer_1_8.push_back(3); 
  buffer_1_8.push_back(4); 
  buffer_1_8.push_back(5); 
  KNGEMI002::Audio<int8_t> a1(44100, 8, 1, 5, buffer_1_8);
  string file_name = "Test";
  bool save_complete_1_8 = a1.save(file_name);

// save result
  REQUIRE(save_complete_1_8); // 1 channel 8 bit

  // buffer for test audio
  vector<int16_t> buffer_1_16(5);
  buffer_1_16.push_back(1); 
  buffer_1_16.push_back(2); 
  buffer_1_16.push_back(3); 
  buffer_1_16.push_back(4); 
  buffer_1_16.push_back(5); 
  KNGEMI002::Audio<int16_t> a2(44100, 16, 1, 5, buffer_1_16);
  bool save_complete_1_16 = a2.save(file_name);

// save result
  REQUIRE(save_complete_1_16); // 1 channel 16 bit

  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer_2_8(5, make_pair(1, 1));

  KNGEMI002::Audio<pair<int8_t, int8_t> > a3(44100, 8, 2, 5, buffer_2_8);
  bool save_complete_2_8 = a3.save(file_name);

// save result
  REQUIRE(save_complete_2_8); // 2 channels 8 bit

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer_2_16(5, make_pair(1, 1));

  KNGEMI002::Audio<pair<int16_t, int16_t> > a4(44100, 8, 2, 5, buffer_2_16);
  bool save_complete_2_16 = a4.save(file_name);

// save result
  REQUIRE(save_complete_2_16); // 2 channels 8 bit

}

TEST_CASE("Test Addition", "[ADD OPERATION]")
{
  // buffer for test audio
  vector<int8_t> buffer1_1_8(5, 1);
  KNGEMI002::Audio<int8_t> a1_1_8(44100, 8, 1, 5, buffer1_1_8);

  // buffer for test audio
  vector<int8_t> buffer2_1_8(5,2);
 KNGEMI002::Audio<int8_t> a2_1_8(44100, 8, 1, 5, buffer2_1_8);

  KNGEMI002::Audio<int8_t> sum_1_8 = a1_1_8+a2_1_8;
  bool save_complete_1_8 = sum_1_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_8);

  // buffer for test audio
  vector<int16_t> buffer1_1_16(5, 1);
  KNGEMI002::Audio<int16_t> a1_1_16(44100, 16, 1, 5, buffer1_1_16);

  // buffer for test audio
  vector<int16_t> buffer2_1_16(5, 2);
  KNGEMI002::Audio<int16_t> a2_1_16(44100, 16, 1, 5, buffer2_1_16);

  KNGEMI002::Audio<int16_t> sum_1_16 = a1_1_16+a2_1_16;
  bool save_complete_1_16 = sum_1_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_16);


  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer1_2_8(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int8_t, int8_t> > a1_2_8(44100, 8, 2, 5, buffer1_2_8);

  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer2_2_8(5,make_pair(2, 2));
 KNGEMI002::Audio<pair<int8_t, int8_t> > a2_2_8(44100, 8, 2, 5, buffer2_2_8);

  KNGEMI002::Audio<pair<int8_t, int8_t> > sum_2_8 = a1_2_8+a2_2_8;
  bool save_complete_2_8 = sum_2_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_8);

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer1_2_16(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int16_t, int16_t> > a1_2_16(44100, 16, 2, 5, buffer1_2_16);

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer2_2_16(5, make_pair(2, 2));
  KNGEMI002::Audio<pair<int16_t, int16_t> > a2_2_16(44100, 16, 2, 5, buffer2_2_16);

  KNGEMI002::Audio<pair<int16_t, int16_t> > sum_2_16 = a1_2_16+a2_2_16;
  bool save_complete_2_16 = sum_2_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_16);
}

TEST_CASE("Test Concatenation", "[CAT OPERATION]")
{
  // buffer for test audio
  vector<int8_t> buffer1_1_8(5, 1);
  KNGEMI002::Audio<int8_t> a1_1_8(44100, 8, 1, 5, buffer1_1_8);

  // buffer for test audio
  vector<int8_t> buffer2_1_8(5,2);
 KNGEMI002::Audio<int8_t> a2_1_8(44100, 8, 1, 5, buffer2_1_8);

  KNGEMI002::Audio<int8_t> cat_1_8 = a1_1_8|a2_1_8;
  bool save_complete_1_8 = cat_1_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_8);

  // buffer for test audio
  vector<int16_t> buffer1_1_16(5, 1);
  KNGEMI002::Audio<int16_t> a1_1_16(44100, 16, 1, 5, buffer1_1_16);

  // buffer for test audio
  vector<int16_t> buffer2_1_16(5, 2);
  KNGEMI002::Audio<int16_t> a2_1_16(44100, 16, 1, 5, buffer2_1_16);

  KNGEMI002::Audio<int16_t> cat_1_16 = a1_1_16|a2_1_16;
  bool save_complete_1_16 = cat_1_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_16);


  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer1_2_8(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int8_t, int8_t> > a1_2_8(44100, 8, 2, 5, buffer1_2_8);

  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer2_2_8(5,make_pair(2, 2));
 KNGEMI002::Audio<pair<int8_t, int8_t> > a2_2_8(44100, 8, 2, 5, buffer2_2_8);

  KNGEMI002::Audio<pair<int8_t, int8_t> > cat_2_8 = a1_2_8|a2_2_8;
  bool save_complete_2_8 = cat_2_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_8);

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer1_2_16(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int16_t, int16_t> > a1_2_16(44100, 16, 2, 5, buffer1_2_16);

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer2_2_16(5, make_pair(2, 2));
  KNGEMI002::Audio<pair<int16_t, int16_t> > a2_2_16(44100, 16, 2, 5, buffer2_2_16);

  KNGEMI002::Audio<pair<int16_t, int16_t> > cat_2_16 = a1_2_16|a2_2_16;
  bool save_complete_2_16 = cat_2_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_16);
}

TEST_CASE("Test Cut", "[CUT OPERATION]")
{
  // buffer for test audio
  vector<int8_t> buffer1_1_8(5, 1);
  KNGEMI002::Audio<int8_t> a1_1_8(44100, 8, 1, 5, buffer1_1_8);

  int r1 = 2;
  int r2 = 4;
  pair<int, int> range = make_pair(r1,r2);

  KNGEMI002::Audio<int8_t> cut_1_8 = a1_1_8^range;
  bool save_complete_1_8 = cut_1_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_8);

  // buffer for test audio
  vector<int16_t> buffer1_1_16(5, 1);
  KNGEMI002::Audio<int16_t> a1_1_16(44100, 16, 1, 5, buffer1_1_16);

  KNGEMI002::Audio<int16_t> cut_1_16 = a1_1_16^range;
  bool save_complete_1_16 = cut_1_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_1_16);


  // buffer for test audio
  vector<pair<int8_t, int8_t> > buffer1_2_8(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int8_t, int8_t> > a1_2_8(44100, 8, 2, 5, buffer1_2_8);

  KNGEMI002::Audio<pair<int8_t, int8_t> > cut_2_8 = a1_2_8^range;
  bool save_complete_2_8 = cut_2_8.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_8);

  // buffer for test audio
  vector<pair<int16_t, int16_t> > buffer1_2_16(5, make_pair(1, 1));
  KNGEMI002::Audio<pair<int16_t, int16_t> > a1_2_16(44100, 16, 2, 5, buffer1_2_16);

  KNGEMI002::Audio<pair<int16_t, int16_t> > cut_2_16 = a1_2_16^range;
  bool save_complete_2_16 = cut_2_16.save("Test");

  // sum of test files saved
  REQUIRE(save_complete_2_16);  // buffer for test audio
}


