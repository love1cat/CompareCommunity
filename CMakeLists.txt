cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(AppName ccmty)

project(EvenSimProject)

# FIND_PACKAGE(boost)
INCLUDE_DIRECTORIES("~/Library/boost_1_55_0") 

add_executable(${AppName} cluster_comp_base.h cluster_comp_base.cpp main.cpp)

target_link_libraries(${AppName} m pthread)
      
