#pragma once
#include<cstdlib>
class SortQueue
{
public:
	SortQueue();
	SortQueue(int len);
	~SortQueue();
	void EnQueue(int x);
	int DeQueue();
private:
	int *array;
	int ptr;
	int length;
};

