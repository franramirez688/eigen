#include "main.h"

int main(int argc, char *argv[])
{
    g_has_set_repeat = false;
    g_has_set_seed = false;
    bool need_help = false;

    for(int i = 1; i < argc; i++)
    {
      if(argv[i][0] == 'r')
      {
        if(g_has_set_repeat)
        {
          std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
          return 1;
        }
        set_repeat_from_string(argv[i]+1);
      }
      else if(argv[i][0] == 's')
      {
        if(g_has_set_seed)
        {
          std::cout << "Argument " << argv[i] << " conflicting with a former argument" << std::endl;
          return 1;
        }
         set_seed_from_string(argv[i]+1);
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
      std::cout << std::endl;
      std::cout << "If defined, the environment variables EIGEN_REPEAT and EIGEN_SEED" << std::endl;
      std::cout << "will be used as default values for these parameters." << std::endl;
      return 1;
    }

    char *env_EIGEN_REPEAT = getenv("EIGEN_REPEAT");
    if(!g_has_set_repeat && env_EIGEN_REPEAT)
      set_repeat_from_string(env_EIGEN_REPEAT);
    char *env_EIGEN_SEED = getenv("EIGEN_SEED");
    if(!g_has_set_seed && env_EIGEN_SEED)
      set_seed_from_string(env_EIGEN_SEED);

    if(!g_has_set_seed) g_seed = (unsigned int) time(NULL);
    if(!g_has_set_repeat) g_repeat = DEFAULT_REPEAT;

    std::cout << "Initializing random number generator with seed " << g_seed << std::endl;
    std::stringstream ss;
    ss << "Seed: " << g_seed;
    g_test_stack.push_back(ss.str());
    srand(g_seed);
    std::cout << "Repeating each test " << g_repeat << " times" << std::endl;

    Eigen::g_test_stack.push_back(std::string(EI_PP_MAKE_STRING(EIGEN_TEST_FUNC)));

    EIGEN_CAT(test_,EIGEN_TEST_FUNC)();
    return 0;
}