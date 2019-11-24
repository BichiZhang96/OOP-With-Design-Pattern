#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__

#include <iostream>

using namespace std;

class GameOfLife 
{
public:
    GameOfLife(): generations(0) {}
    void setOrganism(int i, int j) 
	{
        matrix[i][j] = 'x';
    }

    ~GameOfLife();

    GameOfLife(const GameOfLife& rhs);

    GameOfLife& operator=(const GameOfLife& rhs);    

    void generate();

    friend istream& operator>>(istream& in, GameOfLife& life);
    friend ostream& operator<<(ostream& out, const GameOfLife& life);

private:
    bool isValid(int i, int j) 
	{
        return 0 <= i && i < nrows && 0 <= j && j < ncols;
    }

    int countNeibors(int i, int j);

    int nrows;
    int ncols;
    int generations;
    char** matrix;
};

#endif
