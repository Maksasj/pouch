#include "pouch.h"
#include <string>

int main () {
    using namespace pouch;

    FrostWeaveBag<std::string, int> container;

    container.put("key1", 12);
    container.put("key2", 24);

    auto p1 = container.get("key1");
    auto p2 = container.get("key2");

    container.erase("key1");

    long s = container.size();

    return 0;
}