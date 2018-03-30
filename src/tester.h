#ifndef TESTER_H
#define TESTER_H

bool basicBoardMechanics() {
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

bool solving() {
    std::cout <<"------------- start of solver -------------" << std::endl;
    Grid grid;
    return grid.solve();
    std::cout <<"-------------  end of solver  -------------" << std::endl;
}


bool tester() {
    std::cout <<"------------- START OF TESTER -------------" << std::endl;
    // if(!basicBoardMechanics()) {
    //     return false;
    // }
    if(!solving()) {
       return false;
    }

    std::cout <<"-------------  END OF TESTER  -------------" << std::endl;
    return true;
}




#endif