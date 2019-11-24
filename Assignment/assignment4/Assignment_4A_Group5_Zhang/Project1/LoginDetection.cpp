#include "LoginDetection.h"
#include <iostream>

using namespace std;

LoginDetection* LoginDetection::_instance = 0;

LoginDetection::LoginDetection()
{
	cout << "Create Singleton ..." << endl;
	count = 0;
}

LoginDetection* LoginDetection::GetInstance()
{
	if (_instance==0)
	{
		_instance = new LoginDetection();
	}
	return _instance;
}

void LoginDetection::OutputInfor()
{
	cout << "This account logged in " << ++count <<" times today."<< endl;
}