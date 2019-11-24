#include<iomanip>
#include "game_of_life.h"

GameOfLife::~GameOfLife() 
{
    for (int i = 0;i < nrows; ++i) 
	{
        delete[] matrix[i];
    }
    delete[] matrix;
}

GameOfLife::GameOfLife(const GameOfLife& rhs) 
{
    nrows = rhs.nrows;
    ncols = rhs.ncols;
    generations = rhs.generations;
    matrix = new char*[nrows];
    for (int i = 0;i < nrows; ++i) 
	{
        matrix[i] = new char[ncols];
        for (int j = 0;j < ncols; ++j) 
		{
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

GameOfLife& GameOfLife::operator=(const GameOfLife& rhs) 
{
    for (int i = 0;i < nrows; ++i) 
	{
        delete[] matrix[i];
    }
    delete[] matrix;
    nrows = rhs.nrows;
    ncols = rhs.ncols;
    generations = rhs.generations;
    matrix = new char*[nrows];
    for (int i = 0;i < nrows; ++i) 
	{
        matrix[i] = new char[ncols];
        for (int j = 0;j < ncols; ++j) 
		{
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
    return *this;
}

    void GameOfLife::generate() 
	{
        if (generations != 0) 
		{
            //create new matrix
            char** newMatrix = new char*[nrows + 2];
            for (int i = 0;i < nrows + 2; ++i) 
			{
                newMatrix[i] = new char[ncols + 2];
                for (int j = 0;j < ncols + 2; ++j) 
				{
                    newMatrix[i][j] = '#';
                }
            }
            for (int i = 0;i < nrows + 2; ++i) 
			{
                for (int j = 0;j < ncols + 2; ++j) 
				{
                    int neibors = countNeibors(i, j);
                    if (neibors == 3) 
					{
                        newMatrix[i][j] = 'x';
                    } else if (neibors > 3 || neibors < 2) 
					{
                        newMatrix[i][j] = '#';
                    } else {
                        if (1 <= i && i <= nrows && 1 <= j && j <= ncols) 
						{
                            newMatrix[i][j] = matrix[i - 1][j - 1];
                        } else 
						{
                            newMatrix[i][j] = '#';
                        }
                    }
                }
            }
            for (int i = 0;i < nrows; ++i) 
			{
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = newMatrix;
            nrows += 2;
            ncols += 2;
        }
        generations += 1;
    }

    int GameOfLife::countNeibors(int i, int j) 
	{
        int count = 0;
        i -= 1;
        j -= 1;
        //left-top
        if (isValid(i - 1, j - 1) && matrix[i - 1][j - 1] == 'x') ++count;
        //top
        if (isValid(i - 1, j) && matrix[i - 1][j] == 'x') ++count;
        //right-top
        if (isValid(i - 1, j + 1) && matrix[i - 1][j + 1] == 'x') ++count;
        //left
        if (isValid(i, j - 1) && matrix[i][j - 1] == 'x') ++count;
        //right
        if (isValid(i, j + 1) && matrix[i][j + 1] == 'x') ++count;
        //left-bottom
        if (isValid(i + 1, j - 1) && matrix[i + 1][j - 1] == 'x') ++count;
        //bottom
        if (isValid(i + 1, j) && matrix[i + 1][j] == 'x') ++count;
        //right-bottom
        if (isValid(i + 1, j + 1) && matrix[i + 1][j + 1] == 'x') ++count;
        return count;
    }

istream& operator>>(istream& in, GameOfLife& life) 
{
    in >> life.nrows >> life.ncols;
    life.matrix = new char*[life.nrows];
    for (int i = 0;i < life.nrows; ++i) 
	{
        life.matrix[i] = new char[life.ncols];
        for (int j = 0;j < life.ncols; ++j) 
		{
            life.matrix[i][j] = '#';
        }
    }
    int i, j;
    while (true) 
	{
        in >> i;
        if (i == -1) 
		{
            break;
        }
        in >> j;
        life.setOrganism(i, j);
    }
    return in;
}

ostream& operator<<(ostream& out, const GameOfLife& life) 
{
    out << "Generation " << life.generations << ":" << endl;
    int minRow = life.nrows, maxRow = -1, minCol = life.ncols, maxCol = -1;
    for (int i = 0;i < life.nrows; ++i) 
	{
        for (int j = 0;j < life.ncols; ++j) 
		{
            if (life.matrix[i][j] == 'x') 
			{
                if (minRow > i) minRow = i;
                if (maxRow < i) maxRow = i;
                if (minCol > j) minCol = j;
                if (maxCol < j) maxCol = j;
            }
        }
    }

    out << "#";
    for (int j = minCol;j <= maxCol; ++j) 
	{
		out << setw(2) << "#";
    }
	out << setw(2) << "#" << endl;
    for (int i = minRow;i <= maxRow; ++i) 
	{
        out << "#";
        for (int j = minCol;j <= maxCol; ++j) 
		{
			out << setw(2) << life.matrix[i][j];
        }
		out << setw(2) << "#" << endl;
    }
    out << "#";
    for (int j = minCol;j <= maxCol; ++j) 
	{
		out << setw(2) << "#";
    }
	out << setw(2) << "#" << endl;
    return out;
}