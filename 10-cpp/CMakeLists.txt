cmake_minimum_required(VERSION 3.16)

project(adivina-numero-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Genera el código que Qt necesita para las clases con Q_OBJECT.
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(adivina-numero
    main.cpp
    game.cpp
    gamewindow.cpp
)

target_link_libraries(adivina-numero PRIVATE Qt6::Widgets)
