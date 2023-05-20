//
// Created by Gregory Kogan on 19.05.2023.
//

#ifndef LAB3_BASE_CONTAINER_HPP
#define LAB3_BASE_CONTAINER_HPP

#include <sequences/Sequence.hpp>
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

} // kogan

#endif //LAB3_BASE_CONTAINER_HPP
