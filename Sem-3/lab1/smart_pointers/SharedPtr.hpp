#ifndef LAB1_SHARED_PTR_HPP
#define LAB1_SHARED_PTR_HPP

#include <utility>

namespace kogan {

template <class T>
class SharedPtr {
   private:
    T* ptr_;
    unsigned int* reference_counter_;

    void decrement_counter_and_delete_ptr_if_zero();

   public:
    SharedPtr() noexcept;                        // default constructor
    explicit SharedPtr(T* ptr) noexcept;         // constructor from pointer
    SharedPtr(const SharedPtr& other) noexcept;  // copy constructor
    SharedPtr(SharedPtr&& other) noexcept;       // move constructor

    ~SharedPtr();

    explicit operator bool() const noexcept;  // check if pointer is not null
    T* get() const noexcept;                  // get pointer
    T* operator->() const noexcept;           // get pointer and use operator ->
    T& operator*() const noexcept;            // get reference
    unsigned int use_count() const noexcept;  // get reference counter

    SharedPtr& operator=(const SharedPtr& other) noexcept {  // copy assignment
        if (this != &other) {
            decrement_counter_and_delete_ptr_if_zero();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            if (ptr_ != nullptr) ++(*reference_counter_);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {  // move assignment
        if (this != &other) {
            decrement_counter_and_delete_ptr_if_zero();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            other.ptr_ = nullptr;
            other.reference_counter_ = nullptr;
        }
        return *this;
    }

    SharedPtr& operator=(T* ptr) noexcept {  // assignment from pointer
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = ptr;
        if (ptr_ == nullptr)
            reference_counter_ = nullptr;
        else
            reference_counter_ = new unsigned int(1);
        return *this;
    }

    friend bool operator==(const SharedPtr& lhs, const SharedPtr& rhs) noexcept { return lhs.ptr_ == rhs.ptr_; }
    friend bool operator!=(const SharedPtr& lhs, const SharedPtr& rhs) noexcept { return !(lhs == rhs); }
    friend bool operator==(const SharedPtr& lhs, std::nullptr_t) noexcept { return lhs.ptr_ == nullptr; }
    friend bool operator==(std::nullptr_t, const SharedPtr& rhs) noexcept { return rhs.ptr_ == nullptr; }
    friend bool operator!=(const SharedPtr& lhs, std::nullptr_t) noexcept { return !(lhs == nullptr); }
    friend bool operator!=(std::nullptr_t, const SharedPtr& rhs) noexcept { return !(nullptr == rhs); }
};

template <class T>
class SharedPtr<T[]> {  // specialization for arrays
   private:
    T* ptr_;
    unsigned int* reference_counter_;

    void decrement_counter_and_delete_ptr_if_zero();

   public:
    SharedPtr() noexcept;                        // default constructor
    explicit SharedPtr(T* ptr) noexcept;         // constructor from pointer
    SharedPtr(const SharedPtr& other) noexcept;  // copy constructor
    SharedPtr(SharedPtr&& other) noexcept;       // move constructor

    ~SharedPtr();

    explicit operator bool() const noexcept;  // check if pointer is not null
    T* get() const noexcept;                  // get pointer
    T* operator->() const noexcept;           // get pointer and use operator ->
    T& operator*() const noexcept;            // get reference
    T& operator[](std::size_t index) const;   // array subscript operator
    unsigned int use_count() const noexcept;  // get reference counter

    SharedPtr& operator=(const SharedPtr& other) noexcept {  // copy assignment
        if (this != &other) {
            decrement_counter_and_delete_ptr_if_zero();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            if (ptr_ != nullptr) ++(*reference_counter_);
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {  // move assignment
        if (this != &other) {
            decrement_counter_and_delete_ptr_if_zero();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            other.ptr_ = nullptr;
            other.reference_counter_ = nullptr;
        }
        return *this;
    }

    SharedPtr& operator=(T* ptr) noexcept {  // assignment from pointer
        decrement_counter_and_delete_ptr_if_zero();
        ptr_ = ptr;
        if (ptr_ == nullptr)
            reference_counter_ = nullptr;
        else
            reference_counter_ = new unsigned int(1);
        return *this;
    }

    friend bool operator==(const SharedPtr& lhs, const SharedPtr& rhs) noexcept { return lhs.ptr_ == rhs.ptr_; }
    friend bool operator!=(const SharedPtr& lhs, const SharedPtr& rhs) noexcept { return !(lhs == rhs); }
    friend bool operator==(const SharedPtr& lhs, std::nullptr_t) noexcept { return lhs.ptr_ == nullptr; }
    friend bool operator==(std::nullptr_t, const SharedPtr& rhs) noexcept { return rhs.ptr_ == nullptr; }
    friend bool operator!=(const SharedPtr& lhs, std::nullptr_t) noexcept { return !(lhs == nullptr); }
    friend bool operator!=(std::nullptr_t, const SharedPtr& rhs) noexcept { return !(nullptr == rhs); }
};

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
inline SharedPtr<T>::operator bool() const noexcept {
    return static_cast<bool>(ptr_);
}

template <class T>
inline SharedPtr<T[]>::operator bool() const noexcept {
    return static_cast<bool>(ptr_);
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
inline T* SharedPtr<T[]>::operator->() const noexcept {
    return ptr_;
}

template <class T>
inline T& SharedPtr<T>::operator*() const noexcept {
    return *ptr_;
}

template <class T>
inline T& SharedPtr<T[]>::operator*() const noexcept {
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