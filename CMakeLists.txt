cmake_minimum_required(VERSION 3.19)
project(covidVierosesSimolation)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(covidVierosesSimolation
        Alpha.cpp
        Alpha.h
        Delta.cpp
        Delta.h
        main.cpp
        Omicron.cpp
        Omicron.h
        SARS_COV2.cpp
        SARS_COV2.h
        Simulation.cpp
        Simulation.h)
