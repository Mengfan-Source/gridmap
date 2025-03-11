
#pragma once
#include <iostream>
#include<string>
#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace gridmap {

/**
 * @brief pcd点云地图转gridmap的相关参数服务结构体
 */
typedef struct MapGeneratorParam {
        float mfResolution; // 栅格分辨率
        double mfResolutionInverse;      // 栅格分辨率的逆

        int mnMapWidth;    // 参数设置栅格地图的宽
        int mnMapHight;  //参数设置栅格地图的宽


        int mnMinPointsInPix;  // 每个像素的最小激光点数量
        int mnMaxPointsInPix;  // 每个像素的最大激光点数量
        float mfMinHeight;      //  截取点云的最小高度
        float mfMaxHeight;    //   截取点云的最大高度

        std::string mstrSaveMapPath;  //  保存电云地图转成的栅格地图（可能又有噪点）
        std::string mstrMapName;  //  栅格地图名称
        bool mstrSaveOriginGridMapFlag;   //  是否保存原始栅格地图
        float mfOccupiedThred;   //  栅格被占据阈值
        float mfFreeThred;     //   栅格空闲阈值
        int mfNegate;

}MapGeneratorParamter;

class MapGenerator
{
public:
        // 构造函数，加载参数
        MapGenerator (const MapGeneratorParamter& param);
        // 析构函数
        ~MapGenerator () {}
        // 点云地图--->栅格地图
        void Generate (const pcl::PointCloud<pcl::PointXYZI>& cloud);
        // 保存栅格地图
        void SaveGridMap ();

public:
        // 相关参数对象
        MapGeneratorParamter mstruParam;
        // gridmap对象
        cv::Mat mmgridMap;
};
} //  namespace gridmap
