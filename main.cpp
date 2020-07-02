#include <iostream>
#include <string>

#include "lru.h"

int main() {
  yc::LRUList<int, std::string> ll(3);
  ll.Set(1, "111");
  ll.Set(2, "222");
  ll.Set(3, "333");
  ll.Set(4, "444");
  std::string res;
  std::cout << ll.Get(1, res) << std::endl;
  std::cout << "res: " << res << std::endl;

  ll.Get(2, res);
  ll.Set(5, "555");
  res.clear();
  std::cout << ll.Get(2, res) << std::endl;
  std::cout << "res: " << res << std::endl;

  res.clear();
  std::cout << ll.Get(3, res) << std::endl;
  std::cout << "res: " << res << std::endl;

  res.clear();
  std::cout << ll.Get(2, res) << std::endl;
  std::cout << "res: " << res << std::endl;
  return 0;
}