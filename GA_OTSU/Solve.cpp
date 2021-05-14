/****************************************
Solve.cpp
Author: gzy
Date: 2021/4/23
Description:
求解，获取最优阈值
求解方法包括传统法和GA法
以后更新算法GA时，请在solve.cpp里重载GASolve()函数
*****************************************/
#include "GA.h"
extern const int breed_time;
/****************************************
传统OTSU求解，最终结果放在th[]中
*****************************************/
void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax)
//遍历所有从0到255灰度级的阈值分割条件，测试哪一个的类间方差最大
{
	int k = (depth == num) ? -1 : tmp[depth];
	if (depth == 1) {
		for (int i = k + 1; i < GrayScale; i++) {
			tmp[0] = i;
			double deltaTmp = sum.CalculateVariance(tmp, num);

			if (deltaTmp > deltaMax) {
				deltaMax = deltaTmp;
				th = tmp;
			}
		}
		return;
	}
	for (int i = k + 1; i < GrayScale; ++i) {
		tmp[depth - 1] = i;
		Solve(sum, depth - 1, tmp, num, th, deltaMax);
	}
}

/****************************************
求组合数，计算理论上应搜索的节点总数
*****************************************/
long long Combination(int num)
{
	long long t = 1;
	for (int i = 0; i < num; ++i)
	{
		t *= (GrayScale - i);
	}
	for (int i = 2; i <= num; ++i)
	{
		t /= i;
	}
	return t;
}

/****************************************
GA方法求解，最终结果放在th[]中
*****************************************/
void GASolve(PrefixSum& sum, int num, string& th, double& deltaMax)
{
	GA otsu(num);
	for (int i = 1; i <= breed_time; ++i) {
		//请在传参时选择具体的选择、交叉、变异函数，默认参数是0
		otsu.Choose(sum, num, th, deltaMax);
		otsu.Cross(num);
		//可以在此保存下亲代
		otsu.Variation(num);
		//可以写一个if语句判断突变后的子代是否可以替代亲代，这里就不判断了
		// 
		//可在此输出各代之间的信息
		//cout << deltaMax << endl;
	}
	cout << "已搜索节点数：" << otsu.GetHisDataSize() << endl;
	if (num > 10)cout << "理论上存在的总节点数：>2^64" << endl;
	else cout << "理论上存在的总节点数：" << Combination(num) << endl;
}