#include "unboundedWSDequeue.hpp"

namespace WSD
{
    void UnboundedWSDequeue::pushBottom(std::shared_ptr<task::Task> task)
    {
    }

    std::shared_ptr<task::Task> UnboundedWSDequeue::popBottom()
    {
        return nullptr;
    }

    std::shared_ptr<task::Task> UnboundedWSDequeue::popTop()
    {
        return nullptr;
    }

} // namespace WSD
