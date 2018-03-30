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
