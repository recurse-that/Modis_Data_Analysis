classdef MXVI_Circle
  %UNTITLED3 Summary of this class goes here
  %   Detailed explanation goes here
  
  properties
    fx
    fy
    r
    
    i_mat
    bools_mat
    c_sums
    c_counts
  end
  
  methods
    function c = Circle(x, y, h, w, r)
      %UNTITLED3 Construct an instance of this class
      %   Detailed explanation goes here
      c.fx = x;
      c.fy = y;
      c.r = r;
      
      c.bools_mat = (x1-x).^2+(y1-y).^2 <= r^2;
      
      c.c_sums = c.bools_mat(x-r:x+r, y-r:y+r);
      c.c_counts = c.c_sums;
    end
    
    function mapCircle(obj,inputArg)
      %METHOD1 Summary of this method goes here
      %   Detailed explanation goes here
      outputArg = obj.Property1 + inputArg;
    end
    
    function calc()
      sum = 0;
      count = 0; 
      avg = 0;
      focal_px = get_t_series(scene_mxvis, x, y, year_count);

      for px = (c.x - c.r) : (c.x + c.r)
        for py = (c.y - c.r) : (c.y + c.r)
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
    
    function shift = get_shift(x1, y1, x2, y2)
      dx = x1 - x2;
      dy = x2 - y2;
      shift = [c.r, c.r] + [dx, dy];
    end
    
  end
end

