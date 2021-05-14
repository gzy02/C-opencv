/****************************************
GA.h
Author: gzy
Date: 2021/4/23
Description:
定义了GA类，用于遗传算法求解
声明了求解函数Solve()及GASolve()

各函数说明：
void GASolve(PrefixSum& sum, int num, string& th,double& deltaMax);//求解，最终结果放在th中
传入PrefixSum对象用于计算方差，传引用以提高速度

void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax);//求解，最终结果放在th中
depth为深度，通过函数Solve求解最优阈值，结果放在th中

size_t GetHisDataSize() { return his_data.size(); }//获取搜索节点数
void Cross(int num,int order=0);//交叉
void Variation(int num,int order=0);//变异
void Choose(PrefixSum& sum, int num, string& maxth,double& deltaMax,int order=0);//选择
*****************************************/
#pragma once
#include<cstdlib>
#include<ctime>
#include<map>
#include<string>
#include "PrefixSum.h"
extern const int breed_time;	// 繁殖代数
extern const int group_size;	// 种群数量
extern double p_cross;			// 交叉概率
extern double p_variation;      // 变异概率

class GA {
	map<string, double> his_data;//历史数据
	vector<string> group;//存放种群，每个string都是一个个体，即一组阈值
public:
	size_t GetHisDataSize() { return his_data.size(); }
	GA(int num);
	~GA() { group.clear(); his_data.clear(); }
	void Cross(int num, int order=0);//交叉
	void Variation(int num, int order=0);//变异
	void Choose(PrefixSum& sum, int num, string& maxth,double& deltaMax,int order=0);//选择
};
void GASolve(PrefixSum& sum, int num, string& th,double& deltaMax);//求解，最终结果放在th中
void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax);//传统方法求解，最终结果放在th中

//以下为具体的选择/交叉/变异方法，欢迎不同的实现以提高算法准确性
void Roulette_Choose(double fitness[], double chance[], vector<string>& next, const vector<string>& group);
void Adjacent_Cross(vector<string>& group, int num);
void RandomOneBit_Variaton(vector<string>& group, int num);
