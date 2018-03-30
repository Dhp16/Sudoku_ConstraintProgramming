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

Grid::Grid(): _latestIndexChanged(81),  _entities(27, std::vector<unsigned short*>(9)) { // after last digit
    _grid.resize(81);
    std::string grid ="060090305004820009070000640000035860690080054025760000016000080900043500507010090";
    stringToVector(grid);
    _initialGrid = _grid;
    bool isValidGrid = isValid();
    bool isSolution = isValid(true);
    setupDomains();
    mapIndexToSquare();
    domainForEach();

    for(unsigned int i = 0; i < _domainForEachIndex.size(); ++i) {
        std::cout << i << "  " << _domainForEachIndex[i].size() << std::endl;
    }


    std::cout <<"isValid: " << printBoolean(isValidGrid) << std::endl;
    std::cout <<"isSolution: " << printBoolean(isSolution) << std::endl;
}

Grid::~Grid(){}

void Grid::stringToVector(const std::string& grid) {
    for(unsigned short i = 0; i < grid.size(); ++i) {
        _grid[i] = (unsigned short)grid[i]-48;
    }
    return;
}

bool Grid::isValid(const bool isSolutionCheck){
    unsigned short nEntities = 0;
    for(unsigned int i = 0; i < 9; ++i) {
        createLine(i, _entities[i]);
        createColumn(i, _entities[i+9]);
        createSquare(i, _entities[i+18]);
    }
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
        std::vector<unsigned short> entitiesToCheck(3); // indices only
        entitiesToCheck[0] = std::floor(i / 9); // line to check
        entitiesToCheck[1] = (i % 9 ) +9; // column to check
        entitiesToCheck[2] = _indexToSquare[i]+18; // square to check
        for(unsigned short j = 0; j < 3; ++j) {
            for(unsigned short k = 0; k < 9; ++k) {
                _domainForEachIndex[i].erase(*_entities[entitiesToCheck[j]][k]);
            }
        }
    }
}
void Grid::setupDomains() {
    _domainForEachIndex.resize(81);
    std::set<unsigned short> options;
    for (unsigned short i = 0; i < 9; ++i) {
        options.insert(i);
    }
    for(unsigned short i = 0; i < 81; ++i) {
        _domainForEachIndex[i] = options;
    }
}
