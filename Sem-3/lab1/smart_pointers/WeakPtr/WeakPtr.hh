#ifndef LAB1_WEAK_PTR_INC
#define LAB1_WEAK_PTR_INC

#include "WeakPtr.hpp"

namespace kogan {

template <class T>
inline WeakPtr<T>::WeakPtr() noexcept : ptr_(nullptr), reference_counter_(nullptr) {}  // default constructor

template <class T>
inline WeakPtr<T>::WeakPtr(const WeakPtr& other) noexcept  // copy constructor
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {}

template <class T>
inline WeakPtr<T>::WeakPtr(const SharedPtr<T>& other) noexcept  // constructor from SharedPtr
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {}

template <class T>
inline WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept  // move constructor
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {
    other.ptr_ = nullptr;
    other.reference_counter_ = nullptr;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other) noexcept {
    if (this != &other) {
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
    }
    return *this;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
    if (this != &other) {
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
    }
    return *this;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept {
    if (this != &other) {
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
        other.ptr_ = nullptr;
        other.reference_counter_ = nullptr;
    }
    return *this;
}

template <class T>
inline void WeakPtr<T>::reset() noexcept {
    ptr_ = nullptr;
    reference_counter_ = nullptr;
}

template <class T>
inline void WeakPtr<T>::swap(WeakPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(reference_counter_, other.reference_counter_);
}

template <class T>
inline unsigned int WeakPtr<T>::use_count() const noexcept {
    if (reference_counter_ == nullptr) return 0;
    return *reference_counter_;
}

template <class T>
inline bool WeakPtr<T>::expired() const noexcept {
    return use_count() == 0;
}

template <class T>
inline SharedPtr<T> WeakPtr<T>::lock() const noexcept {
    return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
}

}  // namespace kogan

#endif