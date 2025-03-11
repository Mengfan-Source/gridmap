

#include "gridmap/image_denoise.h"
namespace gridmap {

ImageDenoise::ImageDenoise (const ImageDenoiseParamter& param) {
        this->mstruParamter = param;
}
void ImageDenoise::mask (const cv::Mat& mat, cv::Mat& dst) {
        cv::Mat kernal =
                (cv::Mat_<char> (3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
        cv::filter2D (mat, dst, mat.depth (), kernal, cv::Point (-1, -1));
}

void  ImageDenoise::blur (const cv::Mat& mat, cv::Mat& dst) {
        cv::blur (mat, dst, cv::Size (5, 5), cv::Point (-1, -1));
}

void  ImageDenoise::gaussianBlur (const cv::Mat& mat, cv::Mat& dst) {
        cv::GaussianBlur (mat, dst, cv::Size (this->mstruParamter.mnGaussBlurWindow, this->mstruParamter.mnGaussBlurWindow), 0, 0);
}
// 中值滤波，去除椒盐噪声
void  ImageDenoise::medianBlur (const cv::Mat& mat, cv::Mat& dst) {
        cv::medianBlur (mat, dst, this->mstruParamter.mnMedianBlurWindow);
}

// 膨胀操作
void  ImageDenoise::dilate (const cv::Mat& mat, cv::Mat& dst) {
        gaussianBlur (mat, dst);
        cv::Mat tmp = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (5, 5),
                                                cv::Point (-1, -1));
        cv::dilate (dst, dst, tmp, cv::Point (-1, -1), 1);
}

// 闭操作
void  ImageDenoise::close (const cv::Mat& mat, cv::Mat& dst) {
        gaussianBlur (mat, dst);
        cv::Mat tmp = cv::getStructuringElement (cv::MORPH_RECT, cv::Size (3, 3),
                                                cv::Point (-1, -1));
        cv::morphologyEx (dst, dst, cv::MORPH_CLOSE, tmp, cv::Point (-1, -1), 1);
}

void  ImageDenoise::HandleGridImage (const cv::Mat& src) {
        cv::Mat medBlur, gaussblur, result;
        if (!src.data) {
                std::cout << "laod image false" << std::endl;
                return;
        }
        result = cv::Mat (src.rows, src.cols, src.type ());

        medianBlur (src, medBlur);
        if (this->mstruParamter.mbIsGaussBlurFlag) {
                gaussianBlur (medBlur, gaussblur);
                if (this->mstruParamter.mbIsMaskFlag && this->mstruParamter.mbIsCloseFlag) {
                        mask (gaussblur, medBlur);
                        close (medBlur, result);
                }
                else if (!this->mstruParamter.mbIsMaskFlag && this->mstruParamter.mbIsCloseFlag) {
                        close (gaussblur, result);
                }
                else if (this->mstruParamter.mbIsMaskFlag && !this->mstruParamter.mbIsCloseFlag) {
                        mask (gaussblur, result);
                }
                else {
                        std::cout << "Result is GaussBlur image" << std::endl;
                        gaussblur.copyTo (result);
                }
        }
        else if (this->mstruParamter.mbIsMaskFlag && this->mstruParamter.mbIsCloseFlag) {
                mask (medBlur, medBlur);
                close (medBlur, result);
        }
        else if (!this->mstruParamter.mbIsMaskFlag && this->mstruParamter.mbIsCloseFlag) {
                close (medBlur, result);
        }
        else if (this->mstruParamter.mbIsMaskFlag && !this->mstruParamter.mbIsCloseFlag) {
                mask (medBlur, result);
        }
        else {
                medBlur.copyTo (result);
        }
        cv::imwrite (this->mstruParamter.mstrSaveImagePath + "/" + this->mstruParamter.mstrMapName + ".pgm", result);
        std::cout << "Successfully get grid map." << std::endl;
}
} // namespace  gridmap