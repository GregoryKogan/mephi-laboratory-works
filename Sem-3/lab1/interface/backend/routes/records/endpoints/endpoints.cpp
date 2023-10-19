#include "endpoints.hpp"

void get_records(const httplib::Request& req, httplib::Response& res) {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"records\": " << *kogan::global_state.get_records() << "\n"
        << "}";
    res.status = 200;
    res.set_content(oss.str(), "application/json");
}

void add_record(const httplib::Request& req, httplib::Response& res) {
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

void remove_record(const httplib::Request& req, httplib::Response& res) {
    auto index_param = req.path_params.at("index");
    if (index_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"index is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    int index = stoi(index_param);

    try {
        kogan::global_state.get_records()->remove(index);
    } catch (std::exception& e) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"index is out of range\"\n"
            "}",
            "application/json");
        return;
    }

    res.status = 200;
    res.set_content(
        "{\n"
        "    \"message\": \"record removed\"\n"
        "}",
        "application/json");
}

void append(const httplib::Request& req, httplib::Response& res) {
    auto index_param = req.path_params.at("index");
    if (index_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"index is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    int index = stoi(index_param);

    std::string value_param = req.get_param_value("value");
    if (value_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"value is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    int value = stoi(value_param);

    try {
        kogan::global_state.get_records()->get(index).get_seq()->append(value);
    } catch (std::exception& e) {
        res.status = 400;
        std::string error_msg =
            "{\n"
            "    \"message\": \"" +
            std::string(e.what()) +
            "\"\n"
            "}";
        res.set_content(error_msg, "application/json");
        return;
    }

    res.status = 200;
    res.set_content(
        "{\n"
        "    \"message\": \"value appended\"\n"
        "}",
        "application/json");
}

void prepend(const httplib::Request& req, httplib::Response& res) {
    auto index_param = req.path_params.at("index");
    if (index_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"index is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    int index = stoi(index_param);

    std::string value_param = req.get_param_value("value");
    if (value_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"value is not specified\"\n"
            "}",
            "application/json");
        return;
    }

    int value = stoi(value_param);

    try {
        kogan::global_state.get_records()->get(index).get_seq()->prepend(value);
    } catch (std::exception& e) {
        res.status = 400;
        std::string error_msg =
            "{\n"
            "    \"message\": \"" +
            std::string(e.what()) +
            "\"\n"
            "}";
        res.set_content(error_msg, "application/json");
        return;
    }

    res.status = 200;
    res.set_content(
        "{\n"
        "    \"message\": \"value prepended\"\n"
        "}",
        "application/json");
}
