#ifndef LAB1_SMART_PTR_LINKED_LIST_HPP
#define LAB1_SMART_PTR_LINKED_LIST_HPP

#include "../smart_pointers/SharedPtr.hpp"
#include "exception_lib.hpp"

namespace kogan {

template <class T>
class SmartPtrLinkedList {
   private:
    typedef struct Node {
        T data;
        SharedPtr<Node> next;
        SharedPtr<Node> prev;
    } Node;

    typedef struct Root {
        SharedPtr<Node> head;
        SharedPtr<Node> tail;
    } Root;

    SharedPtr<Root> root_;
    std::size_t length_;

    SharedPtr<Node> get_node(int index) const;

   public:
    SmartPtrLinkedList();
    SmartPtrLinkedList(SharedPtr<T[]> data, int length);
    SmartPtrLinkedList(const SmartPtrLinkedList<T>& other);

    T get(int index) const;
    T get_first() const;
    T get_last() const;
    [[nodiscard]] std::size_t get_length() const noexcept;

    void set(int index, T value);
    void append(T value) noexcept;
    void prepend(T value) noexcept;
    void insert(int index, T value);
    void remove(int index);
    void clear() noexcept;

    SmartPtrLinkedList<T> get_sublist(int start_index, int end_index) const;
    SmartPtrLinkedList<T> concat(const SmartPtrLinkedList<T>& other) const;

    T& operator[](int index);
};

template <class T>
inline SharedPtr<typename SmartPtrLinkedList<T>::Node> SmartPtrLinkedList<T>::get_node(int index) const {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);

    if (index < length_ / 2) {  // search from head
        auto cur_node = root_->head;
        for (std::size_t i = 0; i < index; ++i) cur_node = cur_node->next;
        return cur_node;
    } else {  // search from tail
        auto cur_node = root_->tail;
        for (std::size_t i = length_ - 1; i > index; --i) cur_node = cur_node->prev;
        return cur_node;
    }
}

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList() {
    root_ = make_shared<Root>();
    root_->head = nullptr;
    root_->tail = nullptr;
    length_ = 0;
}

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList(SharedPtr<T[]> data, int length) {
    if (length < 0) throw InvalidArgumentException("length must be positive");

    length_ = length;
    root_ = make_shared<Root>();

    if (length_ == 0) {
        root_->head = nullptr;
        root_->tail = nullptr;
        return;
    }

    auto cur_node = make_shared<Node>();
    cur_node->data = data[0];
    cur_node->prev = nullptr;
    cur_node->next = nullptr;
    root_->head = cur_node;
    root_->tail = cur_node;

    for (std::size_t i = 1; i < length_; ++i) {
        auto new_node = make_shared<Node>();
        new_node->data = data[i];
        new_node->prev = cur_node;
        new_node->next = nullptr;
        cur_node->next = new_node;
        cur_node = new_node;
        root_->tail = cur_node;
    }
}

template <class T>
inline SmartPtrLinkedList<T>::SmartPtrLinkedList(const SmartPtrLinkedList<T>& other) {
    length_ = other.length_;
    root_ = make_shared<Root>();

    if (length_ == 0) {
        root_->head = nullptr;
        root_->tail = nullptr;
        return;
    }

    auto cur_node = make_shared<Node>();
    auto cur_other_node = other.root_->head;
    cur_node->data = cur_other_node->data;
    cur_node->prev = nullptr;
    root_->head = cur_node;
    root_->tail = cur_node;

    while (cur_other_node->next != nullptr) {
        cur_other_node = cur_other_node->next;
        auto new_node = make_shared<Node>();
        new_node->data = cur_other_node->data;
        new_node->prev = cur_node;
        new_node->next = nullptr;
        cur_node->next = new_node;
        cur_node = new_node;
        root_->tail = cur_node;
    }
}

template <class T>
inline T SmartPtrLinkedList<T>::get(int index) const {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    return get_node(index)->data;
}

template <class T>
inline T SmartPtrLinkedList<T>::get_first() const {
    if (length_ == 0) throw EmptyContainerException();
    return root_->head->data;
}

template <class T>
inline T SmartPtrLinkedList<T>::get_last() const {
    if (length_ == 0) throw EmptyContainerException();
    return root_->tail->data;
}

template <class T>
inline std::size_t SmartPtrLinkedList<T>::get_length() const noexcept {
    return length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::set(int index, T value) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    get_node(index)->data = value;
}

template <class T>
inline void SmartPtrLinkedList<T>::append(T value) noexcept {
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = root_->tail;
    new_node->next = nullptr;
    if (length_ == 0) {
        root_->head = new_node;
        root_->tail = new_node;
    } else {
        root_->tail->next = new_node;
        root_->tail = new_node;
    }
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::prepend(T value) noexcept {
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = nullptr;
    new_node->next = root_->head;
    if (length_ == 0) {
        root_->head = new_node;
        root_->tail = new_node;
    } else {
        root_->head->prev = new_node;
        root_->head = new_node;
    }
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::insert(int index, T value) {
    if (index < 0 || index > length_) throw IndexOutOfRangeException(index, 0, length_);

    if (index == 0) {
        prepend(value);
        return;
    }
    if (index == length_) {
        append(value);
        return;
    }

    auto cur_node = get_node(index);
    auto new_node = make_shared<Node>();
    new_node->data = value;
    new_node->prev = cur_node->prev;
    new_node->next = cur_node;
    cur_node->prev->next = new_node;
    cur_node->prev = new_node;
    ++length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::remove(int index) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);

    if (index == 0) {
        root_->head = root_->head->next;
        if (root_->head != nullptr) root_->head->prev = nullptr;
        --length_;
        return;
    }
    if (index == length_ - 1) {
        root_->tail = root_->tail->prev;
        if (root_->tail != nullptr) root_->tail->next = nullptr;
        --length_;
        return;
    }

    auto cur_node = get_node(index);
    cur_node->prev->next = cur_node->next;
    cur_node->next->prev = cur_node->prev;
    --length_;
}

template <class T>
inline void SmartPtrLinkedList<T>::clear() noexcept {
    root_->head = nullptr;
    root_->tail = nullptr;
    length_ = 0;
}

template <class T>
inline SmartPtrLinkedList<T> SmartPtrLinkedList<T>::get_sublist(int start_index, int end_index) const {
    if (start_index < 0 || start_index >= length_) throw IndexOutOfRangeException(start_index, 0, length_ - 1);
    if (end_index < 0 || end_index >= length_) throw IndexOutOfRangeException(end_index, 0, length_ - 1);
    if (start_index > end_index) throw InvalidArgumentException("start_index must be less than or equal to end_index");

    auto new_list = SmartPtrLinkedList<T>();
    for (std::size_t i = start_index; i <= end_index; ++i) new_list.append(get_node(i)->data);
    return new_list;
}

template <class T>
inline SmartPtrLinkedList<T> SmartPtrLinkedList<T>::concat(const SmartPtrLinkedList<T>& other) const {
    auto new_list = SmartPtrLinkedList<T>(*this);
    for (std::size_t i = 0; i < other.length_; ++i) new_list.append(other.get_node(i)->data);
    return new_list;
}

template <class T>
inline T& SmartPtrLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= length_) throw IndexOutOfRangeException(index, 0, length_ - 1);
    return get_node(index)->data;
}

}  // namespace kogan

#endif