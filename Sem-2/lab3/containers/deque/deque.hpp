//
// Created by Gregory Kogan on 16.05.2023.
//

#ifndef LAB3_DEQUE_HPP
#define LAB3_DEQUE_HPP

#include "sequence_lib.hpp"
#include "../base_container.hpp"


namespace kogan {

    template <class T> class Deque: public BaseContainer<T> {
        using BaseContainer<T>::sequence;

    public:
        using BaseContainer<T>::empty;

        Deque();
        Deque(T* items, int count);
        explicit Deque(const Sequence<T>* other_seq);
        explicit Deque(const Deque<T>* deque);

        void push_front(const T& item);
        void push_back(const T& item);
        T pop_front();
        T pop_back();
        T front() const;
        T back() const;

        Deque<T>* concat(const Deque<T>& other) const;
    };

    template<class T>
    Deque<T>::Deque() {
        sequence = new LinkedListSequence<T>();
    }

    template<class T>
    Deque<T>::Deque(T *items, int count) {
        sequence = new LinkedListSequence<T>(items, count);
    }

    template<class T>
    Deque<T>::Deque(const Sequence<T> *other_seq) {
        T* items = new T[other_seq->get_length()];
        for (int i = 0; i < other_seq->get_length(); ++i)
            items[i] = other_seq->get(i);
        sequence = new LinkedListSequence<T>(items, other_seq->get_length());
        delete [] items;
    }

    template<class T>
    Deque<T>::Deque(const Deque<T> *deque) {
        sequence = new LinkedListSequence<T>();
        for (int i = 0; i < deque->size(); ++i)
            sequence->append(deque->sequence->get(i));
    }

    template<class T>
    void Deque<T>::push_front(const T &item) {
        sequence->prepend(item);
    }

    template<class T>
    void Deque<T>::push_back(const T &item) {
        sequence->append(item);
    }

    template<class T>
    T Deque<T>::pop_front() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = sequence->get_first();
        sequence->remove(0);
        return value;
    }

    template<class T>
    T Deque<T>::pop_back() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = sequence->get_last();
        sequence->remove(sequence->get_length() - 1);
        return value;
    }

    template<class T>
    T Deque<T>::front() const {
        if (empty())
            throw kogan::EmptyContainerException();

        return sequence->get_first();
    }

    template<class T>
    T Deque<T>::back() const {
        if (empty())
            throw kogan::EmptyContainerException();

        return sequence->get_last();
    }

    template<class T>
    Deque<T> *Deque<T>::concat(const Deque<T> &other) const {
        auto* result = new Deque<T>(this);
        for (auto x: other)
            result->push_back(x);
        return result;
    }

} // kogan

#endif //LAB3_DEQUE_HPP
