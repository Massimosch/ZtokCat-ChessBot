cmake_minimum_required(VERSION 3.21)

project(ChessBot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChessBot
    main.cpp
    _laillisetSiirrot.cpp
    _laillisetSiirrot.h
)
