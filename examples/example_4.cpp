#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    RottenSnag<int> container;

    for(int i = 0; i < 1000; ++i)
        container.put(i);

    for(int i = 0; i < 1000; ++i)
        std::cout << *container.get(i) << "\n";

    for(int i = 0; i < 1000; ++i)
        container.erase(i);

    for(int i = 0; i < 1000; ++i) {
        int* a = container.get(i);
        std::cout << *a << "\n";
    }

    return 0;
}