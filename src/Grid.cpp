#include "Grid.h"

#include <algorithm>
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
    std::cout << "  || squares remaining: " << counterV4 << std::endl;
    return counter;
}

// constructor
Grid::Grid(std::string grid): _latestIndexChanged(81),  _entities(27, std::vector<unsigned short*>(9)) { // after last digit
    _grid.resize(81);
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
// tools

void Grid::indicesForLine(const unsigned short lineId, std::set<unsigned short>& lineIndices)
{
    for(unsigned short i = lineId*9; i < lineId*9+9; ++i) {
        lineIndices.insert(i);
    }
}
void Grid::indicesForColumn(const unsigned short columnId, std::set<unsigned short>& columnIndices)
{
    for(unsigned short i = 0, k = columnId; i < 9; ++i, k+=9) {
        columnIndices.insert(k);
    }
}

void Grid::indicesOfLineLessThoseFromSquare(const unsigned short squareId, const unsigned short lineId,
                                                std::set<unsigned short>& indicesOfLine) 
{
    std::set<unsigned short> indicesOfSquare;
    indicesForLine(lineId, indicesOfLine);
    addDigitsForSquare(squareId, indicesOfSquare);
    for(std::set<unsigned short>::iterator it = indicesOfSquare.begin(); 
        it != indicesOfSquare.end(); ++it) {
        indicesOfLine.erase(*it);
    }
}
void Grid::indicesOfColumnLessThoseFromSquare(const unsigned short squareId, const unsigned short columnId,
                                                std::set<unsigned short>& indicesOfColumn)
{
    std::set<unsigned short> indicesOfSquare;
    indicesForColumn(columnId, indicesOfColumn);
    addDigitsForSquare(squareId, indicesOfSquare);
    for(std::set<unsigned short>::iterator it = indicesOfSquare.begin(); 
        it != indicesOfSquare.end(); ++it) {
        indicesOfColumn.erase(*it);
    }
}

// runtime
void Grid::updateAffectedDomains(const unsigned short index, const unsigned short digit) {
    _domainForEachIndex[index].clear();
    std::set<unsigned short> affectedIndices = _indexLinkage[index];
    for(std::set<unsigned short>::iterator it = affectedIndices.begin(); 
        it != affectedIndices.end(); ++it) {
        _domainForEachIndex[*it].erase(digit);
    }
}
void Grid::entityInteractions() {
    _advancedDomains = _domainForEachIndex;
    // find a restriction within a square

    // as soon as you reach a square with only one option, should leave the loop

    //  0 1 2 
    //  3 4 5 
    //  6 7 8
    for(unsigned short i = 0; i < 9; ++i) { // once for each square
        checkColumnSquareInteraction(i);
        checkLineSquareInteraction(i);
    }
}
unsigned short Grid::getLineId(const unsigned short squareId, const unsigned short lineNumber) 
{
    if(squareId < 3) {
        return lineNumber;
    } else if(squareId < 6) {
        return lineNumber+3;
    } else {
        return lineNumber+6;
    }
}
unsigned short Grid::getColumnId(const unsigned short squareId, const unsigned short columnNumber)
{
    if(squareId % 3 == 0) {
        return columnNumber;
    } else if(squareId % 3 == 1) {
        return columnNumber + 3;
    } else {
        return columnNumber + 6;
    }
}

void Grid::removeExclusivesFromLinesDomains(const unsigned short squareId, const unsigned short lineId,
                        const unsigned short digitToRemove) 
{
    // get indices to be to take away from
    std::set<unsigned short> indices;
    indicesOfLineLessThoseFromSquare(squareId, lineId, indices);
    for(std::set<unsigned short>::iterator it = indices.begin(); 
            it != indices.end(); ++it) 
    {
        //_advancedDomains[*it].erase(digitToRemove);
        _domainForEachIndex[*it].erase(digitToRemove);
    }   
}
void Grid::removeExclusivesFromColumnDomains(const unsigned short squareId, const unsigned short columnId,
                        const unsigned short digitToRemove) 
{
    // get indices to be to take away from
    std::set<unsigned short> indices;
    indicesOfColumnLessThoseFromSquare(squareId, columnId, indices);
    for(std::set<unsigned short>::iterator it = indices.begin(); 
            it != indices.end(); ++it) 
    {
        //_advancedDomains[*it].erase(digitToRemove);
        _domainForEachIndex[*it].erase(digitToRemove);
    }   
}
bool Grid::checkForLineExclusives() {
    bool foundOne = false;
    for(unsigned int lineId = 0; lineId < 9; lineId++) {
        std::set<unsigned short> indicesOfThisLine;
        indicesForLine(lineId, indicesOfThisLine);
        if(!foundOne) {
            foundOne = exclusiveFinder(indicesOfThisLine);
        } else {
            exclusiveFinder(indicesOfThisLine);
        }
    }
    return foundOne;
}
bool Grid::checkForColumnExclusives() {
    bool foundOne = false;
    for(unsigned int columnId = 0; columnId < 9; columnId++) {
        std::set<unsigned short> indicesOfThisColumn;
        indicesForColumn(columnId, indicesOfThisColumn);
        if(!foundOne) {
            foundOne = exclusiveFinder(indicesOfThisColumn);
        } else {
            exclusiveFinder(indicesOfThisColumn);
        }
    }
    return foundOne;
}
bool Grid::checkForSquareExclusives(){
    bool foundOne = false;
    for(unsigned short squareId = 0; squareId < 9; ++squareId) {
        std::set<unsigned short> indicesForThisSquare;
        addDigitsForSquare(squareId, indicesForThisSquare);
        if(!foundOne) {
            foundOne = exclusiveFinder(indicesForThisSquare);
        } else {
            exclusiveFinder(indicesForThisSquare);
        }
    }
    return foundOne;
}
bool Grid::exclusiveFinder(std::set<unsigned short>& indicesOfEntity){
    bool foundOne = false;
    std::vector<std::set<unsigned short>> domainsForEachIndex(9);
    unsigned short index = 0;
    for(std::set<unsigned short>::iterator it = indicesOfEntity.begin();
        it != indicesOfEntity.end(); ++it) {
        domainsForEachIndex[index] = _domainForEachIndex[*it];
        index++;
    }
    for(unsigned short i = 0; i < domainsForEachIndex.size(); ++i){
        for(std::set<unsigned short>::iterator it = domainsForEachIndex[i].begin();
            it != domainsForEachIndex[i].end(); ++it) {
            bool exclusive = true;
            for(unsigned short j = 0; j < domainsForEachIndex.size(); ++j) {
                if(i!= j) {
                    if(std::find(domainsForEachIndex[j].begin(), domainsForEachIndex[j].end(),
                        *it) != domainsForEachIndex[j].end()) {
                        exclusive =  false;
                        break;
                    }
                }
            }
            if(exclusive) {
                unsigned short index = *std::next(indicesOfEntity.begin(), i); // work it out from square 
                _grid[index] = *it;
                updateAffectedDomains(index, *it);
                foundOne = true;
                break;
            }
        }
    }
    return foundOne;
}
void Grid::checkLineSquareInteraction(const unsigned short squareId){
    std::set<unsigned short> indicesForThisSquare;
    addDigitsForSquare(squareId, indicesForThisSquare);
    std::vector<std::vector<unsigned short>> domainsForLines(3);
    int counter = 0;
    int index = 0;
    for(std::set<unsigned short>::iterator it = indicesForThisSquare.begin();
        it != indicesForThisSquare.end(); ++it) {
        counter++;
        for(std::set<unsigned short>::iterator it2 = _advancedDomains[*it].begin();
            it2 != _advancedDomains[*it].end(); ++it2) {
            domainsForLines[index].push_back(*it2);
        }
        if(counter % 3 == 0) {
            index++;
        }
    }
    for(unsigned short i = 0; i < domainsForLines.size(); ++i) {
        int exclusiveDomain = -1;
        for(unsigned short j = 0; j < domainsForLines[i].size(); ++j) {
            bool exclusive = true;
            for(unsigned short k = 0; k < 3; ++k) {
                if(k != i) {
                    unsigned short domain = domainsForLines[i][j];
                    if(std::find(domainsForLines[k].begin(), 
                        domainsForLines[k].end(), 
                        domain) != domainsForLines[k].end()) {
                        exclusive = false;
                        continue;
                    }
                }
            }
            if(exclusive) {
                unsigned short lineId = getLineId(squareId, i);
                removeExclusivesFromLinesDomains(squareId, lineId, domainsForLines[i][j]);
            }
        }
    }
}
void Grid::checkColumnSquareInteraction(const unsigned short squareId){
    std::set<unsigned short> indicesForThisSquare;
    addDigitsForSquare(squareId, indicesForThisSquare);
    std::vector<std::vector<unsigned short>> domainsForColumns(3);
    int counter = 0;
    for(std::set<unsigned short>::iterator it = indicesForThisSquare.begin();
        it != indicesForThisSquare.end(); ++it) {
        for(std::set<unsigned short>::iterator it2 = _advancedDomains[*it].begin();
            it2 != _advancedDomains[*it].end(); ++it2) {
            if(counter % 3 == 0) {
                domainsForColumns[0].push_back(*it2);
            } else if (counter % 3 == 1) {
                domainsForColumns[1].push_back(*it2);
            } else {
                domainsForColumns[2].push_back(*it2);
            }
        }
        counter++;
    }
    for(unsigned short i = 0; i < domainsForColumns.size(); ++i) {
        int exclusiveDomain = -1;
        for(unsigned short j = 0; j < domainsForColumns[i].size(); ++j) {
            bool exclusive = true;
            for(unsigned short k = 0; k < 3; ++k) {
                if(k != i) {
                    unsigned short domain = domainsForColumns[i][j];
                    if(std::find(domainsForColumns[k].begin(), 
                        domainsForColumns[k].end(), 
                        domain) != domainsForColumns[k].end()) {
                        exclusive = false;
                        continue;
                    }
                }
            }
            if(exclusive) {
                unsigned short columnId = getColumnId(squareId, i);
                removeExclusivesFromColumnDomains(squareId, columnId, domainsForColumns[i][j]);
            }
        }
    }
}

// tools for naked subset
void Grid::getPairsForEachIndex(std::vector<std::set<unsigned short>>& domainsForEachIndex,
    std::vector<std::vector<std::pair<short,short>>>& pairsForEachIndex) 
{
    pairsForEachIndex.resize(domainsForEachIndex.size());
    for(unsigned int i = 0; i < domainsForEachIndex.size(); ++i) {
        for(std::set<unsigned short>::iterator it = domainsForEachIndex[i].begin();
            it != domainsForEachIndex[i].end(); ++it) {
                for(std::set<unsigned short>::iterator it2 = domainsForEachIndex[i].begin();
                    it2 != domainsForEachIndex[i].end(); ++it2) {
                        if(it != it2) {
                            pairsForEachIndex[i].push_back(std::pair<double,double>(*it, *it2));
                        }
                    }
            }
    }
}
bool Grid::checkItsWorthInvestigating(const std::vector<std::set<unsigned short>>& domainsForEachIndex) {
    unsigned short counter = 0;
    for(unsigned short i = 0; i < domainsForEachIndex.size(); ++i) {
        if(domainsForEachIndex.size() > 2) {
            counter++;
        }
        if(counter > 2) {
            return true;
        }
    }
    return false;
}

// Naked Subset
bool Grid::checkLinesForNakedSubsets() {
    bool foundOne = false;
    for(unsigned int lineId = 0; lineId < 9; lineId++) {
        std::set<unsigned short> indicesOfThisLine;
        indicesForLine(lineId, indicesOfThisLine);
        if(!foundOne) {
            foundOne = nakedSubsetFinder(indicesOfThisLine);
        } else {
            nakedSubsetFinder(indicesOfThisLine);
        }
    }
    return foundOne;
}
bool Grid::checkColumnsForNakedSubsets() {
    bool foundOne = false;
    for(unsigned int columnId = 0; columnId < 9; columnId++) {
        std::set<unsigned short> indicesOfThisColumn;
        indicesForColumn(columnId, indicesOfThisColumn);
        if(!foundOne) {
            foundOne = nakedSubsetFinder(indicesOfThisColumn);
        } else {
            nakedSubsetFinder(indicesOfThisColumn);
        }
    }
    return foundOne;
}
bool Grid::checkSquaresForNakedSubsets() {
    bool foundOne = false;
    for(unsigned short squareId = 0; squareId < 9; ++squareId) {
        std::set<unsigned short> indicesForThisSquare;
        addDigitsForSquare(squareId, indicesForThisSquare);
        if(!foundOne) {
            foundOne = exclusiveFinder(indicesForThisSquare);
        } else {
            exclusiveFinder(indicesForThisSquare);
        }
    }
    return foundOne;
}
bool Grid::nakedSubsetFinder(std::set<unsigned short>& entityIndices) {
    bool foundOne = false;
    std::vector<std::set<unsigned short>> domainsForEachIndex(9);
    unsigned short index = 0;
    for(std::set<unsigned short>::iterator it = entityIndices.begin();
        it != entityIndices.end(); ++it) {
        domainsForEachIndex[index] = _domainForEachIndex[*it];
        index++;
    }
    // check that there are more than two spaces not completed
    if(!checkItsWorthInvestigating(domainsForEachIndex))
    {
        return false;
    }

    // create all possible pairs from the domainsForEachIndex
    std::vector<std::vector<std::pair<short,short>>> pairsForEachIndex;
    getPairsForEachIndex(domainsForEachIndex, pairsForEachIndex);
    for(unsigned int i = 0; i < pairsForEachIndex.size(); ++i) {
        std::vector<short> pairPresentIndices;
        if(pairsForEachIndex[i].size() == 1){
            pairPresentIndices.push_back(i);
            for(unsigned int j = 0; j < pairsForEachIndex.size(); ++j) {
                if(i!=j) {
                    if(pairsForEachIndex[j].size() == 1) {
                        if(pairsForEachIndex[i][0] == pairsForEachIndex[j][0]) {
                            pairPresentIndices.push_back(j);
                            foundOne = true;
                        }
                    }
                }
            }
            if(foundOne) {
                for(std::set<unsigned short>::iterator it = entityIndices.begin(); 
                    it != entityIndices.end(); ++it) {
                    if(std::find(pairPresentIndices.begin(), pairPresentIndices.end(), *it) == pairPresentIndices.end()) {
                        _domainForEachIndex[*it].erase(pairsForEachIndex[i][0].first);
                        _domainForEachIndex[*it].erase(pairsForEachIndex[i][0].second);
                    }
                }
            return true;
            }
        }
    }
    return false;
}

bool Grid::nakedSubset() {
    // different for each entitt again
    if(checkLinesForNakedSubsets() ||
    checkColumnsForNakedSubsets() ||
    checkSquaresForNakedSubsets()) {
        return true;
    }
    return false;
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
        //Sole candidate
        for(short int i = 0; i < 81; ++i) {
            if(_domainForEachIndex[i].size() == 1) {
                if(add(i,*_domainForEachIndex[i].begin())){
                    updateAffectedDomains(i, *_domainForEachIndex[i].begin());              
                    jump = true;
                    break;
                }
            }
        }
        if(jump) {
            jump = false;
            continue;
        }
        if(isValid(true)) {
            break;
        }
        // Unique candidate Square
        if(checkForSquareExclusives()) {
            continue;
        }
        // Unique candidate Column
        if(checkForLineExclusives()) {
            continue;
        }
        // Unique candidate Line
        if(checkForColumnExclusives()) {
            continue;
        }
        
        // Naked Subset
        if(nakedSubset()) {
            std::cout << "NAKED SUBSET SUCCESS" << std::endl;
            continue;
        }

        entityInteractions();
        // Sole candidate leveraging entity interaction
        for(short int i = 0; i < 81; ++i) {
            if(_advancedDomains[i].size() == 1) {
                if(add(i,*_advancedDomains[i].begin())){
                    updateAffectedDomains(i, *_advancedDomains[i].begin());        
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
    domainTotal(_domainForEachIndex);
    std::cout << "isValid: " << printBoolean(isValid()) << std::endl;
    std::cout << "isSolution: " << printBoolean(isValid(true)) << std::endl;
    print();

    // std::cout << "Domain for index " << 16 << std::endl;
    // for(std::set<unsigned short>::iterator it = _domainForEachIndex[16].begin();
    //             it != _domainForEachIndex[16].end(); ++it) {
    //     std::cout << *it << "  ";
    // }
    std::cout << std::endl;

    return isValid(true);
}
void Grid::print() {
    std::cout <<"Grid:" << std::endl;
    for(unsigned int i = 0; i < 81; ++i) {
        if(i % 9 == 0) 
            std::cout << std::endl;
        if(_grid[i] != 0) {
            std::cout << _grid[i] << "   ";
        } else {
            std::cout << "_   ";
        }
    }
    std::cout << std::endl;
}
