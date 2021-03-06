// MyProject.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Demo.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;



int main()
{
	decisionnoed d1;
	d1.outputmy_data();//输出原列表
	while (d1.column != EOF)
	{
		d1.dividest();//拆分的列号以及参考值的输入
		d1.split_function();//根据所给参考值进行拆分
		d1.uniquecounts();//对各种可能结果进行计数
		d1.entropy();//计算数据集合的熵
		d1.outputmy_dataAgain();//再次输出原列表
		d1.output();//输出满足条件的拆分列表
		d1.buildtree();//构建决策树
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
	cout << "数据集合的熵为：";
	cout << entTrue;
	cout << endl << endl;

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
	cout << "数据集合的熵为：";
	cout << entFalse;
	cout << endl << endl;
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
	cout << endl;
}

void  decisionnoed::outputmy_dataAgain()//再次输出原列表
{
	cout << "数据列表集：" << endl;
	for (int k = 0; k < 15; k++)
	{
		for (int l = 0; l < 5; l++)
		{
			cout << setw(12) << my_data[k][l];
		}
		cout << endl;
	}
	for (int l = 0; l < 5; l++)
	{
		cout << setw(12) << results[l].resultAll;
	}
	cout << endl;
	cout << "数据集合的熵为：";
	cout << entAll;
	cout << endl << endl;
}

void decisionnoed::uniquecounts()//对各种可能结果进行计数
{
	//char *equlFalse[100];
	//char *equlTrue[100];
	//char *equlAll[100];
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
				results[l].resultTrue = 0;
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

	for (int l = 0; l < 5; l++)//All结果计数
	{
	    for (int k = 0; k < 15; k++)
		{
			if (k == 0)
			{
				results[l].resultAll = 0;
				results[l].valueAll = 0;
			}
			equlAll[k] = my_data[k][l];
			for (int m = 0; m < k; m++)
			{
				if (my_data[k][l] != my_data[m][l])
				{
					for (int i = 0; i < k; i++)
					{
						if (equlAll[i] != my_data[k][l])
							results[l].valueAll++;
					}
				}
				if (results[l].valueAll == k && (results[l].valueAll != 0))
				{
					results[l].valueAll = 0;
					results[l].resultAll++;
					break;
				}
				results[l].valueAll = 0;
			}
		}
	}
}

void decisionnoed::entropy() //计算数据集合的熵
{
	double p = 0;
	double q = 0;
	double all = 0;
	for (int l = 0; l < 5; l++) 
	{
		if (results[l].resultTrue != 0) 
		{
			p = double(results[l].resultTrue) / 15.00;
			entTrue = entTrue - p * (log(p) / log(2));
		}
		if (results[l].resultFalse != 0) 
		{
			q = double(results[l].resultFalse) / 15.00;
			entFalse = entFalse - q * (log(q) / log(2));
		}
		if (results[l].resultAll != 0) 
		{
			all = double(results[l].resultAll) / 15.00;
			entAll = entAll - all * (log(all) / log(2));
		}
	}
}

void decisionnoed::buildtree()//构建决策树
{
	char *row_values[100];
	double best_gain = 0.0;
	double gain;
	double p;
	double len_rows = 0.0;
	for (int i = 0; i < 5; i++)
	{
		len_rows = len_rows + results[i].resultAll + 1;
	}
	for(int l=0;l<5;l++) //在当前列中生成由不同值构成的序列
	{
		for(int k=0;k<15;k++)
		{
			if (k == 0) 
			{
				results[l].resultAll = 0;
				results[l].valueAll = 0;
				row_values[k] = my_data[k][l];
			}
			for (int m = 0; m < k; m++)
			{
				if (my_data[k][l] != my_data[m][l])
				{
					for (int i = 0; i < k; i++)
					{
						if (row_values[i] != my_data[k][l])
							results[l].valueAll++;
					}
				}
				if ((results[l].valueAll == k) && (results[l].valueAll != 0))
				{
					results[l].valueAll = 0;
					results[l].resultAll++;
					row_values[results[l].resultAll] = my_data[k][l];
					break;
				}
			}results[l].valueAll = 0;
		}
		for (int i = 0; i < results[l].resultAll+1; i++) 
		{
			cout << row_values[i];
		}
		cout << endl;
		p = double(results[l].resultAll + 1) / len_rows; cout << p <<"+"<<results[l].resultAll + 1<<"+"<< len_rows <<endl;
		gain = entAll - p * entTrue - (1 - p)*entFalse; cout << gain <<"+"<<entAll<< endl;
		if (gain > best_gain&&(results[l].resultTrue + 1>0)&&(results[l].resultFalse + 1>0))
		{
			best_gain = gain; cout << best_gain << endl;
		}
		p = 0;
		gain = 0;
		cout << endl;
	}
	entTrue = 0;
	entFalse = 0;
	entAll = 0;
}

