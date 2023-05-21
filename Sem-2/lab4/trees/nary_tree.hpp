//
// Created by Gregory Kogan on 21.05.2023.
//

#ifndef LAB4_NARY_TREE_HPP
#define LAB4_NARY_TREE_HPP

#include <limits>
#include <sequences/ArraySequence.hpp>
#include <containers/stack/stack.hpp>


namespace kogan {

    template <class T> class NaryTree {
        T data;
        int max_children;
        Sequence<NaryTree<T>*>* children;

        Sequence<T>* traverse_root_left_right() const;
        Sequence<T>* traverse_root_right_left() const;
        Sequence<T>* traverse_left_right_root() const;
        Sequence<T>* traverse_right_left_root() const;

    public:
        enum TraverseType {
            ROOT_LEFT_RIGHT,
            ROOT_RIGHT_LEFT,
            LEFT_RIGHT_ROOT,
            RIGHT_LEFT_ROOT,
        };

    public:
        NaryTree(T root_value, int max_children);
        explicit NaryTree(T root_value);

        ~NaryTree();

        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t children_count() const;
        [[nodiscard]] size_t max_children_count() const;
        T get_data() const;
        void set_data(T new_data);

        void add_child(T child);
        NaryTree<T>* get_child(int index) const;

        Sequence<T>* traverse() const;
        Sequence<T>* traverse(TraverseType traverse_type) const;

        NaryTree<T>& operator[](int index);
    };

    template<class T>
    NaryTree<T>::NaryTree(T root_value): NaryTree(root_value, std::numeric_limits<int>::max()) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

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
    void NaryTree<T>::set_data(T new_data) {
        data = new_data;
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
    Sequence<T> *NaryTree<T>::traverse() const {
        return traverse(ROOT_LEFT_RIGHT);
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse(NaryTree::TraverseType traverse_type) const {
        switch (traverse_type) {
            case ROOT_LEFT_RIGHT:
                return traverse_root_left_right();
            case ROOT_RIGHT_LEFT:
                return traverse_root_right_left();
            case LEFT_RIGHT_ROOT:
                return traverse_left_right_root();
            case RIGHT_LEFT_ROOT:
                return traverse_right_left_root();
            default:
                throw InvalidArgumentException("traverse_type");
        }
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_root_left_right() const {
        Sequence<T>* result = new LinkedListSequence<T>;
        Stack<const NaryTree<T>*> stack;
        stack.push(this);

        while (!stack.empty()) {
            const NaryTree<T>* current = stack.pop();
            result->append(current->get_data());

            for (int i = current->children_count() - 1; i >= 0; --i)
                stack.push(current->get_child(i));
        }

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_root_right_left() const {
        Sequence<T>* result = new LinkedListSequence<T>;
        Stack<const NaryTree<T>*> stack;
        stack.push(this);

        while (!stack.empty()) {
            const NaryTree<T>* current = stack.pop();
            result->append(current->get_data());

            for (int i = 0; i < current->children_count(); ++i)
                stack.push(current->get_child(i));
        }

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_left_right_root() const {
        Sequence<T>* result = new LinkedListSequence<T>;

        if (children_count() == 0) {
            result->append(get_data());
            return result;
        }

        for (int i = 0; i < children_count(); ++i) {
            Sequence<T> *child_traverse = get_child(i)->traverse_left_right_root();
            Sequence<T>* concatenation = result->concat(child_traverse);
            delete result;
            result = concatenation;
        }
        result->append(get_data());

        return result;
    }

    template<class T>
    Sequence<T> *NaryTree<T>::traverse_right_left_root() const {
        Sequence<T>* result = new LinkedListSequence<T>;

        if (children_count() == 0) {
            result->append(get_data());
            return result;
        }

        for (int i = children_count() - 1; i >= 0; --i) {
            Sequence<T> *child_traverse = get_child(i)->traverse_right_left_root();
            Sequence<T>* concatenation = result->concat(child_traverse);
            delete result;
            result = concatenation;
        }
        result->append(get_data());

        return result;
    }

    template<class T>
    NaryTree<T>& NaryTree<T>::operator[](int index) {
        return *(children->operator[](index));
    }

} // kogan

#endif //LAB4_NARY_TREE_HPP
