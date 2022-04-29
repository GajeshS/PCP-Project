#ifndef INCLUDE_CIRCULAR_ARRAY_HPP
#define INCLUDE_CIRCULAR_ARRAY_HPP

#include "task.hpp"

#include <vector>
#include <memory>
#include <mutex>

namespace WSD
{
    /**
     * @brief
     * The internal container of the tasks in the unbounded implementation
     * of the work stealing dequeue
     */
    class CircularArray
    {
        int m_log_capacity;
        std::vector<std::shared_ptr<task::Task>> m_tasks;
        // std::atomic doesn't work with large objects. Hence,
        // we are forced to use locks to mimic the behaviour.
        std::recursive_mutex m_atomicizer;

    public:
        /**
         * @brief Construct a new Circular Array object
         *
         * @param capacity
         */
        explicit CircularArray(const int &capacity = 4);

        /**
         * @brief
         *
         * @return int
         */
        int capacity();

        /**
         * @brief Get the Task object
         *
         * @param index
         * @return std::shared_ptr<task::Task>
         */
        std::shared_ptr<task::Task> getTask(const int &index);

        /**
         * @brief Set the Task object
         *
         * @param index
         * @param task
         */
        void setTask(const int &index, std::shared_ptr<task::Task> task);

        /**
         * @brief
         *
         * @param bottom
         * @param top
         * @return CircularArray
         */
        void resize(const int &bottom, const int &top);
    };

}
#endif // INCLUDE_CIRCULAR_ARRAY_HPP