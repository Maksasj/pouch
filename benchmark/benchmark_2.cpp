#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <list>
#include <deque>
#include <random>
#include <map>

#include "benchmark.h"
#include "pouch.h"

int main () {
    using namespace pouch;
    using namespace std;
    using namespace chrono;

    const unsigned int test_sample_data_size = 1'000'000;

    {
        cout << "\nstd::vector<int>\n";

        vector<int> arr;

        testOperation("Push back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.push_back(i);
        });

        testOperation("Get at", [&]() {
            auto p = 0;
            for(auto i = 0; i < test_sample_data_size - 1; ++i)
                p = arr.at(i);
        });

        testOperation("Pop back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.pop_back();
        });
    }

    {
        cout << "\nstd::deque<int>\n";

        deque<int> arr;

        testOperation("Push back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.push_back(i);
        });

        testOperation("Get at", [&]() {
            auto p = 0;
            for(auto i = 0; i < test_sample_data_size - 1; ++i)
                p = arr.at(i);
        });

        testOperation("Pop back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.pop_back();
        });
    }

    {
        cout << "\nstd::list<int>\n";

        list<int> arr;

        testOperation("Push back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.push_back(i);
        });

        testOperation("Pop back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.pop_back();
        });
    }

    {
        cout << "\npouch::HoleyPouch<int>\n";

        HoleyPouch<int, 0> arr;

        testOperation("Push back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.push_on_top(i);
        });

        testOperation("Get at", [&]() {
            auto p = 0;
            for(auto i = 0; i < test_sample_data_size - 1; ++i)
                arr.get(i);
        });

        testOperation("Pop back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.pop_top();
        });
    }

    {
        cout << "\npouch::HoleyPouchCompact<int>\n";

        HoleyPouchCompact<int, 0, 100> arr;

        testOperation("Push back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.push_on_top(i);
        });

        testOperation("Get at", [&]() {
            auto p = 0;
            for(auto i = 0; i < test_sample_data_size - 1; ++i)
                arr.get(i);
        });

        testOperation("Pop back", [&]() {
            for(auto i = 0; i < test_sample_data_size; ++i)
                arr.pop_top();
        });
    }

    return 0;
}