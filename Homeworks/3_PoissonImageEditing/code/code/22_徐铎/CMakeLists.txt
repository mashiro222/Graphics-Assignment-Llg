# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# 设定项目
project(PoissonImageEditing VERSION 1.0)
message(STATUS "[Project] ${PROJECT_NAME}")

# 修改默认的安装路径前缀
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH "install prefix" FORCE)
endif()

# 在 Debug 模式下自动对 dll 和 lib 文件名后边加 d，但 exe 仍然需要手动设置
set(CMAKE_DEBUG_POSTFIX d)

# 确定 C++ 版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
 
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

# 将生成的 exe, dll, lib 等放置在 bin, lib 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")

# 开启 VS 的文件夹功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)
FetchContent_Declare(
  UCMake
  GIT_REPOSITORY https://github.com/Ubpa/UCMake
  GIT_TAG        d133da1
)
FetchContent_MakeAvailable(UCMake)

Ubpa_QtInit(COMPONENTS Core Gui Widgets)

message(STATUS "----------")
find_package(OpenCV REQUIRED)

message(STATUS "----------")
# https://eigen.tuxfamily.org/dox/TopicCMakeGuide.html
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/Eigen3Config.cmake.in
# https://gitlab.com/libeigen/eigen/-/blob/master/cmake/UseEigen3.cmake
find_package(Eigen3 3.3 NO_MODULE REQUIRED)
if(TARGET Eigen3::Eigen)
	message(STATUS "EIGEN3_FOUND: ${EIGEN3_FOUND}")
	message(STATUS "EIGEN3_USE_FILE: ${EIGEN3_USE_FILE}")
	message(STATUS "EIGEN3_DEFINITIONS: ${EIGEN3_DEFINITIONS}")
	message(STATUS "EIGEN3_INCLUDE_DIR: ${EIGEN3_INCLUDE_DIR}")
	message(STATUS "EIGEN3_INCLUDE_DIRS: ${EIGEN3_INCLUDE_DIRS}")
	message(STATUS "EIGEN3_ROOT_DIR: ${EIGEN3_ROOT_DIR}")
	message(STATUS "EIGEN3_VERSION_STRING: ${EIGEN3_VERSION_STRING}")
	include(${EIGEN3_USE_FILE})
else()
	message(WARNING "find_package(Eigen3 3.3 NO_MODULE) failed, so use include/_deps/Eigen/")
	if(NOT EXISTS "${PROJECT_SOURCE_DIR}/include/_deps/Eigen")
		message(FATAL_ERROR "not found Eigen/ in ${PROJECT_SOURCE_DIR}/include/_deps/")
	endif()
endif()

include_directories (
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/_deps
	${utemplate_SOURCE_DIR}/include
	${OpenCV_DIR}/include
	# $ENV{XXX_INCLUDE_PATH}
	# ...
)
link_directories (
	${PROJECT_SOURCE_DIR}/lib
	${OpenCV_DIR}/x64/vc15/lib
	# $ENV{XXX_LIB_PATH}
	# ...
)

Ubpa_AddSubDirsRec(src)
