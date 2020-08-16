

#include <gtest/gtest.h>
#include "../src/using_openssl.h"

TEST(Web_tests, IsResult) {
    std::string output;
    simple_https::https_client httpsClient("google.com");
    output.assign(httpsClient.get_request("GET / HTTP/1.1\r\nHost:google.com\r\n\r\n"));
    std::cout << output <<std::endl;
    ASSERT_TRUE(!output.empty());
}





