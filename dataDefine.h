#ifndef DATADEFINED
#define DATADEFINED
#include<vector>
#include<set>
using namespace std;

//������һ���򵥵���ϵĶ����ֵ������ϵ���˼��ʹ�õĹ��ۺ�����GINI������Ļ���������0��1
//Ҳ����˵���������ֻ����0��1��ϣ���������Ƕ���ֻ࣬��Ҫ�����������Ӽ�����ɣ���������аٶȡ�
//�ٶȵĹؼ����ǣ��ö�������������������ʵ���ϣ������������Եȼ������ɸ�����������
//���磬һ��26������������Էֳ�26��0 | 1 �࣬�ֱ����26��0|1������ϣ��ҳ�����������һ����Ҷ�ӽڵ�ֵ���ģ�

//������ļ��п������������������Ϣ��numparametresָ����������������ÿһ�е��ֶ�����
//���磬ĳ�����ݼ��ļ�¼��ʽΪ id,attr1,attr2,attr3,attr3��result 
//��ônumparameteres��ֵ�� 6 

//��������Ч�ʺܵͣ�����ʹ��randforest ֮��ķ������ȿ��ԼӴ���ȷ�ʣ��ֿ��Խ�Լʱ��

#define numparametres 619//619  //��¼�е��ֶ�����
#define trainsetNum 6239//100       //ѵ�����ļ�¼����
#define testsetNum 1560//100       //���Լ��ļ�¼����
#define typesNum 26//26           //��������
#define nodesNum 200//200      //�����ܽ����

//���ﶨ��������ɭ�ֵ�size�� ��ע�⣬�����ɭ���У�ÿtypesNum�ö��������ľۺϲű���Ϊ�����ɭ���е�һ������
//��ˣ�������ɭ�ֵ�sizeΪ 1000�� ��ôʵ���ϻṹ�� 1000 * typesNum�ö�������
#define ForestSize 1000
#define perTimeNum trainsetNum / 2 
#define SelectedColumns 40 //ÿ�ηָ�ʱѡȡ���еĸ�����������н����ģ���˵�����ʱ������ֵӦΪ sqrt��numparameters - 2��
//���ʱ����ֵΪ��numparametres - 2�� / 3��������Ȼ����ϣ�����Ϊ�˼��ټ��㣬����ѡ����ǰ�ߡ�
#define MaxLayerNum 7


struct node
{
	//DataIndex  ��ָ��������ԭ���ݼ���Ѱ�����ݼ�¼
	void assign(vector<int>dataIndex_); //����������ڽڵ㸳ֵ
	node::node(){}
	//void getAttributes(vector<int>selectedCols);  //����������ڻ������ֵ������ֵ��ÿһ���ϵ�ֵ����һ�����ǿ����Ż��ģ�
	void copy(node ele);  //����������������õģ�����ʵ��û������
	//void computeValue(); //����������ڼ���Ҷ�ӽڵ��ֵ����0~1֮�䣩


	vector<int>dataIndex; //����װ�ýڵ�����ݵ�����
    
	//���ڼ�¼�ýڵ�ķָ��
	vector<double>attributes[SelectedColumns]; 
	int leftChild, rightChild;                                    //�ӽڵ��Index
	int isLeaf;                                                         // 0 ��ʾ�ڲ��ڵ㣬1 ��ʾ�ⲿ�ڵ�
	int splitLabel;                                                        //��¼��ǰ�ķָ����Ե�λ��
	double labelvalue;                                        //ԓ�ڵ�ָ�ֵ                  
	double value;                                                  //�ýڵ��ƽ��ֵ���������ʱ������
	int layer;                                                          //���ڼ�¼���ڲ���
	double gini;                                                    //��ǰ�ڵ��GINIֵ
};
//node1������ѵ����ɺ�����ļ�����Ҫ�Ĵ洢�ڵ㣬��Ϊѵ����ɺ�node��ֻ��Ҫ������Ϣ��������Ҫ�����ݼ���ص���Ϣ��
//����node1�����Ĵ洢�ṹ��Ϊ�˽�Լ�洢�ռ�
struct node1 {
	int leftChild, rightChild;    //�ӽڵ��Index
	int isLeaf;                          // 0 ��ʾ�ڲ��ڵ㣬1 ��ʾ�ⲿ�ڵ�
	int label;
	double labelvalue;        //ԓ�ڵ���ѡ�õķָ������Լ��ָ�ֵ    
	double value;                 //�ýڵ��ƽ��ֵ���������ʱ������

	void copy(node ele);
};
struct decisionTree {
	double trainIn[perTimeNum][numparametres -2];
	int trainOut[perTimeNum];
	node Nodes[nodesNum];
	//�ڽ���ʱ��Ҫʹ�õĿ��ýڵ�������¼
	int usableNode;
	//container ���ڽ�������������ͷ�ڵ㣬[-1,-1]��ʾ�ָ�ʧ�ܣ���ʱ��������false
	decisionTree(){};
	void setDecisionTree(double trainIn_[][numparametres - 2], int trainOut_[]);
	bool getPartition(int index, int container[]);                            //���������Ľڵ�ָ�
	double computeGini(int index, int label, double value);        //���ڼ���ָ�ڵ�ʱ����Ҫ��giniֵ
	//double computeNodeGini(int index);                                  //����ĳһ�ڵ��Gini
	double computeRes(double[numparametres - 2]);               //ѵ����ɺ�����Ԥ��ĺ����������ǲ�����������
	//�õ��������Nodes�ڵ����У����ڽ�һ���������Ĳ������ļ�
	//��ʼ������ͷ�ڵ㣬����ֻ��Ϊ�˷���������е��������
	//����뱣�����Ĳ����Ա��´�ʹ�ã������getNodesSequence��
	//Ȼ�������н����ļ��洢����
	void getNodesSequence(node1[]);                                       
	//��ʼ����
	void initialize(node ele);                                                      
	                                                                                           
	 //����ÿ���ڵ��һЩ����                                                                      
	void getNodeAttr(vector<int>selectedCols, int index);
	void computePerNodeGini(int index);
	void computeNodeValue(int index);
};
//���ڴ������еĽṹ
struct pair1{
	int index;
	int value;

	pair1(){}
	pair1(int index1, int value1){ index = index1; value = value1; }
};

bool cmp(pair1 a, pair1 b);



#endif
