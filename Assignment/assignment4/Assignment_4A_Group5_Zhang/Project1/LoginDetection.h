#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class LoginDetection
{
public:
	static LoginDetection* GetInstance();
	void OutputInfor();
protected:
	LoginDetection();
private:
	static LoginDetection *_instance;
	int count;
};

#endif