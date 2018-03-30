#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <map>
#include <set>

class Grid
{
  public:
    Grid();
    ~Grid();
    bool isValid(const bool isSolutionCheck=false);

    bool add(const unsigned short index, const unsigned short newDigit);
    bool cancelPreviousChange();
    bool resetBoard();

  private:
    void stringToVector(const std::string& grid);
    void createLine(const unsigned short index, std::vector<unsigned short*>& line);
    void createColumn(const unsigned short index, std::vector<unsigned short*>& column);
    void createSquare(const unsigned short index, std::vector<unsigned short*>& cube);
    void domainForEach();
    void mapIndexToSquare();
    void setupDomains();

    std::vector<std::vector<unsigned short*>> _entities;
    std::vector<unsigned short> _grid;
    std::vector<unsigned short> _initialGrid;
    unsigned short _latestIndexChanged;
    std::map<unsigned short, unsigned short> _indexToSquare;
    std::vector<std::set<unsigned short>> _domainForEachIndex;
};


#endif // GRID_H