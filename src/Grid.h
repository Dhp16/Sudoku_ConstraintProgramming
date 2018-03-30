#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class Grid
{
  public:
    Grid();
    ~Grid();
    bool isValid(const bool isSolutionCheck=false) const;

  private:
    void stringToVector(const std::string& grid);
    void createLine(const unsigned short index, std::vector<unsigned short>& line) const;
    void createColumn(const unsigned short index, std::vector<unsigned short>& column) const;
    void createCube(const unsigned short index, std::vector<unsigned short>& cube) const;

    std::vector<unsigned short> _grid;
};


#endif // GRID_H