#ifndef TESTER_H
#define TESTER_H

#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

std::vector<std::pair<std::string, std::string>> readTestcases() {
    std::vector<std::pair<std::string, std::string>> testcases;
    for(unsigned int i = 0; i < 8; ++i) {
        std::string fileName;
        switch(i) {
            case 0:
                fileName = "easy";
                break;
            case 1:
                fileName = "hard";
                break;
            case 2:
                fileName = "evil_fromExtremeSudokuInfo";
                break;
            case 3:
                fileName = "excessive_fromExtremeSudokuInfo";
                break;
            case 4:
                fileName = "egregious_fromExtremeSudokuInfo";
                break;
            case 5:
                fileName = "excruciating_fromExtremeSudokuInfo";
                break;
            case 6:
                fileName = "extreme_fromExtremeSudokuInfo";
                break;
            case 7:
                fileName = "impossible";
                break;
        }
        std::string folder = std::string("testcases//");
        std::string extention =  std::string(".txt");
        std::string pathAndfileName = folder + fileName + extention;
        std::fstream reader;
        reader.open(pathAndfileName);
        std::string inputGrid;
        reader >> inputGrid;
        testcases.push_back(std::pair<std::string,std::string>(fileName, inputGrid));
    }
    return testcases;
}
std::vector<std::pair<std::string, std::string>> development() {
    std::vector<std::pair<std::string, std::string>> testcases(6);
    for(unsigned int i = 0; i < 6; ++i) {
        std::string fileName;
        switch(i) {
            case 0:
                fileName = "test";
                break;
            case 1:
                fileName = "test2";
                break;
            case 2:
                fileName = "NakedSubsetTester2";
                break;
            case 3:
                fileName = "HiddenSubsetTester";
                break;
            case 4:
                fileName = "XWing";
                break;
            case 5:
                fileName = "Skyscraper";
                break;
        }
        testcases[i].first = fileName;
        std::string folder = std::string("testcases//");
        std::string extention =  std::string(".txt");
        fileName = folder + fileName + extention;
        std::fstream reader;
        reader.open(fileName);
        std::string inputGrid;
        reader >> inputGrid;
        testcases[i].second = inputGrid;
    }
    return testcases; 
}

bool basicBoardMechanics(std::string testcase) {
    Grid grid(testcase);
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

bool solving(std::string testcase) {
    std::cout <<"------------- start of solver -------------" << std::endl;
    Grid grid(testcase);
    return grid.solve();
    return true;
    std::cout <<"-------------  end of solver  -------------" << std::endl;
}

bool tester() {
    std::cout <<"------------- START OF TESTER -------------" << std::endl;

    std::vector<std::pair<std::string,std::string>> testcases;
//    testcases = development();
    testcases = readTestcases();
    bool isSuccess = true;
    for(unsigned int i = 0; i < testcases.size(); ++i) {
        std::cout <<"\n\n======================================================";
        std::cout <<"\n\n-----------> Starting testcase: " << testcases[i].first << std::endl;
        // if(!basicBoardMechanics(testcases[i].second)) {
        //     std::cout << "Board mechanics failed" << std::endl;
        //     continue;
        // }
        clock_t begin = clock();
        if(!solving(testcases[i].second)) {
            std::cout << "Solver failed" << std::endl;
        }
        clock_t end = clock();
        std::cout << "Solving took: " << double(end - begin) / CLOCKS_PER_SEC << " seconds." << std::endl;
    }
    std::cout <<"-------------  END OF TESTER  -------------" << std::endl;
    return isSuccess;
}


// need to go through an example of dependency --> create a grid with specific condition and test it

#endif