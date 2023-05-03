//
// Created by Gregory Kogan on 04.05.2023.
//

#ifndef LAB2_LINKEDLISTSEQUENCE_H
#define LAB2_LINKEDLISTSEQUENCE_H

#include "Sequence.h"
#include "../data_structures/LinkedList.h"

namespace kogan {

    template <class T> class LinkedListSequence: public Sequence<T> {
        LinkedList<T>* list;

    public:
        LinkedListSequence(T* items, int count);
        LinkedListSequence();
        LinkedListSequence(const LinkedListSequence<T> &linkedListSequence);

        ~LinkedListSequence();

        T get_first();
        T get_last();
        T get(int index);
        Sequence<T>* get_subsequence(int start_index, int end_index);
        size_t get_length();

        void set(int index, T item);
        void append(T item);
        void prepend(T item);
        void insert(T item, int index);
        Sequence<T>* concat(Sequence<T>* sequence);
    };

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(T *items, int count) {
        list = new LinkedList<T>(items, count);
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence() {
        list = new LinkedList<T>;
    }

    template<class T>
    LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T> &linkedListSequence) {
        list = new LinkedList<T>(*linkedListSequence.list);
    }

    template<class T>
    LinkedListSequence<T>::~LinkedListSequence() {
        delete list;
    }

    template<class T>
    T LinkedListSequence<T>::get_first() {
        return list->get_first();
    }

    template<class T>
    T LinkedListSequence<T>::get_last() {
        return list->get_last();
    }

    template<class T>
    T LinkedListSequence<T>::get(int index) {
        return list->get(index);
    }

    template<class T>
    Sequence<T> *LinkedListSequence<T>::get_subsequence(int start_index, int end_index) {
        LinkedList<T> sub_list = list->get_sublist(start_index, end_index);

        auto sub_seq = new LinkedListSequence<T>;
        for (int i = 0; i < sub_list.get_length(); ++i)
            sub_seq->append(sub_list.get(i));
        return sub_seq;
    }

    template<class T>
    size_t LinkedListSequence<T>::get_length() {
        return list->get_length();
    }

    template<class T>
    void LinkedListSequence<T>::set(int index, T item) {
        list->set(index, item);
    }

    template<class T>
    void LinkedListSequence<T>::append(T item) {
        list->append(item);
    }

    template<class T>
    void LinkedListSequence<T>::prepend(T item) {
        list->prepend(item);
    }

    template<class T>
    void LinkedListSequence<T>::insert(T item, int index) {
        list->insert(item, index);
    }

    template<class T>
    Sequence<T> *LinkedListSequence<T>::concat(Sequence<T> *sequence) {
        auto concatenation = new LinkedListSequence<T>(*this);
        for (int i = 0; i < sequence->get_length(); ++i)
            concatenation->append(sequence->get(i));
        return concatenation;
    }

} // kogan

#endif //LAB2_LINKEDLISTSEQUENCE_H