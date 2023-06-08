#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    FrostWeaveBag<int, int> map;

    map.put(1, 1);
    std::cout << map.get(1) << "\n"; 
    std::cout << *map.get(1) << "\n"; 
    map.put(1, 2);
    std::cout << map.get(1) << "\n"; 
    std::cout << *map.get(1) << "\n"; 

    return 0;
}