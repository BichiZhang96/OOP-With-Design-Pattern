#include "LoginDetection.h"

int main()
{

	LoginDetection *t1 = LoginDetection::GetInstance();
	t1->OutputInfor();

	LoginDetection *t2 = LoginDetection::GetInstance();
	t2->OutputInfor();

	LoginDetection *t3 = LoginDetection::GetInstance();
	t3->OutputInfor();
	return 0;
}