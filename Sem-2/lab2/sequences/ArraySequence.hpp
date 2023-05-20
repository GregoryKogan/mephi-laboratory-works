//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "Sequence.hpp"
#include "../data_structures/DynamicArray.hpp"

namespace kogan {

    template <class T> class ArraySequence: public Sequence<T> {
        DynamicArray<T>* array;

    public:
        ArraySequence(T* items, int count);
        ArraySequence();
        ArraySequence(const ArraySequence<T> &arraySequence);

        ~ArraySequence() override;

        T get_first() const override;
        T get_last() const override;
        T get(int index) const override;
        Sequence<T>* get_subsequence(int start_index, int end_index) const override;
        [[nodiscard]] size_t get_length() const override;

        void set(int index, T item) override;
        void append(T item) override;
        void prepend(T item) override;
        void insert(int index, T item) override;
        Sequence<T>* concat(Sequence<T>* sequence) override;
        void clear() override;
        void remove(int index) override;

        T& operator[](int index) override;
    };

    template<class T>
    ArraySequence<T>::ArraySequence(T *items, int count) {
        array = new DynamicArray<T>(items, count);
    }

    template<class T>
    ArraySequence<T>::ArraySequence() {
        array = new DynamicArray<T>(0);
    }

    template<class T>
    ArraySequence<T>::ArraySequence(const ArraySequence<T> &arraySequence) {
        array = new DynamicArray<T>(*arraySequence.array);
    }

    template<class T>
    ArraySequence<T>::~ArraySequence() {
        delete array;
    }

    template<class T>
    T ArraySequence<T>::get_first() const {
        return get(0);
    }

    template<class T>
    T ArraySequence<T>::get_last() const {
        return get(get_length() - 1);
    }

    template<class T>
    T ArraySequence<T>::get(int index) const {
        return array->get(index);
    }

    template<class T>
    Sequence<T>* ArraySequence<T>::get_subsequence(int start_index, int end_index) const {
        if (start_index < 0 || start_index >= get_length())
            throw IndexOutOfRangeException(start_index, 0, get_length() - 1);

        if (end_index < 0 || end_index >= get_length())
            throw IndexOutOfRangeException(end_index, 0, get_length() - 1);

        if (end_index < start_index)
            throw InvalidArgumentException("end_index");

        auto sub_seq = new ArraySequence<T>;
        for (int i = start_index; i <= end_index; ++i)
            sub_seq->append(get(i));
        return sub_seq;
    }

    template<class T>
    size_t ArraySequence<T>::get_length() const {
        return array->get_length();
    }

    template<class T>
    void ArraySequence<T>::set(int index, T item) {
        array->set(index, item);
    }

    template<class T>
    void ArraySequence<T>::append(T item) {
        array->resize(get_length() + 1);
        set(get_length() - 1, item);
    }

    template<class T>
    void ArraySequence<T>::prepend(T item) {
        array->resize(get_length() + 1);
        for (int i = get_length() - 1; i > 0; --i)
            set(i, get(i - 1));
        set(0, item);
    }

    template<class T>
    void ArraySequence<T>::insert(int index, T item) {
        if (index < 0 || index > get_length())
            throw IndexOutOfRangeException(index, 0, get_length());

        if (index == 0)
            prepend(item);
        else if (index == get_length())
            append(item);
        else {
            array->resize(get_length() + 1);
            for (int i = get_length() - 1; i > index; --i)
                set(i, get(i - 1));
            set(index, item);
        }
    }

    template<class T>
    Sequence<T> *ArraySequence<T>::concat(Sequence<T> *sequence) {
        auto concatenation = new ArraySequence<T>(*this);
        for (int i = 0; i < sequence->get_length(); ++i)
            concatenation->append(sequence->get(i));
        return concatenation;
    }

    template<class T>
    void ArraySequence<T>::clear() {
        array->resize(0);
    }

    template<class T>
    void ArraySequence<T>::remove(int index) {
        if (index < 0 || index >= get_length())
            throw IndexOutOfRangeException(index, 0, get_length() - 1);

        for (int i = index; i < get_length() - 1; ++i)
            set(i, get(i + 1));
        array->resize(get_length() - 1);
    }

    template<class T>
    T &ArraySequence<T>::operator[](int index) {
        return array->operator[](index);
    }

} // kogan

#endif //LAB2_ARRAYSEQUENCE_H
