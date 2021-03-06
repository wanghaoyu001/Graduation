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
	while (d1.column != EOF)
	{
		d1.dividest();
		d1.split_function();
		d1.uniquecounts();
		d1.output();
	}
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
	for (int l = 0; l < 5; l++)
	{
		cout << setw(12) << results[l].resultTrue;
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
	for (int l = 0; l < 5; l++)
	{
		cout << setw(12) << results[l].resultFalse;
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

void decisionnoed::uniquecounts()//对各种可能结果进行计数
{
	char *equlFalse[100];
	char *equlTrue[100];
	int num=0;
	for (int l = 0; l < 5; l++)//False结果计数
	{
		num = 0;
		for (int k = 0; k < 15; k++)
		{
			if (k == 0)
			{
				results[l].resultFalse = 1;
				results[l].valueFalse = 0;
			}
			if (divs[k].value == -1)
			{
				equlFalse[(k - num)] = my_data[k][l];
				for (int m = 0; m < k ; m++)
				{
					if ((my_data[k][l] != my_data[m][l]) && (divs[m].value == -1))
					{
						for (int i = 0; i < (k - num); i++)
						{
							if (equlFalse[i] != my_data[k][l])
								results[l].valueFalse++;
						}
					}
					if (results[l].valueFalse == (k - num)&& (results[l].valueFalse !=0))
						{
						    results[l].valueFalse = 0;
							results[l].resultFalse++;
							break;
						}
					results[l].valueFalse = 0;
				}
				num = num - 1; 
			}
			num = num + 1; 
		}
	}

	for (int l = 0; l < 5; l++)//True结果计数
	{
		num = 0;
		for (int k = 0; k < 15; k++)
		{
			if (k == 0)
			{
				results[l].resultTrue = 1;
				results[l].valueTrue = 0;
			}
			if (divs[k].value == 1)
			{
				equlTrue[(k - num)] = my_data[k][l];
				for (int m = 0; m < k; m++)
				{
					if ((my_data[k][l] != my_data[m][l]) && (divs[m].value == 1))
					{
						for (int i = 0; i < (k - num); i++)
						{
							if (equlTrue[i] != my_data[k][l])
								results[l].valueTrue++;
						}
					}
					if (results[l].valueTrue == (k - num) && (results[l].valueTrue != 0))
					{
						results[l].valueTrue = 0;
						results[l].resultTrue++;
						break;
					}
					results[l].valueTrue = 0;
				}
				num = num - 1;
			}
			num = num + 1;
		}
	}
}

