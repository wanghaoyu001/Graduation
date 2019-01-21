#include"dataDefine.h"
#include<algorithm>
#include<time.h>
#include<stdlib.h>

void node::assign(vector<int> dataIndex_){
	//给索引赋值
    dataIndex = dataIndex_;
	//int i1 = 0;

	//getAttributes();

	// 计算本节点的gini
	//int category1 = 0;  // res[ i ] = 0的数量
	//int category2 = 0; // res[ i ] = 1的数量
	//for (int i = 0; i < res.size(); ++i){
	//	if (res[i] == 0) {
	//		category1 += 1;
	//	}
//	}
//	category2 = res.size() - category1;
//	gini = 1 - pow((double)category1 / res.size(), 2) - pow((double)category2 / res.size(), 2);
}
void decisionTree::getNodeAttr(vector<int>selectedCols, int index){
	//for (int i = 0; i < dataSet.size(); ++i){
	//	for (int j = 0; j < numparametres - 2; j++) {
	//		attributes[j].insert(dataSet[i][j]);
	//	}
	//}
	//在这里我们下采样的方法是将列排序后除以100，这个比率可以根据样本大小自行修改
	
	int sampleNum = 100;
	if (Nodes[index].dataIndex.size() <= 100){
		for (int i = 0; i < selectedCols.size(); ++i){
		    Nodes[index].attributes[i].resize(Nodes[index].dataIndex.size());
			for (int j = 0; j < Nodes[index].dataIndex.size(); j++){
				Nodes[index].attributes[i][j] = trainIn[Nodes[index].dataIndex[j]][selectedCols[i]];
			}
		}
		return;
	}

	//样本数大于三十的情况
	for (int i = 0; i < selectedCols.size(); ++i){
		//每个特征选取的分割点的个数
		Nodes[index].attributes[i].resize(100);
		vector<double> temp(Nodes[index].dataIndex. size());
		for (int j = 0; j < Nodes[index].dataIndex.size(); ++j) {
			//temp[j] = dataSet[j][selectedCols[i]];
			temp[j] = trainIn[Nodes[index].dataIndex[j]][selectedCols[i]];
		}
		sort(temp.begin(), temp.end());
		//乘数因子
		double factor = (double)Nodes[index].dataIndex.size() / 100;
		for (int j = 0; j < Nodes[index].attributes[i].size(); j++){
			int curIndex = factor * j - int(factor * j) < 0.5 ? int(factor * j) : int(factor * j + 1);
			curIndex = curIndex > Nodes[index].dataIndex.size() - 1 ? Nodes[index].dataIndex.size() - 1 : curIndex;
			Nodes[index].attributes[i][j] = temp[curIndex];

		}
	}
}
void node::copy(node ele) {
	//res = ele.res;
	leftChild = ele.leftChild;
	rightChild = ele.rightChild;
	isLeaf = ele.isLeaf;
	splitLabel = ele.splitLabel;
	labelvalue = ele.labelvalue;
	value = ele.value;
	layer = ele.layer;
	dataIndex = ele.dataIndex;
	gini = ele.gini;
	//dataSet.resize(ele.dataSet.size());
    //初始化二维动态数组	
	//for (int i = 0; i < dataSet.size(); ++i){
	//	dataSet[i].resize(numparametres - 2);
	//}
	//int i1 = 0;
	//for (vector<vector<double>>::iterator it = ele.dataSet.begin(); it != ele.dataSet.end(); ++it) {
	//	for (int i = 0; i < numparametres - 2; ++i) {
	//		dataSet[i1][i] = (*it)[i];
	//	}
	//	++i1;
	//}
	/*for (int i = 0; i < numparametres - 2; i++) {
		attributes[i] = ele.attributes[i];
	}*/

}
void decisionTree::computeNodeValue(int index){
	double sum = 0;
	for (unsigned int i = 0; i < Nodes[index].dataIndex.size(); ++i){
		sum += trainOut[Nodes[index].dataIndex[i]];
	}
	Nodes[index].value = sum / Nodes[index].dataIndex.size();
}
void decisionTree::setDecisionTree(double trainIn_[][numparametres -2],  int trainOut_[]){
	for (int i = 0; i < perTimeNum; ++i){
		for (int j = 0; j < numparametres - 2; ++j){
			trainIn[i][j] = trainIn_[i][j];
		}
		trainOut[i] = trainOut_[i];
	}
}

void node1::copy(node ele){
	leftChild = ele.leftChild;
	rightChild = ele.rightChild;
	isLeaf = ele.isLeaf;
	label = ele.splitLabel;
	labelvalue = ele.labelvalue;
	value = ele.value;
}

