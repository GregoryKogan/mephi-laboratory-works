//
// Created by Gregory Kogan on 15.05.2023.
//

#ifndef LAB3_QUEUE_HPP
#define LAB3_QUEUE_HPP

#include "sequence_lib.hpp"


namespace kogan {

    template <class T> class Queue {
        LinkedListSequence<T>* list;

        public:
            Queue();
            Queue(T* items, int count);
            explicit Queue(const Sequence<T>* sequence);
            explicit Queue(const Queue<T>* queue);

            ~Queue();

            [[nodiscard]] bool empty() const;
            [[nodiscard]] size_t size() const;
            void swap(Queue<T>& other);
            void push(const T& item);
            T pop();

            Queue<T>* concat(const Queue<T>& other) const;
    };

    template<class T>
    Queue<T>::Queue() {
        list = new LinkedListSequence<T>();
    }

    template<class T>
    Queue<T>::Queue(T *items, int count) {
        list = new LinkedListSequence<T>(items, count);
    }

    template<class T>
    Queue<T>::Queue(const Sequence<T> *sequence) {
        T* items = new T[sequence->get_length()];
        for (int i = 0; i < sequence->get_length(); ++i)
            items[i] = sequence->get(i);
        list = new LinkedListSequence<T>(items, sequence->get_length());
    }

    template<class T>
    Queue<T>::Queue(const Queue<T> *queue) {
        list = new LinkedListSequence<T>();
        for (int i = 0; i < queue->size(); ++i)
            list->append(queue->list->get(i));
    }

    template<class T>
    Queue<T>::~Queue() {
        delete list;
    }

    template<class T>
    bool Queue<T>::empty() const {
        return list->get_length() == 0;
    }

    template<class T>
    size_t Queue<T>::size() const {
        return list->get_length();
    }

    template<class T>
    void Queue<T>::swap(Queue<T> &other) {
        auto tmp = list;
        list = other.list;
        other.list = tmp;
    }

    template<class T>
    void Queue<T>::push(const T &item) {
        list->append(item);
    }

    template<class T>
    T Queue<T>::pop() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = list->get_first();
        list->remove(0);
        return value;
    }

    template<class T>
    Queue<T> *Queue<T>::concat(const Queue<T> &other) const {
        auto* result = new Queue<T>(this);
        for (int i = 0; i < other.size(); ++i)
            result->push(other.list->get(i));
        return result;
    }

} // kogan

#endif //LAB3_QUEUE_HPP
