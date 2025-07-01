#!/bin/sh

filesdir=$1
searchstr=$2

if [ -z "$filesdir" ] || [ -z "$searchstr" ]; then
    echo "filesdir or searchstr was not specified."
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "filesdir is not a directory."
    exit 1
fi

file_count=$(find "$filesdir" -type f | wc -l)
found_files_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $file_count and the number of matching lines are $found_files_count"
