# Minimum required version of cmake
cmake_minimum_required(VERSION 3.5)

# ===

set(ProjectName "XCRG-Test")
set(ProjectVersion "1.0")
set(ExecutableName "xcrg-test")

set(CMAKE_CXX_STANDARD 20)
set(CMakeFlags "")
set(CMakeDebugFlags "-g")

# ===

project("${ProjectName}" VERSION "${ProjectVersion}" LANGUAGES CXX)

# Project root directory and the source directory src/
set(ProjectDir "${PROJECT_SOURCE_DIR}") # PROJECT_SOURCE_DIR is set by calls to project()
set(SourceDir "${ProjectDir}/src")

# ==
# CMake Subdirectories

add_subdirectory(libxcrg)

# ===

set(Libraries xcrg)

set(IncludeDirs "${ProjectDir}" "${SourceDir}" "${ProjectDir}/libxcrg" "${ProjectDir}/libxcrg/wide-integer/")

set(SourceFiles
	"${SourceDir}/Main.cpp"
)

set(HeaderFiles
)

# ===

set(CMAKE_CXX_FLAGS_DEBUG "${CMakeDebugFlags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMakeFlags}")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

add_executable("${ExecutableName}" "${SourceFiles}" "${HeaderFiles}")

target_include_directories("${ExecutableName}" PRIVATE "${IncludeDirs}")

target_link_libraries("${ExecutableName}" PRIVATE "${Libraries}")

install(TARGETS ${ExecutableName} DESTINATION "${CMAKE_INSTALL_BINDIR}")
