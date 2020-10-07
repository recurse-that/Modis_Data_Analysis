
#include "MXVI.h"

MXVI::MXVI(string file_path, int row, int col, int year) {
    m_border_width = 2;
    m_row = row;
    m_col = col;
    m_px_count = row * col;

    m_year = year;
    m_vals = new double[m_px_count];  // Initialize pointer array for vegitation values
    if ( set_file_path( file_path ) )  // Confirm the file passed can be opened
        file_exists = 1;
    else { file_exists = 0;}
}  // End constructor

 MXVI::MXVI(const MXVI &orig) { 
        m_px_count = orig.m_px_count; 
        m_row = orig.m_row;
        m_col = orig.m_col;
        m_year = orig.m_year;
        m_file_path = orig.m_file_path;
        file_exists = orig.file_exists;
        m_vals = new double[m_px_count];

        for (int i = 0; i < m_px_count; i++) {
            m_vals[i] = orig.m_vals[i];
        }

} 

void MXVI::set_MXVI_val(int px_index, double val) {
    cout << val << ' ';
        m_vals[px_index] = val;
}  // End set_MXVI_val

bool MXVI::set_file_path(string file_path){
    ifstream check_for_file(file_path);
    if( check_for_file ) { 
        string str_year = to_string(m_year);
        m_file_path = file_path + str_year + ".txt";
        return 1; 
    }  // End if
    std::cout << "Unchanged\n";
    return 0;
}  // end set_file_path

void MXVI::print_MXVI() {
    int count = 0;
    while ( count < m_px_count ) {
        cout << m_vals[count] << ' ';
        count++;
    }  // End while
}  // End print_MXVI

