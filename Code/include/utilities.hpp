#ifndef INCLUDE_UTILITIES_HPP
#define INCLUDE_UTILITIES_HPP

#include <chrono>
#include <random>

namespace utils
{
    /**
     * @brief Get the time for the program to sleep
     *
     * @param distribution
     * @param seeder
     * @return std::chrono::duration<double>
     */
    std::chrono::duration<double> getWaitTime(std::exponential_distribution<double> distribution, std::default_random_engine seeder);

} // namespace utils

#endif