
#include "Correlations.h"

void Correlations::set_scene() {
    m_scene.set_timeframe(m_start_year, m_end_year);
    m_scene.set_size(outer_row, outer_col);
    m_scene.set_timeframe(m_start_year, m_end_year);
    m_scene.set_MXVI_paths(m_path);
}
void Correlations::set_name(string scene_name) { m_name = scene_name; }
void Correlations::set_radius(int radius) { m_px_radius = radius; }
void Correlations::set_size(int row_count, int col_count) {
    outer_row = row_count;
    inner_row = outer_row - m_px_radius;
    outer_col = col_count;
    inner_col = outer_col - m_px_radius;

    outer_px_count = row_count * col_count;
    inner_px_count = inner_row * inner_col;
    
}  // End set_size

void Correlations::set_timeframe(int start_year, int end_year) {
  m_year_count = end_year - start_year;
  m_start_year = start_year;
  m_end_year = end_year;
}

void Correlations::set_Scene_MXVI_paths(string full_path) { m_path = full_path; }


/* CALCULATE */
void Correlations::calculate_pearson() {
    cout << "calculate called";
    int rad = ((m_px_radius * 2) - 1);

    int inner_count = 0;

    for (int px_i = rad; px_i <= rad; px_i++) {
        inner_count = px_i - rad;  // Indexes starting at 0
        double* focal_px_ts = get_time_series(px_i);
        m_pearson[inner_count] = map_nearby_pixels(px_i, m_px_radius, focal_px_ts);
    }  // End inner for
        
}  // End calculate_pearson

double* Correlations::get_time_series(int px_i) {
    double* vals = new double[m_year_count];
    for(int year_i = 0; year_i <= m_year_count; year_i++) {
        vals[year_i] = m_scene.get_pixel_MXVI(year_i, px_i);
    }  // End for
    return vals;
}  // End get_time_series

int Correlations::get_row_of_px(bool outer, int px_index) {
    if( px_index == 0 ) { return 0; }
    
    int first_px_in_row = 0;
    int row_count = 0;
    while( first_px_in_row <= px_index) {
        row_count++;
        if( outer )
            first_px_in_row = row_count * outer_col;
        else
            first_px_in_row = row_count * inner_col;
    }  // End while
    return (row_count - 1);
}  // End get_row_px
int Correlations::get_col_of_px(bool outer, int px_index) {
    if( px_index == 0 ) { return 0; }
    
    int row = get_row_of_px(outer, px_index);
    int pixels_before_row;
    
    if( outer ) 
        pixels_before_row = row * outer_col;
    else 
        pixels_before_row = row * inner_col;

    return (px_index - pixels_before_row);
}  // End get_col_of_px

float Correlations::correlation_coefficient(double *X, double *Y, int year_count) { 
  
    int sum_X = 0, sum_Y = 0, sum_XY = 0; 
    int squareSum_X = 0, squareSum_Y = 0; 
  
    for (int i = 0; i < year_count; i++) { 
        // sum of elements of array X. 
        sum_X = sum_X + X[i]; 
  
        // sum of elements of array Y. 
        sum_Y = sum_Y + Y[i]; 
  
        // sum of X[i] * Y[i]. 
        sum_XY = sum_XY + X[i] * Y[i]; 
  
        // sum of square of array elements. 
        squareSum_X = squareSum_X + X[i] * X[i]; 
        squareSum_Y = squareSum_Y + Y[i] * Y[i]; 
    } 
  
    // use formula for calculating correlation coefficient. 
    double corr = (double)(year_count * sum_XY - sum_X * sum_Y)  
                  / sqrt((year_count * squareSum_X - sum_X * sum_X)  
                      * (year_count * squareSum_Y - sum_Y * sum_Y)); 
  
    return corr; 
}  // End correlation_coefficient

float Correlations::map_nearby_pixels(int px_i, int r, double* focal_arr) {
    int focal_x = get_row_of_px(1, px_i);
    int focal_y = get_col_of_px(1, px_i);

    float avg_corr_coeff;
    float sum = 0.0f;
    
    int adj_px_compared = 1;  // Counter
    
    for(int x = focal_x - r; x <= focal_x + r; x++) {
        float cur_val;
        for(int y = focal_y - r; y <= focal_y + r; y++) {
            int dx = focal_x - x, dy = focal_y - y;
            int check = dx * dx + dy * dy;
            if ( check <= r * r ) {
                
                cur_val = correlation_coefficient(get_time_series(dx*dy), focal_arr, m_year_count);
                sum += cur_val;
                avg_corr_coeff = sum / adj_px_compared;
                adj_px_compared++;

            }  // End if

        }  // End inner for
        std::cout << std::endl;
    }  // End outer for
    return avg_corr_coeff;
}  // End MapNearbyPixels

void Correlations::print() {
    for (int i = 0; i < inner_row; i++) {
        for (int j = 0; j < inner_col; j++) {
            cout << m_pearson[i*j] << ' ';
        }
        cout << endl;
    }
}