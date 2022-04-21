#include <random>
#include <chrono>
#include <memory>
#include <thread>

namespace task
{

    class Task
    {
        std::exponential_distribution<> m_waiting_time;
        std::default_random_engine m_seeder;

    public:
        /**
         * @brief Construct a new Task object
         *
         */
        Task()
        {
            m_waiting_time = std::exponential_distribution<>(3.7); // just a randomly chosen number for init
        }

        void run()
        {
            std::this_thread::sleep_for(timing::getWaitTime(m_waiting_time, m_seeder));
        }
    };

}

namespace WSD
{
    class WSDequeue
    {
    public:
        virtual void pushBottom(std::shared_ptr<task::Task> task) = 0;

        virtual std::shared_ptr<task::Task> popBottom() = 0;

        virtual std::shared_ptr<task::Task> popTop() = 0;
    };

    class BoundedWSDequeue : public WSDequeue
    {
    public:
        void pushBottom(std::shared_ptr<task::Task> task) final
        {
        }

        std::shared_ptr<task::Task> popBottom() final
        {
        }

        std::shared_ptr<task::Task> popTop() final
        {
        }
    };

} // namespace WSD
