
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Data.h"
#include "Scene.h"
#include "MXVI.h"
#include "Correlations.h"

#include <stdio.h> 
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


// #ifdef WINDOWS
// #include <direct.h>
// #define GetCurrentDir _getcwd
// #else
// #include <unistd.h>
// #define GetCurrentDir getcwd
// #endif

using namespace std;

class Executive {
public:
  Executive();  // Stable
  /*   @PARAM:
   *   @PRE:
   *   @HELPERS:
   *   @POST:
   *   @RETURN:
   */
  ~Executive();
  
  Data* get_data(int data_i);
  /*   @PARAM:
   *   @PRE:
   *   @HELPERS:
   *   @POST:
   *   @RETURN:
   */

  Data *test_data;  // i = 0

  int read_path_info_called;
  int read_scene_data_called;
  int set_data_called;
  int set_scene_called;
  int read_MXVI_matrices_called;
  int write_test_called;


  string get_current_working_dir();
  void set_current_proj_dir(string &cur_working_dir, const string &wd_path_from_proj);

private:
  void read_path_info(string path_info_file);
  /*   @PARAM: 
   *    path_info_file: text file within working directory containing proper paths to data
   *   @PRE: called from constructor
   *   @HELPERS:
   *    get_current_working_dir
   *    set_current_proj_dir
   *   @FUNCTIONS: 
   *    read_scene_data_info_file
   *   @POST: reads given file and calls functions to assign input data properly
   *   @RETURN: NA
   */
  void read_scene_data_info_file(int dir_i, string scene_data_dir, string dir_info_file);
  /*   @PARAM:
   *    dir_i: the index of the data directory that holds data
   *    scene_data_dir: the path from project to data folder
   *    dir_info_file: the name of the directories info file
   *   @PRE: called from read_path_info
   *   @HELPERS: set_current_proj_dir: removes the info file from the path string
   *   @FUNCTIONS: set_data, set_scene;
   *   @POST:
   *   @RETURN:
   */
  void set_data(int dir_i, string dir_path, int scene_count, int start_year, int end_year);
  /*   @PARAM:
   *   @PRE:
   *   @HELPERS:
   *   @POST:
   *   @RETURN:
   */

  void set_corr(int data_dir_i, int scene_i, string name, int row, int col);
  /*   @PARAM:
   *   @PRE:
   *   @HELPERS:
   *   @POST:
   *   @RETURN:
   */
  void set_path_info(int data_i, string data_dir);

  
  // bool read_study_info(string file_name);  // Stable
  bool read_MXVI_matrices();
  // void write_test(int count, string path, int row, int col, int start_year, int end_year);
  
  void print();
  string m_project_path;
  string m_data_path;  // path to data from project path
  int scene_data_dir_count;
  
  Data *simple_data;  // i = 1
  Data *complex_data;  // i = 2

};  // end class definition
#endif
