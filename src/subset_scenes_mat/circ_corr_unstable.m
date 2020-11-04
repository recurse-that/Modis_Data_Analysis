classdef Correlation
  %UNTITLED2 Summary of this class goes here
  %   Detailed explanation goes here
  
  properties
    year_count
    height
    width
    mxvi_mats
    
    sum_mat
    count_mat
  end
  
  methods
    function m_corr = Correlation(mxvis,years, h,w)
      %UNTITLED2 Construct an instance of this class
      %   Detailed explanation goes here
      m_corr.year_count = years;
      m_corr.height = h;
      m_corr.width = w;
      
      m_corr.mxvi_mats = mxvis;
      m_corr.sum_mat = zeros(h,w)
      m_corr.count_mat = zeros(h,w);
      
    end
    
    function circ_corr(m_corr, f_x, f_y)
      %METHOD1 Summary of this method goes here
      %   Detailed explanation goes here
      sum1 = m_corr.sum_mat(f_x, f_y);
      count1 = m_corr.sum_mat; 
      avg = 0;
      focal_px = get_t_series(scene_mxvis, x, y, year_count);

      for px = (x - r) : (x + r)
        for py = (y - r) : (y + r)
          dx = x - px;
          dy = y - py;

          if (dx * dx + dy * dy <= r * r)
            adj_px = get_t_series(t_matrix, px, py, year_count);
            cur_corr = pearsonCorrelationCoefficents(focal_px, adj_px, year_count);

            count = count + 1;
            sum = sum + cur_corr;

            avg = sum / count;

          end % if
        end % inner for
      end % outer for

      circ_corr = avg;
    end
  end
end

