cmake_minimum_required(VERSION 3.16)
project(RayTracing_Dev)

set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracing_Dev main.cpp vec3.h ray.h hittable.h sphere.h hittable_list.h rtweekend.h)