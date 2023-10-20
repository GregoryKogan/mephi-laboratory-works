#ifndef LAB1_INTERFACE_STATE_HPP
#define LAB1_INTERFACE_STATE_HPP

#include "../../../sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"
#include "../../../sequences/SmartPtrSequence.hpp"

namespace kogan {

class State {
   public:
    enum class sequence_type { array, list };
    class SequenceRecord {
        sequence_type type;
        kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq;

       public:
        SequenceRecord() = default;
        SequenceRecord(sequence_type type, kogan::SharedPtr<kogan::SmartPtrSequence<int>> seq);

        [[nodiscard]] sequence_type get_type() const;
        [[nodiscard]] kogan::SharedPtr<kogan::SmartPtrSequence<int>> get_seq() const;

        [[nodiscard]] std::string to_string() const;
    };

   private:
    kogan::SharedPtr<kogan::SmartPtrSequence<SequenceRecord>> records_;

   public:
    State();

    [[nodiscard]] kogan::SharedPtr<kogan::SmartPtrSequence<SequenceRecord>> get_records() const;
};

std::ostream &operator<<(std::ostream &os, const State::SequenceRecord &record);

static kogan::State global_state;

}  // namespace kogan

#endif
