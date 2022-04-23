#include "boundedWSDequeue.hpp"

#include <iostream>

namespace WSD
{
    BoundedWSDequeue::BoundedWSDequeue(int capacity)
        : WSDequeue(),
          m_capacity(capacity),
          m_tasks(capacity),
          m_bottom(0),
          m_top() {}

    void BoundedWSDequeue::pushBottom(std::shared_ptr<task::Task> task)
    {
        // we don't need to worry about this too much
        // since only 1 thread will be able to call this.
        if (m_bottom == m_capacity)
        {
            std::cout << "Capacity full. Rejecting" << std::endl;
            return;
        }
        m_tasks[m_bottom.load()] = task;
        m_bottom++; // the Linearization Point
    }

    bool BoundedWSDequeue::isEmpty()
    {
        return m_top.getValue() >= m_bottom.load();
    }

    std::shared_ptr<task::Task> BoundedWSDequeue::popBottom()
    {
        if (m_bottom.load() == 0)
            return nullptr;
        m_bottom--;
        auto task = m_tasks[m_bottom];
        auto top_val_ref = m_top.get();
        if (m_bottom.load() > top_val_ref.second)
        {
            return task;
        }
        if (m_bottom.load() == top_val_ref.second)
        {
            m_bottom.store(0);
            // if we manage to set the value correctly, then we 'win'
            if (m_top.compareAndSet(top_val_ref.first, top_val_ref.first + 1, top_val_ref.second, 0))
            {
                return task;
            }
        }
        m_top.set(top_val_ref.first + 1, 0);
        return nullptr;
    }

    std::shared_ptr<task::Task> BoundedWSDequeue::popTop()
    {
        auto top_val_ref = m_top.get();
        if (m_bottom <= top_val_ref.second)
        {
            return nullptr;
        }
        auto task = m_tasks[top_val_ref.second];
        if (m_top.compareAndSet(top_val_ref.first, top_val_ref.first + 1, top_val_ref.second, top_val_ref.second + 1))
        {
            return task;
        }
        return nullptr;
    }

} // namespace WSD
