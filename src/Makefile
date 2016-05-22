.PHONY: all, clean

LIBNAME := libphysics.so

CPPFLAGS := -I./
CFLAGS :=
CXXFLAGS += -fPIC -std=c++11
LDFLAGS += -shared -pthread

SOURCES = $(wildcard *.cpp) \
          $(wildcard particles/*.cpp) \
          $(wildcard aux/*.cpp)
HEADERS = $(wildcard %.hpp) \
          $(wildcard particles/%.hpp) \
          $(wildcard aux/%.hpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all : $(LIBNAME)

$(LIBNAME) : $(OBJECTS) Makefile
	$(CXX) -o $@ $(LDFLAGS) $(OBJECTS)

%.o: %.cpp $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean:
	@echo "Clean."
	-rm -f $(OBJECTS) $(LIBNAME)

