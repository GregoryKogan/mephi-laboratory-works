#include "dependencies/cpp-httplib/httplib.h"

int main(void) {
    using namespace httplib;

    Server svr;

    svr.Get("/hi", [](const Request& req, Response& res) { res.set_content("Hello World!", "text/plain"); });

    svr.Get("/stop", [&](const Request& req, Response& res) { svr.stop(); });

    svr.listen("localhost", 8080);
}