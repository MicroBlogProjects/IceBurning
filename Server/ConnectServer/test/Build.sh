#!/bin/bash
Target="./"
sed -i '/option optimize_for = LITE_RUNTIME;/d' *.proto
for i in $(ls *.proto)
do
    echo "protoc convert $i"
    protoc --cpp_out=$Target $i;
done
sed -i '/package GameJayo/a\option optimize_for = LITE_RUNTIME;' *.proto

cd $Target
rename .pb.cc .cpp *
rename .pb.h .h *
sed -i 's/\.pb.h\>/.h/g' *.cpp
sed -i 's/\.pb.h\>/.h/g' *.h

cd ../..
ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .

cd include/proto_out && make -j 4
