#include <iostream>
#include "Grid.h"
#include "tester.h"

int main() {
    bool isWorking = tester();
    if(!isWorking) {
        std::cout << "Program failed!" << std::endl;
    }
    return 0;    
}

// need to identify which one was the most recently added and which ones are part of the initial;