//
// Created by Gregory Kogan on 20.05.2023.
//

#ifndef LAB3_I_ENUMERATOR_HPP
#define LAB3_I_ENUMERATOR_HPP

#include <sequences/Sequence.hpp>
#include <exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp>

namespace kogan {

    template <class T> class IEnumerator {
        Sequence<T>* sequence;
        int index;

    public:
        IEnumerator(Sequence<T>* sequence, int index);

        bool move_next();
        T& current() const;
        void reset();

        IEnumerator<T> operator++();
        bool operator!=(const IEnumerator& other) const;
        T& operator*() const;
    };

    template<class T>
    IEnumerator<T>::IEnumerator(Sequence<T> *sequence, int index) : sequence(sequence), index(index) {
        if (index < 0 || index > sequence->get_length())
            throw IndexOutOfRangeException(index, 0, sequence->get_length());
    }

    template<class T>
    bool IEnumerator<T>::move_next() {
        if (index < sequence->get_length())
            index++;

        return (index < sequence->get_length());
    }

    template<class T>
    T& IEnumerator<T>::current() const {
        return sequence->operator[](index);
    }

    template<class T>
    void IEnumerator<T>::reset() {
        index = 0;
    }

    template<class T>
    IEnumerator<T> IEnumerator<T>::operator++() {
        move_next();
        return *this;
    }

    template<class T>
    bool IEnumerator<T>::operator!=(const IEnumerator &other) const {
        return (index != other.index) || (sequence != other.sequence);
    }

    template<class T>
    T& IEnumerator<T>::operator*() const {
        return current();
    }

} // kogan

#endif //LAB3_I_ENUMERATOR_HPP
