#ifndef LAB1_UNIQUE_PTR_HPP
#define LAB1_UNIQUE_PTR_HPP

#include <utility>

namespace kogan {

template <class T>
class UniquePtr {
   private:
    T* ptr_;

   public:
    UniquePtr() noexcept : ptr_(nullptr) {}                           // default constructor
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}                // constructor from pointer
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.release()) {}  // move constructor

    UniquePtr& operator=(UniquePtr&& other) noexcept {  // move assignment
        if (this != &other) reset(other.release());
        return *this;
    }

    UniquePtr(const UniquePtr&) = delete;             // copy constructor is deleted
    UniquePtr& operator=(const UniquePtr&) = delete;  // copy assignment is deleted

    ~UniquePtr() {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
    }

    T* release() noexcept;                    // release ownership
    void reset(T* ptr = nullptr) noexcept;    // delete old and set new pointer
    explicit operator bool() const noexcept;  // check if pointer is not null
    T* get() const noexcept;                  // get pointer
    T* operator->() const noexcept;           // get pointer and use operator ->
    T& operator*() const noexcept;            // get reference
};

template <class T, class... Args>
UniquePtr<T> make_unique(Args&&... args) {  // creates new object and returns unique pointer to it
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
inline T* UniquePtr<T>::release() noexcept {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template <class T>
inline void UniquePtr<T>::reset(T* ptr) noexcept {
    if (ptr_ != nullptr) {
        delete ptr_;
    }
    ptr_ = ptr;
}

template <class T>
inline UniquePtr<T>::operator bool() const noexcept {
    return static_cast<bool>(ptr_);
}

template <class T>
inline T* UniquePtr<T>::get() const noexcept {
    return ptr_;
}

template <class T>
inline T* UniquePtr<T>::operator->() const noexcept {
    return ptr_;
}

template <class T>
inline T& UniquePtr<T>::operator*() const noexcept {
    return *ptr_;
}

}  // namespace kogan

#endif