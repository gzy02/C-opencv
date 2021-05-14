/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
定义了具体的变异函数，具体选取哪一种，还有待探讨
有了其他的变异的思路后，请完善该cpp
*****************************************/
#include "GA.h"
void RandomOneBit_Variaton(vector<string>& group, int num)
{
	int point = 0;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;  // 0到1的随机数
		// 概率变异
		// 可以改进为随机选择
		if (pick < p_variation) {
			int position = rand() % num, k = rand() % 7;//随机位点变异
			group[point][position] = (group[point][position] ^ (1 << k));
			//第position位点的0~7位，与1按位异或
			//若为它的那1位是1则置为0，为0则置为1，模拟基因突变
			//最无脑的变异方法，强烈建议改进
		}
		point++;
	}
}