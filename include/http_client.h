

#ifndef HTTPS_CLIENT_HTTP_CLIENT_H
#define HTTPS_CLIENT_HTTP_CLIENT_H

#include "client_interface.h"
#include "socket_wrapper.h"

namespace simple_https {
    class http_client : public client_interface {
        socket_d sock;
        void write(const std::string &request_str) override;
        std::string read() override;
    public:
        explicit http_client(const std::string &hostname_);
        void reload() override;
    };


}

#endif //HTTPS_CLIENT_HTTP_CLIENT_H
