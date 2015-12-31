
# compile bamtools
#mkdir third_party/local/bamtools
cd third_party/src/bamtools
mkdir build
cd build
cmake ..
make

cd ../lib
if [ $(uname) == "Linux" ]; then
	echo "Linux"
	ln -s libbamtools.so.2.4.0 libbamtools.so
fi

