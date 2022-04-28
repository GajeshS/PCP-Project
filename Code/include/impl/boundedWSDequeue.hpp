#ifndef INCLUDE_BOUNDED_WSDEQUEUE
#define INCLUDE_BOUNDED_WSDEQUEUE

#include "WSDequeue.hpp"
#include "atomicStampedReference.hpp"
#include "task.hpp"

#include <atomic>
#include <vector>

namespace WSD
{
    /**
     * @brief
     * The abstract implementation of the Work Stealing DEQueue in a bounded fashion
     */
    class BoundedWSDequeue : public WSDequeue
    {
        int m_capacity;
        std::vector<std::shared_ptr<task::Task>> m_tasks;
        std::atomic<int> m_bottom;
        atomic::AtomicStampedReference m_top;

    public:
        /**
         * @brief Construct a new Bounded W S Dequeue object
         *
         * @param capacity
         */
        explicit BoundedWSDequeue(int capacity);

        /**
         * @copydoc WSDequeue::pushBottom
         *
         * NOTE: should be called only by a single thread.
         * Multiple threads calling this can cause unexpected errors.
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

        /**
         * @copydoc WSDequeue::isEmpty
         */
        bool isEmpty() final;
    };
}
#endif // INCLUDE_BOUNDED_WSDEQUEUE