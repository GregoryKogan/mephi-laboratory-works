//
// Created by Gregory Kogan on 20.05.2023.
//

#ifndef LAB3_I_ENUMERABLE_HPP
#define LAB3_I_ENUMERABLE_HPP

#include <sequences/Sequence.hpp>
#include "i_enumerator.hpp"

namespace kogan {

    template <class T> class IEnumerable {
    protected:
        Sequence<T>* sequence;

    public:
        ~IEnumerable();

        IEnumerator<T> begin() const;
        IEnumerator<T> end() const;
    };

    template<class T>
    IEnumerable<T>::~IEnumerable() {
        delete sequence;
    }

    template<class T>
    IEnumerator<T> IEnumerable<T>::begin() const {
        return IEnumerator<T>(sequence, 0);
    }

    template<class T>
    IEnumerator<T> IEnumerable<T>::end() const {
        return IEnumerator<T>(sequence, sequence->get_length());
    }

} // kogan

#endif //LAB3_I_ENUMERABLE_HPP
