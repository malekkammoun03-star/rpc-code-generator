cmake_minimum_required(VERSION 3.16)

project(RPCCodeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find mbedTLS on the current system
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

if(NOT MBEDTLS_INCLUDE_DIR)
    message(FATAL_ERROR "mbedTLS headers not found")
endif()

if(NOT MBEDTLS_LIBRARY)
    message(FATAL_ERROR "mbedTLS library not found")
endif()

if(NOT MBEDX509_LIBRARY)
    message(FATAL_ERROR "mbedx509 library not found")
endif()

if(NOT MBEDCRYPTO_LIBRARY)
    message(FATAL_ERROR "mbedcrypto library not found")
endif()

# Main application
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

# TLS test
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