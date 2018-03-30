#ifndef TESTER_H
#define TESTER_H

bool basicBoardMechanics() {
    std::cout <<"------------- TESTER -------------" << std::endl;
    Grid grid;
    if(!grid.add(16, 5)) {
        return false;
    }
    if(grid.add(16,4)) {
        return false;
    }
    if(grid.add(16, 85)) {
        return false;
    }
    if(!grid.cancelPreviousChange()) {
        return false;
    }
    grid.add(16,5);
    if(!grid.resetBoard()) {
        return false;
    }
    return true;
}


bool tester() {
    if(!basicBoardMechanics()) {
        return false;
    }


    return true;
}




#endif