//
// Created by Gregory Kogan on 21.05.2023.
//

#ifndef LAB4_NARY_TREE_HPP
#define LAB4_NARY_TREE_HPP

#include <limits>
#include <sequences/ArraySequence.hpp>
#include <containers/queue/queue.hpp>


namespace kogan {

    template <class T> class NaryTree {
        T data;
        int max_children;
        Sequence<NaryTree<T>*>* children;

    public:
        NaryTree(T root_value, int max_children);

        ~NaryTree();

        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t children_count() const;
        [[nodiscard]] size_t max_children_count() const;
        T get_data() const;

        void add_child(T child);
        NaryTree<T>* get_child(int index) const;

        NaryTree<T>& operator[](int index);
    };

    template<class T>
    NaryTree<T>::NaryTree(T root_value, int max_children): max_children(max_children) {
        if (max_children < 1)
            throw InvalidArgumentException("max_children");

        children = new LinkedListSequence<NaryTree<T>*>;
        data = root_value;
    }

    template<class T>
    NaryTree<T>::~NaryTree() {
        for (int i = 0; i < children->get_length(); ++i)
            delete children->get(i);
        delete children;
    }

    template<class T>
    size_t NaryTree<T>::size() const {
        size_t result = 1;
        for (int i = 0; i < children->get_length(); ++i)
            result += children->get(i)->size();
        return result;
    }

    template<class T>
    size_t NaryTree<T>::children_count() const {
        return children->get_length();
    }

    template<class T>
    size_t NaryTree<T>::max_children_count() const {
        return (size_t)max_children;
    }

    template<class T>
    T NaryTree<T>::get_data() const {
        return data;
    }

    template<class T>
    void NaryTree<T>::add_child(T child) {
        if (children->get_length() == max_children)
            throw kogan::IndexOutOfRangeException(max_children + 1, 0, max_children);

        children->append(new NaryTree<T>(child, max_children));
    }

    template<class T>
    NaryTree<T>* NaryTree<T>::get_child(int index) const {
        return children->get(index);
    }

    template<class T>
    NaryTree<T>& NaryTree<T>::operator[](int index) {
        return *(children->operator[](index));
    }

} // kogan

#endif //LAB4_NARY_TREE_HPP
