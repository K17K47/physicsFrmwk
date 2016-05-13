#!/bin/sh

g++ -Wall ./solarSystem.cpp -o ./solarSystem -I../../ -std=c++11 -fPIC -L../../build -lPhysics
