
#ifndef DATA_H
#define DATA_H

#include "Scene.h"
#include "MXVI.h"
#include "Correlations.h"

#include <string>
#include <iostream>

using namespace std;

class Data {
public:
  Data(string dir_path, int scene_count, int start_year, int end_year);
  ~Data();

  void calculate_correlation(int scene_i, int radius);
  
  void set_corr(int scene_i, string name, int row, int col);
  
  bool check_data();
  bool check_path();
  bool check_timeframe();
  bool check_scene_count();

  string get_path(bool full_path) { return m_dir_path; }
  int get_start_year() { return m_start_year; }
  int get_year_count() { return m_year_count; }
  int get_scene_count() { return m_scene_count; }
  Correlations get_corr(int scene_index) { return m_corr[scene_index]; }
  
  bool initialize_scene(int scene_index, string scene_name, int row_count, int col_count);

  void print_constants();
private:
  const string m_dir_path;
  // const string m_MXVI_path;
  // string m_full_path;
  // bool valid_path;
  
  const int m_scene_count;

  const int m_start_year;
  const int m_end_year;
  const int m_year_count;
  // bool valid_years;
  Correlations *m_corr;

  string *scene_paths;
  
};
#endif
