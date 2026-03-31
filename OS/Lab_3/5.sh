#!/bin/bash

echo "Enter file extension (e.g. .txt):"
read ext

echo "Enter destination folder:"
read dest

mkdir -p "$dest"

for file in *"$ext"; do
    if [ -f "$file" ]; then
        cp "$file" "$dest/"
    fi
done

echo "Files copied successfully."