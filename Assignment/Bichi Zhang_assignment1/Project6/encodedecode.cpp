#include <iostream>
#include <string>
#include <fstream>
#include "encodedecode.h"

string Encoder::encode() const 
{
    char op = ~ch;
    string result = "";
    char bit = 0x1;
    for (int i = 0;i < 8; ++i) {
        if ((op & bit) == 0) {
            result += "0";
        } else {
            result += "1";
        }
        bit <<= 1;
    }
    return result;
}

istream& operator>>(istream& in, Encoder& obj) 
{
    obj.ch = in.get();
    return in;
}

ostream& operator<<(ostream& out, const Encoder& obj) 
{
    out << obj.encode();
    return out;
}


char Decoder::decode() const 
{
    char op = 0;
    for (int i = 7;i >= 0; --i) 
	{
        op *= 2;
        if (encoded[i] == '1') 
		{
            op += 1;
        }
    }
    return ~op;
}

istream& operator>>(istream& in, Decoder& obj) 
{
    string input = "";
    char op;
    for (int i = 0;i < 8; ++i) 
	{
        in >> op;
        input += op;        
    }
    obj.encoded = input;
    return in;
}

ostream& operator<<(ostream& out, const Decoder& obj) 
{
    out << obj.decode();
    return out;
}