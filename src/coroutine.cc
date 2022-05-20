#include <boost/coroutine/all.hpp>
#include <iostream>

using namespace boost::coroutines;

void my_coroutine(coroutine<void>::push_type &sink) {
  std::cout << "Hello";
  sink();
  std::cout << "World!" << std::endl;
}

int main() {
  coroutine<void>::pull_type my_routine{my_coroutine};
  std::cout << " ";
  my_routine();
  std::cout << "Good bye!" << std::endl;
  return 0;
}