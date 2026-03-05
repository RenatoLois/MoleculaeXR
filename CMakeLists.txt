cmake_minimum_required(VERSION 4.2)
project(MoleculaeXR LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories (
  include/
  external/glad/include/
  external/stb/include/
)


set( MAIN_FILE
  main.cpp
)

set( GLAD_SRC
  external/glad/src/glad.c
)

file ( GLOB_RECURSE STB_SRC
  external/stb/src/stb_image_implementation.cpp
  external/stb/src/stb_image_resize_implementation.cpp
)

file(GLOB_RECURSE SOURCE_FILES
    src/*.cpp
)


file(GLOB RESOURCES    res/assets/*.png res/assets/*.jpg res/assets/*.jpeg)
file(GLOB SHADERS      res/shaders/*.glsl)

set(ALL_LISTS_TO_COPY ${RESOURCES} ${SHADERS})

foreach(file IN LISTS ALL_LISTS_TO_COPY) 
    file(RELATIVE_PATH relative_file_path ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/${relative_file_path}
        ${CMAKE_CURRENT_BINARY_DIR}/${relative_file_path}
        COPYONLY
    )
endForeach()


add_executable( MoleculaeXR
  ${MAIN_FILE}
  ${SOURCE_FILES}
  ${GLAD_SRC}
  ${STB_SRC}
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenCV REQUIRED REQUIRED core imgproc highgui videoio)
target_link_libraries(MoleculaeXR PRIVATE glfw m ${OpenCV_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})

target_precompile_headers(MoleculaeXR PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:<stb/stb_image.h>>"
    "$<$<COMPILE_LANGUAGE:CXX>:<stb/stb_image_resize.h>>"
    "$<$<COMPILE_LANGUAGE:CXX>:<opencv2/opencv.hpp>>"
)
