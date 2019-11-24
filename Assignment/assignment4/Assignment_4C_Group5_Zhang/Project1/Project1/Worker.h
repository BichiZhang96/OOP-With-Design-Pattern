#pragma once
#include "WorkerState.h"

class Worker
{
public:
	Worker()
	{
		state = new WorkingState();
	}
	void setState(State* stat)
	{
		state = stat;
	}
	double getHour()
	{
		return hour;
	}
	void setHour(double hou)
	{
		hour = hou;
	}

	void requestDoing()
	{
		state->doing(this);
	}
private:
	State* state;
	double hour;
};

void WorkingState::doing(Worker* worker)
{
	if (worker->getHour() > 9 && worker->getHour() < 17)
		cout << "WorkingState!" << endl;
	else
	{
		worker->setState(new OtherState());
		worker->requestDoing();
	}
}

void SleepingState::doing(Worker* worker)
{
	if (worker->getHour() >= 24 || worker->getHour() < 8)
		cout << "SleepingState!" << endl;
	else
	{
		worker->setState(new OtherState());
		worker->requestDoing();

	}
}

void OtherState::doing(Worker* worker)
{
	if ((worker->getHour() >= 8 && worker->getHour() < 9)
		|| (worker->getHour() >= 17 && worker->getHour() < 24))
		cout << "OtherState!" << endl;
	else if (worker->getHour() >= 24 || worker->getHour() < 8)
	{
		worker->setState(new SleepingState());
		worker->requestDoing();
	}
	else
	{
		worker->setState(new WorkingState());
		worker->requestDoing();
	}
}
