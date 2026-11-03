# Offline grid map generation
## Parameter Adjustment Guide(Location of parameter file: ./config/param.yaml)
### 1. Resolution of gridmap
 - related parameters
    ```bash
    grid_resolution: 0.1    #  栅格地图分辨率
    grid_resolution_inverse: 10    #  栅格地图分辨率的逆
    ```
### 2. Size of gridmap
 - related parameters
    ```bash
    grid_map_width: 4000   #  参数配置栅格地图的宽  
    grid_map_hight: 4000    #  参数配置栅格地图的高  
    ```
 - tips
    - These two parameters respectively refer to the number of grids corresponding to the length and width directions of the grid map，multiplying the grid map resolution yields the corresponding metric. units.
### 3. Voxel filtering parameters
 - related parameters
    ```bash
    vexel_flag: 0    #  是否启用
    voxel_filter_size: 0.1    #  分辨率
    ```
 - tips
    - Voxel filters are not enabled by default.
### 4. Parameters related to sporadic noise removal
 - related parameters
    ```bash
    statistic_flag: 0    #  是否启用
    statictis_filter_kmeans: 20    
    kmeans_factor: 4    
    statictis_filter_thred: 0.3    #  滤波阈值
    thred_factor: 3    
    ```
 - tips
    - When sporadic noise is found in the grid map, this function can be turned on and the parameters can be adjusted.
    - To enable the sporadic noise filtering function, you can set statistic_flag to 1.
    - Enabling the sporadic noise filtering function may result in excessive non noise being filtered out if the parameter settings are not appropriate. If this phenomenon occurs, adjust(increase) statitis_filter_thred (typical value 1.0).
### 5. Parameters related to ground point removal
 - related parameters
    ```bash
    ransac_flag: 0  # 是否去除地面点
    ransac_iters: 1000    #  迭代次数
    ransac_distance_thre: 0.1    #拟合地面的距离阈值
    ```
 - tips
    - Enable this function when removing flat points (ground, ceiling, flat walls, etc.).
    - To enable the ground point filtering function, set the ransac_stag to 1.
    - Enabling the ground point filtering function may result in flat surfaces (such as walls) being filtered out. In this case, you can adjust(decrease) the ransac_destance_thre(typical value 0.1).

