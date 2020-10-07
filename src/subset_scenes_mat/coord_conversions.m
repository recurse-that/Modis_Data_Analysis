classdef coord_conversions
    %coord_conversions contains functions to convert given points to other
    %forrms
    %   functions for converting from latitude and logitude, converting
    %   from lat and long to file coordinate rows and columns
    
    properties (Access = public)
        m_num_scenes
        m_scene_dim
    end
    
    methods
        function set_properties = coord_conversions(num_scenes, scene_dim) 
            % init returns true when the classes properties have been set
            coord_conversions.m_num_scenes = num_scenes;
            coord_conversions.m_scene_dim = scene_dim;
            
        end  % end init 
        function pxid = latlon_to_pxid(coord_conversions, m_cur_scene)
            % m_scene_coords Outputs the pixel value associated with the 
            % latitude and longitude of a given scenes focal pixel
            %   Detailed explanation goes here 
            
            % define lat and lon of current scene
            scene_lat = m_cur_scene(1,1);
            scene_lon = m_cur_scene(1,2);
            % load the lat and lon files
            % load("ancillary_mat/modis_qkm_pixel_latlon.mat");
            % checks how close the pixel @ index is to params
            lat_diff = 1;
            lon_diff = 1;
      
            % initialize the values of the pixel closest to params
            lon_pix = 1;
            lat_pix = 1;
            
            load("Data/ancillary_mat/modis_qkm_pixel_latlon.mat");
            % define variable that keeps track of the closest lon pxid
            diff = 212029488;
            prev_diff = diff;
            for i = 1:212029488
                % specify the lat and lon from the file being checked
                file_lat = modis_qkm_pixel_lat(i);
                file_lon = modis_qkm_pixel_lon(i);
                % control vars to check against previous difference
                lat_control = abs(file_lat - scene_lat);
                lon_control = abs(file_lon - scene_lon);
 
                if(lon_diff > lon_control)
                    lon_diff = lon_control;
                    lon_pix = i;
                end  % end if
                
                if(lat_diff >= lat_control)
                    % set a placeholder for the last difference
                    prev_diff = diff;
                    
                    % if the outter loop has run at least once
                    if(diff < 212029468)
                        % set a placeholder for the last lat pixel
                        temp_lat_pix = lat_pix;
                    else
                        % lat_pix has not yet been redefined
                        temp_lat_pix = i;
                    end  % end inner if
                    
                    % set new values for lat_dif, lat_pix, and diff
                    lat_diff = lat_control;
                    lat_pix = i;
                    diff = abs(lon_pix - lat_pix);
                    
                    % if the new lat_pix is further from the lon_pix than
                    % the previous lat_pix
                    if(diff > prev_diff)
                        % reset lat_pix and diff to previous values
                        lat_pix = temp_lat_pix;
                        diff = prev_diff;
                    end  % end inner if
                end  % end if
                % return the 1x2 array containing the lat and lon pixels
                pxid = [lat_pix, lon_pix];
            end  % end inner for
            
 
        end  % end scene_coords
        
        function file_coords = pxid_to_rowcol(coord_conversions, scene_coords, scene_dimensions)
            %scene_pixels Outputs the row and column of a given scene
            %   Detailed explanation goes here
            
            % Define the scene pixels
            lat_pix = scene_coords(1,1);
            lon_pix = scene_coords(1,2);
            
            % Define the scene dimensions
            height = scene_dimensions(1,1);
            width = scene_dimensions(1,2);
            
            % Define the buffer around the displayed scene
            buffer = 16 % pixels outside scene needed to calculate pixels
                        % on the edge of the scene
            %Load the file containing row and col info for each pixel
            load("Data/ancillary_mat/modis_qkm_file_coords.mat");
            
            
            % initialize row and col to the row and col of the focal pixel
            row = modis_qkm_file_coord_row(lat_pix);
            col = modis_qkm_file_coord_col(lon_pix);
            
            % define the first row and col coordinates of the scene. 
            start_row = row - (height / 2) - buffer; 
            start_col = col - (width / 2) - buffer;
            
            % redefine row and col as the number of rows and cols in scene
            height = height + (2 * buffer);
            width = width + (2 * buffer);
            
            file_coords = [start_row, start_col;
                           height, width];
            
        end  % end scene_pixels
        
        function pxid_matrix = rowcol_to_matrix(coord_conversions, file_coords)
            %rowcol_to_matrix defines a matrix containing scene pixel file
            %coordinate info
            %   matrix is a height by width by 3 cell array with page 1
            %   containing file rows, page 2 containing file cols, and page
            %   3 containing pxids
            
            % initialize scene size
            height = file_coords(2,1);
            width = file_coords(2,2);
            
            % initialize starting point
            row = file_coords(1,1);
            col = file_coords(1,2);
            start_col = file_coords(1,2);
            
            % initialize empty height by width by 3 scene matrix
                % page 1 contains the row
                % page 2 contains the col
                % page 3 contains the pxid
            pxid_matrix = cell(height, width, 2);
            
            for m_row = 1:height
                for m_col = 1:width
                    % initialize the first 2 pages of the 3D cell array
                    %at the m_row, m_col coordinate to row and col
                    pxid_matrix{m_row,m_col, 1} = [row,col];
                    %pxid_matrix{m_row,m_col, 2} = col;
                    
                    % initialize the 3rd page at m_row, m_col to the pxid
                    pxid_matrix{m_row,m_col, 2} = 11556 * (col-1) + row;
                    
                    % increment col
                    col = col + 1;
                end  % end inner for
                
                % decrement col
                col = start_col;
                % increment row
                row = row + 1;
                
            end % end outer for
        end % end function
        
        function mxvi_matrix = scene_to_mxvi(coord_conversions, scene_matrices, cur_scene_index, cur_scene_dim, year)
            %scene_to_mxvi calculates mxvi values for scene
            %   takes scene_matrix containing pxids and returns a matrix of
            %   equal size containing corresponding mxvi values
            
            if year == 2002
                data_file = load("Data/mxvi_mat/mxvi_2002.mat");
            elseif year == 2003
                clearvars("Data/mxvi_mat/mxvi_2002.mat");
                data_file = load("Data/mxvi_mat/mxvi_2003.mat");
            elseif year == 2004
                clearvars("Data/mxvi_mat/mxvi_2003.mat");
                data_file = load("Data/mxvi_mat/mxvi_2004.mat");
            elseif year == 2005
                clearvars("Data/mxvi_mat/mxvi_2004.mat");
                data_file = load("Data/mxvi_mat/mxvi_2005.mat");
            elseif year == 2006
                clearvars("Data/mxvi_mat/mxvi_2005.mat");
                data_file = load("Data/mxvi_mat/mxvi_2006.mat");
            elseif year == 2007                
                clearvars("Data/mxvi_mat/mxvi_2006.mat");
                data_file = load("Data/mxvi_mat/mxvi_2007.mat");
            elseif year == 2008                
                clearvars("Data/mxvi_mat/mxvi_2007.mat");
                data_file = load("Data/mxvi_mat/mxvi_2008.mat");
            elseif year == 2009
                clearvars("Data/mxvi_mat/mxvi_2008.mat");
                data_file = load("Data/mxvi_mat/mxvi_2009.mat"); 
            elseif year == 2010
                clearvars("Data/mxvi_mat/mxvi_2009.mat");
                data_file = load("Data/mxvi_mat/mxvi_2010.mat"); 
            elseif year == 2011
                clearvars("Data/mxvi_mat/mxvi_2010.mat");
                data_file = load("Data/mxvi_mat/mxvi_2011.mat"); 
            elseif year == 2012
                clearvars("Data/mxvi_mat/mxvi_2011.mat");
                data_file = load("Data/mxvi_mat/mxvi_2012.mat"); 
            elseif year == 2013
                clearvars("Data/mxvi_mat/mxvi_2012.mat");
                data_file = load("Data/mxvi_mat/mxvi_2013.mat"); 
            elseif year == 2014
                clearvars("Data/mxvi_mat/mxvi_2013.mat");
                data_file = load("Data/mxvi_mat/mxvi_2014.mat");  
            elseif year == 2015
                clearvars("Data/mxvi_mat/mxvi_2014.mat");
                data_file = load("Data/mxvi_mat/mxvi_2015.mat");
            elseif year == 2016
                clearvars("Data/mxvi_mat/mxvi_2015.mat");
                data_file = load("Data/mxvi_mat/mxvi_2016.mat");  
            elseif year == 2017
                clearvars("Data/mxvi_mat/mxvi_2016.mat");
                data_file = load("Data/mxvi_mat/mxvi_2017.mat"); 
            elseif year == 2018
                clearvars("Data/mxvi_mat/mxvi_2017.mat");
                data_file = load("Data/mxvi_mat/mxvi_2018.mat");
            elseif year == 2019
                clearvars("Data/mxvi_mat/mxvi_2018.mat");
                data_file = load("Data/mxvi_mat/mxvi_2019.mat"); 
            end  % end elseif block
            
            % temporarily hold all the scene pixel IDs
            scene_pxid = scene_matrices{cur_scene_index, 1};
            % temporarily hold the current scene's dimensions
            height = cur_scene_dim(1,1);
            width = cur_scene_dim(1,2);
            % initially holds the scene pixel IDs which will be
            % replaced by mxvi numbers by the end of the loop
            mxvi_matrix = cell(height, width);

            for i = 1:height
                for j = 1:width
                    % the pixel ID of the current position
                    cur_pxid_cell = scene_pxid(i,j,2);
                    cur_pxid = cur_pxid_cell{1};
                    % fill the current position in the mxvi matrix
                    mxvi_matrix{i,j} = data_file.mxvi(cur_pxid);
                end  % end innermost for
            end  % end middle for
        end  % end scene_to_mxvi
    end  % end methods
end  % end classdef