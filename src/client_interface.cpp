

#include "client_interface.h"
#include "sstream"


using namespace simple_https;


simple_https::client_interface::client_interface(const std::string &host) : hostname(host) {}

std::string client_interface::read() {return std::string("none");}

void client_interface::write(const std::string &request_str) {}

std::string client_interface::get_request(const std::string &req) {
    std::string request{prepare_request(req)};
    write(request);
    std::string output{read()};
    if ( output.empty() ) {
        reload();
        write(request);
        output.assign(read());
    }
    while(!output.empty() && output.find("\r\n\r\n") == std::string::npos) { output.append(read()); }

    std::vector<std::string> h_lines;
    std::size_t start{}, end, content_length{};
    while ((end = output.find("\r\n", start)) != std::string::npos) {
        h_lines.push_back(output.substr(start, end - start));
        start = end + 2;
    }

    for (auto &line: h_lines) {
        if (auto pos{ line.find(':')}; pos != std::string::npos) {
            if(line.substr(0, pos) == "Content-Length") {
                content_length = std::stoi(line.substr(pos + 1));
                break;
            }
        }
    }

    output.erase(0, output.find("\r\n\r\n") + 4);

    while(output.length() < content_length) output.append(read());

    return output;
}


void client_interface::reload() {}



inline std::string simple_https::client_interface::prepare_request(const std::string &req) {
    std::string output{"GET /"};
    if (req[0] == '/') output.erase(req.begin() + 1, req.end());
    else output.append(req.begin(), req.end());
    output.append(" HTTP/1.1\r\nHost:");
    output.append(hostname);
    output.append("\r\n\r\n");
    return output;
}


