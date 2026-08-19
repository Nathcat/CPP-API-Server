#ifndef _NATHCAT_LOGGING
#define _NATHCAT_LOGGING

#include <iostream>
#include <ostream>
#include <string>
#include <thread>
namespace nathcat {
namespace logging {
class Logger {
public:
  const std::string name;

  Logger(std::string name) : name(name) {};

  void operator<<(std::string msg) {
    std::cout << name << " - (" << std::this_thread::get_id() << ") $ " << msg
              << std::endl;
  }
};
} // namespace logging
} // namespace nathcat

#endif
