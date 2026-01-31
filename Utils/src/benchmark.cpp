#include <Utils/benchmark.h>
#include <chrono>
#include <algorithm>
#include <iostream>

void benchmark(const std::vector<std::pair<std::string, std::function<void()>>>
                   &operations,
               int iterations, bool show_fastest) {
    
    std::vector<std::pair<std::string, long long>> results;
    
    // Run each operation and measure time
    for (const auto& [name, operation] : operations) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            operation();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        results.emplace_back(name, duration);
        std::cout << name << ":  " << duration << " ns\n";
    }
    
    // Find fastest operation
    if (show_fastest && !results.empty()) {
        auto fastest = std::min_element(results.begin(), results.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });
        std::cout << "\n[Fastest: " << fastest->first << "]\n\n";
        
        // Show speedups relative to fastest
        for (const auto& [name, duration] : results) {
            if (name != fastest->first && fastest->second > 0) {
                double speedup = static_cast<double>(duration) / fastest->second;
                std::cout << fastest->first << " is " << speedup << "x faster than " << name << "\n";
            }
        }
        std::cout << "\n";
    }
}