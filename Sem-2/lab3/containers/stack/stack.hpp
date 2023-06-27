//
// Created by Gregory Kogan on 16.05.2023.
//

#ifndef LAB3_STACK_HPP
#define LAB3_STACK_HPP

#include "../base_container.hpp"
#include "sequence_lib.hpp"

namespace kogan {

template <class T> class Stack : public BaseContainer<T> {
  using BaseContainer<T>::sequence;

public:
  using BaseContainer<T>::empty;

  Stack();
  Stack(T *items, int count);
  explicit Stack(const Sequence<T> *other_seq);
  explicit Stack(const Stack<T> *stack);

  void push(const T &item);
  T pop();
  T front() const;

  Stack<T> *concat(const Stack<T> &other) const;
};

template <class T> Stack<T>::Stack() { sequence = new LinkedListSequence<T>(); }

template <class T> Stack<T>::Stack(T *items, int count) {
  sequence = new LinkedListSequence<T>(items, count);
}

template <class T> Stack<T>::Stack(const Sequence<T> *other_seq) {
  T *items = new T[other_seq->get_length()];
  for (int i = 0; i < other_seq->get_length(); ++i)
    items[i] = other_seq->get(i);
  sequence = new LinkedListSequence<T>(items, other_seq->get_length());
  delete[] items;
}

template <class T> Stack<T>::Stack(const Stack<T> *stack) {
  sequence = new LinkedListSequence<T>();
  for (int i = 0; i < stack->size(); ++i)
    sequence->append(stack->sequence->get(i));
}

template <class T> void Stack<T>::push(const T &item) {
  sequence->prepend(item);
}

template <class T> T Stack<T>::pop() {
  if (empty())
    throw kogan::EmptyContainerException();

  T value = sequence->get_first();
  sequence->remove(0);
  return value;
}

template <class T> T Stack<T>::front() const {
  if (empty())
    throw kogan::EmptyContainerException();

  return sequence->get_first();
  ;
}

template <class T> Stack<T> *Stack<T>::concat(const Stack<T> &other) const {
  auto *result = new Stack<T>(this);
  for (auto x : other)
    result->sequence->append(x);
  return result;
}

} // namespace kogan

#endif // LAB3_STACK_HPP
