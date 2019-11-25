#include "ExternalSortEntity.h"

ExternalSortEntity::ExternalSortEntity()
{
	this->osmSource.open(SOURCEPATH, ios::out);//����
	this->loserTree = new int[WORKSPACECAPCITY];
	this->workSpace = new WorkArea[WORKSPACECAPCITY];//����ģ���ڴ�����ʼ��
	this->osmTarget = new ofstream[MAXTEXTTOTAL+1];
}

ExternalSortEntity::~ExternalSortEntity()
{
}

void ExternalSortEntity::GenNum() {
	srand((unsigned)time(NULL));
	//�ļ���β�����ո�
	for (int i = 0; i < RECORDNUM; i++) {
		if (i < (RECORDNUM - 1)) {
			this->osmSource << rand()*rand() % RANDOMNUMRANGE << " ";
		}
		else
		{
			this->osmSource << rand()*rand() % RANDOMNUMRANGE;
		}
	}
	this->osmSource.close();//�����д����Ϻ�ر���
}


void ExternalSortEntity:: GetFileName(int mergeSegNum) {
	this->oss << TEXTHEAD << mergeSegNum << TEXTTAIL;
	this->fileName = this->oss.str();
	this->oss.clear();
	this->oss.str("");//���������
}

void ExternalSortEntity::GenLoserTree() {
	int num;//��������ж�������
			//�������Ͱ���������ֵ
	for (int i = 0; i < WORKSPACECAPCITY; i++) {
		this->loserTree[i] = this->workSpace[i].value = this->workSpace[i].mergeSegNum = this->workSpace[i].key = 0;
	}
	this->ismSource.open(SOURCEPATH, ios::in);//��������
	
	int index = WORKSPACECAPCITY - 1;//�ļ����ڴ���ʱ�������ݽ�ģ���ڴ����±�����
	while (index >= 0 && this->ismSource >> num) {//���ļ����ڴ��ж���WORKSPACECAPCITY����
		this->pos = this->ismSource.tellg();//��¼�ļ�ָ��ָ�����һ�����ĵ�ַ,��ʹ���ļ�ָ��λ�õĻ������һ��ִ��ѭ�������ļ���ʱ�ļ�ָ������һλ
		this->workSpace[index].value = num;//��Ӧ�ڴ��д������
		this->workSpace[index].mergeSegNum = 1;//���ó�ʼ�鲢�κ�Ϊ1
		this->AdjustLoserTree(index);//д��һ�������������������󣬶԰��������е���
		index--;//��һ�������ڴ������
	}
}

void ExternalSortEntity::AdjustLoserTree(int elemIndex) {//elemIndexΪ��Ҫ�����������ڴ���е�����
	// loserTree[parentNode]ΪworkSpace[elemIndex]��˫�׽ڵ㣬temp�ݴ��������
	int parentNode, temp;
	for (parentNode = (elemIndex + WORKSPACECAPCITY) / 2, temp = this->loserTree[parentNode]; parentNode > 0; parentNode /= 2, temp = this->loserTree[parentNode]) {
		// �κ�С�� ���� �κ�����ҹؼ��ָ�С��Ϊʤ��
		if (this->workSpace[temp].mergeSegNum < this->workSpace[elemIndex].mergeSegNum || (this->workSpace[temp].mergeSegNum == this->workSpace[elemIndex].mergeSegNum && this->workSpace[temp].value < this->workSpace[elemIndex].value)) {
			int s;
			s = elemIndex;
			elemIndex = this->loserTree[parentNode]; //elemIndexָʾ�µ�ʤ����
			this->loserTree[parentNode] = s;
		}
	}
	this->loserTree[0] = elemIndex; // ���Ĺھ�
}

