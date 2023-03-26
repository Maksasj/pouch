#include <string>
#include <iostream>

#include "pouch.h"

int main () {
    using namespace std;
    using namespace pouch;

    {
        FrostWeaveBag<int, int> dictionary;

        dictionary.put(1, 5);
        dictionary.put(9, 1);

        cout << dictionary.size() << "\n"; // '2'
        
        auto e = dictionary.get(9).value(); // Note .get() returns optional type 
        cout << e << "\n"; // '1'
        
        dictionary.erase(1); // Erase by key
    }

    {   /* Space focused implementation */
        HoleyPouch<int> stack;

        stack.push_on_top(5);
        stack.push_on_top(9);
        stack.push_on_top(4);
        stack.push_on_top(1);

        cout << stack.size() << "\n"; // '4'

        stack.pop_top(); // pops 1
        stack.pop_top(); // pops 4

        std::cout << stack.get_on_top() << "\n"; // '9'
        
        cout << stack.size() << "\n"; // '2'

        cout << stack.get(0) << "\n"; // '9'
        cout << stack.get(1) << "\n"; // '5'
        
        stack.set(0, 11);
        stack.set(1, 12);

        cout << stack.get(0) << "\n"; // '11'
        cout << stack.get(1) << "\n"; // '12'
    }

    {   /* Space focused implementation */
        HoleyPouchCompact<int> stack;

        stack.push_on_top(5);
        stack.push_on_top(9);
        stack.push_on_top(4);
        stack.push_on_top(1);

        cout << stack.size() << "\n"; // '4'

        stack.pop_top(); // pops 1
        stack.pop_top(); // pops 4

        std::cout << stack.get_on_top() << "\n"; // '9'
        
        cout << stack.size() << "\n"; // '2'

        cout << stack.get(0) << "\n"; // '9'
        cout << stack.get(1) << "\n"; // '5'

        stack.set(0, 11);
        stack.set(1, 12);

        cout << stack.get(0) << "\n"; // '11'
        cout << stack.get(1) << "\n"; // '12'
    }

    return 0;
}