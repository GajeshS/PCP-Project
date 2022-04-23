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
        MatMulTask(const Matrix &matrix1, const Matrix &matrix2, const int &i, const int &j);

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

        int getI() const;

        int getJ() const;
    };

} // namespace matmul

#endif // INCLUDE_MATMUL_MATMULTASK_HPP