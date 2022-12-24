#!/bin/bash

echo "Analysing '$1'..." 1>&2
cat $1 | ./transform-monitor-to-CSV.sh | ./analyse.R
