#include "state.hpp"

static state_vault global_state;

void init_state() {
    global_state.array_seq = kogan::make_shared<kogan::SmartPtrArraySequence<int>>();
    global_state.list_seq = kogan::make_shared<kogan::SmartPtrLinkedListSequence<int>>();
}

kogan::SharedPtr<kogan::SmartPtrArraySequence<int>> get_array_seq() { return global_state.array_seq; }

kogan::SharedPtr<kogan::SmartPtrLinkedListSequence<int>> get_list_seq() { return global_state.list_seq; }
