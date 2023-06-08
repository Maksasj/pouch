#include "../test.h"

int main() {
    using namespace pouch;

    TEST_CASE {
        FrostWeaveBag<int, int> map;

        map.erase(0);

        map.put(5, 5);

        ensure(map.size() == 1);
        ensure(map.has(5) == true);
        ensure(map.has(4) == false);
        ensure(*map.get(5) == 5);
        ensure(map.get(4) == nullptr);

        map.erase(5);

        ensure(map.size() == 0);
        ensure(map.has(5) == false);
        ensure(map.get(5) == nullptr);

        map.erase(0);
        map.erase(1);

        map.put(5, 5);
        map.put(6, 6);
        map.put(7, 7);

        ensure(map.size() == 3);
        ensure(map.has(5) == true);
        ensure(map.has(6) == true);
        ensure(map.has(7) == true);
        ensure(map.has(8) == false);
        ensure(*map.get(5) == 5);
        ensure(*map.get(6) == 6);
        ensure(*map.get(7) == 7);

        map.put(3, 3);
        map.put(4, 4);
        map.put(2, 2);

        map.erase(5);

        ensure(map.size() == 5);
        ensure(map.has(5) == false);
        ensure(map.has(2) == true);
        ensure(map.has(3) == true);
        ensure(map.has(4) == true);
        ensure(map.has(6) == true);
        ensure(map.has(7) == true);

        map.erase(7);
        map.erase(6);

        ensure(map.size() == 3);
        ensure(map.has(6) == false);
        ensure(map.has(2) == true);
        ensure(map.has(3) == true);
        ensure(map.has(4) == true);
    }

    TEST_CASE {
        FrostWeaveBag<int, int> map;

        ensure(map.size() == 0);    
    }

    struct Data {
        int integerField;
        double doubleField;

        Data(int integerField, double doubleField) : integerField(integerField), doubleField(doubleField) {}
    };

    TEST_CASE {
        Data d(42, 1.0);

        FrostWeaveBag<int, Data> map;

        map.put(0, d);

        ensure(map.has(0) == true);
        ensure(map.get(0)->integerField == 42);
        ensure(map.get(0)->doubleField == 1.0);

        d.integerField = 21;

        ensure(map.get(0)->integerField == 42);  
    }

    TEST_CASE {
        FrostWeaveBag<int, int> map;

        map.erase(1);
        map.put(1, 1);

        ensure(map.size() == 1);
        ensure(map.has(1) == true);
        ensure(*map.get(1) == 1);

        map.erase(1);

        ensure(map.size() == 0);
        ensure(map.has(1) == false);
        ensure(map.get(1) == nullptr);

        const int n = 255;
        for (int i = 0; i < n; ++i) {
            map.put(i, i);
        }

        ensure(map.size() == n);
        ensure(map.has(0) == true);
        ensure(map.has(n - 1) == true);
        ensure(map.has(n) == false);
        ensure(map.get(n) == nullptr);
    }

    TEST_CASE {
        FrostWeaveBag<int, int> map;

        map.put(1, 1);

        ensure(map.size() == 1);
        ensure(*map.get(1) == 1);

        map.put(1, 2);

        ensure(map.size() == 1);
        ensure(*map.get(1) == 2);

        map.put(2, 2);
        map.erase(1);
        
        ensure(map.size() == 1);
        ensure(map.get(1) == nullptr);
        ensure(*map.get(2) == 2);
    }

    return 0;   
}