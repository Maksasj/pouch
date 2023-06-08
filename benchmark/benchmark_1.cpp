#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <random>
#include <map>

#include "pouch.h"

int main () {
    using namespace pouch;
    using namespace std;
    using namespace chrono;

    const unsigned int test_sample_data_size = 100'000;

    vector<int> data;
    for(int i = 0; i < test_sample_data_size; ++i) {
        data.push_back(i);
    }

    auto rng = default_random_engine {};
    shuffle(begin(data), end(data), rng);

    {
        cout << "\npouch::FrostWeaveBag<int, int>: \n";
        FrostWeaveBag<int, int> container(100);
        steady_clock::time_point begin = steady_clock::now();

        for(const auto &c : data) {
            container.put(c, c);
        }

        steady_clock::time_point end = steady_clock::now();
        cout << "    Insertion time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
        cout << "    Load factor: " << container.load_factor() << " / " << container.max_load_factor() << "\n";

        begin = steady_clock::now();

        for(const auto &c : data) {
            auto p = container.get(c);

            if(p == nullptr) {
                std::cout << "WTF !\n";
            } else {
                std::cout << "wtf";
            }
        }

        end = steady_clock::now();
        cout << "    Get time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";

        begin = steady_clock::now();
        for(const auto &c : data) {
            container.erase(c);
        }
        end = steady_clock::now();
        cout << "    Erase time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
    }

    {
        cout << "\nC++ std::unordered_map<int, int>: \n";
        unordered_map<int, int> map;
        steady_clock::time_point begin = steady_clock::now();

        for(const auto &c : data) {
            map[c] = c;
        }

        steady_clock::time_point end = steady_clock::now();
        cout << "    Insertion time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
        cout << "    Load factor: " << map.load_factor() << " / " << map.max_load_factor() << "\n";

        begin = steady_clock::now();

        for(const auto &c : data) {
            auto p = map[c];
        }

        end = steady_clock::now();
        cout << "    Get time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";

        begin = steady_clock::now();

        for(const auto &c : data) {
            map.erase(c);
        }

        end = steady_clock::now();
        cout << "    Erase time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
    }

    {
        cout << "\nC++ std::map<int, int>: \n";
        map<int, int> map;
        steady_clock::time_point begin = steady_clock::now();

        for(const auto &c : data) {
            map[c] = c;
        }

        steady_clock::time_point end = steady_clock::now();
        cout << "    Insertion time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";

        begin = steady_clock::now();

        for(const auto &c : data) {
            auto p = map[c];
        }

        end = steady_clock::now();
        cout << "    Get time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";

        begin = steady_clock::now();

        for(const auto &c : data) {
            map.erase(c);
        }

        end = steady_clock::now();
        cout << "    Erase time for: " << test_sample_data_size << ", took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
    }


    return 0;
}