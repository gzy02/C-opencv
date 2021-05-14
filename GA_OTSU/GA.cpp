/****************************************
Main.cpp
Author: gzy
Date: 2021/4/25
Description:
�������ĸ���������ӭ���μ����¾����ѡ�񡢽��桢���캯����ʹ�㷨��������
�����ˡ�����ġ�ѡ�񡢽��桢���캯��������ѡȡ��һ�֣����д�̽��
����������ѡ�񡢽��桢�����˼·��������������������������������Ӧ��cpp���棩
Ȼ���ڶ�Ӧ�ġ�����ġ�ѡ�񡢽��桢���캯�������޸ļ���
�ǵ�ͬʱҪ��GA.h��������һ�µ���д�ľ����ѡ�񡢽��桢���캯��
*****************************************/
#include"GA.h"
//���������
const int breed_time = 50;
const int group_size = 70;
double p_cross = 0.5;      // ������ʣ�������Ϊconst,��������������ı�
double p_variation = 0.1;  // �������
GA::GA(int num) {
	srand((unsigned int)time(0));
	for (int i = 0; i < group_size; ++i)
	{
		string th(num, 0);
		for (int j = 0; j < num; ++j)
			th[j] = rand() % GrayScale;
		group.push_back(th);
		//�˴�ǿ�ҽ���������أ���Ϊ���ܻ��зǷ����壨����������ͬ��ֵ��
		//�����ڼ��㷽��ʱ�Ƿ�����ķ���ֵ��-2�����ᵼ�¼������
		//������ֵ�������࣬��ֳ��������Ⱥ��������ʱ��
		//�п��ܵ��²������ĸ���ȫ��Ϊ�Ƿ����壨ȫ��������������ͬ��ֵ�������¼������
	}
}

// ѡ���������Ⱥ
void GA::Choose(PrefixSum& sum, int num, string& maxth, double& deltaMax, int order) {
	double sum_fitness = 0;
	double fitness[group_size];  //��Ӧ�����飬����Ӧ����������
	double chance[group_size];   //��������
	vector<string> next;//�������Ⱥ
	double Nowmaxfitness = 0;
	string Nowmaxth;
	for (int i = 0; i < group_size; i++) {

		fitness[i] = sum.CalculateVariance(group[i], num);//��������㷽�����
		//�Ľ���fitnessֵΪ������Ӧʹ���ǲ���ѡ��
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
	//���ڴ��������֮�����Ϣ

	cout << Nowmaxfitness << endl;//���ÿһ�������ֵ

	for (int i = 0; i < group_size; i++) {
		chance[i] = fitness[i] / sum_fitness;
	}
	if (order == 0)//Ĭ��ʹ�õ������̶ķ�
		Roulette_Choose(fitness, chance, next, group);
	//else if (order == 1)//��ʵ����������
		//Other_Choose(fitness, chance, next, group);
	//else if ����

	group = next;//����Ⱥ����
}

//����
void GA::Cross(int num, int order) {
	if (order == 0)//Ĭ��ʹ�õ������ڽ���
		Adjacent_Cross(group, num);
	//else if (order == 1)//��ʵ����������
		//Other_Cross(group,num);
	//else if ����
}

// ����
void GA::Variation(int num, int order) {
	if (order == 0)//Ĭ��ʹ�õ��Ǹ���һλ����
		RandomOneBit_Variaton(group, num);
	//else if (order == 1)//��ʵ����������
		//Other_Variaton(group,num);
	//else if ����
}