#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    RottenSnag<int> container;

    for(int i = 0; i < 1000; ++i)
        container.put(i);

    for(int i = 0; i < 1000; ++i)
        std::cout << container.get(i)->_value << "\n";

    for(int i = 0; i < 1000; ++i)
        container.erase(i);

    for(int i = 0; i < 1000; ++i)
        std::cout << container.get(i) << "\n";

    return 0;
}