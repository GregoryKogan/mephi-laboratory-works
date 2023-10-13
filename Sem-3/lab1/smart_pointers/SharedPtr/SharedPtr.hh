#ifndef LAB1_SHARED_PTR_INC
#define LAB1_SHARED_PTR_INC

#include "SharedPtr.hpp"

namespace kogan {

/* std::enable_if is a type trait used to enable or disable function templates based on the properties of their template
 * arguments. std::is_array is a type trait used to determine if a type is an array. std::remove_extent is a type trait
 * used to remove the extent (i.e., the array size) from an array type. std::forward is a utility function used to
 * forward arguments to another function. */

template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    Args&&... args) {  // make_shared for non-array types
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename std::enable_if<std::is_array<T>::value, SharedPtr<T>>::type make_shared(
    std::size_t size) {  // make_shared for array types
    return SharedPtr<T>(new typename std::remove_extent<T>::type[size]());
}

template <class T>
inline void SharedPtr<T>::decrement_counter_and_delete_ptr_if_zero() {
    if (reference_counter_ == nullptr) return;
    --(*reference_counter_);
    if (*reference_counter_ == 0) {
        delete reference_counter_;
        reference_counter_ = nullptr;
        if (ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }
    }
}

template <class T>
inline void SharedPtr<T[]>::decrement_counter_and_delete_ptr_if_zero() {
    if (reference_counter_ == nullptr) return;
    --(*reference_counter_);
    if (*reference_counter_ == 0) {
        delete reference_counter_;
        reference_counter_ = nullptr;
        if (ptr_ != nullptr) {
            delete[] ptr_;
            ptr_ = nullptr;
        }
    }
}

template <class T>
inline SharedPtr<T>::SharedPtr() noexcept : ptr_(nullptr), reference_counter_(nullptr) {}  // default constructor

template <class T>
inline SharedPtr<T[]>::SharedPtr() noexcept
    : ptr_(nullptr), reference_counter_(nullptr) {}  // default constructor for arrays

template <class T>
inline SharedPtr<T>::SharedPtr(T* ptr) noexcept
    : ptr_(ptr), reference_counter_(new unsigned int(1)) {}  // constructor from pointer

template <class T>
inline SharedPtr<T[]>::SharedPtr(T* ptr) noexcept
    : ptr_(ptr), reference_counter_(new unsigned int(1)) {}  // constructor from pointer for arrays

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {  // copy constructor
    if (ptr_ != nullptr) ++(*reference_counter_);
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(const SharedPtr& other) noexcept
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {  // copy constructor for arrays
    if (ptr_ != nullptr) ++(*reference_counter_);
}

template <class T>
inline SharedPtr<T>::SharedPtr(const WeakPtr<T>& other) noexcept {  // constructor from WeakPtr
    // TODO: throw exception if other.expired()
    // if (other.expired()) throw EmptyPointerException();
    if (other.expired()) return;
    ptr_ = other.ptr_;
    reference_counter_ = other.reference_counter_;
    if (ptr_ != nullptr) ++(*reference_counter_);
}

template <class T>
inline SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {  // move constructor
    other.ptr_ = nullptr;
    other.reference_counter_ = nullptr;
}

template <class T>
inline SharedPtr<T[]>::SharedPtr(SharedPtr&& other) noexcept
    : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {  // move constructor for arrays
    other.ptr_ = nullptr;
    other.reference_counter_ = nullptr;
}

template <class T>
inline SharedPtr<T>::~SharedPtr() {
    decrement_counter_and_delete_ptr_if_zero();
}

template <class T>
inline SharedPtr<T[]>::~SharedPtr() {
    decrement_counter_and_delete_ptr_if_zero();
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) noexcept {  // copy assignment
    if (this != &other) {
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
        if (ptr_ != nullptr) ++(*reference_counter_);
    }
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(const SharedPtr<T[]>& other) noexcept {  // copy assignment for arrays
    if (this != &other) {
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
        if (ptr_ != nullptr) ++(*reference_counter_);
    }
    return *this;
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {  // move assignment
    if (this != &other) {
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
        other.ptr_ = nullptr;
        other.reference_counter_ = nullptr;
    }
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(SharedPtr<T[]>&& other) noexcept {  // move assignment for arrays
    if (this != &other) {
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = other.ptr_;
        reference_counter_ = other.reference_counter_;
        other.ptr_ = nullptr;
        other.reference_counter_ = nullptr;
    }
    return *this;
}

template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr
    decrement_counter_and_delete_ptr_if_zero();
    ptr_ = nullptr;
    reference_counter_ = nullptr;
    return *this;
}

template <class T>
inline SharedPtr<T[]>& SharedPtr<T[]>::operator=(std::nullptr_t) noexcept {  // assignment from nullptr for arrays
    decrement_counter_and_delete_ptr_if_zero();
    ptr_ = nullptr;
    reference_counter_ = nullptr;
    return *this;
}

template <class T>
inline void SharedPtr<T>::reset(T* ptr) noexcept {
    decrement_counter_and_delete_ptr_if_zero();
    ptr_ = ptr;
    if (ptr_ == nullptr)
        reference_counter_ = nullptr;
    else
        reference_counter_ = new unsigned int(1);
}

template <class T>
inline void SharedPtr<T[]>::reset(T* ptr) noexcept {
    decrement_counter_and_delete_ptr_if_zero();
    ptr_ = ptr;
    if (ptr_ == nullptr)
        reference_counter_ = nullptr;
    else
        reference_counter_ = new unsigned int(1);
}

template <class T>
inline void SharedPtr<T>::swap(SharedPtr<T>& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(reference_counter_, other.reference_counter_);
}

template <class T>
inline void SharedPtr<T[]>::swap(SharedPtr<T[]>& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(reference_counter_, other.reference_counter_);
}

template <class T>
inline bool SharedPtr<T>::unique() const noexcept {
    return use_count() == 1;
}

template <class T>
inline bool SharedPtr<T[]>::unique() const noexcept {
    return use_count() == 1;
}

template <class T>
inline SharedPtr<T>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline SharedPtr<T[]>::operator bool() const noexcept {
    return get() != nullptr;
}

template <class T>
inline T* SharedPtr<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T* SharedPtr<T[]>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T* SharedPtr<T>::operator->() const noexcept {
    return ptr_;
}

template <class T>
inline T& SharedPtr<T>::operator*() const noexcept {
    return *ptr_;
}

template <class T>
inline T& SharedPtr<T[]>::operator[](std::size_t index) const {
    return ptr_[index];
}

template <class T>
inline unsigned int SharedPtr<T>::use_count() const noexcept {
    if (reference_counter_ == nullptr) return 0;
    return *reference_counter_;
}

template <class T>
inline unsigned int SharedPtr<T[]>::use_count() const noexcept {
    if (reference_counter_ == nullptr) return 0;
    return *reference_counter_;
}

}  // namespace kogan

#endif