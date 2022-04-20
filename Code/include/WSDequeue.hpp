#ifndef INCLUDE_WSDEQUEUE
#define INCLUDE_WSDEQUEUE

#include "task.hpp"

#include <memory>

namespace WSD
{
    /**
     * @brief
     * The abstract implementation of the Work Stealing DEQueue. This defines
     * the 3 APIs to be used by the DEQueue: pushBottom() to add tasks to the Queue
     * and popBottom() and popTop() to pick the tasks to be done from outside the queue.
     */
    class WSDequeue
    {
    public:
        /**
         * @brief
         * API to add a task to the Queue.
         * @param task - the task to be added to the queue
         */
        virtual void pushBottom(std::shared_ptr<task::Task> task) = 0;

        /**
         * @brief
         * API to pick a task added to the queue.
         * @return - the task to be performed by the thread.
         */
        virtual std::shared_ptr<task::Task> popBottom() = 0;

        /**
         * @brief
         * API used by a different thread to 'steal' a task.
         *
         * @return task if successful. Null if not.
         * Note: null return does not imply that there is no task in the queue.
         */
        virtual std::shared_ptr<task::Task> popTop() = 0;
    };
}
#endif // INCLUDE_WSDEQUEUE