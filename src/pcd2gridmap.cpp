

#include "gridmap/pcd2gridmap.h"

namespace gridmap {
MapGenerator::MapGenerator (const MapGeneratorParamter& param) {
        this->mstruParam = param;
}

void MapGenerator::Generate (const pcl::PointCloud<pcl::PointXYZI>& cloud)
{
        //长宽像素点个数，图像大小为mnMapHight x mnMapWidth，类型为CV_8UC1（单通道8位无符号整数），并初始化为全零。
        mmgridMap = cv::Mat (this->mstruParam.mnMapHight, this->mstruParam.mnMapWidth, CV_8UC1, cv::Scalar::all (0));

        for (const auto& point : cloud)
        {
                if (point.z < this->mstruParam.mfMinHeight || point.z > this->mstruParam.mfMaxHeight)
                {
                        continue;
                }
                int x = static_cast<int>(point.x * this->mstruParam.mfResolutionInverse + this->mstruParam.mnMapWidth / 2);
                int y = static_cast<int>(-point.y * this->mstruParam.mfResolutionInverse + this->mstruParam.mnMapHight / 2);
                if (x < 0 || x >= this->mstruParam.mnMapWidth || y < 0 || y >= this->mstruParam.mnMapHight)
                {
                        continue;
                }
//对应的图像像素值自增，用于记录落在该栅格内的点数
                mmgridMap.at<uchar> (y, x)++;
        }
//将每个像素的计数值减去一个最小阈值mnMinPointsInPix，这可以用于去除栅格中的一些低值噪声。
        mmgridMap -= this->mstruParam.mnMinPointsInPix;
        mmgridMap.convertTo (mmgridMap, CV_8UC1, -255.0 / (this->mstruParam.mnMaxPointsInPix - this->mstruParam.mnMinPointsInPix), 255);
}
void MapGenerator::SaveGridMap () {

        if (!boost::filesystem::exists (this->mstruParam.mstrSaveMapPath))
        {
                boost::filesystem::create_directories (this->mstruParam.mstrSaveMapPath);
        }
        if (this->mstruParam.mstrSaveOriginGridMapFlag) {
                std::string map_path = this->mstruParam.mstrSaveMapPath + "/" + this->mstruParam.mstrMapName + "_origin.pgm";
                cv::imwrite (map_path, mmgridMap);
        }
        std::string yaml_path = this->mstruParam.mstrSaveMapPath + "/" + this->mstruParam.mstrMapName + ".yaml";
        std::ofstream ofs (yaml_path);
        ofs << "image: " << this->mstruParam.mstrMapName << ".pgm" << std::endl;
        ofs << "resolution: " << this->mstruParam.mfResolution << std::endl;
        ofs << "origin: ["
                << -this->mstruParam.mfResolution * this->mstruParam.mnMapWidth / 2 << ", "
                << -this->mstruParam.mfResolution * this->mstruParam.mnMapHight / 2 << ", 0.0]" << std::endl;

        ofs << "occupied_thresh: " << this->mstruParam.mfOccupiedThred << std::endl;
        ofs << "free_thresh: " << this->mstruParam.mfFreeThred << std::endl;
        ofs << "negate: " << this->mstruParam.mfNegate << std::endl;

}
} // namespace  gridmap