// MyProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Demo.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;



int main()
{
	decisionnoed d1;
	d1.outputmy_data();
	d1.dividest();
	d1.split_function();
	d1.output();
	return 0;
}


void decisionnoed::dividest()//拆分的列号以及参考值的输入
{
	cout << "请输入需要进行拆分的列号，和拆分所需的参考值："<<endl;
	cin >> column;
	cin >> value;
}


void  decisionnoed::split_function()//根据所给参考值进行拆分
{
	for (int i = 0; i < 15; i++)
	{
		if (strcmp(my_data[i][column - 1], a) == 0)
			divs[i].value = 1;
		else
			divs[i].value = -1;
	}
}


void  decisionnoed::output()//输出满足条件的拆分列表
{
	cout << "满足所给参考值的数据集合："<<endl;
	for (int k = 0; k < 15; k++)
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
	cout << "不满足所给参考值的数据集合：" << endl;
	for (int k = 0; k < 15; k++)
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

void  decisionnoed::outputmy_data()//输出原列表
{
	cout << "数据列表集：" << endl;
	for (int k = 0; k < 15; k++)
	{
		for (int l = 0; l < 5; l++)
		{
			cout << setw(12) << my_data[k][l];
		}
		cout << endl;
	}cout << endl;
}

