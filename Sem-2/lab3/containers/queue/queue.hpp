//
// Created by Gregory Kogan on 15.05.2023.
//

#ifndef LAB3_QUEUE_HPP
#define LAB3_QUEUE_HPP

#include "../base_container.hpp"
#include "sequence_lib.hpp"

namespace kogan {

template <class T> class Queue : public BaseContainer<T> {
  using BaseContainer<T>::sequence;

public:
  using BaseContainer<T>::empty;

  Queue();
  Queue(T *items, int count);
  explicit Queue(const Sequence<T> *other_seq);
  explicit Queue(const Queue<T> *queue);

  void push(const T &item);
  T pop();
  T front() const;

  Queue<T> *concat(const Queue<T> &other) const;
};

template <class T> Queue<T>::Queue() { sequence = new LinkedListSequence<T>(); }

template <class T> Queue<T>::Queue(T *items, int count) {
  sequence = new LinkedListSequence<T>(items, count);
}

template <class T> Queue<T>::Queue(const Sequence<T> *other_seq) {
  T *items = new T[other_seq->get_length()];
  for (int i = 0; i < other_seq->get_length(); ++i)
    items[i] = other_seq->get(i);
  sequence = new LinkedListSequence<T>(items, other_seq->get_length());
  delete[] items;
}

template <class T> Queue<T>::Queue(const Queue<T> *queue) {
  sequence = new LinkedListSequence<T>();
  for (int i = 0; i < queue->size(); ++i)
    sequence->append(queue->sequence->get(i));
}

template <class T> void Queue<T>::push(const T &item) {
  sequence->append(item);
}

template <class T> T Queue<T>::pop() {
  if (empty())
    throw kogan::EmptyContainerException();

  T value = sequence->get_first();
  sequence->remove(0);
  return value;
}

template <class T> T Queue<T>::front() const {
  if (empty())
    throw kogan::EmptyContainerException();

  return sequence->get_first();
  ;
}

template <class T> Queue<T> *Queue<T>::concat(const Queue<T> &other) const {
  auto *result = new Queue<T>(this);
  for (auto x : other)
    result->push(x);
  return result;
}

} // namespace kogan

#endif // LAB3_QUEUE_HPP
