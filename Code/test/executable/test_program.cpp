#include "utilities.hpp"

#include "matmul/matmul.hpp"

#include <iostream>
#include <chrono>

namespace
{

    /**
     * @brief
     * This is the basic non-concurrent approach of matrix multiplication
     * No use of multithreading
     *
     * @param matrix_1
     * @param matrix_2
     *
     * @return The resultant matrix after multiplication.
     */
    matmul::Matrix multiply(matmul::Matrix matrix_1, matmul::Matrix matrix_2)
    {

        int m = matrix_1.size();
        int K = matrix_1[0].size();
        int n = matrix_2[0].size();
        std::vector<std::vector<int>> result(m);
        for (int i = 0; i < m; i++)
        {
            result[i] = std::vector<int>(n);
            for (int j = 0; j < n; j++)
            {
                result[i][j] = 0;
                for (int k = 0; k < K; ++k)
                {
                    result[i][j] += matrix_1[i][k] * matrix_2[k][i];
                }
            }
        }
        return result;
    }

} // namespace

int main()
{
    int m, k, n; // m1 is of dims (m,k) and m2 is of dim (k,n) result is (m,n)

    int num_threads;
    std::cin >> num_threads;

    std::cin >> m >> n;
    std::cin >> k;

    std::vector<std::vector<int>> matrix_1(m);
    std::vector<std::vector<int>> matrix_2(k);

    {
        for (int i = 0; i < m; i++)
        {
            matrix_1[i] = std::vector<int>(k);
            for (int j = 0; j < k; j++)
            {
                std::cin >> matrix_1[i][j];
            }
        }
    }

    {
        for (int i = 0; i < k; i++)
        {
            matrix_2[i] = std::vector<int>(n);
            for (int j = 0; j < n; j++)
            {
                std::cin >> matrix_2[i][j];
            }
        }
    }

    {
        matmul::MatrixMultiplier matrix_multiplier(num_threads, matrix_1, matrix_2, false);
        auto start_time = std::chrono::system_clock::now();

        auto result = matrix_multiplier.getResult();

        auto end_time = std::chrono::system_clock::now();
        auto time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::cout << "Time taken:" << time_taken << std::endl;
        std::cout << "Resultant Matrix:" << std::endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << result[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}