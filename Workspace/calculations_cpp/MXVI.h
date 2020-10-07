
#ifndef MXVI_H
#define MXVI_H


#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>
#include<bits/stdc++.h> 

using namespace std;

class MXVI {
public:
    MXVI() {}
    MXVI(string file_path, int row, int col, int year);
    MXVI(const MXVI &orig); // End copy constructor
    void set_correlation();
    bool set_file_path(string file_path);
    string get_file_path() { return m_file_path; }

    bool get_open_status() { return file_exists; }

    void set_MXVI_val(int px_index, double val);
    double get_MXVI_val(int px_index) { return m_vals[px_index]; }

    void set_size(int row, int col);
    
    void print_MXVI();
private:
    string m_file_path;
    int m_px_count;
    int m_row, m_col;
    int m_year;
    int m_border_width;
    double *m_vals;
    bool file_exists;
}; 
#endif