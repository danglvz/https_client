//
// Created by dd on 14.08.2020.
//

#include <iostream>
#include <random>
#include "../src/client_interface.h"
#include "gtest/gtest.h"

class Interface_Test : public simple_https::client_interface {

    std::stringstream &ss_;
    std::ostringstream &out;
    void write(const std::string &request_str) override{
        out << request_str;
    }
    std::string read() override{
        char buffer[1025]{};
        ss_.read(buffer, 1024);
        return std::string(buffer);
    }

public:
    void reload() override {
        std::cout << "reload!" << std::endl;
    }
    explicit Interface_Test(std::stringstream &s, std::ostringstream &o) : ss_(s), out(o), simple_https::client_interface("something.com"){};
    Interface_Test &operator=(Interface_Test &&intt) noexcept {
        ss_ = std::move(intt.ss_);
        return *this;
    }
};

class response_parse : public testing::Test {
protected:
    std::stringstream ss{};
    std::ostringstream os{};
    std::string response, output;
    Interface_Test interfaceTest{ss, os};
    void SetUp()  override {}
    void TearDown() override {}
    void set_random_response(std::size_t content_length) {
        ss.clear();
        ss << "HTTP/1.1 200 OK\r\n";
        ss << "Date: Sun, 18 Oct 2012 10:36:20 GMT\r\n";
        ss << "Server: Apache/2.2.14 (Win32)\r\n";
        ss << "Content-Length: " << content_length << "\r\n";
        ss << "Content-Type: text/html; charset=iso-8859-1\r\n";
        ss << "Connection: Closed\r\n\r\n";

        std::string char_str{"0123456789"
                             "abcdefghijklmoprstuvxwz"
                             "ABCDEFGHJIKLMNOPRSTUVXWZ"};

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<std::size_t> dist{0, char_str.length() - 1};

        response.clear();
        for ( ;content_length > 0; --content_length ) {
            response.push_back(char_str.at(dist(mt)));
        }

        ss << response;
    }
};


TEST_F(response_parse, simple_test) {
    ss.str("HTTP/1.1 400 Bad Request\r\n"
           "Date: Sun, 18 Oct 2012 10:36:20 GMT\r\n"
           "Server: Apache/2.2.14 (Win32)\r\n"
           "Content-Length: 230\r\n"
           "Content-Type: text/html; charset=iso-8859-1\r\n"
           "Connection: Closed\r\n\r\n"
           "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n"
           "<html>\n"
           "<head>\n"
           "   <title>400 Bad Request</title>\n"
           "</head>\n"
           "<body>\n"
           "   <h1>Bad Request</h1>\n"
           "   <p>Your browser sent a request that this server could not understand.</p>\n"
           "   <p>The request line contained invalid characters following the protocol string.</p>\n"
           "</body>\n"
           "</html>");
    response.assign("<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n"
                    "<html>\n"
                    "<head>\n"
                    "   <title>400 Bad Request</title>\n"
                    "</head>\n"
                    "<body>\n"
                    "   <h1>Bad Request</h1>\n"
                    "   <p>Your browser sent a request that this server could not understand.</p>\n"
                    "   <p>The request line contained invalid characters following the protocol string.</p>\n"
                    "</body>\n"
                    "</html>");

    output.assign(interfaceTest.get_request("none"));
    ASSERT_STREQ(response.c_str(), output.c_str());
}

TEST_F(response_parse, zero_test) {
    ss.clear();
    response.clear();
    output.assign(interfaceTest.get_request("none"));
    ASSERT_STREQ(response.c_str(), output.c_str());
    set_random_response(0);
    output.assign(interfaceTest.get_request("none"));
    ASSERT_STREQ(response.c_str(), output.c_str());
}

TEST_F(response_parse, large_data_test) {
    set_random_response(10000);
    output.assign(interfaceTest.get_request("none"));
    ASSERT_STREQ(response.c_str(), output.c_str());
    set_random_response(10000000);
    output.assign(interfaceTest.get_request("none"));
    ASSERT_STREQ(response.c_str(), output.c_str());
}

TEST_F(response_parse, RequestFormatingTest1) {
    set_random_response(5);
    interfaceTest.get_request("?myreq=0&another=2");
    output.assign(os.str());
    std::string req{"GET /?myreq=0&another=2 HTTP/1.1\r\nHost:something.com\r\n\r\n"};
    ASSERT_STREQ(req.c_str(), output.c_str());
    os.clear();
    interfaceTest.get_request("?myreq=0&another=2");
    ASSERT_STREQ(req.c_str(), output.c_str());
}

TEST_F(response_parse, RequestFormatingZeroTest) {
    set_random_response(5);
    interfaceTest.get_request("");
    output.assign(os.str());
    std::string req{"GET / HTTP/1.1\r\nHost:something.com\r\n\r\n"};
    ASSERT_STREQ(req.c_str(), output.c_str());
}
