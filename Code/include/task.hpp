#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP

namespace task
{
    /**
     * @brief
     * An abstract class to be implemented by the user.
     * This class defines the task to be fed to the Work Stealing Dequeue.It has a single
     * interface API run() which will be invoked by the thread executing the task.
     */
    class Task
    {
    public:
        /**
         * @brief
         * The API to be called by the thread executing the task.
         */
        virtual void run() = 0;
    };
}

#endif // INCLUDE_TASK_HPP