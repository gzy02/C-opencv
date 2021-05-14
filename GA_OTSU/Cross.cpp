/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
定义了具体的交叉函数，具体选取哪一种，还有待探讨
有了其他的交叉的思路后，请完善该cpp
*****************************************/
#include "GA.h"
void Adjacent_Cross(vector<string>& group,int num)
{
	// 选择临近两个点来进行交叉
	// 可以改进为随机选择
	int point = 0;
	int choice1, choice2;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;  // 0到1的随机数
		if (pick > p_cross)
			continue;  //判断是否交叉
		else {
			choice1 = point;
			choice2 = point + 1;
			int position = rand() % num;//随机位点交叉
			swap(group[choice1][position], group[choice2][position]);//交叉
			//最无脑的交叉方法，强烈建议改进
		}
		point += 2;
	}
}