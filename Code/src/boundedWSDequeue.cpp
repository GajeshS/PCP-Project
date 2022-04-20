#include "boundedWSDequeue.hpp"

namespace WSD
{
    void BoundedWSDequeue::pushBottom(std::shared_ptr<task::Task> task)
    {
    }

    std::shared_ptr<task::Task> BoundedWSDequeue::popBottom()
    {
        return nullptr;
    }

    std::shared_ptr<task::Task> BoundedWSDequeue::popTop()
    {
        return nullptr;
    }

} // namespace WSD
