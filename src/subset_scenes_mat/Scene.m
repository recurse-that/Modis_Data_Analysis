classdef Scene < handle
    %Scene Constructs scene object
    %   All info and data for a given scene
    
  properties (Access = public)
      name
      focal_pxid
      height
      width
      buf

      year_count
      pxid_mat
      mxvi_mat
      corr_mat
  end
    
  methods
    function m_scene = Scene(name,focal_pxid, h, w, buf, years)
        %Scene class constructor
        %   Initializes all class member variables
        m_scene.name = name;
        m_scene.focal_pxid = focal_pxid;
        m_scene.height = h;
        m_scene.width = w;
        m_scene.year_count = years;
        m_scene.buf = buf;
       % m_scene.r = 24;

        m_scene.pxid_mat = ones(h,w);
        m_scene.mxvi_mat = ones(years, h, w);
        m_scene.corr_mat = nan(h - 24*2, w - 24*2);

    end

    function set_pxid_mat(m_scene, c)
      %set_pxid_mat defines pxid mat values
      %   Defines matrix with all pxids of the scene
      h = m_scene.height;
      w = m_scene.width;
      
      s_h = h / 2 - 1;
      s_w = w / 2 - 1;

      start_pxid = m_scene.focal_pxid - s_w - (s_h * c);
      cur_pxid = start_pxid;
      
      for i = 1:h
        for j = 1:w
          m_scene.pxid_mat(i,j) = cur_pxid;
          cur_pxid = cur_pxid + 1;
        end
        cur_pxid = start_pxid + c * i;
      end
    end

    function set_mxvi_mat(m_scene, year, mxvi_vector, water_mask)
      %set_mxvi_mat defines mxvi mat values
      %   Defines matrix with all mxvi values from the pxid values in
      %   pxid_mat using water_mask and mxvi vector for given year
      for i = 1:m_scene.height
        for j = 1:m_scene.width
          if water_mask( m_scene.pxid_mat(i, j) ) == 1
            m_scene.mxvi_mat(year, i, j) = nan;
          else
            m_scene.mxvi_mat(year, i, j) = (mxvi_vector(m_scene.pxid_mat(i, j)));
          end % if / else block
        end % inner for
      end % outer for
      % m_scene.mxvi_mat = double(mxvi_vector(m_scene.pxid_mat)) * 0.0001;
    end %set_mxvi
    
    function set_xcorr_mat(m_scene)
      %set_xcorr_mat sets the correlation matrix using cross correlations
      %  Creates the default correlation matrix by calling the 

      m_scene.corr_mat = ovr_xcorr(m_scene);
      
      
    end % sync
    
    function fig = get_MXVI_fig(m_scene, year, rsub, csub, index)
      % returns mxvi colormap for selected scene @ selected year
      mat_in = get_mxvi_mat(m_scene);
      s1 = size(mat_in,2);
      s2 = size(mat_in,3);
      mat_out(1:s1-rsub, 1:s2-csub) = mat_in(year, rsub * 0.5 + 1 : s1 - rsub *0.5, csub * 0.5 + 1 : s2 - csub * 0.5); 
      
      fig = figure(index);
      imshow(mat_out, 'Colormap', parula(256));
    end
    
    function fig = get_corr_fig(m_scene, rsub, csub, index)
      mat_in = get_corr_mat(m_scene);
      s = size(mat_in, 1:2);
      rsub = rsub * 0.5;
      csub = csub * 0.5;
      mat_out = mat_in(rsub + 1 : s(1) - rsub, csub + 1 : s(2) - csub); 
      
      fig = figure(index);
      imshow(mat_out, 'Colormap', parula(256));
    end
    
    function mxvi_mat = get_mxvi_mat(m_scene)
      mxvi_mat = double(m_scene.mxvi_mat) * 0.0001;
    end
    
    function corr_mat = get_corr_mat(m_scene)
      corr_mat = adjust_range(m_scene);
    end
    
  end
end

function ovr_synchrony = ovr_xcorr(m_scene)
  rad = m_scene.buf - 1;
  vals = nan(size(m_scene.mxvi_mat, 2:3) - [m_scene.buf*2, m_scene.buf*2]);
  for focx = m_scene.buf : size(m_scene.mxvi_mat, 2) - m_scene.buf
    for focy = m_scene.buf : size(m_scene.mxvi_mat, 3) - m_scene.buf
      vals(focx+1-m_scene.buf, focy+1-m_scene.buf) = circ_xcorr(m_scene.mxvi_mat, size(m_scene.mxvi_mat,1), focx, focy, rad);
    end % inner for
  end % outer for
  ovr_synchrony = vals; 
end % sync

function px_synchrony = circ_xcorr(mat, years, focx, focy, rad)
%Called to calculate average correlation coefficient of focal px with
%surrounding px within radius rad
% define empty matrix of size equal to bounding box of circle of radius r
% around focal point
% args (mat of size year_count x h x w, focal x, focal y, radius)
  corrs = nan(size(mat, 2:3));
  % define focal time series
  ts1 = mat(1:years, focx, focy);
  % runs for all points in bounding box of circle of radius r
  for curx = focx - rad : focx + rad
    for cury = focy - rad : focy + rad
      if sqrt((curx - focx)^2 + (cury - focy)^2) <= rad
        if (curx == focx && cury == focy)
          % Ignore correlation with itself
          corrs(curx, cury) = nan;
        else
          % define time series to compare
          ts2 = mat(1:years, curx, cury);
          corrs(curx, cury) = mean(xcorr(ts1, ts2));
          % curcorr = curcorr(2);
          % corrs(curx, cury) = curcorr;
        end % inner if / else
      end % outer if
    end % inner for
  end % outer for
  px_synchrony = mean(corrs, 'all', 'omitnan');
end % sync

function range_01 = adjust_range(m_scene)
  range_01 = m_scene.corr_mat - min(m_scene.corr_mat(:));  
  range_01 = range_01 ./ max(m_scene.corr_mat(:));
end

