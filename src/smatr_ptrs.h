

#ifndef HTTPS_CLIENT_IMPL_SMATR_PTRS_H
#define HTTPS_CLIENT_IMPL_SMATR_PTRS_H

namespace simple_https {
    template<typename TYPE>
    struct custom_destructor;

    template<>
    struct custom_destructor<addrinfo> {
        void operator()(addrinfo *addrinfo_ptr) const { freeaddrinfo(addrinfo_ptr); }
    };

    template<>
    struct custom_destructor<SSL_CTX> {
        void operator()(SSL_CTX *ctx_ptr) const { SSL_CTX_free(ctx_ptr); }
    };

    template<>
    struct  custom_destructor<SSL> {
        void operator()(SSL* ssl_ptr) const { SSL_free(ssl_ptr); }
    };

    template<>
    struct custom_destructor<BIO> {
        void operator()(BIO *bio) const { BIO_free_all(bio); }
    };

    template<>
    struct custom_destructor<BIO_METHOD> {
        void operator()(BIO_METHOD *bio_meth) const { BIO_meth_free(bio_meth); }
    };

    template<typename T>
    using UniqPtr = std::unique_ptr<T, custom_destructor<T>>;
}
#endif //HTTPS_CLIENT_IMPL_SMATR_PTRS_H
