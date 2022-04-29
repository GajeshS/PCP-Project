#include "impl/unboundedWSDequeue.hpp"

namespace WSD
{
    UnboundedWSDequeue::UnboundedWSDequeue(int initial_capacity)
        : m_bottom(0),
          m_array(initial_capacity) {}

    void UnboundedWSDequeue::pushBottom(std::shared_ptr<task::Task> task)
    {
        int bottom = m_bottom;
        int top = m_top.getValue();
        if (m_array.capacity() <= (bottom - top + 1))
        {
            m_array.resize(bottom, top);
        }
        m_array.setTask(bottom, task);
        m_bottom.store(bottom + 1);
    }

    std::shared_ptr<task::Task> UnboundedWSDequeue::popBottom()
    {
        m_bottom--;
        int old_top = m_top.getValue();
        int size = m_bottom - old_top;
        if (size < 0)
        {
            m_bottom = old_top;
            return nullptr;
        }
        auto task = m_array.getTask(m_bottom);
        if (size > 0)
        {
            return task;
        }
        if (!m_top.compareAndSet(old_top, old_top + 1))
        {
            task = nullptr;
        }
        m_bottom = old_top + 1;
        return task;
    }

    bool UnboundedWSDequeue::isEmpty()
    {
        return m_top.getValue() >= m_bottom;
    }

    std::shared_ptr<task::Task> UnboundedWSDequeue::popTop()
    {
        int bottom = m_bottom;
        int top = m_top.getValue();
        if (bottom <= top)
        {
            return nullptr;
        }
        auto task = m_array.getTask(top);
        if (m_top.compareAndSet(top, top + 1))
        {
            return task;
        }
        return nullptr;
    }

} // namespace WSD
