cmake_minimum_required (VERSION 3.8)

project ("RayTracer")

add_executable (RayTracer "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracer PROPERTY CXX_STANDARD 20)
endif()