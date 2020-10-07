

#ifndef SCENE_H
#define SCENE_H

#include "MXVI.h"
// #include "Correlations.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Scene {
public:
  Scene() {}  // End default constructor
  // Scene(const Scene& orig);
  void set_name(string scene_name);
  string get_name();

  void set_MXVI_paths(string full_path); 
  string get_MXVI_path(int year_index);
  string get_path();
  
  void set_correlations();
  void set_timeframe(int start_year, int end_year);
  int get_timeframe(string choice);
  
  void set_size(int row_count, int col_count);
  int get_size(string choice);


  MXVI get_MXVI(int year_index);
  bool set_pixel_MXVI(int year_index, int px_index, double MXVI_val);
  double get_pixel_MXVI(int year_index, int px_index);

  void print_scene();
private:
  string m_name;
  string m_path;
  int m_row_count, m_col_count, m_size;
  int m_year_count, m_start_year, m_end_year;
  MXVI *m_MXVI;  // rows are MXVI values, cols are years
                    // m_size by year_count
};
#endif
