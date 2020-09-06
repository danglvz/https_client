# https_client
http and https client based on raw socket (using OpenSSL)

## Features
- modern c++ (17)
- good for web parsing or making simple multiple requests
- OpenSSL dependencies only

## Dependencies
- OpenSSL v 1.1 or higher

## Usage
```cpp
#include "simple_https_client.h"

std::string output;

//http
simple_https::http_client http(/*hostname, example:"google.com"*/);
output = http.get_request(/*request string, example:"search?q=github"*/);
http.reload() //reload socket;

//https
simple_https::https_client https(/*hostname, example:google.com*/);
output = https.get_request(/*request string, example:"search?q=github"*/);
https.reload(); //reload socket and ssl handshake

```
