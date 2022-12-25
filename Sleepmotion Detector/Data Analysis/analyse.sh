#!/bin/bash

echo "Analysing '$1' in '$2' format..." 1>&2
cat $1 | ./transform-monitor-to-CSV.sh $2 | ./analyse.R
