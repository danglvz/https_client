
#include "include.h"
#include "socket_wrapper.h"

using namespace simple_https;


UniqPtr<addrinfo> socket_d::make_addr_ptr(const char *host, const char *port) {
    addrinfo hints{}, *res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ( int err{ getaddrinfo(host, port, &hints, &res)}; err) {
        throw std::runtime_error(std::string("getaddrinfo error: ") +  gai_strerror(err));
    }

    return UniqPtr<addrinfo>(res);
}


socket_d::socket_d(const std::string &hostname, const std::string &port) :
        addr(make_addr_ptr(hostname.c_str(), port.c_str())),
        socket_(socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) {
    if(connect ( socket_, addr->ai_addr, addr->ai_addrlen ) < 0) {
        throw std::system_error(errno, std::generic_category());
    }
}

socket_d::~socket_d() {
    shutdown(socket_, SHUT_RDWR);
    close(socket_);
}

void socket_d::reload() {
    int new_sock_d = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if(connect ( new_sock_d, addr->ai_addr, addr->ai_addrlen ) < 0) {
        throw std::system_error(errno, std::generic_category());
    }
    shutdown(socket_, SHUT_RDWR);
    close(socket_);
    socket_ = new_sock_d;
}

int socket_d::get_descriptor() const {
    return socket_;
}
