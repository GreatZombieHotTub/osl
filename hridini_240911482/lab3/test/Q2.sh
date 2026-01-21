#!/bin/sh
echo "enter folder name:"
read folder
echo "enter search pattern:"
read pattern
grep -l "$pattern" "$folder"/*
