
#include <utility>
#include "client_interface.h"


using namespace simple_https;


std::string client_interface::get_request(const std::string &req) {
    write(req);
    std::string output{read()};
    if ( output.empty() ) {
        reload();
        write(req);
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

std::string client_interface::read() {return std::string("none");}

void client_interface::write(const std::string &request_str) {}




