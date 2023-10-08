//
// Created by Gregory Kogan on 10.05.2023.
//

#include "sequence_lib.hpp"

void sequence_lib_is_working() {
  std::cout << "Sequence lib is working!" << std::endl;

  kogan::ArraySequence<int> arraySequence;
  kogan::LinkedListSequence<int> linkedListSequence;

  for (int i = 0; i < 10; ++i) {
    arraySequence.append(i);
    linkedListSequence.prepend(i);
  }

  std::cout << "ArraySequence: " << arraySequence << std::endl;
  std::cout << "LinkedListSequence: " << linkedListSequence << std::endl;
}
