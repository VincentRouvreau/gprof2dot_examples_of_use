/*    
 *    Author  : Mat - http://codereview.stackexchange.com/users/5209/mat
 *    License : cc-wiki - https://creativecommons.org/licenses/by-sa/3.0/
 */

#include <iostream>
#include <algorithm>    // std::swap

void sub_fibonacci(uint64_t& previous, uint64_t& current)
{
  std::swap(previous, current);
  current += previous;
}

uint64_t fibonacci(unsigned num)
{
  uint64_t previous = 0;
  uint64_t current = 1;
  unsigned iter = 2;
  while (iter <= num) {
    sub_fibonacci(previous, current);
    iter++;
  }
  return current;
}

int main(int argc, char * const argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " number \n";
    return 0;
  }

  unsigned num = atoi(argv[1]);

  uint64_t res = fibonacci(num);
  std::cout << num << "th fibonacci number: " << res << std::endl;
}
