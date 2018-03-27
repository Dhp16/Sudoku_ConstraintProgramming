#include "Grid.h"

#include <set>
#include <iostream>
#include <utility>

Grid::Grid() {
    _grid.resize(81);
    std::string grid ="060090305004820009070000640000035860690080054025760000016000080900043500507010090";
    stringToVector(grid);
    bool success = createAndCheckAllEntities();
    std::cout <<" Success: " << success << std::endl;
}

Grid::~Grid(){}

void Grid::stringToVector(const std::string& grid) {
    for(unsigned short i = 0; i < grid.size(); ++i) {
        _grid[i] = (unsigned short)grid[i]-48;
    }
    return;
}

bool Grid::createAndCheckAllEntities() const{
    std::vector<std::vector<unsigned short>> entities(27, std::vector<unsigned short>(9));
    unsigned short nEntities = 0;
    for(unsigned int i = 0; i < 9; ++i) {
        createLine(i, entities[i]);
        createColumn(i, entities[i+9]);
        createCube(i, entities[i+18]);
    }
    for(unsigned short i = 0; i < 27; ++i) {
        std::set<unsigned short> entity;
        for(unsigned short j = 0; j < 9; ++j) {
            std::pair<std::set<unsigned short>::iterator, bool> success =
                entity.insert(entities[i][j]);
            if(!success.second && entities[i][j] != 0) {
                std::cout <<"Failed on entity: " << i << std::endl;
                return false;
            }
        }
    }
    return true;
}

void Grid::createLine(const unsigned short index, std::vector<unsigned short> &line) const{
    for(unsigned short i = 0; i < 9; ++i) {
        line[i] = _grid[i+index*9];
    }
}
void Grid::createColumn(const unsigned short index, std::vector<unsigned short> &column) const{
    for(unsigned short i = 0; i < 9; ++i) {
        column[i] = _grid[i*9+index];
    }
}
void Grid::createCube(const unsigned short index, std::vector<unsigned short> &cube) const{
    unsigned short index0;
    if(index < 3) {
        index0 = index*3;
        cube[0] = _grid[index*3];
    }
    else if(index < 6) {
        index0 = 27 + 3*(index-3);
        cube[0] = _grid[27 + 3*(index-3)];
    }
    else {
        index0 = 54 + 3*(index-6);
        cube[0] = _grid[54 + 3*(index-6)];
    }
    for(unsigned short i = 1; i < 9; ++i) {
        if(i < 3) {
            cube[i] = _grid[index0 + i];
        }
        else if(i < 6) {
            cube[i] = _grid[index0 + i-3 + 9];
        }
        else {
            cube[i] = _grid[index0 + i-6 + 18];
        }
    }
}
