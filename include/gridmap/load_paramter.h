
#pragma once
#include <string>
#include <memory>

#include <opencv2/opencv.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "./image_denoise.h"
#include "./remove_ground.h"
#include "./pcd2gridmap.h"

namespace gridmap
{
        /**
         * @brief 加载地面分割、点云转gridmap、图像处理的参数服务类
         */
        class LoadParamter
        {
        public:
                LoadParamter(const std::string &param_path)
                {
                        this->msParamPath = param_path;
                        cv::FileStorage fs(this->msParamPath, cv::FileStorage::READ);
                        this->mstruRemoveParamter.msPCDPath = (std::string)fs["pcd_path"];
                        this->mstruRemoveParamter.mfVoxelFilterSize = (float)fs["voxel_filter_size"];
                        this->mstruRemoveParamter.mnStatisticFilterKmeans = (int)fs["statictis_filter_kmeans"];
                        this->mstruRemoveParamter.mfStatisticFilterThre = (float)fs["statictis_filter_thred"];
                        this->mstruRemoveParamter.mnRansacIters = (int)fs["ransac_iters"];
                        this->mstruRemoveParamter.mfRansacDistanceThre = (float)fs["ransac_distance_thre"];
                        this->mstruRemoveParamter.mbVoxelFlag = (int)fs["vexel_flag"];
                        this->mstruRemoveParamter.mbStatisticFlag = (int)fs["statistic_flag"];
                        this->mstruRemoveParamter.mfMaxHight = (float)fs["pass_filter_maxHight"];
                        this->mstruRemoveParamter.mfMinHight = (float)fs["pass_filter_minHight"];
                        this->mstruRemoveParamter.mnKmeansFactor = (int)fs["kmeans_factor"];
                        this->mstruRemoveParamter.mnStaticThredFactor = (int)fs["thred_factor"];
                        this->mstruRemoveParamter.mbGroundCloudViewerFlag = (int)fs["pcl_viewer"];
                        this->mstruRemoveParamter.mbGroundCloudViewerSize = (int)fs["cloud_size_viewer"];

                        this->mstruImageParamter.mnMedianBlurWindow = (int)fs["median_blur_window_size"];
                        this->mstruImageParamter.mnGaussBlurWindow = (int)fs["gauss_blur_window_size"];
                        this->mstruImageParamter.mbIsMaskFlag = (int)fs["is_mask_flag"];
                        this->mstruImageParamter.mbIsCloseFlag = (int)fs["is_close_flag"];
                        this->mstruImageParamter.mbIsGaussBlurFlag = (int)fs["is_gauss_blur_flag"];

                        this->mstruImageParamter.mstrSaveImagePath = (std::string)fs["save_image_path"];
                        this->mstruImageParamter.mstrMapName = (std::string)fs["map_name"];

                        this->mstruMapParamter.mfResolution = (float)fs["grid_resolution"];
                        this->mstruMapParamter.mfResolutionInverse = (float)fs["grid_resolution_inverse"];

                        this->mstruMapParamter.mnMapWidth = (int)fs["grid_map_width"];
                        this->mstruMapParamter.mnMapHight = (int)fs["grid_map_hight"];

                        this->mstruMapParamter.mstrSaveOriginGridMapFlag = (int)fs["save_origin_grid_map_flag"];
                        this->mstruMapParamter.mnMinPointsInPix = (int)fs["min_points_In_pix"];
                        this->mstruMapParamter.mnMaxPointsInPix = (int)fs["max_points_In_pix"];
                        this->mstruMapParamter.mfMinHeight = (float)fs["pass_filter_minHight"];
                        this->mstruMapParamter.mfMaxHeight = (float)fs["pass_filter_maxHight"];
                        this->mstruMapParamter.mstrSaveMapPath = (std::string)fs["save_image_path"];
                        this->mstruMapParamter.mstrMapName = (std::string)fs["map_name"];
                        this->mstruMapParamter.mfOccupiedThred = (float)fs["grid_map_occupied_thred"];
                        this->mstruMapParamter.mfFreeThred = (float)fs["grid_map_free_thred"];
                        this->mstruMapParamter.mfNegate = (int)fs["grid_map_negate"];
                        fs.release();
                }
                ~LoadParamter() {}

        public:
                std::string msParamPath;
                RemoveGroundParamter mstruRemoveParamter;
                MapGeneratorParamter mstruMapParamter;
                ImageDenoiseParamter mstruImageParamter;
        };
} //  namespace gridmap