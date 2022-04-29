#ifndef INCLUDE_MATMUL_MATMUL_HPP
#define INCLUDE_MATMUL_MATMUL_HPP

#include "matmul/matmulTask.hpp"
#include "WSDequeue.hpp"

#include <vector>
#include <memory>

namespace matmul
{
    /**
     * @brief
     *
     */
    class MatrixMultiplier
    {
        std::vector<std::shared_ptr<WSD::WSDequeue>> m_wsdequeue;
        std::vector<std::shared_ptr<MatMulTask>> m_tasks;
        int m_num_threads;
        bool m_uneven_distribution;
        std::vector<int> m_distribution;
        Matrix m_matrix1;
        Matrix m_matrix2;

    public:
        /**
         * @brief Construct a new Matrix Multiplier object
         *
         * @param num_threads - number of threads to run the program on.
         * @param m1 - matrix 1
         * @param m2 - matrix 2
         * @param bounded_wsd - if the dequeue we re using is bounded or not.
         */
        MatrixMultiplier(int num_threads, Matrix m1, Matrix m2, bool bounded_wsd = false);

        /**
         * @brief Construct a new Matrix Multiplier object
         *
         * @param num_threads - number of threads to run the program on.
         * @param m1 - matrix 1
         * @param m2 - matrix 2
         * @param distribution - the distribution of tasks in percentages
         * @param bounded_wsd - if the dequeue we re using is bounded or not.
         */
        MatrixMultiplier(int num_threads, Matrix m1, Matrix m2, std::vector<float> distribution,
                         bool bounded_wsd = false);

        /**
         * @brief Destroy the Matrix Multiplier object
         *
         */
        ~MatrixMultiplier() = default;

        /**
         * @brief Get the Result of the matrix multiplication. When this API is
         * called, we trigger the multi-threaded matrix multiplication.
         *
         * @return - resultant matrix from the matmul operation
         */
        Matrix getResult();
    };

} // namespace matmul

#endif // INCLUDE_MATMUL_MATMUL_HPP