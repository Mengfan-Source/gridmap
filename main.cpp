#include  "gridmap/load_paramter.h"
#include<stdlib.h>

using LoadParamter = gridmap::LoadParamter;
using RemoveGroundCloud = gridmap::RemoveGroundCloud;
using MapGenerator = gridmap::MapGenerator;
using ImageDenoise = gridmap::ImageDenoise;

int main (int argv, char** argc) {
        std::string param_path = "./config/param.yaml";
        LoadParamter param (param_path);
        RemoveGroundCloud removeGround (param.mstruRemoveParamter);
        MapGenerator mapGenerator (param.mstruMapParamter);

        mapGenerator.Generate (*removeGround.mpNoGroundCloud);
        mapGenerator.SaveGridMap ();

        ImageDenoise imageDenoise (param.mstruImageParamter);
        imageDenoise.HandleGridImage (mapGenerator.mmgridMap);


        std::exit (0);
        return 0;
}