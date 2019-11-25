#include "ExternalSortEntity.h"

ExternalSortEntity::ExternalSortEntity()
{
	this->osmSource.open(SOURCEPATH, ios::out);//打开流
	this->loserTree = new int[WORKSPACECAPCITY];
	this->workSpace = new WorkArea[WORKSPACECAPCITY];//树和模拟内存区初始化
	this->osmTarget = new ofstream[MAXTEXTTOTAL+1];
}

ExternalSortEntity::~ExternalSortEntity()
{
}

void ExternalSortEntity::GenNum() {
	srand((unsigned)time(NULL));
	//文件结尾不留空格
	for (int i = 0; i < RECORDNUM; i++) {
		if (i < (RECORDNUM - 1)) {
			this->osmSource << rand()*rand() % RANDOMNUMRANGE << " ";
		}
		else
		{
			this->osmSource << rand()*rand() % RANDOMNUMRANGE;
		}
	}
	this->osmSource.close();//随机数写入完毕后关闭流
}


void ExternalSortEntity:: GetFileName(int mergeSegNum) {
	this->oss << TEXTHEAD << mergeSegNum << TEXTTAIL;
	this->fileName = this->oss.str();
	this->oss.clear();
	this->oss.str("");//流内容清空
}

void ExternalSortEntity::GenLoserTree() {
	int num;//缓存从流中读的数据
			//工作区和败者树赋初值
	for (int i = 0; i < WORKSPACECAPCITY; i++) {
		this->loserTree[i] = this->workSpace[i].value = this->workSpace[i].mergeSegNum = this->workSpace[i].key = 0;
	}
	this->ismSource.open(SOURCEPATH, ios::in);//打开输入流
	
	int index = WORKSPACECAPCITY - 1;//文件往内存区时读入数据进模拟内存块的下标索引
	while (index >= 0 && this->ismSource >> num) {//从文件往内存中读入WORKSPACECAPCITY个数
		this->pos = this->ismSource.tellg();//记录文件指针指向的下一个数的地址,不使用文件指针位置的话，最后一次执行循环条件文件会时文件指针多后移一位
		this->workSpace[index].value = num;//对应内存块写入数据
		this->workSpace[index].mergeSegNum = 1;//设置初始归并段号为1
		this->AdjustLoserTree(index);//写入一个数的索引进败者树后，对败者树进行调整
		index--;//下一个数的内存块索引
	}
}

void ExternalSortEntity::AdjustLoserTree(int elemIndex) {//elemIndex为需要调整数的在内存块中的索引
	// loserTree[parentNode]为workSpace[elemIndex]的双亲节点，temp暂存败者索引
	int parentNode, temp;
	for (parentNode = (elemIndex + WORKSPACECAPCITY) / 2, temp = this->loserTree[parentNode]; parentNode > 0; parentNode /= 2, temp = this->loserTree[parentNode]) {
		// 段号小者 或者 段号相等且关键字更小的为胜者
		if (this->workSpace[temp].mergeSegNum < this->workSpace[elemIndex].mergeSegNum || (this->workSpace[temp].mergeSegNum == this->workSpace[elemIndex].mergeSegNum && this->workSpace[temp].value < this->workSpace[elemIndex].value)) {
			int s;
			s = elemIndex;
			elemIndex = this->loserTree[parentNode]; //elemIndex指示新的胜利者
			this->loserTree[parentNode] = s;
		}
	}
	this->loserTree[0] = elemIndex; // 最后的冠军
}

//败者树建立完毕后开始执行获取归并段
void ExternalSortEntity::GetMergeSegments() {
	this->GenLoserTree();
	int num;////缓存从流中读的数据
	int *length = new int[MAXTEXTTOTAL];//记录对应归并段长度
	for (int i = 0; i < MAXTEXTTOTAL; i++) {
		length[i] = 0;
	}
	WorkArea min = this->workSpace[this->loserTree[0]];//存放败者树的冠军workArea[loserTree[0]]
	this->ismSource.seekg(this->pos);//将文件指针指向到第WORKCAPCOCITY+1数
	//开始生成归并段
	while (this->ismSource >> num) {
		if (!this->osmTarget[min.mergeSegNum].is_open()) {
			this->GetFileName(min.mergeSegNum);
			this->osmTarget[min.mergeSegNum].open(this->fileName, ios::out);
		}
		int temp;
		temp = min.mergeSegNum;
		this->osmTarget[min.mergeSegNum] << min.value;//往对应文件写值
		length[min.mergeSegNum]++;
		if (num < min.value) {//如果新读入内存的数小于败者树冠军，将该数放入下一个归并段
			this->workSpace[this->loserTree[0]].mergeSegNum++;
		}
		this->workSpace[this->loserTree[0]].value = num;//将新读入的数替换已经写入文件的数（败者树冠军）
		this->AdjustLoserTree(this->loserTree[0]);//重新调整败者树，调整位置为新读入内存树的索引
		min = this->workSpace[this->loserTree[0]];//调整完毕后，min重新赋值
		if (min.mergeSegNum == temp) {//相等表示并未切换到下一个归并段，数之间用空格隔开
			this->osmTarget[min.mergeSegNum] << " ";
		}
	}
	//文件中数写入完毕，下面将内存中数写入对应文件（归并段）;
	for (int i = 0; i < WORKSPACECAPCITY; i++) {
		if (!this->osmTarget[min.mergeSegNum].is_open()) {
			this->GetFileName(min.mergeSegNum);
			this->osmTarget[min.mergeSegNum].open(this->fileName, ios::out);
		}
		int temp;
		temp = min.mergeSegNum;
		this->osmTarget[min.mergeSegNum] << min.value;
		length[min.mergeSegNum]++;
		this->workSpace[this->loserTree[0]].mergeSegNum = MAXTEXTTOTAL + 1;//内存中数写入文件完毕，将当前数的段号调整为最大段号+1，就是为了在之后几次调整败者树时，它始终未败者；
		this->AdjustLoserTree(this->loserTree[0]);
		min = this->workSpace[this->loserTree[0]];
		if (min.mergeSegNum == temp) {
			this->osmTarget[min.mergeSegNum] << " ";
		}
	}
	//关闭流,并将段号，长度存入优先队列，方便使用最佳归并算法完成归并
	for (int i = 0; i < MAXTEXTTOTAL; i++) {
		if (this->osmTarget[i].is_open()) {
			segTag wTag;
			wTag.SegNum = i;
			wTag.length = length[i];
			this->pQueue.push(wTag);
			this->osmTarget[i].close();
		}
	}
	//释放资源
	delete[] workSpace;
	workSpace = nullptr;
	delete[] loserTree;
	loserTree = nullptr;
	delete[] osmTarget;
	osmTarget = nullptr;
	delete[] length;
}

