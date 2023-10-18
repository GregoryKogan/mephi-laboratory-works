#include "../dependencies/cpp-httplib/httplib.h"
#include "../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"
#include "endpoints/endpoints.hpp"
#include "state/state.hpp"

int main(void) {
    httplib::Server svr;

    svr.Get("/ping", ping);
    svr.Get("/stop", [&](const httplib::Request& req, httplib::Response& res) { svr.stop(); });

    // observers
    svr.Get("/state", get_state);

    // modifiers
    svr.Post("/state", add_sequence_record);

    svr.listen("localhost", 8080);
}