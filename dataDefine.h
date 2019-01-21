#ifndef DATADEFINED
#define DATADEFINED
#include<vector>
#include<set>
using namespace std;

//该树是一个简单的拟合的二叉二值树，拟合的意思是使用的估价函数是GINI，二叉的划分依据是0和1
//也就是说，这个颗树只能做0，1拟合，但是如果是多分类，只需要将二叉树叠加即可完成，这个请自行百度。
//百度的关键词是：用二分类树构造多分类树，实际上，多分类问题可以等价于若干个二分类问题
//例如，一个26类的样本，可以分成26个0 | 1 类，分别对这26个0|1类做拟合，找出可能性最大的一个（叶子节点值最大的）

//在这个文件中可以配置输入变量的信息，numparametres指的是完整的样本的每一行的字段总数
//例如，某个数据集的记录格式为 id,attr1,attr2,attr3,attr3，result 
//那么numparameteres的值是 6 

//决策树的效率很低，建议使用randforest 之类的方法，既可以加大正确率，又可以节约时间

#define numparametres 619//619  //记录中的字段总数
#define trainsetNum 6239//100       //训练集的记录条数
#define testsetNum 1560//100       //测试集的记录条数
#define typesNum 26//26           //类型数量
#define nodesNum 200//200      //树的总结点数

//这里定义的是随机森林的size， 请注意，在随机森林中，每typesNum棵二分类树的聚合才被认为是随机森林中的一棵树。
//因此，如果随机森林的size为 1000， 那么实际上会构造 1000 * typesNum棵二分类树
#define ForestSize 1000
#define perTimeNum trainsetNum / 2 
#define SelectedColumns 40 //每次分割时选取的列的个数，这个是有讲究的，据说分类的时候它的值应为 sqrt（numparameters - 2）
//拟合时它的值为（numparametres - 2） / 3，我们虽然是拟合，但是为了加速计算，还是选用了前者。
#define MaxLayerNum 7


struct node
{
	//DataIndex  将指引我们在原数据集中寻找数据记录
	void assign(vector<int>dataIndex_); //这个函数用于节点赋值
	node::node(){}
	//void getAttributes(vector<int>selectedCols);  //这个函数用于获得属性值（属性值即每一列上的值，这一部分是可以优化的）
	void copy(node ele);  //这个函数想着是有用的，但其实并没有用上
	//void computeValue(); //这个函数用于计算叶子节点的值。（0~1之间）


	vector<int>dataIndex; //用于装该节点的数据的容器
    
	//用于记录该节点的分割点
	vector<double>attributes[SelectedColumns]; 
	int leftChild, rightChild;                                    //子节点的Index
	int isLeaf;                                                         // 0 表示内部节点，1 表示外部节点
	int splitLabel;                                                        //记录当前的分割属性的位置
	double labelvalue;                                        //該节点分割值                  
	double value;                                                  //该节点的平均值，用于拟合时的运算
	int layer;                                                          //用于记录所在层数
	double gini;                                                    //当前节点的GINI值
};
//node1是树在训练完成后存入文件所需要的存储节点，因为训练完成后，node将只需要参数信息，而不需要与数据集相关的信息，
//定义node1这样的存储结构是为了节约存储空间
struct node1 {
	int leftChild, rightChild;    //子节点的Index
	int isLeaf;                          // 0 表示内部节点，1 表示外部节点
	int label;
	double labelvalue;        //該节点所选用的分割属性以及分割值    
	double value;                 //该节点的平均值，用于拟合时的运算

	void copy(node ele);
};
struct decisionTree {
	double trainIn[perTimeNum][numparametres -2];
	int trainOut[perTimeNum];
	node Nodes[nodesNum];
	//在建树时需要使用的可用节点索引记录
	int usableNode;
	//container 用于接受左右子树的头节点，[-1,-1]表示分割失败，此时函数返回false
	decisionTree(){};
	void setDecisionTree(double trainIn_[][numparametres - 2], int trainOut_[]);
	bool getPartition(int index, int container[]);                            //用于做树的节点分割
	double computeGini(int index, int label, double value);        //用于计算分割节点时所需要的gini值
	//double computeNodeGini(int index);                                  //计算某一节点的Gini
	double computeRes(double[numparametres - 2]);               //训练完成后，用于预测的函数，输入是测试输入向量
	//得到这颗树的Nodes节点序列，用于进一步保存树的参数进文件
	//初始化树的头节点，这里只是为了方便操作才有的这个函数
	//如果想保存树的参数以便下次使用，请调用getNodesSequence，
	//然后再自行进行文件存储操作
	void getNodesSequence(node1[]);                                       
	//初始化树
	void initialize(node ele);                                                      
	                                                                                           
	 //对于每个节点的一些操作                                                                      
	void getNodeAttr(vector<int>selectedCols, int index);
	void computePerNodeGini(int index);
	void computeNodeValue(int index);
};
//用于打乱序列的结构
struct pair1{
	int index;
	int value;

	pair1(){}
	pair1(int index1, int value1){ index = index1; value = value1; }
};

bool cmp(pair1 a, pair1 b);



#endif
