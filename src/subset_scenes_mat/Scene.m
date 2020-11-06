classdef Scene < handle
    %Scene Constructs scene object
    %   All info and data for a given scene
    
  properties (Access = public)
      name
      focal_pxid
      height
      width

      year_count
      pxid_mat
      mxvi_mat
      corr_mat
  end
    
  methods
    function m_scene = Scene(name,focal_pxid, h, w, years)
        %m_scene Scene class constructor
        %   Initializes all class member variables
        m_scene.name = name;
        m_scene.focal_pxid = focal_pxid;
        m_scene.height = h;
        m_scene.width = w;
        m_scene.year_count = years;
       % m_scene.r = 24;

        m_scene.pxid_mat = ones(h,w);
        m_scene.mxvi_mat = ones(years, h, w);
        m_scene.corr_mat = ones(h - 24*2, w - 24*2);

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
            div = double(mxvi_vector(m_scene.pxid_mat(i, j))) / 10000;
            m_scene.mxvi_mat(year, i, j) = div;
          end
        end
      end
    end
    
    function set_MXVI_fig(m_scene, year, rsub, csub, index)
      ss = size(m_scene.mxvi_mat, 2:3);
      mat_out = ones( ss(1)-rsub, ss(2)-csub);
      mat_in = ones(ss(1), ss(2));
      
      mat_in(1:end, 1:end) = m_scene.mxvi_mat(year, :, :);
      
      mat_out(1:end, 1:end) = mat_in(rsub*0.5+1 : end - rsub*0.5, csub*0.5+1 : end-csub*0.5);
      
      figure(index)
      imshow(mat_out, 'Colormap', parula(256));
    end
    
    function 
  end
end

