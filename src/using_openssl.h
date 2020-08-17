
#ifndef HTTPS_CLIENT_IMPL_USING_OPENSSL_H
#define HTTPS_CLIENT_IMPL_USING_OPENSSL_H

#include "include.h"
#include "client_interface.h"
#include "socket_wrapper.h"

namespace simple_https {

    class https_client : public client_interface {
    public:
        explicit https_client(const std::string& hostname);
        void reload() override;

    private:

        std::string read() override;
        void write(const std::string &request_str) override;
        UniqPtr<SSL> ssl;
        UniqPtr<SSL_CTX> ssl_ctx;
        socket_d socket_;
    };

}



#endif //HTTPS_CLIENT_IMPL_USING_OPENSSL_H
