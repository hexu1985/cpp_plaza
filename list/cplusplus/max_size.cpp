// list::max_size
#include <iostream>
#include "list.h"

int main ()
{
  unsigned int i;
  list<int> mylist;

  std::cout << "Enter number of elements: ";
  std::cin >> i;

  if (i<mylist.max_size()) mylist.resize(i);
  else std::cout << "That size exceeds the limit.\n";

  return 0;
}
