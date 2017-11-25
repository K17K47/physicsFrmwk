lib_LTLIBRARIES = libphysics.la
libphysics_la_SOURCES = aux/logger.cpp aux/ocl.cpp particles/forceGenerators.cpp particles/particle.cpp particles/pForceGens.cpp particles/pMngr.cpp particles/pWorld.cpp
libphysics_la_CPPFLAGS = -I./
libphysics_la_CXXFLAGS = -fPIC -std=c++11
libphysics_la_LDFLAGS = -pthread

bin_PROGRAMS = massSpring solarSystem

massSpring_SOURCES = samples/massSpring/massSpring.cpp
massSpring_CPPFLAGS = -I./
massSpring_CXXFLAGS = -fPIC -std=c++11

solarSystem_SOURCES = samples/solarSystem/solarSystem.cpp
solarSystem_CPPFLAGS = -I./
solarSystem_CXXFLAGS = -fPIC -std=c++11

massSpring_LDADD = libphysics.la
solarSystem_LDADD = libphysics.la
