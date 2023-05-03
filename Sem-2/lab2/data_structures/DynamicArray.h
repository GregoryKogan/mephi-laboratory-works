//
// Created by Gregory Kogan on 02.05.2023.
//

#ifndef LAB2_DYNAMICARRAY_H
#define LAB2_DYNAMICARRAY_H

#include "../exceptions/Exception.h"

namespace kogan {

    template <class T> class DynamicArray {
        size_t length;
        T* data;

    public:
        DynamicArray(T* items, size_t count);
        explicit DynamicArray(size_t size);
        DynamicArray(const DynamicArray<T> &dynamicArray);

        ~DynamicArray();

        T get(int index) const;
        [[nodiscard]] size_t get_length() const;

        void set(int index, T value);
        void resize(int new_size);
    };


    template<class T>
    DynamicArray<T>::DynamicArray(T* items, size_t count) {
        length = count;
        data = new T[length];

        for (size_t i = 0; i < count; ++i)
            data[i] = items[i];
    }

    template<class T>
    DynamicArray<T>::DynamicArray(size_t size) {
        length = size;
        data = new T[length];
    }

    template<class T>
    DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray) {
        length = dynamicArray.get_length();
        data = new T[length];

        for (size_t i = 0; i < length; ++i)
            data[i] = dynamicArray.get(i);
    }

    template<class T>
    DynamicArray<T>::~DynamicArray() {
        delete [] data;
    }

    template<class T>
    T DynamicArray<T>::get(int index) const {
        if (index < 0 || index >= length)
            throw Exception(
                    ExceptionType::IndexOutOfRange,
                    "Index " + std::to_string(index) + " is out of range: [0, " + std::to_string(length) + ")"
            );
        return data[index];
    }

    template<class T>
    size_t DynamicArray<T>::get_length() const {
        return length;
    }

    template<class T>
    void DynamicArray<T>::set(int index, T value) {
        if (index < 0 || index >= length)
            throw Exception(
                    ExceptionType::IndexOutOfRange,
                    "Index " + std::to_string(index) + " is out of range: [0, " + std::to_string(length) + ")"
            );
        data[index] = value;
    }

    template<class T>
    void DynamicArray<T>::resize(int new_size) {
        if (new_size < 0)
            throw Exception(
                    ExceptionType::InvalidSize,
                    "Size " + std::to_string(new_size) + " is invalid. Size could not be less than 0"
            );

        T* new_data = new T[new_size];
        for (size_t i = 0; i < length && i < new_size; ++i) {
            new_data[i] = data[i];
        }

        delete [] data;
        data = new_data;
        length = new_size;
    }

} // kogan

#endif //LAB2_DYNAMICARRAY_H
