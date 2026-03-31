#!/bin/bash

for file in *; do
    if [ -f "$file" ]; then
        sed -i 's/^ex:/Example:/g; s/\. Example:/\. Example:/g' "$file"
    fi
done

echo "Replacement done."