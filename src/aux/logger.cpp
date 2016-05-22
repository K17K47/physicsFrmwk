#include<stddef.h>
#include<iostream>

#include"aux/logger.hpp"

Logger& Logger::instance(){
   static Logger _instance;
   return _instance;
}

void Logger::printMsg(std::string funcID,std::string msg){
   std::chrono::duration<double> t=std::chrono::steady_clock::now()-start;
   std::cout<<"["<<t.count()<<"] "<<funcID<<": "<<msg<<"\n";
}
