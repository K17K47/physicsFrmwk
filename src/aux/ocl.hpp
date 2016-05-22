#ifndef OCL_HPP_
#define OCL_HPP_

#define CL_VERSION_1_2

#include<CL/cl2.hpp>

class OCLcntxt{
   private:
      cl::Platform def_platform;
      cl::Device def_device;
      cl::Context context;
   public:
      int init();
};

#endif
