//
// Created by Gregory Kogan on 16.05.2023.
//

#ifndef LAB3_DEQUE_HPP
#define LAB3_DEQUE_HPP

#include "sequence_lib.hpp"


namespace kogan {

    template <class T> class Deque {
        LinkedListSequence<T>* list;

    public:
        Deque();
        Deque(T* items, int count);
        explicit Deque(const Sequence<T>* sequence);
        explicit Deque(const Deque<T>* deque);

        ~Deque();

        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t size() const;
        void swap(Deque<T>& other);
        void push_front(const T& item);
        void push_back(const T& item);
        T pop_front();
        T pop_back();

        Deque<T>* concat(const Deque<T>& other) const;
        Sequence<T>* get_subsequence(int start_index, int end_index) const;
    };

    template<class T>
    Deque<T>::Deque() {
        list = new LinkedListSequence<T>();
    }

    template<class T>
    Deque<T>::Deque(T *items, int count) {
        list = new LinkedListSequence<T>(items, count);
    }

    template<class T>
    Deque<T>::Deque(const Sequence<T> *sequence) {
        T* items = new T[sequence->get_length()];
        for (int i = 0; i < sequence->get_length(); ++i)
            items[i] = sequence->get(i);
        list = new LinkedListSequence<T>(items, sequence->get_length());
    }

    template<class T>
    Deque<T>::Deque(const Deque<T> *deque) {
        list = new LinkedListSequence<T>();
        for (int i = 0; i < deque->size(); ++i)
            list->append(deque->list->get(i));
    }

    template<class T>
    Deque<T>::~Deque() {
        delete list;
    }

    template<class T>
    bool Deque<T>::empty() const {
        return list->get_length() == 0;
    }

    template<class T>
    size_t Deque<T>::size() const {
        return list->get_length();
    }

    template<class T>
    void Deque<T>::swap(Deque<T> &other) {
        auto tmp = list;
        list = other.list;
        other.list = tmp;
    }

    template<class T>
    void Deque<T>::push_front(const T &item) {
        list->prepend(item);
    }

    template<class T>
    void Deque<T>::push_back(const T &item) {
        list->append(item);
    }

    template<class T>
    T Deque<T>::pop_front() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = list->get_first();
        list->remove(0);
        return value;
    }

    template<class T>
    T Deque<T>::pop_back() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = list->get_last();
        list->remove(list->get_length() - 1);
        return value;
    }

    template<class T>
    Deque<T> *Deque<T>::concat(const Deque<T> &other) const {
        auto* result = new Deque<T>(this);
        for (int i = 0; i < other.size(); ++i)
            result->push_back(other.list->get(i));
        return result;
    }

    template<class T>
    Sequence<T> *Deque<T>::get_subsequence(int start_index, int end_index) const {
        return list->get_subsequence(start_index, end_index);
    }

} // kogan

#endif //LAB3_DEQUE_HPP
