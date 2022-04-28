#ifndef INCLUDE_UNBOUNDED_WSDEQUEUE
#define INCLUDE_UNBOUNDED_WSDEQUEUE

#include "WSDequeue.hpp"
#include "circularArray.hpp"
#include "atomicStampedReference.hpp"

#include <atomic>

namespace WSD
{

    /**
     * @brief
     * Internal class used to maintain a circular array.
     * Defined in the implementation file
     */
    class CircularArray;

    /**
     * @brief
     * The abstract implementation of the Work Stealing DEQueue in a bounded fashion
     */
    class UnboundedWSDequeue : public WSDequeue
    {
        std::shared_ptr<CircularArray> m_array;
        std::atomic<int> m_bottom;
        atomic::AtomicStampedReference m_top;

    public:
        /**
         * @brief Construct a new Unbounded WSDequeue object
         *
         */
        explicit UnboundedWSDequeue(int initial_capacity = 6);

        /**
         * @copydoc WSDequeue::pushBottom
         */
        void pushBottom(std::shared_ptr<task::Task> task) final;

        /**
         * @copydoc WSDequeue::popBottom
         */
        std::shared_ptr<task::Task> popBottom() final;

        /**
         * @brief API called by thieves to make sure they can steal from this WSD
         *
         * @return true
         * @return false
         */
        bool isEmpty() final;

        /**
         * @copydoc WSDequeue::popTop
         */
        std::shared_ptr<task::Task> popTop() final;
    };
}
#endif // INCLUDE_UNBOUNDED_WSDEQUEUE