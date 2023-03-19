#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    FrostWeaveBag<std::string, int> container(5);

    container.put("key1", 1);
    container.put("key2", 2);
    container.put("key3", 3);
    container.put("key4", 4);
    container.put("key5", 5);
    container.put("key6", 6);
    container.put("key7", 7);

    std::cout << "Bag size: " << container.size() << "\n";

    container.erase("key8");
    container.erase("key7");

    std::cout << "Bag size: " << container.size() << "\n";

    container.erase("key1");
    container.erase("key2");
    container.erase("key3");
    container.erase("key4");
    container.erase("key5");
    container.erase("key6");
    
    std::cout << "Bag size: " << container.size() << "\n";

    return 0;
}