#!/bin/sh

gcc -fPIC -c subhook/subhook.c
g++ -fPIC -c -fno-inline -std=c++20 litium/api/*.cpp
gcc -fPIC -c -O2 litium/addresses.c litium/hooks.c litium/patches.c litium/litium.c
g++ -fPIC -shared -s -o litium.so *.o
rm *.o
