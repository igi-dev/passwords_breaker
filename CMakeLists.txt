cmake_minimum_required(VERSION 3.0)
project(passwords_breaker)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-g)

set(SOURCES
    src/Consumer.c
    src/Producer.c
    src/StringConversion.c
    src/Utilities.c
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread crypto)