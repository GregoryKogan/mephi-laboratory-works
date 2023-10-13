#ifndef LAB1_CONTROL_BLOCK_HPP
#define LAB1_CONTROL_BLOCK_HPP

#include "../../exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp"

namespace kogan {

template <class T>
class ControlBlock {
   private:
    T* ptr_;
    unsigned int reference_counter_;
    unsigned int weak_ptr_reference_counter_;

   public:
    explicit ControlBlock(T* ptr) noexcept;  // constructor from pointer

    void increment_reference_counter() noexcept;
    void decrement_reference_counter_and_delete_ptr_if_zero();
    void increment_weak_ptr_reference_counter() noexcept;
    void decrement_weak_ptr_reference_counter_and_delete_ptr_if_zero();

    T* get() const noexcept;
    unsigned int get_reference_counter() const noexcept;
    unsigned int get_weak_ptr_reference_counter() const noexcept;
};

template <class T>
class ControlBlock<T[]> {  // specialization for arrays
   private:
    T* ptr_;
    unsigned int reference_counter_;
    unsigned int weak_ptr_reference_counter_;

   public:
    explicit ControlBlock(T* ptr) noexcept;

    void increment_reference_counter() noexcept;
    void decrement_reference_counter_and_delete_ptr_if_zero();
    void increment_weak_ptr_reference_counter() noexcept;
    void decrement_weak_ptr_reference_counter_and_delete_ptr_if_zero();

    T* get() const noexcept;
    unsigned int get_reference_counter() const noexcept;
    unsigned int get_weak_ptr_reference_counter() const noexcept;
};

}  // namespace kogan

#include "ControlBlock.hh"

#endif