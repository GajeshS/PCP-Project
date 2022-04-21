#ifndef INCLUDE_MATMUL_MATMULTASK_HPP
#define INCLUDE_MATMUL_MATMULTASK_HPP

#include "task.hpp"

#include <vector>

namespace matmul
{
    using Matrix = std::vector<std::vector<int>>;

    /**
     * @brief The task for matrix mltiplication. We calculate
     *
     */
    class MatMulTask : public task::Task
    {
        Matrix m_matrix1;
        Matrix m_matrix2;
        int m_i, m_j;
        int m_result;

    public:
        /**
         * @brief Construct a new MatMul Task object
         *
         * @param matrix1
         * @param matrix2
         * @param i
         * @param j
         */
        MatMulTask(const Matrix &matrix1, const Matrix &matrix2, const int &i, const int &j)
            : m_matrix1(matrix1),
              m_matrix2(matrix2),
              m_i(i),
              m_j(j),
              m_result(0)
        {
        }

        /**
         * @copydoc task::Task::run()
         */
        void run() final;

        /**
         * @brief Get the Result of the task.
         *
         * @return int
         */
        int getResult() const;
    };

} // namespace matmul

#endif // INCLUDE_MATMUL_MATMULTASK_HPP