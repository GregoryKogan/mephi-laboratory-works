#include "endpoints.hpp"

void ping(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"message\": \"pong\"\n"
        << "}";
    res.set_content(oss.str(), "application/json");
    res.status = 200;
}

void get_state(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"records\": " << *kogan::global_state.get_records() << "\n"
        << "}";
    res.set_content(oss.str(), "application/json");
    res.status = 200;
}

void add_sequence_record(const httplib::Request& req, httplib::Response& res) {
    std::string type = req.get_param_value("type");

    if (type.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"type is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    if (type == "array") {
        kogan::global_state.get_records()->append(kogan::State::SequenceRecord(
            kogan::State::sequence_type::array,
            kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrArraySequence<int>())));
    } else if (type == "list") {
        kogan::global_state.get_records()->append(kogan::State::SequenceRecord(
            kogan::State::sequence_type::list,
            kogan::SharedPtr<kogan::SmartPtrSequence<int>>(new kogan::SmartPtrLinkedListSequence<int>())));
    } else {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"type is not valid\"\n"
            "}",
            "application/json");
        return;
    }

    res.set_content(
        "{\n"
        "    \"message\": \"record added\"\n"
        "}",
        "application/json");
    res.status = 200;
}
