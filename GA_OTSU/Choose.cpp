/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
�����˾����ѡ����������ѡȡ��һ�֣����д�̽��
����������ѡ���˼·�������Ƹ�cpp
*****************************************/
#include "GA.h"
void Roulette_Choose(double fitness[],double chance[], vector<string>& next,const vector<string>& group)
{
	double pick;                 //�������̶ĵ������

	//���̶Ĳ���
	for (int i = 0; i < group_size; ++i) {
		pick = ((double)rand()) / RAND_MAX;  // 0��1�������
		for (int j = 0; j < group_size; ++j) {
			pick -= chance[j];
			// ��������ѡ����pickС��0��ѡ����Ⱥ��chanceԽ��Խ�л���
			// ����ѡ��m ~ m+chance[i]����ĸ��壬������Խ��ѡ�еĻ���Խ��
			if (pick <= 0) {
				next.push_back(group[j]);
				break;
			}
			//��δѡ�У������Ѿ������һ����
			if (j == group_size - 1) {
				next.push_back(group[j]);
			}
		}
	}
}