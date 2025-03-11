
#pragma once
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/filters/voxel_grid.h>
#include<pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/statistical_outlier_removal.h>


#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/visualization/cloud_viewer.h>

namespace gridmap {

/**
 * @brief 地面分割的相关参数结构体
 */
typedef struct RemoveGroundParam {
        std::string msPCDPath;  // 加载PCD格式点云地图路径
        bool mbVoxelFlag;    //  是否进行体素降采样标志位
        bool mbStatisticFlag;    //  是否进行统计滤波标志位
        bool mbGroundCloudViewerFlag; //  是否查看非地面点云标志位
        int mbGroundCloudViewerSize; //  是查看非地面点云时的激光点大小
        float mfVoxelFilterSize;   //  体素降采样的体素边长大小
        int mnStatisticFilterKmeans;   //  统计滤波的搜寻的近邻点数量
        float mfStatisticFilterThre;  //  统计滤波的距离阈值
        int mnKmeansFactor;   //  统计滤波近邻因子（用于非地面点的统计滤波改变上面kmeans值）
        int mnStaticThredFactor;  //  统计滤波距离阈值因子（用于非地面点的统计滤波改变上面距离阈值）
        int mnRansacIters;   //  RANSAC算法迭代次数
        float mfRansacDistanceThre;   //  RANSAC算法拟合平面的距离阈值
        float mfMaxHight;   //  条件滤波的最大高度（z轴）
        float mfMinHight;  //  条件滤波的最小高度（z轴）
}RemoveGroundParamter;


class RemoveGroundCloud {
public:
        // 构造函数，加载参数
        RemoveGroundCloud (const RemoveGroundParamter& param_path);
        // 析构函数
        ~RemoveGroundCloud () {}
        // 提取非地面点才操作
        void Remove ();
public:
        // 参数对象
        RemoveGroundParamter mstruParam;
        // 原始加载点云数据
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpCloud;
        //  目标非地面点云数据（对原始非地面点云进行统计滤波获得）
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpNoGroundCloud;
        //   条件滤波点云
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpCloudFilteredIn;
        //  体素滤波点云
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpCloudFiltered;
        //  统计滤波点云
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpCloudFilterOut;
        // 原始非地面点云
        pcl::PointCloud<pcl::PointXYZI>::Ptr mpNoGroundPoints;
};
} // namespace  gridmap