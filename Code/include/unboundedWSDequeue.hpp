#ifndef INCLUDE_UNBOUNDED_WSDEQUEUE
#define INCLUDE_UNBOUNDED_WSDEQUEUE

#include "WSDequeue.hpp"

namespace WSD
{
    /**
     * @brief
     * The abstract implementation of the Work Stealing DEQueue in a bounded fashion
     */
    class UnboundedWSDequeue : public WSDequeue
    {
    public:
        /**
         * @copydoc WSDequeue::pushBottom
         */
        void pushBottom(std::shared_ptr<task::Task> task) final;

        /**
         * @copydoc WSDequeue::popBottom
         */
        std::shared_ptr<task::Task> popBottom() final;

        /**
         * @copydoc WSDequeue::popTop
         */
        std::shared_ptr<task::Task> popTop() final;
    };
}
#endif // INCLUDE_UNBOUNDED_WSDEQUEUE