#!/bin/bash

echo "Enter file extension (example: .text):"
read ext

echo "Enter destination folder name:"
read folder

mkdir -p "$folder"
cp *"$ext" "$folder" 2>/dev/null

echo "Files copied successfully"

