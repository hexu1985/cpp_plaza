// all_of example
#include <iostream>     // std::cout
#include <array>        // std::array
#include "algorithm.h"  // all_of

int main () {
  std::array<int,8> foo = {3,5,7,11,13,17,19,23};

  if ( all_of(foo.begin(), foo.end(), [](int i){return i%2;}) )
    std::cout << "All the elements are odd numbers.\n";

  return 0;
}
