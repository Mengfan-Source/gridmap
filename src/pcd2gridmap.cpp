

#include "gridmap/pcd2gridmap.h"

namespace gridmap {
MapGenerator::MapGenerator (const MapGeneratorParamter& param) {
        this->mstruParam = param;
}

void MapGenerator::Generate (const pcl::PointCloud<pcl::PointXYZI>& cloud)
{
        double x_min = std::numeric_limits<double>::max();
        double x_max = std::numeric_limits<double>::lowest();
        double y_min = std::numeric_limits<double>::max();
        double y_max = std::numeric_limits<double>::lowest();

        for (const auto& point : cloud)
        {
                if (point.z < this->mstruParam.mfMinHeight || point.z > this->mstruParam.mfMaxHeight)
                        continue;

                x_min = std::min(x_min, (double)point.x);
                x_max = std::max(x_max, (double)point.x);
                y_min = std::min(y_min, (double)point.y);
                y_max = std::max(y_max, (double)point.y);
        }

        x_min -= 1.0;
        x_max += 1.0;
        y_min -= 1.0;
        y_max += 1.0;
        this->mstruParam.x_min_pcl2 = x_min;
        this->mstruParam.y_min_pcl2 = y_min;
		// std::cerr << "x_min = " << x_min << ", x_max = " << x_max << ", y_min = " << y_min << ", y_max = " << y_max << std::endl;

        int width  = static_cast<int>((x_max - x_min) * this->mstruParam.mfResolutionInverse);
        int height = static_cast<int>((y_max - y_min) * this->mstruParam.mfResolutionInverse);

        mmgridMap = cv::Mat(height, width, CV_8UC1, cv::Scalar::all(0));

        double center_x = (x_min + x_max) * 0.5;
        double center_y = (y_min + y_max) * 0.5;

        for (const auto& point : cloud)
        {
                if (point.z < this->mstruParam.mfMinHeight || point.z > this->mstruParam.mfMaxHeight)
                        continue;

                int x = static_cast<int>((point.x - center_x) * this->mstruParam.mfResolutionInverse + width  / 2);
                int y = static_cast<int>((center_y - point.y) * this->mstruParam.mfResolutionInverse + height / 2);

                if (x < 0 || x >= width || y < 0 || y >= height)
                        continue;

                mmgridMap.at<uchar>(y, x)++;
        }

        mmgridMap -= this->mstruParam.mnMinPointsInPix;
        mmgridMap.convertTo(mmgridMap, CV_8UC1,
                -255.0 / (this->mstruParam.mnMaxPointsInPix - this->mstruParam.mnMinPointsInPix), 255);
        
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
                << this->mstruParam.x_min_pcl2 << ", "
                << this->mstruParam.y_min_pcl2 << ", 0.0]" << std::endl;

        ofs << "occupied_thresh: " << this->mstruParam.mfOccupiedThred << std::endl;
        ofs << "free_thresh: " << this->mstruParam.mfFreeThred << std::endl;
        ofs << "negate: " << this->mstruParam.mfNegate << std::endl;

}
} // namespace  gridmap