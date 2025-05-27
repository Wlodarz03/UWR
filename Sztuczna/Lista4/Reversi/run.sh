#!/bin/bash

g++ -std=c++17 -O2 -o agent test2.cpp

if [ $? -ne 0 ]; then
  echo "❌ Kompilacja nieudana"
  exit 1
fi

echo "✅ Kompilacja OK"
# echo "Uruchamianie..."

# ./agent