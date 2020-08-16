add_library(https_client "")

find_package(OpenSSL REQUIRED)
IF(NOT OPENSSL_FOUND)
    MESSAGE("OpenSSL not found")
    RETURN()
ENDIF()

FILE(GLOB SRC
        "*.h"
        "*.cpp")
MESSAGE(${SRC})
target_sources(https_client PUBLIC ${SOURCE} ${SRC} )
target_include_directories(https_client PRIVATE ${OPENSSL_INCLUDE_DIR} ${https_client_SOURCE_DIR}/include)
target_link_libraries(https_client PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_compile_options(https_client PRIVATE -Wall -lssl -lcrypto)