#include "task.hpp"

namespace task
{
    STATUS Task::getStatus() const
    {
        return m_current_status;
    }

    Task::Task() : m_current_status(STATUS::YET_TO_START) {}

} // namespace task
