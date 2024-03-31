cmake_minimum_required(VERSION 3.27)
project(TP_SFSD_2023_KERMI C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c11")

# Include GTK3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(TP_SFSD_2023_KERMI main.c
        machine_abtraite.c
        fonction.c
        fonction.h
        variable_globale.h
        variable_globale.c
        affichage.c
        affichage.h
        config.h)

target_include_directories(TP_SFSD_2023_KERMI PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(TP_SFSD_2023_KERMI PRIVATE ${GTK3_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")