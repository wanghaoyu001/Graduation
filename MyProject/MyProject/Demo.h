class decisionnoed
{
public:
	struct dividest
	{
		int rows;
		int column;
		int value;
	};
	int col;
	int column;
	const char *value ="yes";
	char results;
	char tb;
	char fb;
	dividest divs[100];
	//char dividest(/*int rows, int column, char value*/);
	void split_function();
	void output();
	const char *my_data[100][5] =
	{
	{ "slashdot","USA","yes","18","None" },
	{ "google","France","yes","23","Premium" },
	{ "digg","USA","yes","24","Basic" },
	{ "kiwitobes","France","yes","23","Basic" },
	{ "google","UK","no","21","Premium" },
	{ "(direct)","New Zealand","no","12","None" },
	{ "(direct)","UK","no","21","Basic" },
	{ "google","USA","no","24","Premium" },
	{ "slashodot","France","yes","19","None" },
	{ "digg","USA","no","18","None" },
	{ "google","UK","no","18","None" },
	{ "kiwitobes","UK","no","19","None" },
	{ "digg","New Zealand","yes","12","Basic" },
	{ "google","UK","yes","18","Basic" },
	{ "kiwitobes","France","yes","19","Basic" }
	};
};

