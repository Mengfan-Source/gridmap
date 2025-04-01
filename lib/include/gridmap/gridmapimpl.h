/**
 * @file gridmapimpl.h
 * @brief gridmap封装类
 * @author  (deionllz@foxmail.com)
 * @version 1.0
 * @date 2023-12-01
 * @copyright Copyright (C) 2023 中国电科科技集团公司第二十一研究所
 */
#pragma once
#include <memory>
namespace gridmap {

class GridMap;
/**
 * @brief gridmap封装类
 */
class GridMapImpl {
public:
        explicit GridMapImpl (const std::string& param_path);
        ~GridMapImpl () {}
private:
        std::shared_ptr<GridMap> mptrGridMap;
};
} // namespace gridmap