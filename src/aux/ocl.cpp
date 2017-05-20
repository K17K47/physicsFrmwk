#include<vector>
/*
#include"aux/logger.hpp"
#include"aux/ocl.hpp"

int OCLcntxt::init(){
   std::string tmpString;
   Logger::instance().printMsg("OCLcntxt::init()","Initializing OpenCL...");

   std::vector<cl::Platform> platforms;
   if (cl::Platform::get(&platforms)!=CL_SUCCESS){
      Logger::instance().printMsg("OCLcntxt::init()","No OpenCL platforms!");
      return 1;
   }

   Logger::instance().printMsg("OCLcntxt::init()","OpenCL Platforms found:");
   for(std::vector<cl::Platform>::iterator it = platforms.begin(); it !=platforms.end(); it++){
      tmpString=tmpString + " \n" + it->getInfo<CL_PLATFORM_NAME>();
   }
   Logger::instance().printMsg("OCLcntxt::init()",tmpString);

   OCLcntxt::def_platform=platforms[0];
   Logger::instance().printMsg("OCLcntxt::init()","Using OpenCL platform " + OCLcntxt::def_platform.getInfo<CL_PLATFORM_NAME>());

   std::vector<cl::Device> devices;
   if(def_platform.getDevices(CL_DEVICE_TYPE_ALL,&devices)!=CL_SUCCESS){
      Logger::instance().printMsg("OCLcntxt::init()","No OpenCL devices!");
      return 1;
   }

   tmpString.clear();
   Logger::instance().printMsg("OCLcntxt::init()","OpenCL Devices found:");
   for(std::vector<cl::Device>::iterator it = devices.begin(); it !=devices.end(); it++){
      tmpString=tmpString + "\n" + it->getInfo<CL_DEVICE_NAME>();
   }
   Logger::instance().printMsg("OCLcntxt::init()",tmpString);

   OCLcntxt::def_device=devices[0];
   Logger::instance().printMsg("OCLcntxt::init()","Using OpenCL device " + OCLcntxt::def_device.getInfo<CL_DEVICE_NAME>());

   return 0;
}
*/
