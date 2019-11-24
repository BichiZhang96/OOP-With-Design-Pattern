#include "WorkerState.h"
#include "Worker.h"

int main()
{
	Worker* pWorker = new Worker();
	pWorker->setHour(24);
	cout << "time 24" << endl;
	pWorker->requestDoing();

	pWorker->setHour(11.5);
	cout << "time 10.5" << endl;
	pWorker->requestDoing();

	pWorker->setHour(19);
	cout << "time 19" << endl;
	pWorker->requestDoing();

	delete pWorker;
	return 0;
}