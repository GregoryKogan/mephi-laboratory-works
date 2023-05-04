//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include "../exceptions/IndexOutOfRangeException/IndexOutOfRangeException.h"
#include "../exceptions/EmptyContainerException/EmptyContainerException.h"
#include "../exceptions/InvalidArgumentException/InvalidArgumentException.h"

namespace kogan {

    template <class T> class LinkedList {
        typedef struct Node {
            T value;
            Node* previous;
            Node* next;
        } node;

        typedef struct ListRoot {
            Node* head;
            Node* tail;
        } list_root;

        size_t length;
        list_root* root;

        node* get_node(int index);

    public:

        LinkedList(T* items, size_t count);
        LinkedList();
        LinkedList(const LinkedList<T> &linkedList);

        ~LinkedList();

        T get_first();
        T get_last();
        T get(int index);
        LinkedList<T> get_sublist(int start_index, int end_index);
        size_t get_length();

        void set(int index, T item);
        void append(T item);
        void prepend(T item);
        void insert(T item, int index);

        LinkedList<T> concat(LinkedList<T> list);
    };

    template<class T>
    LinkedList<T>::LinkedList(T *items, size_t count) {
        length = count;
        root = new list_root;

        if (length == 0) {
            root->head = NULL;
            root->tail = NULL;
            return;
        }

        node* cur_node = new node;
        cur_node->value = items[0];
        cur_node->next = NULL;
        cur_node->previous = NULL;
        root->head = cur_node;
        root->tail = cur_node;

        for (size_t i = 1; i < length; ++i) {
            node* new_node = new node;
            new_node->value = items[i];
            new_node->next = NULL;
            new_node->previous = cur_node;
            cur_node->next = new_node;
            cur_node = new_node;
            root->tail = new_node;
        }
    }

    template<class T>
    LinkedList<T>::LinkedList() {
        length = 0;
        root = new list_root;
        root->head = NULL;
        root->tail = NULL;
    }

    template<class T>
    LinkedList<T>::LinkedList(const LinkedList<T> &linkedList) {
        length = linkedList.length;
        root = new list_root;

        if (length == 0) {
            root->head = NULL;
            root->tail = NULL;
            return;
        }

        node* cur_node = new node;
        node* other_cur_node = linkedList.root->head;
        cur_node->value = other_cur_node->value;
        cur_node->next = NULL;
        cur_node->previous = NULL;
        root->head = cur_node;
        root->tail = cur_node;

        for (size_t i = 1; i < length; ++i) {
            other_cur_node = other_cur_node->next;
            node* new_node = new node;
            new_node->value = other_cur_node->value;
            new_node->next = NULL;
            new_node->previous = cur_node;
            cur_node->next = new_node;
            cur_node = new_node;
            root->tail = cur_node;
        }
    }

    template<class T>
    LinkedList<T>::~LinkedList() {
        node* cur_node = root->head;
        node* next = NULL;
        while (cur_node != NULL) {
            next = cur_node->next;
            delete cur_node;
            cur_node = next;
        }
        delete root;
    }

    template<class T>
    typename LinkedList<T>::node *LinkedList<T>::get_node(int index) {
        if (index < 0 || index >= length)
            throw IndexOutOfRangeException(index, 0, length - 1);

        if (index == 0)
            return root->head;
        if (index == length - 1)
            return root->tail;

        if (index < length / 2) {
            int cur_index = 0;
            node *cur_node = root->head;
            while (cur_index < index) {
                cur_index++;
                cur_node = cur_node->next;
            }

            return cur_node;
        } else {
            int cur_index = length - 1;
            node *cur_node = root->tail;
            while (cur_index > index) {
                cur_index--;
                cur_node = cur_node->previous;
            }

            return cur_node;
        }
    }

    template<class T>
    T LinkedList<T>::get_first() {
        if (length == 0)
            throw EmptyContainerException();
        return root->head->value;
    }

    template<class T>
    T LinkedList<T>::get_last() {
        if (length == 0)
            throw EmptyContainerException();
        return root->tail->value;
    }

    template<class T>
    T LinkedList<T>::get(int index) {
        if (index < 0 || index >= length)
            throw IndexOutOfRangeException(index, 0, length - 1);

        return get_node(index)->value;
    }

    template<class T>
    LinkedList<T> LinkedList<T>::get_sublist(int start_index, int end_index) {
        if (start_index < 0 || start_index >= length)
            throw IndexOutOfRangeException(start_index, 0, length - 1);

        if (end_index < 0 || end_index >= length)
            throw IndexOutOfRangeException(end_index, 0, length - 1);

        if (end_index < start_index)
            throw InvalidArgumentException("end_index");

        LinkedList<T> sublist;
        int cur_index = start_index;
        node* cur_node = get_node(start_index);
        while (cur_index <= end_index) {
            sublist.append(cur_node->value);

            cur_index++;
            cur_node = cur_node->next;
        }

        return sublist;
    }

    template<class T>
    size_t LinkedList<T>::get_length() {
        return length;
    }

    template<class T>
    void LinkedList<T>::set(int index, T item) {
        if (index < 0 || index >= length)
            throw IndexOutOfRangeException(index, 0, length - 1);

        get_node(index)->value = item;
    }

    template<class T>
    void LinkedList<T>::append(T item) {
        node* new_node = new node;
        new_node->value = item;
        new_node->next = NULL;
        length++;

        if (length == 1) {
            new_node->previous = NULL;
            root->head = new_node;
            root->tail = new_node;
            return;
        }

        new_node->previous = root->tail;
        root->tail->next = new_node;
        root->tail = new_node;
    }

    template<class T>
    void LinkedList<T>::prepend(T item) {
        node* new_node = new node;
        new_node->value = item;
        new_node->previous = NULL;
        length++;

        if (length == 1) {
            root->head = new_node;
            root->tail = new_node;
            return;
        }

        new_node->next = root->head;
        root->head->previous = new_node;
        root->head = new_node;
    }

    template<class T>
    void LinkedList<T>::insert(T item, int index) {
        if (index < 0 || index > length)
            throw IndexOutOfRangeException(index, 0, length);

        if (index == 0)
            prepend(item);
        else if (index == length)
            append(item);
        else {
            node* prev_node = get_node(index - 1);
            node* new_node = new node;
            new_node->value = item;
            new_node->next = prev_node->next;
            new_node->next->previous = new_node;
            new_node->previous = prev_node;
            prev_node->next = new_node;
            length++;
        }
    }

    template<class T>
    LinkedList<T> LinkedList<T>::concat(LinkedList<T> list) {
        LinkedList<T> concatenation;

        node* cur_node = root->head;
        while (cur_node != NULL) {
            concatenation.append(cur_node->value);
            cur_node = cur_node->next;
        }
        cur_node = list.root->head;
        while (cur_node != NULL) {
            concatenation.append(cur_node->value);
            cur_node = cur_node->next;
        }
        return concatenation;
    }

} // kogan

#endif //LAB2_LINKEDLIST_H
