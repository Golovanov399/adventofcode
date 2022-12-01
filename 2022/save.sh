#!/bin/bash

day=$(date +%d)
part=${1:-a}
qwe=$(ls -t qwe* | head -n 1)
ext="${qwe##*.}"

name="${day}_$part.$ext"
cp $qwe $name
echo $name
