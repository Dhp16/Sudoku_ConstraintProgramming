#include "Grid.h"

#include <iostream>
#include <utility>
#include <string>
#include <cmath>

#define isLegit(a) (a > 0 && a < 10)

std::string printBoolean(const bool isTrue) {
    if(isTrue) {
        return std::string("true");
    } else {
        return std::string("false");
    }
}

// TEMP
void addDigitsForSquare(const unsigned short squareNumber, std::set<unsigned short> &linkedIndices)
{
    switch (squareNumber)
    {
    case 0:
        linkedIndices.insert(0);
        linkedIndices.insert(1);
        linkedIndices.insert(2);
        linkedIndices.insert(9);
        linkedIndices.insert(10);
        linkedIndices.insert(11);
        linkedIndices.insert(18);
        linkedIndices.insert(19);
        linkedIndices.insert(20);
        break;
    case 1:
        linkedIndices.insert(3);
        linkedIndices.insert(4);
        linkedIndices.insert(5);
        linkedIndices.insert(12);
        linkedIndices.insert(13);
        linkedIndices.insert(14);
        linkedIndices.insert(21);
        linkedIndices.insert(22);
        linkedIndices.insert(23);
        break;
    case 2:
        linkedIndices.insert(6);
        linkedIndices.insert(7);
        linkedIndices.insert(8);
        linkedIndices.insert(15);
        linkedIndices.insert(16);
        linkedIndices.insert(17);
        linkedIndices.insert(24);
        linkedIndices.insert(25);
        linkedIndices.insert(26);
        break;
    case 3:
        linkedIndices.insert(27);
        linkedIndices.insert(28);
        linkedIndices.insert(29);
        linkedIndices.insert(36);
        linkedIndices.insert(37);
        linkedIndices.insert(38);
        linkedIndices.insert(45);
        linkedIndices.insert(46);
        linkedIndices.insert(47);
        break;
    case 4:
        linkedIndices.insert(30);
        linkedIndices.insert(31);
        linkedIndices.insert(32);
        linkedIndices.insert(39);
        linkedIndices.insert(40);
        linkedIndices.insert(41);
        linkedIndices.insert(48);
        linkedIndices.insert(49);
        linkedIndices.insert(50);
        break;
    case 5:
        linkedIndices.insert(33);
        linkedIndices.insert(34);
        linkedIndices.insert(35);
        linkedIndices.insert(42);
        linkedIndices.insert(43);
        linkedIndices.insert(44);
        linkedIndices.insert(51);
        linkedIndices.insert(52);
        linkedIndices.insert(53);
        break;
    case 6:
        linkedIndices.insert(54);
        linkedIndices.insert(55);
        linkedIndices.insert(56);
        linkedIndices.insert(63);
        linkedIndices.insert(64);
        linkedIndices.insert(65);
        linkedIndices.insert(72);
        linkedIndices.insert(73);
        linkedIndices.insert(74);
        break;
    case 7:
        linkedIndices.insert(57);
        linkedIndices.insert(58);
        linkedIndices.insert(59);
        linkedIndices.insert(66);
        linkedIndices.insert(67);
        linkedIndices.insert(68);
        linkedIndices.insert(75);
        linkedIndices.insert(76);
        linkedIndices.insert(77);
        break;
    case 8:
        linkedIndices.insert(60);
        linkedIndices.insert(61);
        linkedIndices.insert(62);
        linkedIndices.insert(69);
        linkedIndices.insert(70);
        linkedIndices.insert(71);
        linkedIndices.insert(78);
        linkedIndices.insert(79);
        linkedIndices.insert(80);
        break;
    }
}
int Grid::domainTotal(std::vector<std::set<unsigned short>> domainOptions) {
    int counter = 0;
    int counterV2 = 0;
    int counterV3 = 0, counterV4 = 0;
    for (unsigned int i = 0; i < domainOptions.size(); ++i)
    {
        if(domainOptions[i].empty()) {
            counterV2++;
        }
        if(domainOptions[i].size() == 1) {
            counterV3++;
        }
        for (std::set<unsigned short>::iterator it = domainOptions[i].begin(); it != domainOptions[i].end();
             ++it){
            counter++;
        }
    }
    for(unsigned int i = 0; i < 81; ++i) {
        if(_grid[i] == 0)
            counterV4++;
    }
    
    std::cout << "0 size domains: " << counterV2 << "  || 1 size domains: " << counterV3 << "  ||  total size: " << counter;
    std::cout << "  ||  non-0 squares remaining: " << counterV4 << std::endl;
    return counter;
}