// 这个函数应该传进一个 大小为nodesNum 的node1类型的数组作为参数的容器，
//nodesNum指的是节点个数，当然也可以自行修改
void decisionTree::getNodesSequence(node1 container[]) {
	for (int i = 0; i < nodesNum; ++i){
		container[i].copy(Nodes[i]);
	}
}
void decisionTree::initialize(node ele){
	Nodes[0].copy(ele);
	computePerNodeGini(0);
	usableNode = 1;
}
double decisionTree::computeRes(double item[numparametres - 2]){
	int position = 0;                //目前访问的节点
	while (Nodes[position].isLeaf != 1){
		int  label_ = Nodes[position].splitLabel;
		double label_v = Nodes[position].labelvalue;
		if (item[label_] <= label_v){
			position = Nodes[position].leftChild;
		}
		else {
			position = Nodes[position].rightChild;
		}
	}
	return Nodes[position].value;
}
// index 为Node节点下标，label 为属性标签， value为该属性标签下的分割阈值
double decisionTree::computeGini(int index, int label, double value_) {
	int category1 = 0;         //一共两part，小于等于value的一part，大于value的一part,category用于记录该part的元素数量
	int category2 = 0;
	int type10 = 0;
	int type11 = 0;
	int type20 = 0;
	int type21 = 0;
	int ones = 0;
	int zeros = 0;
	
	unsigned int size = Nodes[index].dataIndex.size();
	//unsigned int size = Nodes[index].dataSet.size();
	//std::vector<int>res1(size);
	//std::vector<int>res2(size);
	for (unsigned int i = 0; i < size; ++i){
		if (trainIn[Nodes[index].dataIndex[i]][label] <= value_){
			type10 += (trainOut[Nodes[index].dataIndex[i]] == 0 ? 1 : 0);
			++category1;
		}

		zeros += (trainOut[Nodes[index].dataIndex[i]] == 0 ? 1 : 0);
	}
	category2 = Nodes[index].dataIndex.size() - category1;
	type20 = zeros - type10;
	type11 = category1 - type10;
	type21 = category2 - type20;

	double gini1 = 0;  //两个部分分别的gini系数
	double gini2 = 0;
	
	if (category1 != 0)
	    gini1 = 1 - pow((double)type10 / category1, 2) - pow((double)type11 / category1, 2);
	if (category2 != 0)
	    gini2 = 1 - pow((double)type20 / category2, 2) - pow((double)type21 / category2, 2);
	return (double)category1 / size * gini1 + (double)category2 / size * gini2;

}
bool decisionTree::getPartition(int index, int container[2]){
	//******************************************* overfitting control / finishing control
	  // 此处是要return false的
	if (Nodes[index].gini == 0 || Nodes[index].layer >= MaxLayerNum/* || /*Nodes[index].dataSet.size() < 10*/) {
		Nodes[index].isLeaf = 1;
		//计算叶子节点的拟合值
		double sum = 0;
		for (int i = 0; i < Nodes[index].dataIndex.size(); ++i){
			sum += trainOut[Nodes[index].dataIndex[i]];//Nodes[index].res[i];
		}
		Nodes[index].value = sum / Nodes[index].dataIndex.size();
		container[0] = container[1] = -1;
		return false;
	}
	//********************************************
	int i = 0; // 遍历当前节点中所有的元素用
	double min_gini = 10000;
	//用于分割用的属性和属性的值
	int par_label = -1;
	double par_value = -1;
	double temp_gini;
	
	//获得打乱后的索引，并选取前面的25个作为选取的列的索引，传递给getAttr，获得所需要的分割值
	vector<pair1> sequence(numparametres -2);
	srand((unsigned)time(NULL));
	for (i = 0; i < sequence.size(); ++i){
		sequence[i].index = i;
		sequence[i].value = rand();
	}
	std::sort(sequence.begin(), sequence.end(),cmp);
	vector<int>s(SelectedColumns);
	for (int i = 0; i < SelectedColumns; ++i){
		s[i] = sequence[i].index;
	}
	getNodeAttr(s, index);
	//Nodes[index].getAttributes(s);
	for (i = 0; i < SelectedColumns; ++i) {
		vector<double>::iterator cursor;
		for (cursor = Nodes[index].attributes[i].begin(); cursor != Nodes[index].attributes[i].end(); ++cursor){
			temp_gini = computeGini(index, s[i], *cursor);
			if (min_gini > temp_gini) {
				min_gini = temp_gini;
				par_label = s[i];
				par_value = *cursor;
			}
		}
	}

	unsigned int size = Nodes[index].dataIndex.size();

	vector<int>dataIndex1(size);
	vector<int>dataIndex2(size);
	int num1 = 0;  // num1 和 num2 是计数器,再resize dSet中会被用到
	int num2 = 0;
	for (int i = 0; i < Nodes[index].dataIndex.size(); ++i){
		if (trainIn[Nodes[index].dataIndex[i]][par_label] <= par_value) {
			dataIndex1[num1] = Nodes[index].dataIndex[i];
			++num1;
		}
		else {

			dataIndex2[num2] = Nodes[index].dataIndex[i];
			//res2[num2] = Nodes[index].res[i];
			++num2;
		}
	}
	dataIndex1.resize(num1);

	dataIndex2.resize(num2);


	Nodes[usableNode].assign(dataIndex1);
	Nodes[usableNode].layer = Nodes[index].layer + 1;
	computePerNodeGini(usableNode);
	container[0] = usableNode;
	++usableNode;
	
	Nodes[usableNode].assign(dataIndex2);
	Nodes[usableNode].layer = Nodes[index].layer + 1;
	computePerNodeGini(usableNode);
	container[1] = usableNode;
	++usableNode;
	

	// 更新当前节点的各种label
	Nodes[index].isLeaf = 0;
	Nodes[index].splitLabel = par_label;
	Nodes[index].labelvalue = par_value;
	Nodes[index].leftChild = usableNode - 2;
	Nodes[index].rightChild = usableNode - 1;
	return true;

}
void decisionTree::computePerNodeGini(int index){
	// 计算本节点的gini
	int category1 = 0;  // res[ i ] = 0的数量
	int category2 = 0; // res[ i ] = 1的数量
	for (int i = 0; i < Nodes[index].dataIndex.size(); ++i){
		if (trainOut[Nodes[index].dataIndex[i]] == 0) {
			category1 += 1;
		}
	}
		category2 = Nodes[index].dataIndex.size() - category1;
		int SIZE = Nodes[index].dataIndex.size();
		Nodes[index].gini = 1 - pow((double)category1 / SIZE, 2) - pow((double)category2 / SIZE, 2);
}

bool cmp(pair1 a, pair1 b){
	return (a.value < b.value);
}
