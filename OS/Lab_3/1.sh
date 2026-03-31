#!/bin/bash

echo "Enter File Name:"
read fname
if [ -d "$fname" ]; then
    echo "Directory you have found"
elif [ -f "$fname" ]; then
    echo "Stumbled upon a file"
else 
    echo "Whoosh! What are you looking for ? There is nothing here"
fi