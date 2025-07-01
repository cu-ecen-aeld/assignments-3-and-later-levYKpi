#!/bin/sh

writefile=$1
writestr="$@"
writestr="${writestr#* }"

if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "writefile or writestr was not specified."
    exit 1
fi

if [ "$(echo "$writefile" | cut -c1)" != "/" ]; then
    echo "writefile is not a full path to a file."
    exit 1
fi

mkdir -p $(dirname "$writefile")
echo $writestr > $writefile
ret_value=$?
if [ $ret_value -ne 0 ]; then
    echo "writer failed."
    exit 1
fi
