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
		int valueTrue;
		int valueFalse;
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
	
	void dividest();//��ֵ��к��Լ��ο�ֵ������
	void split_function();//���������ο�ֵ���в��
	void output();//������������Ĳ���б�
	void outputmy_data();//���ԭ�б�
	void uniquecounts();//�Ը��ֿ��ܽ�����м���

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

