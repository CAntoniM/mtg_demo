cmake_minimum_required(VERSION 3.20)

project(mtg)

#this is the main exe we will be using as an example
file(GLOB mtg_src "app/src/*.cpp")
add_executable(mtg "app/src/main.cpp")
target_include_directories(mtg PUBLIC "app/inc")

#this is the second lib we will be using as an example
file(GLOB atherdrift_src "libs/atherdrift/src/*.cpp") 
add_library(atherdrift SHARED ${atherdrift_src})
target_include_directories(atherdrift PUBLIC "libs/atherdrift/inc" PRIVATE "app/inc")

#this is the second lib we will be using as an example
file(GLOB bloomburrow_src "libs/bloomburrow/src/*.cpp") 
add_library(bloomburrow SHARED ${bloomburrow_src})
target_include_directories(bloomburrow PUBLIC "libs/bloomburrow/inc" PRIVATE "app/inc")

