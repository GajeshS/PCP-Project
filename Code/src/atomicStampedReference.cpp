#include "atomicStampedReference.hpp"

namespace atomic
{

    long AtomicStampedReference::getStamp()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_stamp;
    }

    int AtomicStampedReference::getValue()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_value;
    }

    std::pair<long, int> AtomicStampedReference::get()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return {m_stamp, m_value};
    }

    bool AtomicStampedReference::compareAndSet(long old_stamp, long new_stamp, int old_value, int new_value)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if (m_stamp == old_stamp && m_value == old_value)
        {
            m_stamp = new_stamp;
            m_value = new_value;
            return true;
        }
        return false;
    }

    bool AtomicStampedReference::compareAndSet(int old_value, int new_value)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if (m_value == old_value)
        {
            m_value = new_value;
            return true;
        }
        return false;
    }

    void AtomicStampedReference::set(long stamp, int value)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_stamp = stamp;
        m_value = value;
    }

} // namespace atomic
