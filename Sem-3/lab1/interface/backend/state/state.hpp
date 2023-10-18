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

        [[nodiscard]] std::string to_string() const;
        friend std::ostream &operator<<(std::ostream &os, const State::SequenceRecord &record);
    };

   private:
    kogan::SharedPtr<kogan::SmartPtrSequence<SequenceRecord>> records_;

   public:
    State();

    kogan::SharedPtr<kogan::SmartPtrSequence<SequenceRecord>> get_records() const;
};

static kogan::State global_state;

}  // namespace kogan

#endif