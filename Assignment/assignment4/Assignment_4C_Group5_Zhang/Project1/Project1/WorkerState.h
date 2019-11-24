#pragma once
#include <iostream>
using namespace std;

class Worker;

class State
{
public:
	virtual void doing(Worker* w) {}
};

class WorkingState : public State
{
public:
	void doing(Worker* worker);
};

class SleepingState : public State
{
public:
	void doing(Worker* worker);
};

class OtherState : public State
{
public:
	void doing(Worker* worker);
};
