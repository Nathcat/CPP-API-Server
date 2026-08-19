cmake_minimum_required(VERSION 3.28.3)

project(apiserver)

add_subdirectory(libs)

add_library(apiserver STATIC
  src/Server.cpp
  src/sqlwrapper.cpp
  src/util.cpp
)

target_include_directories(apiserver PUBLIC
  include
  libs/mysql/include
  libs/httplib
)

target_link_directories(apiserver PUBLIC
  libs/mysql/lib64
)

target_link_libraries(apiserver PUBLIC
  httplib
  mysqlcppconn
)

if (DEFINED BUILD_TESTS)
  project(logging_test)
  add_executable(logging_test src/test/logging.cpp)
  target_include_directories(logging_test PUBLIC include)
  target_link_libraries(logging_test PUBLIC apiserver)
endif()
