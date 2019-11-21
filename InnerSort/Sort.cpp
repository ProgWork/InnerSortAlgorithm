#include "Sort.h"
Sort::Sort()
{
		
}
Sort::Sort(int len, int *array) {
	if (array == NULL) {
		this->len = 0;
		this->array = NULL;
		return;
	}
	this->len = len;
	this->array = new int[len];
	for (int i = 1; i < len; i++) {
		this->array[i] = array[i];
	}
	this->B = new int[len];

}
Sort::~Sort()
{
	if (this->array != NULL) {
		this->len = 0;
		delete[] this->array;
		this->array = NULL;
	}
	if (this->B != NULL) {
		delete[] this->B;
		this->B = NULL;
	}
	cout << "~Sort()...";
}
int Sort::GetLen() {
	return this->len;
}
void Sort::InsertSort() {
	int i, j;
	for (i = 2; i<this->len; i++) {
		if (this->array[i]<this->array[i - 1]) {
			this->array[0] = this->array[i];
			for (j = i - 1; j > 0 && this->array[0] < this->array[j]; j--) {
				this->array[j + 1] = this->array[j];
			}
			this->array[j + 1] = this->array[0];
		}
	}
}
void Sort::HalfInsertSort() {
	int i, j, low, high, mid;
	for (i = 2; i < this->len; i++) {
		this->array[0] = this->array[i];
		low = 1;
		high = i - 1;
		while (low < high) {
			mid = (high + low) / 2;
			if (this->array[i] < this->array[mid]) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= high + 1; j--)
			this->array[j + 1] = this->array[j];
		this->array[j + 1] = this->array[0];
	}
}
void Sort::ShellSort() {
	int i, j;
	//初始增量为总长度的一半，之后依次除2且向下取整，且最后一次要为1
	for (int d = (this->len-1) / 2; d >= 1; d /= 2) {
		for (i = d + 1; i < this->len; i++) {//分组
			if (this->array[i] < this->array[i - d]) {
				this->array[0] = this->array[i];
				for (j = i - d; j > 0 && this->array[0] < this->array[j]; j -= d) {
					this->array[j + d] = this->array[j];
				}
				this->array[j + d] = this->array[0];
			}
		}
	}
}
void Sort::BubbleSort() {
	for (int i = 1; i < this->len-1; i++) {
		bool flag = false;//当整个序列有序的时候，标志位不发生修改，从而表示已经排好了
		for (int j = this->len - 1; j > i; j--) {
			if (this->array[j] < this->array[j - 1]) {
				int temp = this->array[j];
				this->array[j] = this->array[j - 1];
				this->array[j - 1] = temp;
				flag = true;
			}
		}
		if (flag == false) {
			return;
		}
	}
}
int Sort::Partition(int low, int high) {
	int ptr = this->array[low];
	while (low<high){
		while (low<high&&this->array[high]>=ptr) {//low<high避免完全顺序的序列出现数组下溢
			high--;
		}
		this->array[low] = this->array[high];
		while (low < high&&this->array[low] <= ptr) {
			low++;
		}
		this->array[high] = this->array[low];
	}
	this->array[low] = ptr;
	return low;
}
void Sort::QuickSort(int low, int high) {
	if (low < high) {
		int ptr = Partition(low, high);
		QuickSort(low, ptr - 1);
		QuickSort(ptr + 1, high);
	}
}
void Sort::SelectSort() {
	for (int i = 1; i < this->len-1; i++) {
		int min = i;//min记录当前最小元素所在的下标，初值设为第i个
		for (int j = i + 1; j < this->len; j++) {
			if (this->array[j] < this->array[min])
				min = j;
		}
		if (min != i) {
			int temp = this->array[i];
			this->array[i] = this->array[min];
			this->array[min] = temp;
		}
	}
}
void Sort::BuildMaxHeap() {
	for (int i = (this->len - 1) / 2; i > 0; i--)//len-1/2为第一个可能要检查的元素下标
		AdjustDown(i,this->len-1);
}
void Sort::AdjustDown(int k,int len) {
	this->array[0] = this->array[k];//k为需要检查的结点值
	for (int i = 2 * k; i <= len; i *= 2) {//2*k为其左孩子结点
		if (i < len && this->array[i] < this->array[i + 1])
			i++;
		if (this->array[0] >= this->array[i])
			break;
		else {
			this->array[k] = this->array[i];
			k = i;
		}
	}
	this->array[k] = this->array[0];
}
void Sort::HeapSort() {
	BuildMaxHeap();
	for (int i = this->len - 1; i > 1; i--) {
		int temp = this->array[i];
		this->array[i] = this->array[1];
		this->array[1] = temp;
		AdjustDown(1, i - 1);
	}
}
void Sort::Merge(int low, int mid, int high) {
	for (int k = 1; k <= this->len - 1; k++) {
		this->B[k] = this->array[k];
	}
	int i, j, k;
	for (i = low,j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (this->B[i] <= this->B[j])
			this->array[k] = this->B[i++];
		else
			this->array[k] = this->B[j++];
	}
	while (i<=mid)
	{
		this->array[k++] = this->B[i++];
	} 
	while (j<=high)
	{
		this->array[k++] = this->B[j++];
	}
}
void Sort::MergeSort(int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;

		MergeSort(low, mid);
		MergeSort(mid + 1, high);
		Merge(low, mid, high);
	}
}  
int Sort::MaxBit() {
	int d = 1;//初始化记位数为1
	int r = 10;//r代表基数
	for (int i = 1; i < this->len; i++) {
		while (this->array[i]>=r)
		{
			r *= 10;
			d++;
		}
	}
	return d;
}
void Sort::RadixSort() {
	int d = MaxBit();//寻找待排序序列中最大数的位数
	queue<int> *queue_list[10];//定义十个队列
	queue<int> *queue_total = new queue<int>;//存放每趟排序的结果
	for (int i = 0; i < 10; i++) {//给十个队列申请空间
		queue<int> *q = new queue<int>;
		queue_list[i] = q;
	}
	for (int i = 1; i < this->len; i++) {//将待排序序列存入队列
		queue_total->push(this->array[i]);
	}
	for (int i = 0; i < d; i++) {
		unsigned int size = queue_total->size();
		for (unsigned int j = 0; j < size; j++) {
			int temp = int(queue_total->front() /pow(10,i));
			int value = temp % 10;//获取对应位的值
			queue_list[value]->push(queue_total->front());//将数放入队列
			queue_total->pop();//删除已出队的数
		}
		for (int m = 0; m < 10; m++) {
			unsigned int queue_len = queue_list[m]->size();
			for (unsigned int n = 0; n < queue_len; n++) {
				if (!queue_list[m]->empty()) {
					queue_total->push(queue_list[m]->front());
					queue_list[m]->pop();
				}			
			}
		}
	}
	if (queue_total->size() == (this->len - 1)) {
		for (int i = 1; i < this->len; i++) {
			this->array[i] = queue_total->front();
			queue_total->pop();
		}
	}
}