// constructor
Grid::Grid(): _latestIndexChanged(81),  _entities(27, std::vector<unsigned short*>(9)) { // after last digit
    _grid.resize(81);
    std::string grid ="060090305004820009070000640000035860690080054025760000016000080900043500507010090";
    stringToVector(grid);
    _initialGrid = _grid;
    int counter = 0;
    for(unsigned int i = 0; i < _grid.size(); ++i) {
        if(_grid[i] != 0)
            counter++;
    }
    std::cout << counter << " numbers provided, " << 81-counter << " to find." << std::endl;
    setupEntities();
    setupDomains();
    mapIndexToSquare();
    domainForEach();

    setupIndexLinkage();

    bool isValidGrid = isValid();
    bool isSolution = isValid(true);
    std::cout <<"isValid: " << printBoolean(isValidGrid) << std::endl;
    std::cout <<"isSolution: " << printBoolean(isSolution) << std::endl;
}
Grid::~Grid(){}
//

// setup
void Grid::stringToVector(const std::string& grid) {
    for(unsigned short i = 0; i < grid.size(); ++i) {
        _grid[i] = (unsigned short)grid[i]-48;
        if(_grid[i]!= 0) {
            _goldenOriginals.insert(i);
        }
    }
    return;
}
void Grid::createLine(const unsigned short index, std::vector<unsigned short*> &line){
    for(unsigned short i = 0; i < 9; ++i) {
        line[i] = &_grid[i+index*9];
    }
}
void Grid::createColumn(const unsigned short index, std::vector<unsigned short*> &column){
    for(unsigned short i = 0; i < 9; ++i) {
        column[i] = &_grid[i*9+index];
    }
}
void Grid::createSquare(const unsigned short index, std::vector<unsigned short*> &cube){
    unsigned short index0;
    if(index < 3) {
        index0 = index*3;
        cube[0] = &_grid[index*3];
    }  else if(index < 6) {
        index0 = 27 + 3*(index-3);
        cube[0] = &_grid[27 + 3*(index-3)];
    }  else {
        index0 = 54 + 3*(index-6);
        cube[0] = &_grid[54 + 3*(index-6)];
    }
    for(unsigned short i = 1; i < 9; ++i) {
        if(i < 3) {
            cube[i] = &_grid[index0 + i];
        } else if(i < 6) {
            cube[i] = &_grid[index0 + i-3 + 9];
        } else {
            cube[i] = &_grid[index0 + i-6 + 18];
        }
    }
}
void Grid::setupEntities() {
    for(unsigned int i = 0; i < 9; ++i) {
        createLine(i, _entities[i]);
        createColumn(i, _entities[i+9]);
        createSquare(i, _entities[i+18]);
    }
}
void Grid::setupDomains() {
    _domainForEachIndex.resize(81);
    std::set<unsigned short> options;
    for (unsigned short i = 1; i < 10; ++i) {
        options.insert(i);
    }
    for(unsigned short i = 0; i < 81; ++i) {
        _domainForEachIndex[i] = options;
    }
}
void Grid::mapIndexToSquare() { 
    for(unsigned int i = 0; i < 81; ++i) {
        if((i % 9) < 3  ) {
            if(i / 9 < 3) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i, 0));
            }
            else if ( i / 9 < 6) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i,  
                    i/9 - (i/9 - 3)));
            }
            else if ( i / 9 < 9) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i, 
                    i/9 - (i/9 - 6)));
            }
        }
        else if ((i % 9) < 6) {
            if(i / 9 < 3) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i,  1));
            }
            else if ( i / 9 < 6) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i,  
                    i/9 - (i/9 - 3) +1));
            }
            else if ( i / 9 < 9) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i, 
                    i/9 - (i/9 - 6) + 1));
            }
        }
        else {
            if(i / 9 < 3) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i, 2));
            }
            else if ( i / 9 < 6) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i,  
                    i/9 - (i/9 - 3) +2));
            }
            else if ( i / 9 < 9) {
                _indexToSquare.insert(std::pair<unsigned short, unsigned short>(i,
                    i/9 - (i/9 - 6) + 2));
            }
        }
    }
}
void Grid::domainForEach() {
    for(unsigned short i = 0; i < 81; ++i) {
        if(_goldenOriginals.find(i) != _goldenOriginals.end()){
            _domainForEachIndex[i].clear();
        }
        std::vector<unsigned short> entitiesToCheck(3); // indices only
        entitiesToCheck[0] = std::floor(i / 9);     // line to check
        entitiesToCheck[1] = i % 9 + 9;              // column to check
        entitiesToCheck[2] = _indexToSquare[i] + 18;     // square to check
        
        for(unsigned short j = 0; j < 3; ++j) {
            for(unsigned short k = 0; k < 9; ++k) {
                _domainForEachIndex[i].erase(*_entities[entitiesToCheck[j]][k]);
            }
        }
    }
}
void Grid::setupIndexLinkage() {
    _indexLinkage.resize(81);
    for(unsigned int i = 0; i < 81; ++i) {
        std::set<unsigned short> linkedIndices;
        unsigned short lineNumber = std::floor(i/9);
        unsigned short columnNumber = (i % 9 );
        unsigned short squareNumber = _indexToSquare[i];
        for(unsigned short j = lineNumber*9; j < (lineNumber+1)*9; ++j ) {
            linkedIndices.insert(j);
        }
        for(unsigned short j = 0, k = columnNumber; j < 9; ++j, k+=9) {
            linkedIndices.insert(k);
        }
        addDigitsForSquare(squareNumber, linkedIndices);
        _indexLinkage[i] = linkedIndices;
    }
    return;
}
// runtime
void Grid::removeChangeFromDomains(const unsigned short index, const unsigned short digit) {
    for(unsigned int i = 0; i < _indexLinkage[index].size(); ++i) {
        _domainForEachIndex[i].erase(digit);
    }
}

