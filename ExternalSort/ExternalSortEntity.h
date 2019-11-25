#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<queue>
using namespace std;


#pragma region 类型定义
typedef struct {//每块工作区存放变量
	int mergeSegNum;//归并段号
	int value;//具体值
	int key;//辅助变量，用来调整败者树
} *WorkSpace, WorkArea;
typedef struct SegTag {//用于建立最佳归并树
	int SegNum;//存放归并段号
	int length;//存放该段的长度		  
	bool operator <(const SegTag &a) const{ //重载<操作符，当segTag实例写入priority_queue<segTag>中时按length字段由小到大排
		return this->length > a.length;
	}
}segTag;
typedef struct {
	ifstream ismSource;//文件流
	int segNum;//对应文件编号
}*StreamInfo, streamInfomation;
#pragma endregion


class ExternalSortEntity
{
public:
	ExternalSortEntity();
	~ExternalSortEntity();
	void GenNum();//往指定地址文件中写入随机数
	void GetMergeSegments();//获取归并段
	void AccordingWayNumGenLoserTree(StreamInfo sInfo, const int &treeLength);
	void AddVirSegment();
	void AccordingWayNumAdjustLoserTree(int elemIndex, const int &treeLength);
	void Merge();
private:
	void GetFileName(int mergeSegNum);//根据归并段生成文件名
	void GenLoserTree();//生成败者树，使用置换-选择排序获取初始归并段
	void AdjustLoserTree(int elemIndex);//调整败者树

private:
#pragma region 常量
	const int WORKSPACECAPCITY = 20;//模拟内存工作区大小
	const int RANDOMNUMRANGE = 213121;//随机数范围
	const int RECORDNUM = 5000; //记录数目
	const int MAXTEXTTOTAL = RECORDNUM % WORKSPACECAPCITY == 0 ? (RECORDNUM / WORKSPACECAPCITY) : (RECORDNUM / WORKSPACECAPCITY + 1);//存放归并段的文件个数最大值
	const int WAYNUM = 10;//归并路数
	const string SOURCEPATH = "D:\\TestData\\source.txt";//初始文件地址
	const string TEXTHEAD = "D:\\TestData\\target";//用于动态生成目标文件名
	const string TEXTTAIL = ".txt";
#pragma endregion
	ofstream osmSource;//初始文件（存放随机数）对应输出流
	ifstream ismSource;//初始文件输入流
	ofstream *osmTarget;//用于往目标文件（存放归并段的文件）写数据
	ostringstream oss;//用于构造文件名
	int *loserTree;//败者树
	WorkSpace workSpace;//模拟内存块
	streampos pos;//记录文件指针位置
	string fileName;//文件名
	priority_queue<segTag> pQueue;//优先队列从小到大排
	StreamInfo sInfo;//存放文件流和对应文件编号
};

