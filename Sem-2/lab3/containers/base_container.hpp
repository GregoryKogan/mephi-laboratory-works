//
// Created by Gregory Kogan on 19.05.2023.
//

#ifndef LAB3_BASE_CONTAINER_HPP
#define LAB3_BASE_CONTAINER_HPP

#include <sequences/Sequence.hpp>
#include <exceptions/EmptyContainerException/EmptyContainerException.hpp>
#include <sequences/LinkedListSequence.hpp>
#include "i_enumerable.hpp"

namespace kogan {

    template <class T> class BaseContainer: public IEnumerable<T> {
    protected:
        using IEnumerable<T>::sequence;

    public:
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t size() const;
        void swap(BaseContainer<T>& other);
        Sequence<T>* get_subsequence(int start_index, int end_index) const;

        Sequence<T>* map(T (*func)(T)) const;
        Sequence<T>* where(bool (*func)(T)) const;
        T reduce(T (*func)(T, T), T initial_value) const;

        std::string to_string() const;

        friend std::ostream& operator<<(std::ostream& os, const BaseContainer<T>& container) {
            os << container.to_string();
            return os;
        }
    };

    template<class T>
    bool BaseContainer<T>::empty() const {
        return sequence->get_length() == 0;
    }

    template<class T>
    size_t BaseContainer<T>::size() const {
        return sequence->get_length();
    }

    template<class T>
    void BaseContainer<T>::swap(BaseContainer<T> &other) {
        auto tmp = sequence;
        sequence = other.sequence;
        other.sequence = tmp;
    }

    template<class T>
    Sequence<T> *BaseContainer<T>::get_subsequence(int start_index, int end_index) const {
        return sequence->get_subsequence(start_index, end_index);
    }

    template<class T>
    Sequence<T> *BaseContainer<T>::map(T (*func)(T)) const {
        auto result = new LinkedListSequence<T>;
        for (auto x: *this)
            result->append(func(x));
        return result;
    }

    template<class T>
    Sequence<T> *BaseContainer<T>::where(bool (*func)(T)) const {
        auto result = new LinkedListSequence<T>;
        for (auto x: *this)
            if (func(x))
                result->append(x);
        return result;
    }

    template<class T>
    T BaseContainer<T>::reduce(T (*func)(T, T), T initial_value) const {
        if (empty())
            throw EmptyContainerException();

        T result = initial_value;
        for (auto x: *this)
            result = func(result, x);

        return result;
    }

    template<class T>
    std::string BaseContainer<T>::to_string() const {
        if (empty())
            return "[]";

        std::string result = "[";
        for (auto x: *this)
            result += std::to_string(x) + ", ";
        result += "\b\b]";

        return result;
    }

} // kogan

#endif //LAB3_BASE_CONTAINER_HPP
