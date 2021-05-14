/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
定义了具体的选择函数，具体选取哪一种，还有待探讨
有了其他的选择的思路后，请完善该cpp
*****************************************/
#include "GA.h"
void Roulette_Choose(double fitness[],double chance[], vector<string>& next,const vector<string>& group)
{
	double pick;                 //用于轮盘赌的随机数

	//轮盘赌策略
	for (int i = 0; i < group_size; ++i) {
		pick = ((double)rand()) / RAND_MAX;  // 0到1的随机数
		for (int j = 0; j < group_size; ++j) {
			pick -= chance[j];
			// 不断往下选，当pick小于0就选该种群，chance越大越有机会
			// 即：选择m ~ m+chance[i]区间的个体，区间跨度越大被选中的机会越大
			if (pick <= 0) {
				next.push_back(group[j]);
				break;
			}
			//仍未选中，但是已经到最后一个了
			if (j == group_size - 1) {
				next.push_back(group[j]);
			}
		}
	}
}