cmake_minimum_required(VERSION 2.8)
project(LeetApi)

if (CMAKE_VERSION VERSION_LESS 3.0.0)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(ModLoader REQUIRED)
find_library(Lua lua)

include_directories(minecraft-headers/)

add_library(LeetApi SHARED src/main.cpp src/BanCommand.h src/EventManager.h src/sol.hpp src/LuaPlayer.h src/events/PlayerJoinEvent.cpp)
target_link_libraries(LeetApi PUBLIC ModLoader "${Lua}")
