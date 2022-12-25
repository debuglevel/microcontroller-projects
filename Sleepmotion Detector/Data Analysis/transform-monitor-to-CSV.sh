#!/bin/bash

echo "Transforming monitor output to CSV..." 1>&2

if [[ "$1" == "RAWv1" ]]; then
    echo "time,AccZ"
    cat | grep -v '^--- ' | awk '{ gsub("Zraw:","",$3); print $1 "," $3 }'
fi

if [[ "$1" == "RAWv2" ]]; then
    echo "time,AccX,AccY,AccZ,GyroX,GyroY,GyroZ"
    cat | grep -v '^--- ' | awk '{ gsub("AccX:","",$3);gsub("AccY:","",$4);gsub("AccZ:","",$5);gsub("GyroX:","",$6);gsub("GyroY:","",$7);gsub("GyroZ:","",$8); print $1 "," $3 "," $4 "," $5 "," $6 "," $7 "," $8 }'
fi

if [[ "$1" == "CSVv3" ]]; then
    echo "time,AccX,AccY,AccZ,GyroX,GyroY,GyroZ"
    cat | grep -v '^--- ' | sed 's/ > /,/'
fi

