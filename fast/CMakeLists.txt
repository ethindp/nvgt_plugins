cmake_minimum_required(VERSION 3.14...3.22)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")
# ---- Project ----
project(
  fast
  VERSION 0.1.0
  LANGUAGES CXX
)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add source files ----
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----
add_library(${PROJECT_NAME} SHARED ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DSLEEF_STATIC_LIBS=1)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Dependencies (from vcpkg)
find_package(scn CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE scn::scn)
find_package(Threads REQUIRED)
find_package(llfio CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC llfio::sl)
find_package(Poco REQUIRED COMPONENTS Foundation)
target_link_libraries(${PROJECT_NAME} PRIVATE Poco::Foundation)
# download CPM.cmake
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.3/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
CPMAddPackage(
  NAME sleef
  VERSION 3.6.1
  GITHUB_REPOSITORY "shibatch/sleef"
  GIT_TAG 3.6.1
  OPTIONS
    "SLEEF_BUILD_SHARED_LIBS OFF"
    "SLEEF_BUILD_STATIC_TEST_BINS OFF"
    "SLEEF_ENABLE_LTO ON"
    "SLEEF_BUILD_LIBM ON"
    "SLEEF_BUILD_DFT ON"
    "SLEEF_BUILD_QUAD ON"
    "SLEEF_BUILD_GNUABI_LIBS ON"
    "SLEEF_BUILD_SCALAR_LIB ON"
    "SLEEF_BUILD_TESTS OFF"
    "SLEEF_ENABLE_CXX ON"
)
target_include_directories(${PROJECT_NAME} PRIVATE ${sleef_BINARY_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sleef sleefdft sleefquad)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)
