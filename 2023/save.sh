#!/bin/bash

day=$(date +%d)
part=${1:-a}
qwe=$(ls -t qwe.* | head -n 1)
ext="${qwe##*.}"

while [[ -f "${day}_$part.$ext" ]]; do
	part=$(echo $part | tr '[a-y]z' '[b-z]a')
done

name="${day}_$part.$ext"
cp $qwe $name
echo $name
