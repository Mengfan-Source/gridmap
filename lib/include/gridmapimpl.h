
#pragma once
#include <memory>
namespace gridmap {

class GridMap;
class GridMapImpl {
public:
        explicit GridMapImpl (const std::string& param_path);
        ~GridMapImpl () {}
private:
        std::shared_ptr<GridMap> mptrGridMap;
};
} // namespace gridmap