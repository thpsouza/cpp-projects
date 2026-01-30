#include <iostream>

/**
 * @brief Easier printing
 * 
 * @tparam Args
 * @param args  
 */
template<typename ...Args>
void print(Args && ...args) {
    (std::cout << ... << args);
}

