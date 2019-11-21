#pragma once
#include<iostream>
#include<cstdlib>
#include<queue>
#include<math.h>
using namespace std;
class Sort
{
public:
	Sort();
	Sort(int len, int *array);
	~Sort();
	void InsertSort();//直接插入排序
	void HalfInsertSort();//折半插入排序
	void ShellSort();//希尔排序
	void BubbleSort();//冒泡排序
	int Partition(int low,int high);//快速排序划分
	void QuickSort(int low, int high);//快速排序
	void SelectSort();//简单快速排序
	void BuildMaxHeap();//建立最大堆
	void AdjustDown(int k,int len);//调整结点
	void HeapSort();//堆排序
	void Merge(int low, int mid, int high);//归并
	void MergeSort(int low, int high);//归并排序
	int MaxBit();//获取数组中最大数的位数
	void RadixSort();//distrution sort基数排序

	int GetLen();
	int *array;
private:
	int len;
	int *B;//归并排序辅助数组
};


