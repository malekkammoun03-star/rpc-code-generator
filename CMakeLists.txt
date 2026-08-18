cmake_minimum_required(VERSION 3.16)

project(RPCCodeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    main.cpp
    parser/ProtoParser.cpp
    generator/CodeGenerator.cpp
    runtime/TlsClient.cpp
    runtime/RpcClient.cpp
)

target_include_directories(app PRIVATE
    parser
    generator
    runtime
)

target_link_libraries(app PRIVATE
    mbedtls
    mbedx509
    mbedcrypto
)

add_executable(test_tls
    tests/test_tls.cpp
    runtime/TlsClient.cpp
)

target_include_directories(test_tls PRIVATE
    runtime
)

target_link_libraries(test_tls PRIVATE
    mbedtls
    mbedx509
    mbedcrypto
)