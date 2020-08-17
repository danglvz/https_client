
#include "include.h"
#include "socket_wrapper.h"
#include "using_openssl.h"


#define HTTPS_DEFAULT_PORT "443"

using namespace simple_https;

class ErrorString {
    std::string str_ptr;
    UniqPtr<BIO> bio_ptr;
    UniqPtr<BIO_METHOD> bio_meth_ptr;
public:
    ErrorString(ErrorString &&) = delete;

    ErrorString &operator=(ErrorString &&) = delete;

    explicit ErrorString() {
        bio_meth_ptr.reset(BIO_meth_new(BIO_TYPE_SOURCE_SINK, "ErrorString"));
        BIO_meth_set_write(bio_meth_ptr.get(), [](BIO *bio, const char *data, int length) {
            auto str = reinterpret_cast<std::string *>(BIO_get_data(bio));
            str->append(data, length);
            return length;
        });
        bio_ptr.reset(BIO_new(bio_meth_ptr.get()));
        if (!bio_ptr) throw std::runtime_error("ErrorString: error in BIO_new\n");
        BIO_set_data(bio_ptr.get(), &str_ptr);
        BIO_set_init(bio_ptr.get(), 1);
    }

    BIO *bio() { return bio_ptr.get(); }

    std::string str() &&{ return std::move(str_ptr); }
};

[[noreturn]] void throw_runtime_error_openssl(const std::string &s) {
    ErrorString errorString;
    ERR_print_errors(errorString.bio());
    throw std::runtime_error(std::string("OpenSSl error: ") + s + '\n' + std::move(errorString).str());
}


https_client::https_client(const std::string &hostname_) :
client_interface(hostname_),
socket_(hostname_, HTTPS_DEFAULT_PORT)
{
    ssl_ctx.reset(SSL_CTX_new(TLS_client_method()));
    if (!ssl_ctx) {
        throw_runtime_error_openssl("error in SSL_CTX_new");
    }
    ssl.reset(SSL_new(ssl_ctx.get()));
    if (!ssl) throw_runtime_error_openssl("error in SSL_new");
    SSL_set_fd(ssl.get(), socket_.get_descriptor());
    if (SSL_connect(ssl.get()) != 1) throw_runtime_error_openssl("SSL_connection error");
}

void https_client::reload() {
    socket_.reload();
    ssl.reset(SSL_new(ssl_ctx.get()));
    if (!ssl) throw_runtime_error_openssl("error in SSL_new");
    SSL_set_fd(ssl.get(), socket_.get_descriptor());
    if (SSL_connect(ssl.get()) != 1) throw_runtime_error_openssl("https_client reload error : SSL_connection error");
}

std::string https_client::read() {
    char buffer[1024]{};
    SSL_read(ssl.get(), buffer, 1024);
    return std::string(buffer);
}

void https_client::write(const std::string &request_str) {
    SSL_write(ssl.get(), request_str.c_str(), request_str.length());
}




