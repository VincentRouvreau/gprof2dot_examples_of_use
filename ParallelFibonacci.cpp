/*    
 *    Author  : Jasdeep Singh Arora - http://stackoverflow.com/users/1837662/jasdeep-singh-arora
 *    License : cc-wiki - https://creativecommons.org/licenses/by-sa/3.0/
 */

#include <iostream>
#include <list>
#include <stdlib.h>

#include <tbb/task.h>
#include <tbb/task_group.h>
#include <tbb/compat/thread>
#include <tbb/task_scheduler_init.h>

class fibonacci_task: public tbb::task 
{
  public:
  const unsigned n;
  uint64_t* const sum;

  fibonacci_task( unsigned n_, uint64_t* sum_ ) : n(n_), sum(sum_) {}

  task* execute() 
  {
    if(n < 3) {
      *sum = 1;
    } else {
      uint64_t x, y;
      fibonacci_task& a = *new( allocate_child() ) fibonacci_task(n-1,&x);
      fibonacci_task& b = *new( allocate_child() ) fibonacci_task(n-2,&y);
      set_ref_count(3); // 3 = 2 children + 1 for wait 
                        // ref_countis used to keep track of the number of tasks spawned at
                        // the current level of the task graph
      spawn( b );
      spawn_and_wait_for_all( a ); //set tasks for execution and wait for them
      *sum = x+y;
    }
    return NULL;
  }
};

uint64_t fibonacci(unsigned num) {
  uint64_t result;
  fibonacci_task& a = *new(tbb::task::allocate_root()) fibonacci_task(num, &result);
  tbb::task::spawn_root_and_wait(a);
  return result;
}

int main(int argc, char * const argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " number \n";
    return 0;
  }

  unsigned num = atoi(argv[1]);

  uint64_t res = fibonacci(num);
  std::cout << num << "th fibonacci number: " << res << std::endl;

  return(0);
}
