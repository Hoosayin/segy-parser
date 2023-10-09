#!/bin/sh

echo '1. Creating build directory...'
mkdir build

echo '2. Copying sample SEGY files...'
cp velocity.segy build/

echo '3. Running cmake configuration...'
cmake -S . -B build
