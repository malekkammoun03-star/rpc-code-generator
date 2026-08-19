cmake_minimum_required(VERSION 3.16)

project(RPCCodeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_path(MBEDTLS_INCLUDE_DIR
    NAMES mbedtls/ssl.h
)

find_library(MBEDTLS_LIBRARY
    NAMES mbedtls
)

find_library(MBEDX509_LIBRARY
    NAMES mbedx509
)

find_library(MBEDCRYPTO_LIBRARY
    NAMES mbedcrypto
)

if(NOT MBEDTLS_INCLUDE_DIR OR
   NOT MBEDTLS_LIBRARY OR
   NOT MBEDX509_LIBRARY OR
   NOT MBEDCRYPTO_LIBRARY)

    message(FATAL_ERROR "Mbed TLS not found")
endif()

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
    ${MBEDTLS_INCLUDE_DIR}
)

target_link_libraries(app PRIVATE
    ${MBEDTLS_LIBRARY}
    ${MBEDX509_LIBRARY}
    ${MBEDCRYPTO_LIBRARY}
)

add_executable(test_tls
    tests/test_tls.cpp
    runtime/TlsClient.cpp
)

target_include_directories(test_tls PRIVATE
    runtime
    ${MBEDTLS_INCLUDE_DIR}
)

target_link_libraries(test_tls PRIVATE
    ${MBEDTLS_LIBRARY}
    ${MBEDX509_LIBRARY}
    ${MBEDCRYPTO_LIBRARY}
)