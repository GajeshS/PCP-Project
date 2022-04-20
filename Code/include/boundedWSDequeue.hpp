#ifndef INCLUDE_BOUNDED_WSDEQUEUE
#define INCLUDE_BOUNDED_WSDEQUEUE

#include "WSDequeue.hpp"

namespace WSD
{
    /**
     * @brief
     * The abstract implementation of the Work Stealing DEQueue in a bounded fashion
     */
    class BoundedWSDequeue : public WSDequeue
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
#endif // INCLUDE_BOUNDED_WSDEQUEUE