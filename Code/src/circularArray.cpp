#include "circularArray.hpp"

namespace WSD
{
    CircularArray::CircularArray(const int &log_capacity)
        : m_log_capacity(log_capacity)
    {
        m_tasks = std::vector<std::shared_ptr<task::Task>>(1 << log_capacity);
    }

    int CircularArray::capacity()
    {
        std::lock_guard<std::recursive_mutex> atomic(m_atomicizer);
        return 1 << m_log_capacity;
    }

    std::shared_ptr<task::Task> CircularArray::getTask(const int &index)
    {
        std::lock_guard<std::recursive_mutex> atomic(m_atomicizer);
        return m_tasks[index % capacity()];
    }

    void CircularArray::setTask(const int &index, std::shared_ptr<task::Task> task)
    {
        std::lock_guard<std::recursive_mutex> atomic(m_atomicizer);
        m_tasks[index % capacity()] = task;
    }

    void CircularArray::resize(const int &bottom, const int &top)
    {
        std::lock_guard<std::recursive_mutex> atomic(m_atomicizer);
        auto new_array = std::vector<std::shared_ptr<task::Task>>(2 * capacity());
        for (int i = top; i < bottom; ++i)
        {
            new_array[i % (2 * capacity())] = getTask(i);
        }
        m_tasks = new_array;
        m_log_capacity++;
    }

} // namespace WSD
