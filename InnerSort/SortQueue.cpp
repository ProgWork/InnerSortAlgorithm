#include "SortQueue.h"


SortQueue::SortQueue()
{
}
SortQueue::SortQueue(int length) {
	this->array = new int[length];
	this->length = length;
	this->ptr = 0;

}

SortQueue::~SortQueue()
{
	if (this->array != NULL) {
		delete[] this->array;
		this->length = 0;
		this->ptr = 0;
		this->array = NULL;
	}


}
void SortQueue::EnQueue(int x) {
	if (this->ptr < this->length-1) {
		this->array[this->ptr] = x;
		this->ptr++;
	}
}
int SortQueue::DeQueue() {
	if (this->array != NULL) {
		int p = this->ptr;
		this->ptr--;
		return this->array[p];
	}
}