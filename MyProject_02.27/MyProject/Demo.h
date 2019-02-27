class decisionnoed
{
public:
	struct dividest
	{
		int rows;
		int column;
		int value;
		int resultTrue;
		int resultFalse;
		int resultAll;
		int valueTrue;
		int valueFalse;
		int valueAll;
	};
	dividest divs[100];
	dividest results[100];

	int col;
	//char results;
	char tb;
	char fb;
	int column;
	char value[100];
	char *const a = value;
	double entTrue = 0;
	double entFalse = 0;
	double entAll = 0;
	char *equlFalse[100];
	char *equlTrue[100];
	char *equlAll[100];
	
	void dividest();//拆分的列号以及参考值的输入
	void split_function();//根据所给参考值进行拆分
	void output();//输出满足条件的拆分列表
	void outputmy_data();//输出原列表
	void outputmy_dataAgain(); //再次输出原列表
	void uniquecounts();//对各种可能结果进行计数
	void entropy();//计算数据集合的熵
	void buildtree();//构建决策树

	char *const my_data[15][5] =
	{
	{ "slashdot","USA","yes","18","None" },
	{ "google","France","yes","23","Premium" },
	{ "digg","USA","yes","24","Basic" },
	{ "kiwitobes","France","yes","23","Basic" },
	{ "google","UK","no","21","Premium" },
	{ "(direct)","New Zealand","no","12","None" },
	{ "(direct)","UK","no","21","Basic" },
	{ "google","USA","no","24","Premium" },
	{ "slashdot","France","yes","19","None" },
	{ "digg","USA","no","18","None" },
	{ "google","UK","no","18","None" },
	{ "kiwitobes","UK","no","19","None" },
	{ "digg","New Zealand","yes","12","Basic" },
	{ "google","UK","yes","18","Basic" },
	{ "kiwitobes","France","yes","19","Basic" }
	};
};

