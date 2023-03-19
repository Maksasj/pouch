#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    HoleyPouch<int, 100> stack;

    std::cout << stack.size() << "\n";
    
    stack.push_on_top(5);
    std::cout << "On top: " << stack.get_on_top() << "\n";
    std::cout << "Stack size: " << stack.size() << ", capacity: " << stack.capacity() << "\n";

    stack.push_on_top(13);
    std::cout << "On top: " << stack.get_on_top() << "\n";
    std::cout << "Stack size: " << stack.size() << ", capacity: " << stack.capacity() << "\n";

    stack.pop_top();
    std::cout << "On top: " << stack.get_on_top() << "\n";
    std::cout << "Stack size: " << stack.size() << ", capacity: " << stack.capacity() << "\n";

    for(int i = 0; i < 24; ++i) {
        stack.push_on_top(i);
    }
    
    std::cout << "On top: " << stack.get_on_top() << "\n";
    std::cout << "Stack size: " << stack.size() << ", capacity: " << stack.capacity() << "\n";

    for(int i = 0; i < 24; ++i) {
        stack.pop_top();
    }

    std::cout << "On top: " << stack.get_on_top() << "\n";
    std::cout << "Stack size: " << stack.size() << ", capacity: " << stack.capacity() << "\n";

    return 0;
}