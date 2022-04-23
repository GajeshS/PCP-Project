#ifndef INCLUDE_ATOMIC_STAMPED_REFERENCE
#define INCLUDE_ATOMIC_STAMPED_REFERENCE

#include <utility>
#include <mutex>

namespace atomic
{
    /**
     * @brief class that implements the atomic stamped reference.
     * This class is simply to mimic the hardware primitives.
     *
     */
    class AtomicStampedReference
    {
        std::mutex m_mutex;
        long m_stamp;
        int m_value;

    public:
        /**
         * @brief Get the Stamp object
         *
         * @return long
         */
        long getStamp();

        /**
         * @brief Get the Value object
         *
         * @return int
         */
        int getValue();

        /**
         * @brief get the stamped reference
         *
         * @return std::pair<long, int>
         */
        std::pair<long, int> get();

        /**
         * @brief Implementation of the compareAndSet
         *
         *
         * @param old_stamp
         * @param new_stamp
         * @param old_value
         * @param new_value
         * @return true
         * @return false
         */
        bool compareAndSet(long old_stamp, long new_stamp, int old_value, int new_value);

        /**
         * @brief
         *
         * @param stamp
         * @param value
         */
        void set(long stamp, int value);
    };

} // namespace atomic

#endif // INCLUDE_ATOMIC_STAMPED_REFERENCE