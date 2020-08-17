

#include <gtest/gtest.h>
#include "../src/using_openssl.h"

TEST(Web_tests, IsResult) {
    std::string output;
    simple_https::https_client httpsClient("google.com");
    output.assign(httpsClient.get_request(""));
    ASSERT_TRUE(!output.empty());
}

TEST(Web_tests, ReloadSocketAndLibTest) {
    std::cout << "Reload Test:" << std::endl;
    std::string output;
    simple_https::https_client httpsClient("api.vk.com");
    for ( int i{}; i < 106; ++i  ) {
        output.assign(httpsClient.get_request("wall.get?id=i"));
        std::cout << "number of request: " << i << std::endl;
        ASSERT_TRUE(!output.empty());
    }
}








