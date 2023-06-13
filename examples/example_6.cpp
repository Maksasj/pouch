#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace pouch;

    // HoleyPouch<int> arr(4, 1);
// 
    // //std::cout << arr.size() << "\n";
// 
    // arr.insert(0, 2);
    // // arr.push_on_top(99);
// 
    // //std::cout << arr.get(0) << "\n";
// 
    // //std::cout << arr.size() << "\n";
// 
    // for (size_t i = 0; i < arr.size(); ++i) {
    //     std::cout << arr.get(i) << "\n";
    // }

    RottenSnag<int> a;
    a.put(8);
    a.put(4);
    a.put(1);
    a.put(12);
    a.put(10);
    a.put(15);
    a.trace();

    return 0;
}