// operations
bool Grid::add(const unsigned short index, const unsigned short newDigit)  {
    if(_grid[index] == 0 && isLegit(newDigit)) {
        _grid[index] = newDigit;
        _latestIndexChanged = index;
        return true;
    }  else {
        return false;
    }
}
bool Grid::cancelPreviousChange() {
    if (_latestIndexChanged < 81)  {
        _grid[_latestIndexChanged] = 0;
        return true;
    }    else    {
        return false;
    }
}
bool Grid::resetBoard() {
    _grid = _initialGrid;
    _latestIndexChanged = 81;
    return (_grid == _initialGrid);
}
// public:
bool Grid::isValid(const bool isSolutionCheck){
    for(unsigned short i = 0; i < 27; ++i) {
        std::set<unsigned short> entity;
        for(unsigned short j = 0; j < 9; ++j) {
            if(isSolutionCheck && *_entities[i][j] == 0) {
                return false;
            }
            std::pair<std::set<unsigned short>::iterator, bool> success =
                entity.insert(*_entities[i][j]);
            if(!success.second && *_entities[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}
bool Grid::solve() {
    bool jump = false;
    int counter = 0;
    while(true) {
        counter++;
        for(short int i = 0; i < 81; ++i) {
            if(_domainForEachIndex[i].size() == 1) {
                if(add(i,*_domainForEachIndex[i].begin())){
                    //removeChangeFromDomains(i, *_domainForEachIndex[i].begin());              
                    domainForEach();    // updates the domain for everypoint -> a different function could do it faster
                    jump = true;
                    break;
                }
            }
        }
        if(jump) {
            jump = false;
            continue;
        }
        break;
    }
    std::cout << "isValid: " << printBoolean(isValid()) << std::endl;
    std::cout << "isSolution: " << printBoolean(isValid(true)) << std::endl;
    print();
    return isValid(true);
}
void Grid::print() {
    std::cout <<"Grid:" << std::endl;
    for(unsigned int i = 0; i < 81; ++i) {
        if(i % 9 == 0) 
            std::cout << std::endl;
        std::cout << _grid[i] << "   ";
    }
    std::cout << std::endl;
}