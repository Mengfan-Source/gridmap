
#include "gridmapimpl.h"
#include "gridmap.h"
namespace gridmap {
GridMapImpl::GridMapImpl (const std::string& param_path) {
        mptrGridMap = std::make_shared<GridMap> (param_path);
}
} // namespace gridmap
