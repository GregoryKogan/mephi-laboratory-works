//
// Created by Gregory Kogan on 16.05.2023.
//

#ifndef LAB3_STACK_HPP
#define LAB3_STACK_HPP

#include "sequence_lib.hpp"


namespace kogan {

    template <class T> class Stack {
        LinkedListSequence<T>* list;

    public:
        Stack();
        Stack(T* items, int count);
        explicit Stack(const Sequence<T>* sequence);
        explicit Stack(const Stack<T>* stack);

        ~Stack();

        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t size() const;
        void swap(Stack<T>& other);
        void push(const T& item);
        T pop();

        Stack<T>* concat(const Stack<T>& other) const;
        Sequence<T>* get_subsequence(int start_index, int end_index) const;
    };

    template<class T>
    Stack<T>::Stack() {
        list = new LinkedListSequence<T>();
    }

    template<class T>
    Stack<T>::Stack(T *items, int count) {
        list = new LinkedListSequence<T>(items, count);
    }

    template<class T>
    Stack<T>::Stack(const Sequence<T> *sequence) {
        T* items = new T[sequence->get_length()];
        for (int i = 0; i < sequence->get_length(); ++i)
            items[i] = sequence->get(i);
        list = new LinkedListSequence<T>(items, sequence->get_length());
    }

    template<class T>
    Stack<T>::Stack(const Stack<T> *stack) {
        list = new LinkedListSequence<T>();
        for (int i = 0; i < stack->size(); ++i)
            list->append(stack->list->get(i));
    }

    template<class T>
    Stack<T>::~Stack() {
        delete list;
    }

    template<class T>
    bool Stack<T>::empty() const {
        return list->get_length() == 0;
    }

    template<class T>
    size_t Stack<T>::size() const {
        return list->get_length();
    }

    template<class T>
    void Stack<T>::swap(Stack<T> &other) {
        auto tmp = list;
        list = other.list;
        other.list = tmp;
    }

    template<class T>
    void Stack<T>::push(const T &item) {
        list->prepend(item);
    }

    template<class T>
    T Stack<T>::pop() {
        if (empty())
            throw kogan::EmptyContainerException();

        T value = list->get_first();
        list->remove(0);
        return value;
    }

    template<class T>
    Stack<T> *Stack<T>::concat(const Stack<T> &other) const {
        auto* result = new Stack<T>(this);
        for (int i = 0; i < other.size(); ++i)
            result->list->append(other.list->get(i));
        return result;
    }

    template<class T>
    Sequence<T> *Stack<T>::get_subsequence(int start_index, int end_index) const {
        return list->get_subsequence(start_index, end_index);
    }

} // kogan

#endif //LAB3_STACK_HPP
