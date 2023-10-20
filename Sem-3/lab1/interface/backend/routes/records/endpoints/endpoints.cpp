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
        set_message_and_status(res, "type is not specified", 400);
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
        set_message_and_status(res, "type is not valid", 400);
        return;
    }

    set_message_and_status(res, "record added", 200);
}

void remove_record(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    try {
        kogan::global_state.get_records()->remove(index);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "record removed", 200);
}

void append(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> value_pair = get_parameter_value(req, res);
    if (!value_pair.second) return;
    int value = value_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->append(value);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "value appended", 200);
}

void prepend(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> value_pair = get_parameter_value(req, res);
    if (!value_pair.second) return;
    int value = value_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->prepend(value);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "value prepended", 200);
}

void set(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> value_pair = get_parameter_value(req, res);
    if (!value_pair.second) return;
    int value = value_pair.first;

    std::pair<int, bool> index_to_set_pair = get_parameter_value(req, res, "index");
    if (!index_to_set_pair.second) return;
    int index_to_set = index_to_set_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->set(index_to_set, value);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "value set", 200);
}

void insert(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> value_pair = get_parameter_value(req, res);
    if (!value_pair.second) return;
    int value = value_pair.first;

    std::pair<int, bool> index_to_insert_pair = get_parameter_value(req, res, "index");
    if (!index_to_insert_pair.second) return;
    int index_to_insert = index_to_insert_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->insert(index_to_insert, value);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "value inserted", 200);
}

void remove_item(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> index_to_remove_pair = get_parameter_value(req, res, "index");
    if (!index_to_remove_pair.second) return;
    int index_to_remove = index_to_remove_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->remove(index_to_remove);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "value removed", 200);
}

void clear(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    try {
        kogan::global_state.get_records()->get(index).get_seq()->clear();
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }

    set_message_and_status(res, "sequence cleared", 200);
}

void subsequence(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> index_pair = get_seq_index(req, res);
    if (!index_pair.second) return;
    int index = index_pair.first;

    std::pair<int, bool> start_pair = get_parameter_value(req, res, "start");
    if (!start_pair.second) return;
    int start = start_pair.first;

    std::pair<int, bool> end_pair = get_parameter_value(req, res, "end");
    if (!end_pair.second) return;
    int end = end_pair.first;

    try {
        auto sub_seq = kogan::global_state.get_records()->get(index).get_seq()->get_subsequence(start, end);
        std::ostringstream oss;
        oss << "{\n"
            << "    \"subsequence\": " << *sub_seq << "\n"
            << "}";
        res.status = 200;
        res.set_content(oss.str(), "application/json");
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }
}

void concat(const httplib::Request& req, httplib::Response& res) {
    std::pair<int, bool> first_index_pair = get_seq_index(req, res);
    if (!first_index_pair.second) return;
    int first_index = first_index_pair.first;

    std::pair<int, bool> second_index_pair = get_parameter_value(req, res, "index");
    if (!second_index_pair.second) return;
    int second_index = second_index_pair.first;

    try {
        auto first_seq = kogan::global_state.get_records()->get(first_index).get_seq();
        auto second_seq = kogan::global_state.get_records()->get(second_index).get_seq();
        auto concat_seq = first_seq->concat(second_seq);

        auto items = kogan::make_shared<int[]>(concat_seq->get_length());
        for (int i = 0; i < concat_seq->get_length(); ++i) items[i] = concat_seq->get(i);

        auto new_seq = kogan::SharedPtr<kogan::SmartPtrSequence<int>>(
            new kogan::SmartPtrArraySequence<int>(items, concat_seq->get_length()));
        kogan::global_state.get_records()->append(
            kogan::State::SequenceRecord(kogan::global_state.get_records()->get(first_index).get_type(), new_seq));
        set_message_and_status(res, "sequences concatenated", 200);
    } catch (std::exception& e) {
        handle_exception_with_status(e, res, 400);
        return;
    }
}

void set_message_and_status(httplib::Response& res, const std::string& message, int status) {
    res.status = status;
    res.set_content(
        "{\n"
        "    \"message\": \"" +
            message +
            "\"\n"
            "}",
        "application/json");
}

void handle_exception_with_status(std::exception& e, httplib::Response& res, int status) {
    res.status = status;
    std::string error_msg =
        "{\n"
        "    \"message\": \"" +
        std::string(e.what()) +
        "\"\n"
        "}";
    res.set_content(error_msg, "application/json");
}

std::pair<int, bool> get_seq_index(const httplib::Request& req, httplib::Response& res) {
    auto index_param = req.path_params.at("index");
    if (index_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"index is not specified\"\n"
            "}",
            "application/json");
        return std::make_pair(-1, false);
    }

    int index = stoi(index_param);
    return std::make_pair(index, true);
}

std::pair<int, bool> get_parameter_value(const httplib::Request& req, httplib::Response& res,
                                         const std::string& parameter_name) {
    std::string value_param = req.get_param_value(parameter_name);
    if (value_param.empty()) {
        res.status = 400;
        res.set_content(
            "{\n"
            "    \"message\": \"" +
                parameter_name +
                " is not specified\"\n"
                "}",
            "application/json");
        return std::make_pair(0, false);
    }

    int value = stoi(value_param);
    return std::make_pair(value, true);
}
