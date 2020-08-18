#include <gtest/gtest.h>
#include "../src/http_client.h"



TEST(http_client_web_test, IsResult) {
    std::string output;
    simple_https::http_client httpClient("api.vk.com");
    output.assign(httpClient.get_request("?"));
    std::cout << output << std::endl;
    ASSERT_TRUE(!output.empty());
}



