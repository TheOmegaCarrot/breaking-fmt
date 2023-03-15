cmake_minimum_required(VERSION 3.16.0)

project(breaking_fmt LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

option(USE_MY_FORK "Use my fork of fmtlib" NO)

if (USE_MY_FORK)
  set(FMT_VERSION "theomegacarrot/fmt-valueless-variant")
  set(COMMIT_HASH "d671bf524ea25f7f0311bd98e4aaefa10b002a07")
else()
  set(FMT_VERSION "fmtlib/fmt")
  set(COMMIT_HASH "7f882918eba6430a0509b5e8547de21611264c5c")
endif()
FetchContent_Declare(fmt
  GIT_REPOSITORY https://www.github.com/${FMT_VERSION}
  GIT_TAG ${COMMIT_HASH}
  )

FetchContent_MakeAvailable(fmt)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
