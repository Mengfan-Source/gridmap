#pragma once
#include <memory>
#include "gridmap/load_paramter.h"

namespace gridmap {
class ImageDenoise;
class LoadParamter;
class MapGenerator;
class RemoveGroundCloud;

/**
 * @brief pcd转gridmap的管理类，用来统筹地面分割、pcd转gridmap、图像处理三部分功能
 */
class GridMap {
public:
        /**
         * @brief Construct a new Grid Map object
         * @param  param_path       yaml参数配置文件路径
         */
        explicit GridMap (const std::string& param_path);
        /**
         * @brief Destroy the Grid Map object
         */
        ~GridMap () {}
private:
        std::shared_ptr<LoadParamter> mptrLoadParamService;
        std::shared_ptr<RemoveGroundCloud> mptrRemoveGround;
        std::shared_ptr<MapGenerator> mptrMapGenerator;
        std::shared_ptr<ImageDenoise> mptrImageDenoise;//图像去噪
};
} // namespace gridmap