//������������Ϻ�ʼִ�л�ȡ�鲢��
void ExternalSortEntity::GetMergeSegments() {
	this->GenLoserTree();
	int num;////��������ж�������
	int *length = new int[MAXTEXTTOTAL];//��¼��Ӧ�鲢�γ���
	for (int i = 0; i < MAXTEXTTOTAL; i++) {
		length[i] = 0;
	}
	WorkArea min = this->workSpace[this->loserTree[0]];//��Ű������Ĺھ�workArea[loserTree[0]]
	this->ismSource.seekg(this->pos);//���ļ�ָ��ָ�򵽵�WORKCAPCOCITY+1��
	//��ʼ���ɹ鲢��
	while (this->ismSource >> num) {
		if (!this->osmTarget[min.mergeSegNum].is_open()) {
			this->GetFileName(min.mergeSegNum);
			this->osmTarget[min.mergeSegNum].open(this->fileName, ios::out);
		}
		int temp;
		temp = min.mergeSegNum;
		this->osmTarget[min.mergeSegNum] << min.value;//����Ӧ�ļ�дֵ
		length[min.mergeSegNum]++;
		if (num < min.value) {//����¶����ڴ����С�ڰ������ھ���������������һ���鲢��
			this->workSpace[this->loserTree[0]].mergeSegNum++;
		}
		this->workSpace[this->loserTree[0]].value = num;//���¶�������滻�Ѿ�д���ļ��������������ھ���
		this->AdjustLoserTree(this->loserTree[0]);//���µ���������������λ��Ϊ�¶����ڴ���������
		min = this->workSpace[this->loserTree[0]];//������Ϻ�min���¸�ֵ
		if (min.mergeSegNum == temp) {//��ȱ�ʾ��δ�л�����һ���鲢�Σ���֮���ÿո����
			this->osmTarget[min.mergeSegNum] << " ";
		}
	}
	//�ļ�����д����ϣ����潫�ڴ�����д���Ӧ�ļ����鲢�Σ�;
	for (int i = 0; i < WORKSPACECAPCITY; i++) {
		if (!this->osmTarget[min.mergeSegNum].is_open()) {
			this->GetFileName(min.mergeSegNum);
			this->osmTarget[min.mergeSegNum].open(this->fileName, ios::out);
		}
		int temp;
		temp = min.mergeSegNum;
		this->osmTarget[min.mergeSegNum] << min.value;
		length[min.mergeSegNum]++;
		this->workSpace[this->loserTree[0]].mergeSegNum = MAXTEXTTOTAL + 1;//�ڴ�����д���ļ���ϣ�����ǰ���Ķκŵ���Ϊ���κ�+1������Ϊ����֮�󼸴ε���������ʱ����ʼ��δ���ߣ�
		this->AdjustLoserTree(this->loserTree[0]);
		min = this->workSpace[this->loserTree[0]];
		if (min.mergeSegNum == temp) {
			this->osmTarget[min.mergeSegNum] << " ";
		}
	}
	//�ر���,�����κţ����ȴ������ȶ��У�����ʹ����ѹ鲢�㷨��ɹ鲢
	for (int i = 0; i < MAXTEXTTOTAL; i++) {
		if (this->osmTarget[i].is_open()) {
			segTag wTag;
			wTag.SegNum = i;
			wTag.length = length[i];
			this->pQueue.push(wTag);
			this->osmTarget[i].close();
		}
	}
	//�ͷ���Դ
	delete[] workSpace;
	workSpace = nullptr;
	delete[] loserTree;
	loserTree = nullptr;
	delete[] osmTarget;
	osmTarget = nullptr;
	delete[] length;
}

//�ж��費Ҫ����������ڽ�����ѹ鲢��
void ExternalSortEntity::AddVirSegment() {
	bool isAddVirSegment = (this->pQueue.size() - 1) % (WAYNUM - 1) == 0 ? false : true;
	if (isAddVirSegment) {
		int addNum = WAYNUM - (this->pQueue.size() - 1) % (WAYNUM - 1) - 1;
		for (int i = 0; i < addNum; i++) {
			segTag sTag = { 0,0 };
			this->pQueue.push(sTag);
		}
	}
}

void ExternalSortEntity::AccordingWayNumGenLoserTree(StreamInfo sInfo, const int &treeLength) {
	int num;
	//�������͹���ȡ��ʼ��
	for (int i = 0; i < treeLength; i++) {
		this->loserTree[i] = this->workSpace[i].value = this->workSpace[i].mergeSegNum = this->workSpace[i].key = 0;
	}
	int index = treeLength - 1;
	for (int i = 0; i < WAYNUM; i++) {
		if (this->sInfo[i].ismSource.is_open()) {
			this->sInfo[i].ismSource >> num;
			this->workSpace[index].value = num;
			this->workSpace[index].mergeSegNum = this->sInfo[i].segNum;
			this->workSpace[index].key = 1;
			this->AccordingWayNumAdjustLoserTree(index, treeLength);
			index--;
		}
	}
}

