cmake_minimum_required(VERSION 3.16.0)

project(breaking_fmt LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

option(USE_MY_FORK "Use my fork of fmtlib" NO)

if (USE_MY_FORK)
  set(FMT_VERSION "theomegacarrot/fmt-valueless-variant")
else()
  set(FMT_VERSION "fmtlib/fmt")
endif()
FetchContent_Declare(fmt
  GIT_REPOSITORY https://www.github.com/${FMT_VERSION}
  GIT_TAG origin/master
  )

FetchContent_MakeAvailable(fmt)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
