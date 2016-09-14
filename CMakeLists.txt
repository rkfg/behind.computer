project(bc)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
aux_source_directory(domain SRC_LIST)
add_definitions(-std=gnu++11)
set(WT_STATIC_ROOT "/opt/build/wt_static")
set(WT_SHARED_ROOT "/opt/build/wt_shared")

set(WT_HTTP_LIB wthttp)
unset(WT_LIBS)
option(FCGI "Use fcgi instead of internal http daemon" OFF)
option(STATIC "Use static linking" OFF)
if (FCGI)
  set(WT_HTTP_LIB wtfcgi)
endif()

find_package(PkgConfig)
find_package(OpenSSL)

if (STATIC)
  set(Boost_USE_STATIC_LIBS ON)
  find_package(Boost 1.60 COMPONENTS system random filesystem program_options thread regex REQUIRED)
  set(OPENSSL_USE_STATIC_LIBS TRUE)
  set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
  pkg_check_modules(GRAPHM REQUIRED GraphicsMagick>=1.3.0)
  find_package(ZLIB REQUIRED)
  find_library(MYSQL NAMES mysqlclient)
  set(AUX_STATIC_LIBRARIES ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${ZLIB_LIBRARIES} ${GRAPHM_STATIC_LIBRARIES} dl)
  set(WT_ROOT ${WT_STATIC_ROOT})
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
else(STATIC)
  find_package(Boost 1.58 COMPONENTS system random filesystem program_options regex thread REQUIRED)
  set(WT_ROOT ${WT_SHARED_ROOT})
endif(STATIC)

find_library(WT_SQL NAMES wtdbomysql HINTS ${WT_ROOT}/lib)
find_library(WT_DBO NAMES wtdbo HINTS ${WT_ROOT}/lib)
find_library(WT_HTTP NAMES ${WT_HTTP_LIB} HINTS ${WT_ROOT}/lib)
find_library(WT NAMES wt HINTS ${WT_ROOT}/lib)

list(INSERT WT_LIBRARIES 0 ${WT_SQL} ${WT_DBO} ${WT_HTTP} ${WT})

message(STATUS "STATIC = ${STATIC}
ROOT = ${WT_ROOT}
WTLIBS = ${WT_LIBRARIES}
AUX = ${AUX_STATIC_LIBRARIES}")

include_directories(${WT_ROOT}/include)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${WT_LIBRARIES} ${AUX_STATIC_LIBRARIES} ${MYSQL} ${Boost_LIBRARIES})
