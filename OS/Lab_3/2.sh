#!/bin/bash

echo "Enter the file path if u have it"
read folder

echo "patter u have in mind?"
read pattern

for file in "$folder"/*; do
    if [ -f "file" ]; then
        if grep -q "$pattern" "$file"; then
            basename "$file"
        fi
    fi
done