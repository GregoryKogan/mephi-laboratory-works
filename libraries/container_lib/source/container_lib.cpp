//
// Created by Gregory Kogan on 21.05.2023.
//

#include "container_lib.hpp"
#include "containers/deque/deque.hpp"
#include "containers/queue/queue.hpp"
#include "containers/stack/stack.hpp"

void containers_lib_is_working() {
  std::cout << "Containers lib is working!" << std::endl;

  kogan::Queue<int> queue;
  kogan::Stack<int> stack;
  kogan::Deque<int> deque;

  for (int i = 0; i < 10; ++i) {
    queue.push(i + 1);
    stack.push(i + 1);
    deque.push_back(i + 1);
  }

  std::cout << "Queue: " << queue << std::endl;
  std::cout << "Stack: " << stack << std::endl;
  std::cout << "Deque: " << deque << std::endl;
}
