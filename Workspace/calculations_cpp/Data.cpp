
#include "Data.h"

Data::Data(string dir_path, int scene_count, int start_year, int end_year) : m_dir_path(dir_path), 
          m_scene_count(scene_count), m_start_year(start_year), 
          m_end_year(end_year), m_year_count(end_year - start_year) {
  m_corr = new Correlations[scene_count];
  scene_paths = new string[scene_count];
}  // End constructor

Data::~Data() {
  delete [] m_corr;
  delete [] scene_paths;
}

void Data::calculate_correlation(int scene_i, int radius) {
  m_corr[scene_i].calculate_pearson();
  m_corr[scene_i].print();
}
void Data::set_corr(int scene_i, string name, int row, int col) {
  m_corr[scene_i].set_name(name);
  m_corr[scene_i].set_radius(2);
  m_corr[scene_i].set_size(row, col);
  m_corr[scene_i].set_timeframe(m_start_year, m_end_year);
  scene_paths[scene_i] = m_dir_path + name + '/';
  m_corr[scene_i].set_Scene_MXVI_paths(scene_paths[scene_i]);

  m_corr[scene_i].set_scene();

  calculate_correlation(scene_i, 2);
}  // End set_scene

bool Data::check_data() {
  return (check_path() + check_timeframe() + check_scene_count());
}  // End check_data
bool Data::check_path() {
  if(m_dir_path.length() > 0) {
    cout << m_dir_path << endl;
    return 1;
  }  // End if
  else {
    cout << "Data::check_path: File path not set \n";
    return 0;
  }  // End else
}  // End set_path
bool Data::check_timeframe() {
  cout << "Data::check_path: year_count = " << m_year_count << endl;
  if (m_year_count > 0) {
    return 1;
  }  // End if
  return 0;
}  // End set_timeframe
bool Data::check_scene_count() {
  cout << "Data::check_scene_count: scene_count = " << m_scene_count << endl;
  if (m_scene_count > 0) {
    return 1;
  }  // End if
  return 0;
}  // End set_scene_count

void Data::print_constants() {
  cout << "Print constants called" << endl;
  // bool check = check_data();
  // cout << "Data passed properly? " << check << endl;
  int count = 0;
  while ( count < m_scene_count ) {
    get_corr(count).get_scene().print_scene();
  }
}  // End print_constants