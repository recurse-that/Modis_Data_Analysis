
#include "Scene.h"

// Scene::Scene(const Scene& orig) {
//     m_name = orig.m_name;
//     m_path = orig.m_path;
//     m_row_count = orig.m_row_count;
//     m_col_count = orig.m_col_count;
//     m_size = orig.m_size;
//     m_year_count = orig.m_year_count;
//     m_start_year = orig.m_start_year;
//     m_end_year = orig.m_start_year;

//     for (int i = 0; i < orig.m_year_count; i++) {
//       m_MXVI[i] = orig.m_MXVI[i];
//     }

// }
void Scene::set_name(string scene_name) { m_name = scene_name; }
string Scene::get_name() { return m_name; }

void Scene::set_MXVI_paths(string full_path) {
  m_path = full_path;
  // cout << "Scene::set_paths called: " << full_path << endl;
  m_MXVI = new MXVI[m_end_year - m_start_year];
  for(int year = m_start_year; year < m_end_year; year++) {
    MXVI cur_MXVI = MXVI(m_path, m_row_count, m_col_count, year);  // Construct new MXVI with directory path param
    m_MXVI[year - m_start_year] = cur_MXVI;  // add MXVI to array
  }  // End for
}  // End set_paths
string Scene::get_MXVI_path(int year_index) { return m_MXVI[year_index].get_file_path(); }

void Scene::set_correlations() {

}

string Scene::get_path() { return m_path; }

void Scene::set_timeframe(int start_year, int end_year) {
  m_year_count = end_year - start_year;
  m_start_year = start_year;
  m_end_year = end_year;
}
int Scene::get_timeframe(string choice) {
  if(choice == "start_year")
    return m_start_year;
  else if(choice == "end_year")
    return m_end_year;
  else 
    return m_year_count;
}  // End set_timeframe

void Scene::set_size(int row_count, int col_count) {
    m_row_count = row_count;
    m_col_count = col_count;
    m_size = row_count * col_count;
}  // End set_size
int Scene::get_size(string choice) {
  if (choice == "size") { return m_size; }
  else if (choice == "row") { return m_row_count; }
  else if (choice == "col") { return m_col_count; }
  else { 
    cout << "Scene::get_size called without proper params\n"; 
    return -1;
  }  // End else
  // TODO: catch errors
}  // End get_size

bool Scene::set_pixel_MXVI(int year_index, int px_index, double MXVI_val) {
    if( px_index > m_size || px_index < 0 ) { return 0; }
    m_MXVI[year_index].set_MXVI_val(px_index, MXVI_val);
    return 1;
}  // End set_piexl_MXVI
double Scene::get_pixel_MXVI(int year_index, int px_index) { 
  return m_MXVI[year_index].get_MXVI_val(px_index);
}

MXVI Scene::get_MXVI(int year_index) { return m_MXVI[year_index]; }

void Scene::print_scene() {
  // cout << m_name << '\n';
  // cout << "Rows: " << m_row_count << " Cols: " << m_col_count;
  // cout << " Size: " << m_size << '\n';
  cout << endl << m_year_count << endl;
  for (int i = 0; i < m_year_count; i++) {
    get_MXVI(i).print_MXVI();
    cout << endl;
  }  // End outer for
}  // end print_scene
