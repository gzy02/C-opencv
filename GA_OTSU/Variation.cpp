/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
�����˾���ı��캯��������ѡȡ��һ�֣����д�̽��
���������ı����˼·�������Ƹ�cpp
*****************************************/
#include "GA.h"
void RandomOneBit_Variaton(vector<string>& group, int num)
{
	int point = 0;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;  // 0��1�������
		// ���ʱ���
		// ���ԸĽ�Ϊ���ѡ��
		if (pick < p_variation) {
			int position = rand() % num, k = rand() % 7;//���λ�����
			group[point][position] = (group[point][position] ^ (1 << k));
			//��positionλ���0~7λ����1��λ���
			//��Ϊ������1λ��1����Ϊ0��Ϊ0����Ϊ1��ģ�����ͻ��
			//�����Եı��췽����ǿ�ҽ���Ľ�
		}
		point++;
	}
}