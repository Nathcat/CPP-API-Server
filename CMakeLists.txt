cmake_minimum_required(VERSION 3.31.11)

project(apiserver)

add_subdirectory(libs)

add_library(apiserver SHARED
  src/Server.cpp
  src/sqlwrapper.cpp
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
