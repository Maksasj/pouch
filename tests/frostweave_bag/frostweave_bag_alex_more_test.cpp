#include "../test.h"

int main() {
    using namespace pouch;

    TEST_CASE {
        FrostWeaveBag<int, std::string> table;

        ensure(table.has(1) == false);
        table.put(1, "hello");
        ensure(table.has(1) == true);
        ensure(*table.get(1) == "hello");
        table.erase(1);
        ensure(table.has(1) == false);
        ensure(table.get(1) == nullptr);

        table.put(1, "a");
        table.put(17, "b");
        table.put(9, "c");

        ensure(table.has(9) == true);
        ensure(table.has(17) == true);
        ensure(table.has(1) == true);
        ensure(*table.get(17) == "b");

        table.erase(17);
        ensure(table.has(17) == false);

        ensure(*table.get(1) == "a");
        auto prevSize = table.size();
        table.put(1, "f");
        // Size should not change
        ensure(table.size() == prevSize);
        ensure(*table.get(1) == "f");
    }

    TEST_CASE {
        FrostWeaveBag<int, int> table;

        table.put(1, 100);
        table.put(2, 100);
        table.put(3, 100);
        table.put(4, 100);
        table.put(5, 100);
        ensure(table.size() == 5);
        table.erase(5);
        ensure(table.size() == 4);
        table.erase(4);
        table.erase(3);
        table.erase(2);
        table.erase(1);
        ensure(table.size() == 0);
    }

    TEST_CASE {
        FrostWeaveBag<std::string, std::string> table;

        ensure(table.has("") == false);
        ensure(table.has("a") == false);
        ensure(table.has("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == false);
        table.erase("");
        table.erase("a");
        table.erase("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

        table.put("a", "value1");
        table.put("a", "value2");
        table.put("a", "value3");

        ensure(table.size() == 1);
        ensure(*table.get("a") == "value3");

        table.erase("");
        table.erase("b");
        table.erase("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

        ensure(table.has("a") == true);

        table.put("b", "gg");
        table.put("c", "gg");
        table.put("d", "gg");

        ensure(table.size() == 4);

        table.erase("a");

        ensure(table.has("b") && table.has("c") && table.has("d") == true);

        table.erase("c");
    }

    return 0;   
}