#ifndef LAB1_INTERFACE_STATE_HPP
#define LAB1_INTERFACE_STATE_HPP

#include "../../sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp"
#include "../../sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp"

struct state_vault {
    kogan::SharedPtr<kogan::SmartPtrArraySequence<int>> array_seq;
    kogan::SharedPtr<kogan::SmartPtrLinkedListSequence<int>> list_seq;
};

void init_state();
kogan::SharedPtr<kogan::SmartPtrArraySequence<int>> get_array_seq();
kogan::SharedPtr<kogan::SmartPtrLinkedListSequence<int>> get_list_seq();

#endif