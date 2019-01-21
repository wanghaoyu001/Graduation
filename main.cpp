#include<iostream>
#include"dataDefine.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include <stdlib.h> 
#include <time.h> 
#include<algorithm>
#include<thread>
using namespace std;

double trainIn[trainsetNum][numparametres - 2];    //训练集输入
double trainOut[trainsetNum][1];                            //训练集输出
double testIn[testsetNum][numparametres - 2];     //测试集输入
//double testOut[testsetNum][1];
double testOut[testsetNum];                                  //测试集输出
double transformTestOut[testsetNum][typesNum + 1] = {0};  //转换后的训练集输出
int trainID[trainsetNum];                                       //训练集每一行记录的ID，这个看实际情况有没有做决定
int testID[testsetNum];                                         //测试集每一行记录的ID
int transformOut[trainsetNum][typesNum + 1] = { 0 }; // 类别数
//每一次bootstrap得到的包
//四个线程，所以对应4个trainInPerTime, trainOutPerTime, transformTestOut
double trainInPerTime[perTimeNum][numparametres - 2];
double trainInPerTimeT1[perTimeNum][numparametres - 2];
double trainInPerTimeT2[perTimeNum][numparametres - 2];
double trainInPerTimeT3[perTimeNum][numparametres - 2];
double trainInPerTimeT4[perTimeNum][numparametres - 2];


int transformOutPerTime[perTimeNum ][typesNum + 1] = { 0 };
int transformOutPerTimeT1[perTimeNum][typesNum + 1] = { 0 };
int transformOutPerTimeT2[perTimeNum][typesNum + 1] = { 0 };
int transformOutPerTimeT3[perTimeNum][typesNum + 1] = { 0 };
int transformOutPerTimeT4[perTimeNum][typesNum + 1] = { 0 };

double transformTestOutT1[testsetNum][typesNum + 1] = { 0 };
double transformTestOutT2[testsetNum][typesNum + 1] = { 0 };
double transformTestOutT3[testsetNum][typesNum + 1] = { 0 };
double transformTestOutT4[testsetNum][typesNum + 1] = { 0 };


decisionTree Tree_;                                             //决策树
decisionTree Tree1;
decisionTree Tree2;
decisionTree Tree3;
decisionTree Tree4;


void readData(string trainsetPath, string testsetPath);  //文件的读取操作，这个看实际情况要做一些调整
int split(std::string token[], std::string s, char d);          //字符串分割函数，妈的C++没有字符串分割，蛋疼
//将输出的值0~26映射为数组上的01序列，方便分别做拟合
void indexTransform(int transformres[][typesNum + 1], double ogres[][1]);  //将原始输出转化为转化型输出

//这个函数用于将中间结果，即res[][26]这样的数组重新映射会1 ~ 26 的值
void getResult(double in[][typesNum + 1], double finalRes[], string outputpath);//将转化型输出重新变回标准输出
//自定义结构的排序cmp



int TRAIN(double trainInPerTime_[][numparametres - 2], int transformOutPerTime_[][typesNum + 1], double transformTestOut_[][typesNum + 1],decisionTree* Tree);
int mainInThread(int transformOutPerTime_[][typesNum + 1], double trainInPerTime_[][numparametres - 2], double transformTestOut_[][typesNum + 1],decisionTree* Tree);


int mainInThread(int transformOutPerTime_[][typesNum + 1], double trainInPerTime_[][numparametres - 2], double transformTestOut_[][typesNum + 1], decisionTree* Tree){
	
	//随机森林的入口
	for (int times = 0; times < ForestSize / 4; times++){
		srand((unsigned)time(NULL));
		//得到打乱后的样本
		vector<pair1>sequence(trainsetNum );
		for (int i = 0; i < trainsetNum; ++i) {
			sequence[i].index = i;
			sequence[i].value = rand();
		}
		sort(sequence.begin(),sequence.end(), cmp);
		for (int i = 0; i < perTimeNum; ++i){
			for (int j = 0; j < numparametres - 2; ++j){
				trainInPerTime_[i][j] = trainIn[sequence[i].index][j];
			}
			for (int j = 0; j < typesNum + 1; ++j){
				transformOutPerTime_[i][j] = transformOut[sequence[i].index][j];
			}
		}
		TRAIN(trainInPerTime_, transformOutPerTime_, transformTestOut_, Tree);
	}

	return 0;
}

int main(){
	readData("train.csv", "test.csv");
	indexTransform(transformOut, trainOut);
	decisionTree &  tasd = Tree1;
	thread thread1(mainInThread, transformOutPerTimeT1, trainInPerTimeT1, transformTestOutT1,&Tree1);
	thread thread2(mainInThread, transformOutPerTimeT2, trainInPerTimeT2, transformTestOutT2, &Tree2);
	thread thread3(mainInThread, transformOutPerTimeT3, trainInPerTimeT3, transformTestOutT3, &Tree3);
	thread thread4(mainInThread, transformOutPerTimeT4, trainInPerTimeT4, transformTestOutT4, &Tree4);

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	for (int i = 0; i < testsetNum; ++i) {
		for (int j = 0; j < typesNum + 1; ++j){
			transformTestOut[i][j] = transformTestOutT1[i][j] + transformTestOutT2[i][j] + transformTestOutT3[i][j] + transformTestOutT4[i][j];
		}
	}

	

	getResult(transformTestOut, testOut, "finalRes.csv");
}

