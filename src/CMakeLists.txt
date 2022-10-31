cmake_minimum_required(VERSION 3.5)
project (ABB VERSION 1.0.0 LANGUAGES CXX )

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
# set (CMAKE_CXX_STANDARD 17)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )


#=== Main App ===

include_directories( "core" "libs" )

add_executable( abb   "main.cpp"
                      "abb.cpp" )

target_compile_features( abb PUBLIC cxx_std_17 )