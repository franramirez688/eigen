#include "main.h"

int main(int argc, char *argv[])
{
    bool has_set_repeat = false;
    bool has_set_seed = false;
    bool need_help = false;
    unsigned int seed = 0;
    int repeat = DEFAULT_REPEAT;

    for(int i = 1; i < argc; i++)
    {
      if(argv[i][0] == 'r')
      {
        if(has_set_repeat)
        {
          std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
          return 1;
        }
        repeat = std::atoi(argv[i]+1);
        has_set_repeat = true;
        if(repeat <= 0)
        {
          std::cout << "Invalid \'repeat\' value " << argv[i]+1 << std::endl;
          return 1;
        }
      }
      else if(argv[i][0] == 's')
      {
        if(has_set_seed)
        {
          std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
          return 1;
        }
        seed = int(std::strtoul(argv[i]+1, 0, 10));
        has_set_seed = true;
        bool ok = seed!=0;
        if(!ok)
        {
          std::cout << "Invalid \'seed\' value " << argv[i]+1 << std::endl;
          return 1;
        }
      }
      else
      {
        need_help = true;
      }
    }

    if(need_help)
    {
      std::cout << "This test application takes the following optional arguments:" << std::endl;
      std::cout << "  rN     Repeat each test N times (default: " << DEFAULT_REPEAT << ")" << std::endl;
      std::cout << "  sN     Use N as seed for random numbers (default: based on current time)" << std::endl;
      return 1;
    }

    if(!has_set_seed) seed = (unsigned int) std::time(NULL);
    if(!has_set_repeat) repeat = DEFAULT_REPEAT;

    std::cout << "Initializing random number generator with seed " << seed << std::endl;
	std::srand(seed);
    std::cout << "Repeating each test " << repeat << " times" << std::endl;

    Eigen::g_repeat = repeat;
    Eigen::g_test_stack.push_back(EI_PP_MAKE_STRING(EIGEN_TEST_FUNC));

    EI_PP_CAT(test_,EIGEN_TEST_FUNC)();
    return 0;
}



