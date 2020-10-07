
#include "Executive.h"

Executive::Executive() {
  read_path_info_called = 0;
  read_path_info_called = 0;
  set_data_called = 0;
  set_scene_called = 0;
  read_MXVI_matrices_called = 0;
  write_test_called = 0;

  read_path_info("Path_Info.txt");
  read_MXVI_matrices();
  // print();
  // test_data->get_scene(0).print_scene();
}  // End Constructor

Executive::~Executive() {}

/* PUBLIC GETTERS */
Data* Executive::get_data(int data_i) {
  if( data_i == 0 )
    return test_data;
  else if( data_i == 1 )
    return simple_data;
  else
    return complex_data;
}  // End get_data

/* PUBLIC HELPERS */
string Executive::get_current_working_dir() {
  // char buff[FILENAME_MAX];
  // GetCurrentDir( buff, FILENAME_MAX );
  // std::string current_working_dir(buff);
  // return current_working_dir;
  return "/Documents/dev/Workspace/MODIS_Data_Analysis/Workspace/calculations_cpp";
}  // End get_current_working_dir

void Executive::set_current_proj_dir(string &cur_working_dir, const string &wd_path_from_proj) {
  size_t pos = cur_working_dir.find(wd_path_from_proj);  // Search for substring
  if ( pos != string::npos ) 
    cur_working_dir.erase(pos, wd_path_from_proj.length());
}  // End set_current_proj_dir



/* PRIVATE METHODS */

/* READ FROM INPUT FILES */
void Executive::read_path_info(string path_info_file) {
  cout << "pussy ";
  read_path_info_called++;
  ifstream path_info(path_info_file);  // open input stream

  string working_dir = get_current_working_dir();
  string path_from_proj;  // String to be removed from end of working directory

  path_info >> path_from_proj;

  set_current_proj_dir(working_dir, path_from_proj);  // remove path to working dir from project

  m_project_path = working_dir;  // root project directory
  path_info >> m_data_path;  // path from root project directory to data
  path_info >> scene_data_dir_count;  // number of scene data folders

  int cur_read = 0;  // Loop counter

  string scene_data_dir, dir_info_file;
  while ( cur_read < scene_data_dir_count ) {
    path_info >> scene_data_dir;
    path_info >> dir_info_file;
    read_scene_data_info_file(cur_read, scene_data_dir, dir_info_file);
    cur_read++;
  }  // End while
  path_info.close();
}  // End read_path_info

void Executive::read_scene_data_info_file(int dir_i, string scene_data_dir, string dir_info_file) {
  read_scene_data_called++;

  string path_to = m_project_path + m_data_path;
  string path_from = scene_data_dir + dir_info_file;
  string dir_path = path_to + path_from;
  cout << dir_path << endl;

  ifstream scene_data(dir_path);  // open file input stream
  set_current_proj_dir(dir_path, dir_info_file);  // remove dir_info_file from path string

  int start_year, end_year;  // first and last year of recorded data
  scene_data >> start_year >> end_year;

  int scene_count;  // Number of scenes in folders
  scene_data >> scene_count;
  set_data(dir_i, dir_path, scene_count, start_year, end_year);


  /* individual scene info */
  int row, col;
  string name;

  int cur_read = 0;
  while ( cur_read < scene_count ) {
    scene_data >> name;
    scene_data >> row >> col;
    string temp_path = dir_path + name;
    set_corr(dir_i, cur_read, name, row, col);
    cur_read++;
  }  // End while
  scene_data.close();

}  // End read_scene_data_info_file

/* PRIVATE SETTERS  */
void Executive::set_data(int dir_i, string dir_path, int scene_count, int start_year, int end_year) {
  set_data_called++;
  if( dir_i == 0 ) {
    test_data = new Data(dir_path, scene_count, start_year, end_year);
  }  // end if
  else if( dir_i == 1 )
    simple_data = new Data(dir_path, scene_count, start_year, end_year);
  else
    complex_data = new Data(dir_path, scene_count, start_year, end_year);
}  // End set_data

void Executive::set_corr(int data_dir_i, int scene_i, string name, int row, int col) {
  // cout << data_dir_i << ' ' << scene_i << ' ' << ' ' << name << ' ' << row << ' ' << col << endl;
  get_data(data_dir_i)->set_corr(scene_i, name, row, col);
}  // End set_scene

bool Executive::read_MXVI_matrices() {
  read_MXVI_matrices_called++;
  cout << endl << "Read_MXVI_Matrices Called" << endl;
  double cur_pixel_MXVI = 0;  // Stores the MXVI values passed from file input stream

  for(int scene_i = 0; scene_i < test_data->get_scene_count(); scene_i++) {
    Correlations cur_corr = test_data->get_corr(scene_i);
    Scene cur_scene = cur_corr.get_scene();  // Scene at given index
    for(int year_i = 0; year_i < test_data->get_year_count(); year_i++) {
      MXVI cur_MXVI = cur_scene.get_MXVI(year_i);  // MXVI at given year for current scene
      string path = cur_scene.get_MXVI_path(year_i);
      //TODO: try catch
      ifstream MXVI_in;
      MXVI_in.open(path);

      int size_count = 0;  // Used to confirm amount of vars in file = expected size
      while ( MXVI_in >> cur_pixel_MXVI ) {
        // Pass the MXVI value from given point to MXVI object's array
        cur_scene.set_pixel_MXVI(year_i, size_count, cur_pixel_MXVI);
        size_count++;  // Increment loop counter
        // If the input file contains more variables than expected, return false
        if( size_count > cur_scene.get_size("size") ) { 
          cout << "file for scene " << scene_i << "too large\n";
          return 0; 
        }  // End if
      }  // End while
      cout << "size_check " << size_count << '/';
      cout << cur_scene.get_size("size") << endl;
      if ( size_count < ( cur_scene.get_size("size") - 1) ) { return 0; }

    }  // End inner for

  }  // End outer for
  return 1;
}  // end read_MXVI_matrices

void Executive::print() {
  // test_data->print_constants();
}

