#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Encoder 
{
public:
    string encode() const;

    friend istream& operator>>(istream& in, Encoder& obj);
    friend ostream& operator<<(ostream& out, const Encoder& obj);
private:
    char ch;
};

class Decoder 
{
public:
    char decode() const;
    friend istream& operator>>(istream& in, Decoder& obj);
    friend ostream& operator<<(ostream& out, const Decoder& obj);
private:
    string encoded;
};