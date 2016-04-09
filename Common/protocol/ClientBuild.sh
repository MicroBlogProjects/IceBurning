#!/bin/bash
Target="../../Client/bingdianranshao/frameworks/runtime-src/Classes/my/ProtoOut"
for i in $(ls *.proto)
do
    echo "protoc convert $i"
    protoc --cpp_out=$Target $i;
done
