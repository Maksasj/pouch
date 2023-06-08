#include "../test.h"

int main() {
    using namespace pouch;

    TEST_CASE {
        HoleyPouchCompact<int> arr(4, 1);

        ensure(arr.size() == 4);

        arr.insert(0, 2);

        ensure(arr.size() == 5);

        for (size_t i = 0; i < 5; ++i) {
            if (i == 0) {
                ensure(arr.get(i) == 2);
            } else {
                ensure(arr.get(i) == 1);
            }
        }

        arr.insert(0, 2);
        arr.insert(0, 2);
        arr.insert(0, 2);

        arr.insert(arr.size(), 42);

        ensure(arr.get(arr.size() - 1) == 42);
        arr.get(arr.size() - 1) = 24;
        ensure(arr.get(arr.size() - 1) == 24);
    }

    TEST_CASE {
        HoleyPouchCompact<int> arr(2, 2);

        // arr.erase(0);
        // arr.erase(0);
        
        arr.pop_top();
        arr.pop_top();

        ensure(arr.size() == 0);

        ensure_throw(arr.pop_top(), std::out_of_range);


        arr.insert(0, 1);
        arr.insert(0, 1);
        arr.insert(0, 1);
        arr.insert(0, 1);
        arr.insert(0, 1);

        ensure(arr.size() == 5);

        for(size_t i = 0; i < arr.size(); ++i) {
            ensure(arr.get(i) == 1);
        }
    }

    return 0;   
}