classdef Scene < handle
    %Scene Constructs scene object
    %   All info and data for a given scene
    
  properties (Access = public)
      name
      focal_pxid
      height
      width
      buffer = 24

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

        m_scene.pxid_mat = ones(h,w);
        m_scene.mxvi_mat = cell(years, 1);
        for i = 1:years
          m_scene.mxvi_mat{i} = ones(h,w);
        end
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
            m_scene.mxvi_mat{year}(i, j) = nan;
          else
            m_scene.mxvi_mat{year}(i, j) = mxvi_vector(m_scene.pxid_mat(i, j));
          end
        end
      end
      m_scene.mxvi_mat{year} = double(m_scene.mxvi_mat{year}); 
      m_scene.mxvi_mat{year} = m_scene.mxvi_mat{year} / 10000;
    end
  end
end

