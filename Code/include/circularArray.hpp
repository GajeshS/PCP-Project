#ifndef INCLUDE_CIRCULAR_ARRAY_HPP
#define INCLUDE_CIRCULAR_ARRAY_HPP

#include "task.hpp"

#include <vector>
#include <memory>

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

    public:
        /**
         * @brief Construct a new Circular Array object
         *
         * @param capacity
         */
        explicit CircularArray(int capacity = 4);

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
        std::shared_ptr<task::Task> getTask(int index);

        /**
         * @brief Set the Task object
         *
         * @param index
         * @param task
         */
        void setTask(int index, std::shared_ptr<task::Task> task);

        /**
         * @brief
         *
         * @param bottom
         * @param top
         * @return CircularArray
         */
        std::shared_ptr<CircularArray> resize(int bottom, int top);
    };

}
#endif // INCLUDE_CIRCULAR_ARRAY_HPP