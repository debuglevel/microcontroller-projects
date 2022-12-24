#!/bin/bash

echo "Transforming monitor output to CSV..." 1>&2
echo "time,ZAccel"
cat | grep -v '^--- ' | awk '{ gsub("Zraw:","",$3); print $1 "," $3 }'
