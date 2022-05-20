#include <boost/coroutine2/all.hpp>
#include <functional>
#include <iostream>
#include <utility>

using namespace boost::coroutines2;

template <typename FuncType, typename... ArgTypes>
struct CoroutineWrapper {
 public:
  CoroutineWrapper(FuncType&& func, ArgTypes&&... args)
      : coroutine_callback_(std::bind(std::forward<FuncType>(func),
                                      std::forward<ArgTypes>(args)...,
                                      std::placeholders::_1)) {}

  void operator()(coroutine<int>::push_type& push_handler) {
    coroutine_callback_(push_handler);
  }

 private:
  std::function<void(coroutine<int>::push_type&)> coroutine_callback_;
};

void my_coroutine(int range, coroutine<int>::push_type& push_handler) {
  for (int i = 1; i < range; i++) {
    push_handler(i);
  }
  std::cout << "Good bye from producer coroutine." << std::endl;
}

int main() {
  CoroutineWrapper wrapper(my_coroutine, 50);
  coroutine<int>::pull_type my_routine{wrapper};
  while (my_routine) {
    int result = my_routine.get();
    std::cout << "The result is " << result << std::endl;
    my_routine();
  }
  std::cout << "Good bye from consumer coroutine." << std::endl;
  return 0;
}