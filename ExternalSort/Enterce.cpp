#include"ExternalSortEntity.h"
#include"windows.h"
void process() {
	long t1 = GetTickCount();
	ExternalSortEntity SEntity;
	SEntity.GenNum();
	SEntity.GetMergeSegments();
	SEntity.Merge();
	long t2 = GetTickCount();
	cout << "运行时间：" << (t2 - t1)<<"ms"<< endl;
}
int main(void) {
	process();
	system("pause");
}