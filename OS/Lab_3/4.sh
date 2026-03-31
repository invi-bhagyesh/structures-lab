#!/bin/bash

echo "Enter Basic Salary:"
read basic

ta=$(echo "$basic * 0.10" | bc)
gs=$(echo "$basic + $ta + $ta" | bc)

echo "Gross Salary = $gs"