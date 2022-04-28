#include "circularArray.hpp"

namespace WSD
{
    CircularArray::CircularArray(int log_capacity)
        : m_log_capacity(log_capacity)
    {
        m_tasks = std::vector<std::shared_ptr<task::Task>>(capacity());
    }

    int CircularArray::capacity()
    {
        return 1 << m_log_capacity;
    }

    std::shared_ptr<task::Task> CircularArray::getTask(int index)
    {
        return m_tasks[index % capacity()];
    }

    void CircularArray::setTask(int index, std::shared_ptr<task::Task> task)
    {
        m_tasks[index % capacity()] = task;
    }

    std::shared_ptr<CircularArray> CircularArray::resize(int bottom, int top)
    {
        auto new_array = std::make_shared<CircularArray>(m_log_capacity + 1);
        for (int i = top; i < bottom; ++i)
        {
            new_array->setTask(i, getTask(i));
        }
        return new_array;
    }

} // namespace WSD
