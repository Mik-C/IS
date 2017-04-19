cmake_minimum_required(VERSION 3.7)
project(RTIS_Students)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        output/normalTransformExercice.txt
        output/transformationsExercise.txt
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
        src/shapes/shape.cpp
        src/shapes/shape.h
        src/shapes/sphere.cpp
        src/shapes/sphere.h
        src/main.cpp
        VisualStudio2015/RTIS/RTIS.vcxproj
        VisualStudio2015/RTIS/RTIS.vcxproj.filters
        VisualStudio2015/RTIS/RTIS.vcxproj.user
        VisualStudio2015/VisualStudio2015.sln
        RTIS.pro src/core/filter.h src/core/filter.cpp)

add_executable(RTIS_Students ${SOURCE_FILES})