void ExternalSortEntity::AccordingWayNumAdjustLoserTree(int elemIndex, const int &treeLength) {
	int parentNode, temp;
	// ls[parentNode]ΪworkSpace[elemIndex]��˫�׽ڵ㣬temp�ݴ��������
	for (parentNode = (elemIndex + treeLength) / 2, temp = loserTree[parentNode]; parentNode > 0; parentNode /= 2, temp = loserTree[parentNode]) {
		//�κŴ��� ���� �κ�����ҹؼ��ָ�С��Ϊʤ��
		if (this->workSpace[temp].key < this->workSpace[elemIndex].key || (this->workSpace[temp].key == this->workSpace[elemIndex].key && this->workSpace[temp].value < this->workSpace[elemIndex].value)) {
			int s;
			s = elemIndex;
			elemIndex = this->loserTree[parentNode]; //elemIndexָʾ�µ�ʤ����
			this->loserTree[parentNode] = s;
		}
	}
	this->loserTree[0] = elemIndex; // ���Ĺھ�
}
void ExternalSortEntity::Merge() {
	//��������
	AddVirSegment();
	ofstream osmMerge;
	this->sInfo = new streamInfomation[WAYNUM];
	int afterMergeSegMentNum = MAXTEXTTOTAL + 1;//�鲢��������ļ����
	while (this->pQueue.size() > 1) {
		//��wayNum��������
		int totalLength = 0;//���й鲢�������ܸ���
		int count = 0;//��¼�򿪵����ĸ���
		for (int i = 0; i < WAYNUM; i++) {//��ʼ��Ҫ���й鲢���ļ�
			if (this->pQueue.top().SegNum != 0) {
				this->GetFileName(this->pQueue.top().SegNum);
				this->sInfo[i].ismSource.open(this->fileName, ios::in);
				this->sInfo[i].segNum = this->pQueue.top().SegNum;
				count++;
			}
			totalLength += this->pQueue.top().length;
			this->pQueue.pop();//ɾ���������Ѿ�����ȡ��segTag
		}
		//�ֱ�����ж�ȡһ�������ڴ����ɰ�����
		this->loserTree = new int[count];
		this->workSpace = new WorkArea[count];
		this->AccordingWayNumGenLoserTree(this->sInfo, count);
		this->GetFileName(afterMergeSegMentNum);
		osmMerge.open(this->fileName, ios::out);//���ļ����ڴ洢wayNum·�鲢��Ľ��
		for (int i = 0; i<totalLength; i++) {
			if (i < totalLength - 1) {
				osmMerge << this->workSpace[this->loserTree[0]].value << " ";
			}
			else
			{
				osmMerge << this->workSpace[this->loserTree[0]].value;
			}
			//д����Ϻ��ж�д���ļ�����������һ���鲢�Σ�֮����Ǹ��鲢�ζ���д���ڴ�workSpace[loserTree[0]]
			for (int j = 0; j < WAYNUM; j++) {
				if (this->sInfo[j].segNum == this->workSpace[this->loserTree[0]].mergeSegNum) {
					if (this->sInfo[j].ismSource.peek() == EOF) {//�����ж��ļ��Ƿ����
						this->workSpace[this->loserTree[0]].key++;//���꽫��������+1,��֮��İ���������ʱ����һֱΪ����
					}
					else
					{
						this->sInfo[j].ismSource >> this->workSpace[this->loserTree[0]].value;
					}
				}
			}
			//�ٶ԰���������ʹworkSpace[loserTree[0]]Ϊ�ھ�����Сֵ
			this->AccordingWayNumAdjustLoserTree(this->loserTree[0], count);
		}
		segTag sTag = { afterMergeSegMentNum,totalLength };
		this->pQueue.push(sTag);//���鲢�������ļ���źͳ���д����У�������һ�ι鲢
		afterMergeSegMentNum++;//��һ���鲢�ļ����
		osmMerge.close();
		//�ر���
		for (int i = 0; i < WAYNUM; i++) {
			if (this->sInfo[i].ismSource.is_open()) {
				this->sInfo[i].ismSource.close();
			}
		}
	}
	delete[] sInfo;
	sInfo = nullptr;
}

