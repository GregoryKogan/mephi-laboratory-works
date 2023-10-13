#include "ControlBlock.hpp"
#ifndef LAB1_CONTROL_BLOCK_HH
#define LAB1_CONTROL_BLOCK_HH

namespace kogan {

template <class T>
inline ControlBlock<T>::ControlBlock(T* ptr) noexcept {  // constructor from pointer
    ptr_ = ptr;
    if (ptr_ != nullptr) {
        reference_counter_ = 1;
    } else {
        reference_counter_ = 0;
    }
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline ControlBlock<T[]>::ControlBlock(T* ptr) noexcept {  // constructor from pointer for arrays
    ptr_ = ptr;
    if (ptr_ != nullptr) {
        reference_counter_ = 1;
    } else {
        reference_counter_ = 0;
    }
    weak_ptr_reference_counter_ = 0;
}

template <class T>
inline void ControlBlock<T>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_reference_counter() noexcept {
    ++reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_reference_counter_and_delete_ptr_if_zero() {
    if (reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --reference_counter_;
    if (reference_counter_ == 0) {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        };
        if (weak_ptr_reference_counter_ == 0) delete this;
    }
}

template <class T>
inline void ControlBlock<T[]>::decrement_reference_counter_and_delete_ptr_if_zero() {
    if (reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) {
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }
        delete this;
    }
}

template <class T>
inline void ControlBlock<T>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T[]>::increment_weak_ptr_reference_counter() noexcept {
    ++weak_ptr_reference_counter_;
}

template <class T>
inline void ControlBlock<T>::decrement_weak_ptr_reference_counter_and_delete_ptr_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T[]>::decrement_weak_ptr_reference_counter_and_delete_ptr_if_zero() {
    if (weak_ptr_reference_counter_ == 0) throw ZeroReferenceDecrementException();

    --weak_ptr_reference_counter_;
    if (reference_counter_ + weak_ptr_reference_counter_ == 0) delete this;
}

template <class T>
inline void ControlBlock<T>::swap(ControlBlock<T>& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(reference_counter_, other.reference_counter_);
    std::swap(weak_ptr_reference_counter_, other.weak_ptr_reference_counter_);
}

template <class T>
inline void ControlBlock<T[]>::swap(ControlBlock<T[]>& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(reference_counter_, other.reference_counter_);
    std::swap(weak_ptr_reference_counter_, other.weak_ptr_reference_counter_);
}

template <class T>
inline T* ControlBlock<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T* ControlBlock<T[]>::get() const noexcept {
    return ptr_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_reference_counter() const noexcept {
    return reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}

template <class T>
inline unsigned int ControlBlock<T[]>::get_weak_ptr_reference_counter() const noexcept {
    return weak_ptr_reference_counter_;
}

}  // namespace kogan

#endif