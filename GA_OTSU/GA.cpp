/****************************************
Main.cpp
Author: gzy
Date: 2021/4/25
Description:
定义了四个参数，欢迎调参及更新具体的选择、交叉、变异函数以使算法更加优秀
定义了“广义的”选择、交叉、变异函数，具体选取哪一种，还有待探讨
有了其他的选择、交叉、变异的思路后，请完善这三个函数（在另外三个对应的cpp里面）
然后在对应的“广义的”选择、交叉、变异函数里面修改即可
记得同时要在GA.h里面声明一下的你写的具体的选择、交叉、变异函数
*****************************************/
#include"GA.h"
//在这里调参
const int breed_time = 50;
const int group_size = 70;
double p_cross = 0.5;      // 交叉概率，不设置为const,可以随进化代数改变
double p_variation = 0.1;  // 变异概率
GA::GA(int num) {
	srand((unsigned int)time(0));
	for (int i = 0; i < group_size; ++i)
	{
		string th(num, 0);
		for (int j = 0; j < num; ++j)
			th[j] = rand() % GrayScale;
		group.push_back(th);
		//此处强烈建议进行判重，因为可能会有非法个体（出现两个相同阈值）
		//不过在计算方差时非法个体的返回值是-2，不会导致计算错误
		//但当阈值个数过多，繁殖代数及种群数量过少时，
		//有可能导致产生出的个体全部为非法个体（全部都带有两个相同阈值），导致计算错误
	}
}

// 选择优秀的种群
void GA::Choose(PrefixSum& sum, int num, string& maxth, double& deltaMax, int order) {
	double sum_fitness = 0;
	double fitness[group_size];  //适应性数组，用适应函数来计算
	double chance[group_size];   //概率数组
	vector<string> next;//存放新种群
	double Nowmaxfitness = 0;
	string Nowmaxth;
	for (int i = 0; i < group_size; i++) {

		fitness[i] = sum.CalculateVariance(group[i], num);//若无则计算方差并插入
		//改进：fitness值为负数则不应使他们参与选择
		his_data[group[i]] = fitness[i];
		if (fitness[i] > Nowmaxfitness) {
			Nowmaxfitness = fitness[i];
			Nowmaxth = group[i];
		}

		sum_fitness += fitness[i];
	}
	if (Nowmaxfitness > deltaMax) {
		deltaMax = Nowmaxfitness;
		maxth = Nowmaxth;
	}
	//可在此输出各代之间的信息

	cout << Nowmaxfitness << endl;//输出每一代的最大值

	for (int i = 0; i < group_size; i++) {
		chance[i] = fitness[i] / sum_fitness;
	}
	if (order == 0)//默认使用的是轮盘赌法
		Roulette_Choose(fitness, chance, next, group);
	//else if (order == 1)//请实现其他方法
		//Other_Choose(fitness, chance, next, group);
	//else if ……

	group = next;//新种群诞生
}

//交叉
void GA::Cross(int num, int order) {
	if (order == 0)//默认使用的是相邻交叉
		Adjacent_Cross(group, num);
	//else if (order == 1)//请实现其他方法
		//Other_Cross(group,num);
	//else if ……
}

// 变异
void GA::Variation(int num, int order) {
	if (order == 0)//默认使用的是概率一位变异
		RandomOneBit_Variaton(group, num);
	//else if (order == 1)//请实现其他方法
		//Other_Variaton(group,num);
	//else if ……
}