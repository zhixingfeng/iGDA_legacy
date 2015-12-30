mkdir third_party/local/

# compile bamtools
#mkdir third_party/local/bamtools
cd third_party/src/bamtools
mkdir build
cd build
cmake ..
make
#cd ..

#mv build ../../local/bamtools
#mv bin ../../local/bamtools
#mv include ../../local/bamtools
#mv lib ../../local/bamtools


