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

double trainIn[trainsetNum][numparametres - 2];    //ѵ��������
double trainOut[trainsetNum][1];                            //ѵ�������
double testIn[testsetNum][numparametres - 2];     //���Լ�����
//double testOut[testsetNum][1];
double testOut[testsetNum];                                  //���Լ����
double transformTestOut[testsetNum][typesNum + 1] = {0};  //ת�����ѵ�������
int trainID[trainsetNum];                                       //ѵ����ÿһ�м�¼��ID�������ʵ�������û��������
int testID[testsetNum];                                         //���Լ�ÿһ�м�¼��ID
int transformOut[trainsetNum][typesNum + 1] = { 0 }; // �����
//ÿһ��bootstrap�õ��İ�
//�ĸ��̣߳����Զ�Ӧ4��trainInPerTime, trainOutPerTime, transformTestOut
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


decisionTree Tree_;                                             //������
decisionTree Tree1;
decisionTree Tree2;
decisionTree Tree3;
decisionTree Tree4;


void readData(string trainsetPath, string testsetPath);  //�ļ��Ķ�ȡ�����������ʵ�����Ҫ��һЩ����
int split(std::string token[], std::string s, char d);          //�ַ����ָ�������C++û���ַ����ָ����
//�������ֵ0~26ӳ��Ϊ�����ϵ�01���У�����ֱ������
void indexTransform(int transformres[][typesNum + 1], double ogres[][1]);  //��ԭʼ���ת��Ϊת�������

//����������ڽ��м�������res[][26]��������������ӳ���1 ~ 26 ��ֵ
void getResult(double in[][typesNum + 1], double finalRes[], string outputpath);//��ת����������±�ر�׼���
//�Զ���ṹ������cmp



int TRAIN(double trainInPerTime_[][numparametres - 2], int transformOutPerTime_[][typesNum + 1], double transformTestOut_[][typesNum + 1],decisionTree* Tree);
int mainInThread(int transformOutPerTime_[][typesNum + 1], double trainInPerTime_[][numparametres - 2], double transformTestOut_[][typesNum + 1],decisionTree* Tree);


int mainInThread(int transformOutPerTime_[][typesNum + 1], double trainInPerTime_[][numparametres - 2], double transformTestOut_[][typesNum + 1], decisionTree* Tree){
	
	//���ɭ�ֵ����
	for (int times = 0; times < ForestSize / 4; times++){
		srand((unsigned)time(NULL));
		//�õ����Һ������
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
	//ȥ����һ�У����ֶ�ͷ,s�����ڴ��浱ǰ�е���ʱ����
	std::string s;
	std::getline(fs, s);
	//fs.getline(s, 10000);
	std::string token[numparametres];
	//����ѵ����
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
	//������Լ�
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
	fstream fs; //�ļ�д����
	fs.open(outputpath.c_str(), std::fstream::out | fstream::trunc);
   //�����ת��

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
		//������
		fs << i << "," << maxIndex << endl;
	}

}


//ÿһ�����ɭ�ֵ����Ľӿ�
int TRAIN(double trainInPerTime_[][numparametres - 2], int transformOutPerTime_[][typesNum + 1], double transformTestOut_[][typesNum + 1],decisionTree* Tree){
	stack<int>trace; //����׷�����ı������̣��������Ǽٶ��õ����ȸ�����;
	//double testresPerTime[testsetNum][typesNum + 1] = { 0 }; //���ڳ��ز���������������

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
		//���ĳ�ʼ��������ͷ�ڵ㣩��ɺ���ʽ��ʼ�������Ĺ���
		while (!trace.empty()){
			int current_node = trace.top();
			trace.pop();
			int container[2] = { 0 };
			(*Tree).getPartition(current_node, container);
			//�жϵ�ǰ�ڵ��Ƿ�ɹ��ָ�
			if (container[0] != -1) {
				trace.push(container[1]);
				trace.push(container[0]);
			}
		}
		//ѵ����ɣ��������

		for (int i = 0; i < testsetNum; ++i){
			//testresPerTime[i][typesN] = Tree.computeRes(testIn[i]);
			transformTestOut_[i][typesN] += (*Tree).computeRes(testIn[i]);
		}
	}

	return 0;
}
