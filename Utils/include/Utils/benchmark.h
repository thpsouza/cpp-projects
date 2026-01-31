#include <functional>
#include <vector>


/**
 * @brief Generic benchmark function that compares multiple operations
 * 
 * @param operations Vector of pairs (operation_name, lambda_function)
 * @param iterations Number of times to run each operation
 * @param show_fastest If true, highlights which operation is fastest
 */
void benchmark(const std::vector<std::pair<std::string, std::function<void()>>>& operations,
               int iterations = 2,
               bool show_fastest = true);

// benchmark({
//     {"transpose2() - naive", [&]() { test.transpose2(); }},
//     {"transpose() - block", [&]() { test.transpose(); }},
//     {"transpose3() - other", [&]() { test.transpose3(); }}
// }, 2);


// Matrix M1({
//     {1, 2, 3, 4, 5},
//     {1, 2, 3, 4, 5},
//     {1, 2, 3, 4, 5},
//     {1, 2, 3, 4, 5},
//     {1, 2, 3, 4, 5}
// });

// Matrix M2({
//     {6, 7, 8, 9, 10},
//     {6, 7, 8, 9, 10},
//     {6, 7, 8, 9, 10},
//     {6, 7, 8, 9, 10},
//     {6, 7, 8, 9, 10}
// });

// benchmark({
//     {"dot() - naive", [&]() { M1.dot(M2); }},
//     {"dot2() - block", [&]() { Matrix::dot2(M1, M2); }},
// }, 100);
