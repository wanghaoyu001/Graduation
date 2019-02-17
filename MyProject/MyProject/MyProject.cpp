// MyProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Demo.h"
#include <iostream>
#include <iomanip>
using namespace std;



int main()
{
	decisionnoed d1;
	d1.split_function();
	d1.output();
	cout<<"数据列表集：" << endl; 
	const char *my_data[100][5] =
	{
		{"slashdot","USA","yes","18","None"},
		{"google","France","yes","23","Premium"},
		{"digg","USA","yes","24","Basic"},
		{"kiwitobes","France","yes","23","Basic"},
		{"google","UK","no","21","Premium"},
		{"(direct)","New Zealand","no","12","None"},
		{"(direct)","UK","no","21","Basic"},
		{"google","USA","no","24","Premium"},
		{"slashodot","France","yes","19","None"},
		{"digg","USA","no","18","None"},
		{"google","UK","no","18","None"},
		{"kiwitobes","UK","no","19","None"},
		{"digg","New Zealand","yes","12","Basic"},
		{"google","UK","yes","18","Basic"},
		{"kiwitobes","France","yes","19","Basic"}
	};
	for (int k = 0; k < 100; k++)
	{
		for (int l = 0; l < 5; l++)
		{
			cout << setw(12) << my_data[k][l];
		}
		cout << endl;
	}
	return 0;
}
/*char decisionnoed::dividest()
{
	cin >> rows >> column >> value;
}*/
void  decisionnoed::split_function()
{

	cin >> column;
	for (int i = 0; i < 10; i++)
	{
		if (my_data[i][column] == value)
			divs[i].value = 1;
		else
			divs[i].value = -1;
	}
}
void  decisionnoed::output()
{
	cout << "满足所给value值的数据集合："<<endl;
	for (int k = 0; k < 10; k++)
	{
		if (divs[k].value == 1) 
		{
			for (int l = 0; l < 5; l++)
			{
				cout << setw(12) << my_data[k][l];
			}
			cout << endl;
		}
	}
	cout << endl;
	cout << "不满足所给value值的数据集合：" << endl;
	for (int k = 0; k < 10; k++)
	{
		if (divs[k].value == -1)
		{
			for (int l = 0; l < 5; l++)
			{
				cout << setw(12) << my_data[k][l];
			}
			cout << endl;
		}
	}
	cout << endl;
}

