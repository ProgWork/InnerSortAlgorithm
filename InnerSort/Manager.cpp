#include"Manager.h"
void Manager::GenRandomNum() {
	srand((int)time(0));
	cout << endl;
	cout << "请输入随机数的最大值" << endl;
	int x;
	cin >> x;
	for (int i = 1; i < this->len; i++) {
		this->array[i] = rand() % x;
	}
}
void Manager::InputNum() {
	for (int i = 1; i < this->len; i++) {
		cout << "第" << i << "个数:" << endl;
		cin >> this->array[i];
	}
}
void Manager::GenNumMethod(int x) {
	switch (x) {
	case 1:this->GenRandomNum(); break;
	case 2:this->InputNum(); break;
	default:
		break;
	}
}
Manager::Manager() {
	cout << "请输入数字个数：" << endl;
	int x;
	cin >> x;
	this->len = x + 1;
	this->array = new int[this->len];
	cout << endl;
	cout << "1.随机生成数\t2.手动输入数" << endl;
	cin >> x;
	this->GenNumMethod(x);
	cout << endl;
	cout << "******************************************************" << endl;
	cout << "未排序前数据为：" << endl;
	for (int i = 1; i < this->len; i++) {
		cout << this->array[i] << " ";
	}
	cout << endl;
	cout << "******************************************************" << endl;
}
Manager::~Manager() {
	if (this->array != NULL) {
		this->len = 0;
		delete[] this->array;
		this->array = NULL;
	}
	cout << "~Manager()..." << endl;
}
void Manager::ChangePos() {
	for (int i = 1; i < this->len / 2; i++) {
		int temp = this->array[len / 2];
		this->array[this->len / 2] = this->array[this->len - 1];
		this->array[this->len - 1] = temp;
		for (int i = 1; i < this->len; i++) {
			this->array[i - 1] = this->array[i];
		}
		this->array[len - 1] = this->array[0];
	}
	for (int i = 1; i < this->len / 2; i++) {
		int temp = this->array[i];
		this->array[i] = this->array[len / 2 * 2 - i];
		this->array[len / 2 * 2 - i] = temp;
	}
	cout << endl;
	cout << "*************************************************" << endl;
	cout << "打乱后的序列：" << endl;
	for (int i = 1; i < this->len; i++) {
		cout << this->array[i] << " ";;
	}
	cout << endl;
	cout << "*************************************************" << endl;
}
int Manager::GetLen() {
	return this->len;
}
int* Manager::GetArray() {
	return this->array;
}
void Manager::DisplaySortOption() {
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "请选择算法：\n1.直接插入排序\t2.折半插入排序\t3.希尔排序\n4.冒泡排序\t5.快速排序\t6.简单选择排序\n7.堆排序\t8.归并排序\t9.基数排序" << endl;
	cout << "------------------------------------------------------" << endl;
}
void Manager::Tip(string name) {
	cout << endl;
	cout << "=======================================================" << endl;
	cout << name << "排序结果为：" << endl;
}
void Manager::ShowData(Sort &s) {
	for (int i = 1; i < s.GetLen(); i++) {
		cout << s.array[i] << " ";
	}
	cout << endl;
	cout << "=======================================================" << endl;
}
void Manager::Select(int x, Sort &s) {
	switch (x)
	{
	case 1:this->Tip("直接插入排序"); s.InsertSort(); this->ShowData(s); break;
	case 2:this->Tip("折半查找排序"); s.HalfInsertSort(); this->ShowData(s); break;
	case 3:this->Tip("希尔排序"); s.ShellSort(); this->ShowData(s); break;
	case 4:this->Tip("冒泡排序"); s.BubbleSort(); this->ShowData(s); break;
	case 5:this->Tip("快速排序"); s.QuickSort(1, this->len - 1); this->ShowData(s); break;
	case 6:this->Tip("简单选择排序"); s.SelectSort(); this->ShowData(s); break;
	case 7:this->Tip("堆排序"); s.HeapSort(); this->ShowData(s); break;
	case 8:this->Tip("归并排序"); s.MergeSort(1, s.GetLen() - 1); this->ShowData(s); break;
	case 9:this->Tip("基数排序"); s.RadixSort(); this->ShowData(s); break;
	default:
		break;
	}
}
void Manager::ExecuteSort() {
	this->DisplaySortOption();
	cout << endl;
	cout << "请输入你选择的排序算法序列号" << endl;
	int x;
	cin >> x;
	Sort s(this->len, this->array);
	this->Select(x, s);
	this->DisplayNextOption();
	cout << endl;
}
void Manager::Init() {
	cout << endl;
	cout << "请重新输入数字个数：" << endl;
	int x;
	cin >> x;
	this->len = x + 1;
	if (this->array != NULL) {
		delete[] this->array;
		this->array = NULL;
	}
	this->array = new int[this->len];
	cout << endl;
	cout << "1.随机生成数\t2.手动输入数" << endl;
	cin >> x;
	this->GenNumMethod(x);
	cout << endl;
	cout << "未排序前数据为：" << endl;
	for (int i = 1; i < this->len; i++) {
		cout << this->array[i] << " ";
	}
	cout << endl;
}
void Manager::DisplayNextOption() {
	cout << endl;
	cout << "1.重新输入数 2.改变算法执行 3.退出程序" << endl;
	int x;
	cin >> x;
	switch (x)
	{
	case 1: this->Init(); this->ExecuteSort(); break;
	case 2: this->ChangePos(); this->ExecuteSort(); break;
	case 3: exit(0);
	default:
		break;
	}
}

