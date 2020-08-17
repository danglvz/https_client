
#include "http_client.h"

#define HTTP_DEFAULT_PORT "80"

simple_https::http_client::http_client(const std::string &hostname_) :
client_interface(hostname_),
sock(hostname_, HTTP_DEFAULT_PORT) {}

void simple_https::http_client::reload() {
    sock.reload();
}

void simple_https::http_client::write(const std::string &request_str) {
    send(sock.get_descriptor(), request_str.c_str(), request_str.length(), 0);
}

std::string simple_https::http_client::read() {
    char buffer[1024]{};
    recv(sock.get_descriptor(), buffer, 1024, 0);
    return std::string(buffer);
}
