
#include "gridmap.h"

namespace gridmap {

GridMap::GridMap (const std::string& param_path) {
        mptrLoadParamService = std::make_shared<LoadParamter> (param_path);
        //去除地面点(用的是pcl库中的RANSAC平面拟合)
        mptrRemoveGround = std::make_shared<RemoveGroundCloud> (mptrLoadParamService->mstruRemoveParamter);

        mptrMapGenerator = std::make_shared<MapGenerator> (mptrLoadParamService->mstruMapParamter);
        //传入的是去除地面后的点云
        mptrMapGenerator->Generate (*mptrRemoveGround->mpNoGroundCloud);
        mptrMapGenerator->SaveGridMap ();
        mptrImageDenoise = std::make_shared<ImageDenoise> (mptrLoadParamService->mstruImageParamter);
        mptrImageDenoise->HandleGridImage (mptrMapGenerator->mmgridMap);
}
} // namespace gridmap