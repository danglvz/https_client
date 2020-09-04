add_library(https_client "")





if(APPLE)
#[set your openssl directories]
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@1.1)
    set(OPENSSL_INCLUDE_DIR /usr/local/opt/openssl@1.1/include)
    set(OPENSSL_LIBRARIES /usr/local/opt/openssl@1.1/lib)
    set(OPENSSL_CRYPTO_LIBRARY /usr/local/Cellar/openssl@1.1/1.1.1g/lib/libcrypto.1.1.dylib)
    set(OPENSSL_SSL_LIBRARY /usr/local/Cellar/openssl@1.1/1.1.1g/lib/libssl.1.1.dylib)
endif()

find_package(OpenSSL REQUIRED)
IF(NOT OPENSSL_FOUND)
    MESSAGE("OpenSSL not found")
    RETURN()
ENDIF()

FILE(GLOB SRC
        "*.h"
        "*.cpp")
MESSAGE(${SRC})
target_sources(https_client PRIVATE ${SRC} )
target_include_directories(https_client PUBLIC ${OPENSSL_INCLUDE_DIR} ${https_client_SOURCE_DIR}/include)
target_link_libraries(https_client PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_compile_options(https_client PRIVATE -Wall -lssl -lcrypto)