#include"Manager.h"
void Manager::GenRandomNum() {
	srand((int)time(0));
	cout << endl;
	cout << "����������������ֵ" << endl;
	int x;
	cin >> x;
	for (int i = 1; i < this->len; i++) {
		this->array[i] = rand() % x;
	}
}
void Manager::InputNum() {
	for (int i = 1; i < this->len; i++) {
		cout << "��" << i << "����:" << endl;
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
	cout << "���������ָ�����" << endl;
	int x;
	cin >> x;
	this->len = x + 1;
	this->array = new int[this->len];
	cout << endl;
	cout << "1.���������\t2.�ֶ�������" << endl;
	cin >> x;
	this->GenNumMethod(x);
	cout << endl;
	cout << "******************************************************" << endl;
	cout << "δ����ǰ����Ϊ��" << endl;
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
	cout << "���Һ�����У�" << endl;
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
	cout << "��ѡ���㷨��\n1.ֱ�Ӳ�������\t2.�۰��������\t3.ϣ������\n4.ð������\t5.��������\t6.��ѡ������\n7.������\t8.�鲢����\t9.��������" << endl;
	cout << "------------------------------------------------------" << endl;
}
void Manager::Tip(string name) {
	cout << endl;
	cout << "=======================================================" << endl;
	cout << name << "������Ϊ��" << endl;
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
	case 1:this->Tip("ֱ�Ӳ�������"); s.InsertSort(); this->ShowData(s); break;
	case 2:this->Tip("�۰��������"); s.HalfInsertSort(); this->ShowData(s); break;
	case 3:this->Tip("ϣ������"); s.ShellSort(); this->ShowData(s); break;
	case 4:this->Tip("ð������"); s.BubbleSort(); this->ShowData(s); break;
	case 5:this->Tip("��������"); s.QuickSort(1, this->len - 1); this->ShowData(s); break;
	case 6:this->Tip("��ѡ������"); s.SelectSort(); this->ShowData(s); break;
	case 7:this->Tip("������"); s.HeapSort(); this->ShowData(s); break;
	case 8:this->Tip("�鲢����"); s.MergeSort(1, s.GetLen() - 1); this->ShowData(s); break;
	case 9:this->Tip("��������"); s.RadixSort(); this->ShowData(s); break;
	default:
		break;
	}
}
void Manager::ExecuteSort() {
	this->DisplaySortOption();
	cout << endl;
	cout << "��������ѡ��������㷨���к�" << endl;
	int x;
	cin >> x;
	Sort s(this->len, this->array);
	this->Select(x, s);
	this->DisplayNextOption();
	cout << endl;
}
void Manager::Init() {
	cout << endl;
	cout << "�������������ָ�����" << endl;
	int x;
	cin >> x;
	this->len = x + 1;
	if (this->array != NULL) {
		delete[] this->array;
		this->array = NULL;
	}
	this->array = new int[this->len];
	cout << endl;
	cout << "1.���������\t2.�ֶ�������" << endl;
	cin >> x;
	this->GenNumMethod(x);
	cout << endl;
	cout << "δ����ǰ����Ϊ��" << endl;
	for (int i = 1; i < this->len; i++) {
		cout << this->array[i] << " ";
	}
	cout << endl;
}
void Manager::DisplayNextOption() {
	cout << endl;
	cout << "1.���������� 2.�ı��㷨ִ�� 3.�˳�����" << endl;
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

