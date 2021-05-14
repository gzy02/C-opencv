/****************************************
Solve.cpp
Author: gzy
Date: 2021/4/23
Description:
��⣬��ȡ������ֵ
��ⷽ��������ͳ����GA��
�Ժ�����㷨GAʱ������solve.cpp������GASolve()����
*****************************************/
#include "GA.h"
extern const int breed_time;
/****************************************
��ͳOTSU��⣬���ս������th[]��
*****************************************/
void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax)
//�������д�0��255�Ҷȼ�����ֵ�ָ�������������һ������䷽�����
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
�������������������Ӧ�����Ľڵ�����
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
GA������⣬���ս������th[]��
*****************************************/
void GASolve(PrefixSum& sum, int num, string& th, double& deltaMax)
{
	GA otsu(num);
	for (int i = 1; i <= breed_time; ++i) {
		//���ڴ���ʱѡ������ѡ�񡢽��桢���캯����Ĭ�ϲ�����0
		otsu.Choose(sum, num, th, deltaMax);
		otsu.Cross(num);
		//�����ڴ˱������״�
		otsu.Variation(num);
		//����дһ��if����ж�ͻ�����Ӵ��Ƿ��������״�������Ͳ��ж���
		// 
		//���ڴ��������֮�����Ϣ
		//cout << deltaMax << endl;
	}
	cout << "�������ڵ�����" << otsu.GetHisDataSize() << endl;
	if (num > 10)cout << "�����ϴ��ڵ��ܽڵ�����>2^64" << endl;
	else cout << "�����ϴ��ڵ��ܽڵ�����" << Combination(num) << endl;
}