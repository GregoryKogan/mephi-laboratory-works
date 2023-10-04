#ifndef LAB1_SHARED_PTR_HPP
#define LAB1_SHARED_PTR_HPP

namespace kogan {

template <class T>
class SharedPtr {
   private:
    T* ptr_;
    unsigned int* reference_counter_;

    void decrease_counter();  // decrease counter and delete pointer if counter is zero

   public:
    SharedPtr() noexcept : ptr_(nullptr), reference_counter_(new unsigned int(0)) {}  // default constructor
    explicit SharedPtr(T* ptr) noexcept
        : ptr_(ptr), reference_counter_(new unsigned int(1)) {}  // constructor from pointer
    SharedPtr(const SharedPtr& other) noexcept : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {
        if (ptr_ != nullptr) ++(*reference_counter_);
    }  // copy constructor
    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), reference_counter_(other.reference_counter_) {
        other.ptr_ = nullptr;
        other.reference_counter_ = nullptr;
    }  // move constructor

    SharedPtr& operator=(const SharedPtr& other) noexcept {  // copy assignment
        if (this != &other) {
            decrease_counter();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            if (ptr_ != nullptr) ++(*reference_counter_);
        }
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& other) noexcept {  // move assignment
        if (this != &other) {
            decrease_counter();
            ptr_ = other.ptr_;
            reference_counter_ = other.reference_counter_;
            other.ptr_ = nullptr;
            other.reference_counter_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr() { decrease_counter(); }

    explicit operator bool() const noexcept { return static_cast<bool>(ptr_); }  // check if pointer is not null
    T* get() const noexcept { return ptr_; }                                     // get pointer
    T* operator->() const noexcept { return ptr_; }                              // get pointer and use operator ->
    T& operator*() const noexcept { return *ptr_; }                              // get reference
    unsigned int use_count() const noexcept {
        if (reference_counter_ == nullptr) return 0;
        return *reference_counter_;
    }  // get reference counter
};

template <class T>
inline void SharedPtr<T>::decrease_counter() {
    if (reference_counter_ == nullptr) return;
    --(*reference_counter_);
    if (*reference_counter_ == 0) {
        if (ptr_ != nullptr) delete ptr_;
        delete reference_counter_;
    }
}

}  // namespace kogan

#endif