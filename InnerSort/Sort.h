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
	void InsertSort();//ֱ�Ӳ�������
	void HalfInsertSort();//�۰��������
	void ShellSort();//ϣ������
	void BubbleSort();//ð������
	int Partition(int low,int high);//�������򻮷�
	void QuickSort(int low, int high);//��������
	void SelectSort();//�򵥿�������
	void BuildMaxHeap();//��������
	void AdjustDown(int k,int len);//�������
	void HeapSort();//������
	void Merge(int low, int mid, int high);//�鲢
	void MergeSort(int low, int high);//�鲢����
	int MaxBit();//��ȡ�������������λ��
	void RadixSort();//distrution sort��������

	int GetLen();
	int *array;
private:
	int len;
	int *B;//�鲢����������
};


