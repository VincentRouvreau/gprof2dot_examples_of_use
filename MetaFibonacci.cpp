/*    
 *    Author  : GManNickG - http://stackoverflow.com/users/87234/gmannickg
 *    License : cc-wiki - https://creativecommons.org/licenses/by-sa/3.0/
 */


#include <iostream>

template <unsigned N>
struct fibonacci {
  static const uint64_t value = fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template <>
struct fibonacci<2> {
  static const uint64_t value = 1;
};

template <>
struct fibonacci<1> {
  static const uint64_t value = 1;
};


int main()
{
  constexpr unsigned num = 42;

  std::cout << num << "th fibonacci number: " << fibonacci<num>::value << std::endl;
}
