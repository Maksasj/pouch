#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <functional>
#include <string>
#include <chrono>
#include <iostream>

void testOperation(std::string oparationTime, std::function<void(void)> lambda) {
    using namespace std;
    using namespace chrono;

    steady_clock::time_point begin = steady_clock::now();

    lambda();

    steady_clock::time_point end = steady_clock::now();
    cout << "    " << oparationTime << " took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
}

#endif
