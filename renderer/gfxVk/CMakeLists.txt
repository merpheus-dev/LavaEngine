cmake_minimum_required(VERSION 2.6)

set(project_name gfxVk)
project(${project_name})
set(HAVE_LIBC TRUE)

set(TARGET_ARCHITECTURE "x64")
set(CMAKE_SUPPRESS_REGENERATION TRUE)
set(src
    gfxDevice.cpp
)

set(headers

)

add_library(${project_name} ${src} ${headers})
add_library(Lava::gfxVk ALIAS ${PROJECT_NAME}) 

find_package(Vulkan)

if(Vulkan_FOUND)
    target_include_directories(${project_name} PUBLIC Vulkan::Vulkan)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()