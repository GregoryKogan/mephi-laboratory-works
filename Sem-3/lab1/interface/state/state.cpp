#include "state.hpp"

kogan::State::SequenceRecord::SequenceRecord(sequence_type type, kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq)
    : type(type), seq(seq) {}

std::string kogan::State::SequenceRecord::to_string() const {
    std::ostringstream oss;
    oss << "{\n"
        << "    \"type\": " << (type == sequence_type::array ? "\"array\"" : "\"list\"") << ",\n"
        << "    \"seq\": " << seq->to_string() << "\n"
        << "}";
    return oss.str();
}

std::ostream& kogan::operator<<(std::ostream& os, const kogan::State::SequenceRecord& record) {
    os << record.to_string();
    return os;
}

kogan::State::State() {
    records_ = kogan::SharedPtr<kogan::SmartPtrSequence<SequenceRecord>>(
        new kogan::SmartPtrLinkedListSequence<SequenceRecord>());
}

kogan::SharedPtr<kogan::SmartPtrSequence<kogan::State::SequenceRecord>> kogan::State::get_records() const {
    return records_;
}
