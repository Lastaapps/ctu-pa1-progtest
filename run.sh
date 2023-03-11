#!/bin/bash

clear
cat < sample/CZE/$1_in.txt
echo

cat < sample/CZE/$1_out.txt
echo

#carmain < sample/CZE/$1_in.txt
~/bin/compile_and_run.sh main < sample/CZE/$1_in.txt


