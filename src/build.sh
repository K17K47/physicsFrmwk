#!/bin/sh

g++ -c particles/particle.cpp -o build/particles/particle.o -I./ -fPIC -std=c++11
g++ -c particles/pMngr.cpp -o build/particles/pMngr.o -I./ -fPIC -std=c++11
g++ -c particles/pWorld.cpp -o build/particles/pWorld.o -I./ -fPIC -std=c++11
g++ -c particles/pForceGens.cpp -o build/particles/pForceGens.o -I./ -fPIC -std=c++11
g++ -c particles/forceGenerators.cpp -o build/particles/forceGenerators.o -I./ -fPIC -std=c++11
g++ -shared -pthread -o build/libPhysics.so build/particles/particle.o build/particles/pMngr.o build/particles/pWorld.o build/particles/pForceGens.o build/particles/forceGenerators.o
