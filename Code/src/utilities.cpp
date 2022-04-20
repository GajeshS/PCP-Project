#include "utilities.hpp"

namespace utils
{

    std::chrono::duration<double> getWaitTime(std::exponential_distribution<double> distribution, std::default_random_engine seeder)
    {
        return std::chrono::duration<double>(distribution(seeder));
    }
}