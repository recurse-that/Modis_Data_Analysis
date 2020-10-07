
#ifndef CORRELATIONS_H
#define CORRELATIONS_H

#include "MXVI.h"
#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>
#include<bits/stdc++.h> 

using namespace std;

class Correlations {
    public:
        Correlations() { Scene m_scene(); }
        void set_scene();
        void set_size(int row_count, int col_count);
        void set_radius(int radius);
        void set_name(string scene_name);
        void set_timeframe(int start_year, int end_year);
        void set_Scene_MXVI_paths(string full_path);
        
        Scene get_scene() { return m_scene; }
        
        
        void calculate_pearson();
        void print();

    private:
        double* get_time_series(int px_i);
        int get_row_of_px(bool outer, int px_index);
        int get_col_of_px(bool outer, int px_index);
        float correlation_coefficient(double X[], double Y[], int year_count);
        float map_nearby_pixels(int px_i, int r, double* focal_r);


        Scene m_scene;
        string m_name;


        string m_path;
        string output_path;
        int m_year_count;
        int m_start_year, m_end_year;
        int m_px_radius;
        
        int outer_row, outer_col;
        int inner_row, inner_col;
        int outer_px_count, inner_px_count;

        float* m_pearson;
        float* m_spearman;


};
#endif