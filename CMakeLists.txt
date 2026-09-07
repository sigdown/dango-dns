cmake_minimum_required(VERSION 3.20)

project(dango, LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(dango
    ${SOURCES}
)

target_include_directories(dango
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

target_compile_options(dango PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -g
    -O0
    -fsanitize=address,undefined
)

target_link_options(dango PRIVATE
    -fsanitize=address,undefined
)
