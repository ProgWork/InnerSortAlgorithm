#pragma once
#include<string>
#include<cstdlib>
#include<ctime>
#include"Sort.h"
using namespace std;
class Manager {
public:
	Manager();
	~Manager();
	void ChangePos();
	void GenRandomNum();
	void InputNum();
	void GenNumMethod(int x);
	int GetLen();
	int * GetArray();
	void ExecuteSort();
	void Tip(string name);
	void DisplaySortOption();
	void Select(int x, Sort &s);
	void ShowData(Sort &s);
	void Init();
	void DisplayNextOption();
private:
	int len;
	int *array;
};