//
// Created by Gregory Kogan on 03.05.2023.
//

#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <sstream>
#include <string>

namespace kogan {

template <class T> class Sequence {

public:
  virtual ~Sequence() = 0;

  virtual T get_first() const = 0;
  virtual T get_last() const = 0;
  virtual T get(int index) const = 0;
  virtual Sequence<T> *get_subsequence(int start_index,
                                       int end_index) const = 0;
  [[nodiscard]] virtual size_t get_length() const = 0;

  virtual void set(int index, T item) = 0;
  virtual void append(T item) = 0;
  virtual void prepend(T item) = 0;
  virtual void insert(int index, T item) = 0;
  virtual Sequence<T> *concat(Sequence<T> *sequence) = 0;
  virtual void clear() = 0;
  virtual void remove(int index) = 0;

  virtual T &operator[](int index) = 0;

  [[nodiscard]] std::string to_string() const;

  friend std::ostream &operator<<(std::ostream &os, const Sequence<T> &seq) {
    os << seq.to_string();
    return os;
  }
};

template <class T> Sequence<T>::~Sequence() = default;

template <class T> std::string Sequence<T>::to_string() const {
  if (get_length() == 0)
    return "[]";

  std::ostringstream oss;
  oss << "[" << get_first();
  for (int i = 1; i < get_length(); ++i)
    oss << ", " << get(i);
  oss << "]";

  return oss.str();
}

} // namespace kogan

#endif // LAB2_SEQUENCE_H