void readData(string trainsetPath, string testsetPath){
	std::fstream fs;
	fs.open(trainsetPath.c_str(), std::fstream::in);
	//去除第一行，即字段头,s是用于储存当前行的临时变量
	std::string s;
	std::getline(fs, s);
	//fs.getline(s, 10000);
	std::string token[numparametres];
	//读入训练集
	int i, j;
	for (i = 0; i < trainsetNum; i++){
		std::getline(fs, s);
		int count = split(token, s, ',');
		trainID[i] = stoi(token[0]);
		for (j = 1; j < numparametres - 1; j++){
			double t;
			t = std::stod(token[j]);
			trainIn[i][j - 1] = t;
			//std::cout << d_in[i][j] << std::endl;
			//fscanf(fp1, "%lf", &d_in[i][j]);
		}
		//fscanf(fp1, "%lf", &d_out[i][0]);
		trainOut[i][0] = std::stod(token[j]);
		std::cout << i << std::endl;
	}
	fs.close();
	//读入测试集
	fs.open(testsetPath.c_str(), std::fstream::in);
	std::getline(fs, s);
	for (i = 0; i< testsetNum; i++){
		std::getline(fs, s);
		//std::string token[numparametres];
		int count = split(token, s, ',');
		testID[i] = stoi(token[0]);
		for (j = 1; j < numparametres - 1; j++){
			double t;
			t = std::stod(token[j]);
			testIn[i][j - 1] = t;
		}
		//testOut[i][0] = std::stod(token[j]);
		//dt_out[i][0] = std::stod(token[j]);
	}
	fs.close();

}
int split(std::string token[], std::string s, char d) {
	int begin = 0;
	int end = 0;
	int count = 0;
	for (unsigned int i = 0; i < s.length(); ++i) {
		if (i == s.length() - 1 && s[i] != d) {
			end = s.length();
			token[count] = std::string(s, begin, end - begin);
			++count;
			begin = end + 1;
		}
		else if (s[i] == d) {
			end = i;
			token[count] = std::string(s, begin, end - begin);
			++count;
			begin = end + 1;
		}
	}
	return count;
}
void indexTransform(int transformres[][typesNum + 1], double ogres[][1]) {
	for (int i = 0; i < trainsetNum; ++i){
		transformres[i][int(ogres[i][0])] = 1;
	}
}
void getResult(double in[testsetNum][typesNum + 1], double finalRes[testsetNum], string outputpath){
	fstream fs; //文件写操作
	fs.open(outputpath.c_str(), std::fstream::out | fstream::trunc);
   //做结果转换

	for (int i = 0; i < testsetNum; ++i){
		double max = -9999;
		int maxIndex = -9999;
		for (int j = 1; j <= typesNum; ++j){
			if (max < in[i][j]) {
				max = in[i][j];
				maxIndex = j;
			}
		}
		finalRes[i] = maxIndex;
		//储存结果
		fs << i << "," << maxIndex << endl;
	}

}


//每一次随机森林迭代的接口
int TRAIN(double trainInPerTime_[][numparametres - 2], int transformOutPerTime_[][typesNum + 1], double transformTestOut_[][typesNum + 1],decisionTree* Tree){
	stack<int>trace; //用于追踪树的遍历过程，这里我们假定用的是先根遍历;
	//double testresPerTime[testsetNum][typesNum + 1] = { 0 }; //用于承载测试输出结果的容器

	for (int typesN = 1; typesN <= typesNum; typesN++){
		//std::vector<int>out(perTimeNum);
		int out[perTimeNum];
		for (int i = 0; i < perTimeNum; ++i){
			out[i] = transformOutPerTime_[i][typesN];
		}
		(*Tree).setDecisionTree(trainInPerTime_, out);
		node head;
		vector<int>headIndex(perTimeNum);
		for (int i = 0; i < perTimeNum; ++i){
			headIndex[i] = i;
		}
		head.assign(headIndex);
		head.layer = 1;
		(*Tree).initialize(head);
		trace.push(0);
		//树的初始化（插入头节点）完成后，正式开始决策树的构建
		while (!trace.empty()){
			int current_node = trace.top();
			trace.pop();
			int container[2] = { 0 };
			(*Tree).getPartition(current_node, container);
			//判断当前节点是否成功分割
			if (container[0] != -1) {
				trace.push(container[1]);
				trace.push(container[0]);
			}
		}
		//训练完成，计算输出

		for (int i = 0; i < testsetNum; ++i){
			//testresPerTime[i][typesN] = Tree.computeRes(testIn[i]);
			transformTestOut_[i][typesN] += (*Tree).computeRes(testIn[i]);
		}
	}

	return 0;
}
