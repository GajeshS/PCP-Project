#include "matmul/matmulTask.hpp"

#include <stdexcept>

namespace matmul
{
    /**
     * @brief
     * Construct a new Mat Mul Task:: Mat Mul Task object
     * @param
     * The two matrices to be multiplied and the index of row and columns.
     */
    MatMulTask::MatMulTask(const Matrix &matrix1, const Matrix &matrix2, const int &i, const int &j)
        : m_matrix1(matrix1),
          m_matrix2(matrix2),
          m_i(i),
          m_j(j),
          m_result(0)
    {
        auto num_rows = m_matrix1[0].size();
        if (m_matrix1.size() < i || m_matrix1[0].size() != m_matrix2.size() || m_matrix2[0].size() < j)
        {
            throw std::out_of_range("matrix dimensions out of range");
        }
        for (int i = 0; i < num_rows; ++i)
        {
            if (m_matrix2[i].size() < j)
            {
                throw std::out_of_range("matrix dimensions out of range");
            }
        }
    }
    /**
     * @brief
     * The API to be called to perfom matrix multiplication.
     */
    void MatMulTask::run()
    {
        int n = m_matrix2.size();
        m_result = 0;
        for (int k = 0; k < n; ++k)
        {
            m_result += m_matrix1[m_i][k] + m_matrix2[k][m_j];
        }
    }

    /**
     * @brief
     * The function that produces the result of matrix multiplication.
     * @return
     * The result of matrix multiplication
     */

    int MatMulTask::getResult() const
    {
        return m_result;
    }
    /**
     * @brief
     * An API used to find the index of the row to be multiplied.
     * @return
     * The i'th index
     */
    int MatMulTask::getI() const
    {
        return m_i;
    }
    /**
     * @brief
     * An API used to find the index of the column to be multiplied.
     * @return
     * The j'th index
     */
    int MatMulTask::getJ() const
    {
        return m_j;
    }
} // namespace matmul
