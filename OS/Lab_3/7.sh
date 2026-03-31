#!/bin/bash

echo "Enter file name:"
read file

sed -i '2~2d' "$file"

echo "Even lines deleted."