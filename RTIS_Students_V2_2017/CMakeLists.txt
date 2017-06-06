cmake_minimum_required(VERSION 3.7)
project(RTIS_Students_V2_2017)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/cameras/camera.cpp
        src/cameras/camera.h
        src/cameras/ortographic.cpp
        src/cameras/ortographic.h
        src/cameras/perspective.cpp
        src/cameras/perspective.h
        src/core/bitmap.cpp
        src/core/bitmap.h
        src/core/eqsolver.cpp
        src/core/eqsolver.h
        src/core/film.cpp
        src/core/film.h
        src/core/hemisphericalsampler.cpp
        src/core/hemisphericalsampler.h
        src/core/intersection.cpp
        src/core/intersection.h
        src/core/matrix4x4.cpp
        src/core/matrix4x4.h
        src/core/ray.cpp
        src/core/ray.h
        src/core/tester.cpp
        src/core/tester.h
        src/core/utils.cpp
        src/core/utils.h
        src/core/vector3d.cpp
        src/core/vector3d.h
        src/lightsources/arealightsource.cpp
        src/lightsources/arealightsource.h
        src/lightsources/lightsource.cpp
        src/lightsources/lightsource.h
        src/lightsources/volumelightsource.cpp
        src/lightsources/volumelightsource.h
        src/materials/material.cpp
        src/materials/material.h
        src/materials/mirror.cpp
        src/materials/mirror.h
        src/materials/phong.cpp
        src/materials/phong.h
        src/materials/transmissive.cpp
        src/materials/transmissive.h
        src/shaders/depthshader.cpp
        src/shaders/depthshader.h
        src/shaders/directshader.cpp
        src/shaders/directshader.h
        src/shaders/globalshader.cpp
        src/shaders/globalshader.h
        src/shaders/intersectionshader.cpp
        src/shaders/intersectionshader.h
        src/shaders/normalshader.cpp
        src/shaders/normalshader.h
        src/shaders/shader.cpp
        src/shaders/shader.h
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/shapes/sphere.cpp
        src/shapes/sphere.h
        src/shapes/infiniteplane.cpp
        src/shapes/infiniteplane.h
        src/main.cpp)

add_executable(RTIS_Students_V2_2017 ${SOURCE_FILES})