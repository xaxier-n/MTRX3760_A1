#!/bin/bash
set -e

OUT=robot.out

g++ -std=c++17 -Wall -Wextra -g *.cpp -o "$OUT"

echo "Built $OUT"
