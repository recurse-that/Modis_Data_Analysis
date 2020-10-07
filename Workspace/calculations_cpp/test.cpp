
#include "test.h"

test::test() {
  test_scene_file_names = new string[2];
  test_scenes = new Scene[2];
  test_MXVIs = new MXVI[2];
  test_names = new string[2];
  test_names[1] = "high_corr";
  test_names[2] = "rand_corr";

}

void test::write_scene_file_tests(string path) {
  string dir = "/Data/Test_Input/" + dir;

  ofstream high_corr_file;
  ofstream rand_corr_file;

  string info_path = path + dir + "test_scene_info.txt";
  ofstream info_out(info_path);
  info_out << dir << endl;
  info_out << start_year << ' ' << end_year << endl;
  info_out << num_scenes << endl;
  int ns = 0;
  while ( ns < 2 ) {
    info_out << test_names[ns] << endl;
    info_out << size << ' ' << size << endl;
  }  // End while

  info_out.close();

  string full_path1 = path + dir + test_names[0];
  string full_path2 = path + dir + test_names[1];

  for (int year = start_year; year <= end_year; year++) {
    string cur_year = to_string(year);
    string dir1 = full_path1 + cur_year + ".txt";
    string dir2 = full_path2 + cur_year + ".txt";
    high_corr_file.open(dir1);
    rand_corr_file.open(dir2);
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        double temp = (j+1) * 0.1;
        high_corr_file << temp << ' ';
        temp = ((double) rand() / (RAND_MAX));
        rand_corr_file << temp << ' ';
      }  // End inner for
      high_corr_file << endl;
      rand_corr_file << endl;
    }  // End outer for
    high_corr_file.close();
    rand_corr_file.close();
  }  // End outermost for
}  // End write_test

void test::write_scene_tests() {

}  // End write_scene_tests

void test::write_MXVI_tests() {

}  // End write_MXVI_tests