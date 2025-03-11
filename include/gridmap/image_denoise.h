
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

namespace gridmap {

/**
 * @brief 图像处理相关参数结构体
 */
typedef struct ImageDenoiseParam {
        int mnMedianBlurWindow;   //  中值滤波窗口大小（去除椒盐噪声）
        bool mbIsMaskFlag;   // 是否使用掩膜操作标志位
        bool mbIsCloseFlag;   // 是否使用闭操作标志位
        bool mbIsGaussBlurFlag;   // 是否使用高斯滤波操作标志位
        int mnGaussBlurWindow;   // 中高斯滤波窗口大小（去除随机噪声）
        std::string mstrSaveImagePath;  // 保存GridMap路径
        std::string mstrMapName;  //   栅格地图名字
}ImageDenoiseParamter;


class ImageDenoise {
public:
        // 相关参数
        ImageDenoiseParamter mstruParamter;
        // 构造函数，加载参数
        ImageDenoise (const ImageDenoiseParamter& param);

        // 析构函数
        ~ImageDenoise () {}

        // 掩膜操作，mat:输入；dst:输出
        void mask (const cv::Mat& mat, cv::Mat& dst);

        // 均值滤波操作，mat:输入；dst:输出
        void blur (const cv::Mat& mat, cv::Mat& dst);

        // 高斯滤波操作，mat:输入；dst:输出
        void gaussianBlur (const cv::Mat& mat, cv::Mat& dst);

        // 中值滤波操作，去除椒盐噪声
        void medianBlur (const cv::Mat& mat, cv::Mat& dst);

        // 膨胀操作
        void dilate (const cv::Mat& mat, cv::Mat& dst);

        // 闭操作
        void close (const cv::Mat& mat, cv::Mat& dst);

        // gridmap 去除噪声函数； src:输入图像
        void HandleGridImage (const cv::Mat& src);
};
} //  namespace gridmap