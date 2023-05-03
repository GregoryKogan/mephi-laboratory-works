//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <string>

namespace kogan {

    template <class T> class Sequence {

    public:
        virtual T get_first() = 0;
        virtual T get_last() = 0;
        virtual T get(int index) = 0;
        virtual Sequence<T>* get_subsequence(int start_index, int end_index) = 0;
        virtual size_t get_length() = 0;

        virtual void set(int index, T item) = 0;
        virtual void append(T item) = 0;
        virtual void prepend(T item) = 0;
        virtual void insert(T item, int index) = 0;

        virtual std::string to_string() = 0;
    };

} // kogan

#endif //LAB2_SEQUENCE_H
