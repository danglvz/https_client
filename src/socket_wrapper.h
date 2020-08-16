
#ifndef HTTPS_CLIENT_IMPL_SOCKET_WRAPPER_H
#define HTTPS_CLIENT_IMPL_SOCKET_WRAPPER_H

#include "include.h"
#include "smatr_ptrs.h"

namespace simple_https {

    class socket_d {
        UniqPtr <addrinfo> addr;
        int socket_;

        static inline UniqPtr <addrinfo> make_addr_ptr(const char *host, const char *port);

    public:
        explicit socket_d(const std::string &hostname, const std::string &port);

        ~socket_d();

        void reload();

        int get_descriptor() const;
    };

}

#endif //HTTPS_CLIENT_IMPL_SOCKET_WRAPPER_H
