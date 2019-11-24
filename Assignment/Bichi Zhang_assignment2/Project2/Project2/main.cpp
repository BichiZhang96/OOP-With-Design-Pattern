#include <iostream>
#include <fstream>
#include <iomanip>
#include "game_of_life.h"

using namespace std;

int main() 
{
    ifstream ifs("input.txt");
    if (!ifs.is_open()) 
	{
        return -1;
    }
    GameOfLife gameOfLife;
    ifs >> gameOfLife;
    ifs.close();
    ofstream ofs("output.txt");
    for (int i = 0;i < 5; ++i) 
	{
        gameOfLife.generate();
        ofs << gameOfLife << endl;
    }
    ofs.close();
	ofs << setw(100);
    return 0;
}