#include "gridmapimpl.h"
#include<stdlib.h>
#include <memory>

using GridMapImpl = gridmap::GridMapImpl;

int main (int argv, char** argc) {
        std::string param_path = "./config/param.yaml";
        std::shared_ptr<GridMapImpl> gridmapImpl = std::make_shared<GridMapImpl> (param_path);
        // std::exit (0);
        return 0;
}