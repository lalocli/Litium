#!/bin/sh

gcc -fPIC -c -O2 litium/addresses.c litium/hooks.c litium/litium.c subhook/subhook.c
g++ -fPIC -c -std=c++20 litium/api/*.cpp
g++ -fPIC -shared -s -o litium.so *.o
rm *.o
