cmake_minimum_required(VERSION 3.16)
project(RayTracing_Dev)

set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracing_Dev
        main.cpp
        vec3.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
        rtweekend.h
        camera.h
        material.h
        moving_sphere.h
        aabb.h
        bvh.h
        texture.h
        perlin.h
        surface_texture.h
        vendor/stb/stb_image.h
        rtw_stb_image.h
        aarect.h
        box.h constant_medium.h pi.cpp integrate_x_sq.cpp)