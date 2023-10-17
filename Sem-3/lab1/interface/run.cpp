#include "../dependencies/cpp-httplib/httplib.h"
#include "../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"
#include "endpoints/endpoints.hpp"
#include "state/state.hpp"

int main(void) {
    httplib::Server svr;

    init_state();

    svr.Get("/state", get_state);
    svr.Get("/ping", ping);
    svr.Get("/stop", [&](const httplib::Request& req, httplib::Response& res) { svr.stop(); });

    svr.listen("localhost", 8080);
}