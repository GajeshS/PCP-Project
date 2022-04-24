#include "matmul/matmul.hpp"

#include "boundedWSDequeue.hpp"
#include "unboundedWSDequeue.hpp"

#include <future>
#include <set>
#include <random>

namespace
{
    const int BOUNDED_DEQUEUE_CAPACITY = 30;
}

namespace matmul
{

    MatrixMultiplier::MatrixMultiplier(int num_threads, Matrix m1, Matrix m2, bool bounded_wsd)
        : m_num_threads(num_threads),
          m_matrix1(m1),
          m_matrix2(m2)
    {
        if (bounded_wsd)
        {
            for (int i = 0; i < m_num_threads; ++i)
                m_wsdequeue.push_back(std::make_shared<WSD::BoundedWSDequeue>(BOUNDED_DEQUEUE_CAPACITY));
        }
        else
        {
            // for (int i = 0; i < m_num_threads; ++i)
            // m_wsdequeue.push_back(std::make_shared<WSD::UnboundedWSDequeue>());
        }
    }

    Matrix MatrixMultiplier::getResult()
    {
        // startup for the task
        for (int i = 0; i < m_matrix1.size(); ++i)
        {
            for (int j = 0; j < m_matrix2[0].size(); ++j)
            {
                int x = i * m_matrix1.size() + j;
                auto task = std::make_shared<MatMulTask>(m_matrix1, m_matrix2, i, j);
                m_tasks.push_back(task);
                m_wsdequeue[x % m_num_threads]->pushBottom(task);
            }
        }

        // WSD is ready for execution. Note: we are doing it this way since we know the tasks beforehand.
        std::vector<std::future<void>> running_threads;
        for (int i = 0; i < m_num_threads; ++i)
        {
            running_threads.push_back(std::async(
                std::launch::async, [i](std::vector<std::shared_ptr<WSD::WSDequeue>> wsdequeue, int num_threads)
                {
                    // finish your own work
                    {
                        auto task = wsdequeue[i]->popBottom();
                        while (task != nullptr)
                        {
                            task->run();
                            task = wsdequeue[i]->popBottom();
                        }
                    }
                    // start stealing friend's work
                   {  
                        std::set<int> working_threads{};
                        for (int thread_id = 0; thread_id < num_threads; ++thread_id)
                        {
                            working_threads.insert(i);
                        }
                        working_threads.erase(i);
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> victim_chooser(1, working_threads.size());
                        while(!working_threads.empty())
                        {
                            int victim_index = victim_chooser(gen) % working_threads.size();
                            int victim = *std::next(working_threads.begin(), victim_index);
                            if(wsdequeue[victim]->isEmpty()) 
                            {
                                working_threads.erase(victim); // victim is empty now. No more work from this thread.
                            }
                            else 
                            {
                                auto task = wsdequeue[victim]->popTop();
                                if(task != nullptr) 
                                {
                                    task->run();
                                }
                            }
                        }
                    } },
                m_wsdequeue, m_num_threads));
        }

        // wait for all threads to finish
        for (int i = 0; i < m_num_threads; ++i)
        {
            running_threads[i].wait();
        }

        // create the result matrix
        std::vector<std::vector<int>> result_matrix(m_matrix1.size());
        for (int i = 0; i < m_matrix1.size(); ++i)
        {
            result_matrix[i] = std::vector<int>(m_matrix2[0].size());
        }

        // fill the result matrix
        for (const auto &task : m_tasks)
        {
            result_matrix[task->getI()][task->getJ()] = task->getResult();
        }

        return result_matrix;
    }

} // namespace matmul
