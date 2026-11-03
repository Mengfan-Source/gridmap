cp cmakelists/CMakeLists.pre CMakeLists.txt 
rm -rf ./build
mkdir build
cd build
cmake ..
make -j7
make install
cd ../
cp cmakelists/CMakeLists.back CMakeLists.txt 
rm -rf ./build
mkdir build
cd build
cmake ..
make 

