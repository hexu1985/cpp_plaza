#include "list.h"
#include <iostream>
 
int main()
{
    list<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
    if (!letters.empty()) {
        std::cout << "The last character is: " << letters.back() << '\n';
    }  
}
