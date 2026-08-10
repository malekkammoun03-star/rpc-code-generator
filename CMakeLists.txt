cmake_minimum_required(VERSION 3.16)
project(RPCCodeGenerator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(app
    main.cpp
    parser/ProtoParser.cpp
    generator/CodeGenerator.cpp
)
target_include_directories(app PRIVATE
    parser
    generator
)