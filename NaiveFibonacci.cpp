/*    
 *    Author  : Vincent Rouvreau
 *    License : cc-wiki - https://creativecommons.org/licenses/by-sa/3.0/
 */

#include <iostream>

uint64_t fibonacci(unsigned num)
{
  if (num <= 1)
    return num;
  return (fibonacci(num - 1) + fibonacci(num - 2));
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
