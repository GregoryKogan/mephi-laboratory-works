#ifndef LAB1_WEAK_PTR_INC
#define LAB1_WEAK_PTR_INC

#include "WeakPtr.hpp"

namespace kogan {

template <class T>
inline WeakPtr<T>::WeakPtr() noexcept : control_block_(nullptr) {}  // default constructor

template <class T>
inline WeakPtr<T>::WeakPtr(const WeakPtr& other) noexcept  // copy constructor
    : control_block_(other.control_block_) {
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_weak_ptr_reference_counter();
}

template <class T>
inline WeakPtr<T>::WeakPtr(const SharedPtr<T>& other) noexcept  // constructor from SharedPtr
    : control_block_(other.control_block_) {
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_weak_ptr_reference_counter();
}

template <class T>
inline WeakPtr<T>::WeakPtr(WeakPtr&& other) noexcept  // move constructor
    : control_block_(other.control_block_) {
    other.control_block_ = nullptr;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other) noexcept {
    if (this != &other) {
        if (control_block_) control_block_->decrement_weak_ptr_reference_counter_and_delete_if_zero();
        control_block_ = other.control_block_;
        if (control_block_ && control_block_->get() != nullptr) control_block_->increment_weak_ptr_reference_counter();
    }
    return *this;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
    if (control_block_) control_block_->decrement_weak_ptr_reference_counter_and_delete_if_zero();
    control_block_ = other.control_block_;
    if (control_block_ && control_block_->get() != nullptr) control_block_->increment_weak_ptr_reference_counter();
    return *this;
}

template <class T>
inline WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept {
    if (this != &other) {
        if (control_block_) control_block_->decrement_weak_ptr_reference_counter_and_delete_if_zero();
        control_block_ = other.control_block_;
        other.control_block_ = nullptr;
    }
    return *this;
}

template <class T>
inline void WeakPtr<T>::reset() noexcept {
    if (control_block_) control_block_->decrement_weak_ptr_reference_counter_and_delete_if_zero();
    control_block_ = nullptr;
}

template <class T>
inline void WeakPtr<T>::swap(WeakPtr& other) noexcept {
    std::swap(control_block_, other.control_block_);
}

template <class T>
inline unsigned int WeakPtr<T>::use_count() const noexcept {
    return control_block_ ? control_block_->get_reference_counter() : 0;
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