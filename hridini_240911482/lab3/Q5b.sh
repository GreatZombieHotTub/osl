#!/bin/bash

for file in *
do
    if [ -f "$file" ]; then
        sed -i 's/^ex:/Example:/; s/\. Example:/\. Example:/g' "$file"
    fi
done

