#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <list>
#include <deque>
#include <random>
#include <map>
#include <set>

#include "benchmark.h"

using namespace pouch;
using namespace std;

vector<int> to_vector(const set<int>& s1) {
    return vector<int>(s1.begin(), s1.end());
}

vector<int> to_vector(FrostWeaveBag<int, int>& s1) {
    vector<int> out;

    for(auto it = s1.begin(); it != s1.end(); ++it) {
        out.push_back((*it).second);
    }

    return out;
}

void ensure_sets_are_equal(set<int>& s1, FrostWeaveBag<int, int>& s2) {
    ensure(s1.size() == s2.size());

    auto s1v = to_vector(s1);
    sort(s1v.begin(), s1v.end());
    
    auto s2v = to_vector(s2);
    sort(s2v.begin(), s2v.end());

    for(size_t i = 0; i < s1.size(); ++i)
        ensure(s1v[i] == s2v[i]);
}

int main () {
    srand(time(0));

    for(auto it = 0; it < 10; ++it) {
        cout << "Sample test " << it << "\n";
        const int sample = 10'000; 

        set<int> s1;
        FrostWeaveBag<int, int> s2;

        cout << "    Generating sets\n";
        for(int i = -(sample / 2); i < (sample / 2); ++i) {
            s1.insert(i);
            s2.put(i, i);
        }

        cout << "    Doing operations\n";
        for(int i = 0; i < 10'000; ++i) {
            auto r = rand() % 4;
            auto v = rand() % static_cast<int>(sample * 1.5);

            switch (r) {
                case 0:
                    s1.insert(v);
                    s2.put(v, v);
                    break;
                case 1:
                    s1.erase(v);
                    s2.erase(v);
                    break;
                case 2:
                    s2.has(v);
                    break;
                case 3:
                    s2.get(v);
                    break;
                default:
                    break;
            }
        }

        cout << "    Done doing operations, comparing sets\n";
        ensure_sets_are_equal(s1, s2);
        cout << "    Looks like evrething is fine !\n";
    }

    return 0;
}