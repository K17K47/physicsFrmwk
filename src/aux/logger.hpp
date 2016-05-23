#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include<string>
#include<chrono>

class Logger{
   public:
      static Logger& instance();
      void printMsg(std::string funcID, std::string msg);

      std::chrono::time_point<std::chrono::steady_clock> start=std::chrono::steady_clock::now();

   private:
      Logger(){};

   public:
      Logger(Logger const&) = delete;
      void operator=(Logger const&) = delete;
};

#endif
