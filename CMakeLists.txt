cmake_minimum_required(VERSION 2.6)

# project config
set(project_name LavaEngine)
project(${project_name})

set(TARGET_ARCHITECTURE "x64")

set(HAVE_LIBC TRUE)
set(CMAKE_SUPPRESS_REGENERATION TRUE)

set(src
    app.cpp
)

set(headers

)

add_executable(${project_name} ${src} ${headers})

add_subdirectory(renderer/gfxVk)
#add_subdirectory(application)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC Lava::gfxVk
)

set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${project_name})