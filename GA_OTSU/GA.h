/****************************************
GA.h
Author: gzy
Date: 2021/4/23
Description:
������GA�࣬�����Ŵ��㷨���
��������⺯��Solve()��GASolve()

������˵����
void GASolve(PrefixSum& sum, int num, string& th,double& deltaMax);//��⣬���ս������th��
����PrefixSum�������ڼ��㷽�������������ٶ�

void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax);//��⣬���ս������th��
depthΪ��ȣ�ͨ������Solve���������ֵ���������th��

size_t GetHisDataSize() { return his_data.size(); }//��ȡ�����ڵ���
void Cross(int num,int order=0);//����
void Variation(int num,int order=0);//����
void Choose(PrefixSum& sum, int num, string& maxth,double& deltaMax,int order=0);//ѡ��
*****************************************/
#pragma once
#include<cstdlib>
#include<ctime>
#include<map>
#include<string>
#include "PrefixSum.h"
extern const int breed_time;	// ��ֳ����
extern const int group_size;	// ��Ⱥ����
extern double p_cross;			// �������
extern double p_variation;      // �������

class GA {
	map<string, double> his_data;//��ʷ����
	vector<string> group;//�����Ⱥ��ÿ��string����һ�����壬��һ����ֵ
public:
	size_t GetHisDataSize() { return his_data.size(); }
	GA(int num);
	~GA() { group.clear(); his_data.clear(); }
	void Cross(int num, int order=0);//����
	void Variation(int num, int order=0);//����
	void Choose(PrefixSum& sum, int num, string& maxth,double& deltaMax,int order=0);//ѡ��
};
void GASolve(PrefixSum& sum, int num, string& th,double& deltaMax);//��⣬���ս������th��
void Solve(PrefixSum& sum, int depth, string& tmp, int num, string& th, double& deltaMax);//��ͳ������⣬���ս������th��

//����Ϊ�����ѡ��/����/���췽������ӭ��ͬ��ʵ��������㷨׼ȷ��
void Roulette_Choose(double fitness[], double chance[], vector<string>& next, const vector<string>& group);
void Adjacent_Cross(vector<string>& group, int num);
void RandomOneBit_Variaton(vector<string>& group, int num);