//判断需不要创建虚段用于建立最佳归并树
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
	//败者树和工作取初始化
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
	// ls[parentNode]为workSpace[elemIndex]的双亲节点，temp暂存败者索引
	for (parentNode = (elemIndex + treeLength) / 2, temp = loserTree[parentNode]; parentNode > 0; parentNode /= 2, temp = loserTree[parentNode]) {
		//段号大者 或者 段号相等且关键字更小的为胜者
		if (this->workSpace[temp].key < this->workSpace[elemIndex].key || (this->workSpace[temp].key == this->workSpace[elemIndex].key && this->workSpace[temp].value < this->workSpace[elemIndex].value)) {
			int s;
			s = elemIndex;
			elemIndex = this->loserTree[parentNode]; //elemIndex指示新的胜利者
			this->loserTree[parentNode] = s;
		}
	}
	this->loserTree[0] = elemIndex; // 最后的冠军
}
void ExternalSortEntity::Merge() {
	//添加虚拟段
	AddVirSegment();
	ofstream osmMerge;
	this->sInfo = new streamInfomation[WAYNUM];
	int afterMergeSegMentNum = MAXTEXTTOTAL + 1;//归并后产生的文件编号
	while (this->pQueue.size() > 1) {
		//打开wayNum个输入流
		int totalLength = 0;//进行归并的数的总个数
		int count = 0;//记录打开的流的个数
		for (int i = 0; i < WAYNUM; i++) {//开始打开要进行归并的文件
			if (this->pQueue.top().SegNum != 0) {
				this->GetFileName(this->pQueue.top().SegNum);
				this->sInfo[i].ismSource.open(this->fileName, ios::in);
				this->sInfo[i].segNum = this->pQueue.top().SegNum;
				count++;
			}
			totalLength += this->pQueue.top().length;
			this->pQueue.pop();//删除队列中已经被读取的segTag
		}
		//分别从流中读取一个数到内存生成败者树
		this->loserTree = new int[count];
		this->workSpace = new WorkArea[count];
		this->AccordingWayNumGenLoserTree(this->sInfo, count);
		this->GetFileName(afterMergeSegMentNum);
		osmMerge.open(this->fileName, ios::out);//打开文件用于存储wayNum路归并后的结果
		for (int i = 0; i<totalLength; i++) {
			if (i < totalLength - 1) {
				osmMerge << this->workSpace[this->loserTree[0]].value << " ";
			}
			else
			{
				osmMerge << this->workSpace[this->loserTree[0]].value;
			}
			//写入完毕后判断写入文件的数属于哪一个归并段，之后从那个归并段读数写入内存workSpace[loserTree[0]]
			for (int j = 0; j < WAYNUM; j++) {
				if (this->sInfo[j].segNum == this->workSpace[this->loserTree[0]].mergeSegNum) {
					if (this->sInfo[j].ismSource.peek() == EOF) {//用于判断文件是否读完
						this->workSpace[this->loserTree[0]].key++;//读完将辅助变量+1,在之后的败者树调整时，它一直为败者
					}
					else
					{
						this->sInfo[j].ismSource >> this->workSpace[this->loserTree[0]].value;
					}
				}
			}
			//再对败者树调整使workSpace[loserTree[0]]为冠军即最小值
			this->AccordingWayNumAdjustLoserTree(this->loserTree[0], count);
		}
		segTag sTag = { afterMergeSegMentNum,totalLength };
		this->pQueue.push(sTag);//将归并产生的文件编号和长度写入队列，用于下一次归并
		afterMergeSegMentNum++;//下一个归并文件编号
		osmMerge.close();
		//关闭流
		for (int i = 0; i < WAYNUM; i++) {
			if (this->sInfo[i].ismSource.is_open()) {
				this->sInfo[i].ismSource.close();
			}
		}
	}
	delete[] sInfo;
	sInfo = nullptr;
}

