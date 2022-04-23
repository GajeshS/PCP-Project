#include "matmul/matmul.hpp"

#include "boundedWSDequeue.hpp"
#include "unboundedWSDequeue.hpp"

namespace matmul
{

    MatrixMultiplier::MatrixMultiplier(int num_threads, Matrix m1, Matrix m2, bool bounded_wsd)
        : m_num_threads(num_threads),
          m_matrix1(m1),
          m_matrix2(m2)
    {
        if (bounded_wsd)
        {
            // for (int i = 0; i < m_num_threads; ++i)
            // m_wsdequeue.push_back(std::make_shared<WSD::BoundedWSDequeue>());
        }
        else
        {
            // for (int i = 0; i < m_num_threads; ++i)
            // m_wsdequeue.push_back(std::make_shared<WSD::UnboundedWSDequeue>());
        }
    }

    Matrix MatrixMultiplier::getResult()
    {
    }

} // namespace matmul
