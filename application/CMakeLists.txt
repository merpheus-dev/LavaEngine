cmake_minimum_required(VERSION 2.6)

set(project_name app)
project(${project_name})
set(HAVE_LIBC TRUE)

set(TARGET_ARCHITECTURE "x64")

set(src
    app.cpp
)

set(headers

)

add_executable(${project_name} ${src} ${headers})