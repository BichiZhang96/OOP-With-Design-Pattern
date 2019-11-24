#include <iostream>
#include <string>
#include <fstream>
#include "encodedecode.h"

using namespace std;


void do_encode() 
{
    ifstream fin;
    fin.open("input.txt");
    ofstream fout("encrypted.txt"); 
    Encoder encoder;
    while (fin >> encoder) 
	{
        fout << encoder;
    }
    fin.close();
    fout.close();
}

void do_decode() 
{
    ifstream fin;
    fin.open("encrypted.txt");
    ofstream fout("decrypted.txt"); 
    Decoder decoder;
    while (fin >> decoder) 
	{
        fout << decoder;
    }
    fin.close();
    fout.close();
}

int main() 
{
    do_encode();
    do_decode();
    return 0;
}