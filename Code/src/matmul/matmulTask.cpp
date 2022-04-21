#include "matmul/matmulTask.hpp"

#include <stdexcept>

namespace matmul
{
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

    void MatMulTask::run()
    {
        int n = m_matrix2.size();
        m_result = 0;
        for (int k = 0; k < n; ++k)
        {
            m_result += m_matrix1[m_i][k] + m_matrix2[k][m_j];
        }
    }

    int MatMulTask::getResult() const
    {
        return m_result;
    }
} // namespace matmul
