#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP

namespace task
{
    enum class STATUS
    {
        YET_TO_START,
        STARTED,
        COMPLETED
    };

    /**
     * @brief
     * An abstract class to be implemented by the user.
     * This class defines the task to be fed to the Work Stealing Dequeue.It has a single
     * interface API run() which will be invoked by the thread executing the task.
     */
    class Task
    {
        STATUS m_current_status;

    public:
        /**
         * @brief
         * The API to be called by the thread executing the task.
         */
        virtual void run() = 0;

        STATUS getStatus() const;

        virtual ~Task() = default;

        Task();
    };
}

#endif // INCLUDE_TASK_HPP