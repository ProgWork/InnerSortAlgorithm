#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<queue>
using namespace std;


#pragma region ���Ͷ���
typedef struct {//ÿ�鹤������ű���
	int mergeSegNum;//�鲢�κ�
	int value;//����ֵ
	int key;//������������������������
} *WorkSpace, WorkArea;
typedef struct SegTag {//���ڽ�����ѹ鲢��
	int SegNum;//��Ź鲢�κ�
	int length;//��Ÿöεĳ���		  
	bool operator <(const SegTag &a) const{ //����<����������segTagʵ��д��priority_queue<segTag>��ʱ��length�ֶ���С������
		return this->length > a.length;
	}
}segTag;
typedef struct {
	ifstream ismSource;//�ļ���
	int segNum;//��Ӧ�ļ����
}*StreamInfo, streamInfomation;
#pragma endregion


class ExternalSortEntity
{
public:
	ExternalSortEntity();
	~ExternalSortEntity();
	void GenNum();//��ָ����ַ�ļ���д�������
	void GetMergeSegments();//��ȡ�鲢��
	void AccordingWayNumGenLoserTree(StreamInfo sInfo, const int &treeLength);
	void AddVirSegment();
	void AccordingWayNumAdjustLoserTree(int elemIndex, const int &treeLength);
	void Merge();
private:
	void GetFileName(int mergeSegNum);//���ݹ鲢�������ļ���
	void GenLoserTree();//���ɰ�������ʹ���û�-ѡ�������ȡ��ʼ�鲢��
	void AdjustLoserTree(int elemIndex);//����������

private:
#pragma region ����
	const int WORKSPACECAPCITY = 20;//ģ���ڴ湤������С
	const int RANDOMNUMRANGE = 213121;//�������Χ
	const int RECORDNUM = 5000; //��¼��Ŀ
	const int MAXTEXTTOTAL = RECORDNUM % WORKSPACECAPCITY == 0 ? (RECORDNUM / WORKSPACECAPCITY) : (RECORDNUM / WORKSPACECAPCITY + 1);//��Ź鲢�ε��ļ��������ֵ
	const int WAYNUM = 10;//�鲢·��
	const string SOURCEPATH = "D:\\TestData\\source.txt";//��ʼ�ļ���ַ
	const string TEXTHEAD = "D:\\TestData\\target";//���ڶ�̬����Ŀ���ļ���
	const string TEXTTAIL = ".txt";
#pragma endregion
	ofstream osmSource;//��ʼ�ļ���������������Ӧ�����
	ifstream ismSource;//��ʼ�ļ�������
	ofstream *osmTarget;//������Ŀ���ļ�����Ź鲢�ε��ļ���д����
	ostringstream oss;//���ڹ����ļ���
	int *loserTree;//������
	WorkSpace workSpace;//ģ���ڴ��
	streampos pos;//��¼�ļ�ָ��λ��
	string fileName;//�ļ���
	priority_queue<segTag> pQueue;//���ȶ��д�С������
	StreamInfo sInfo;//����ļ����Ͷ�Ӧ�ļ����
};

