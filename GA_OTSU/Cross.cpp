/****************************************
Main.cpp
Author: gzy
Date: 2021/4/24
Description:
�����˾���Ľ��溯��������ѡȡ��һ�֣����д�̽��
���������Ľ����˼·�������Ƹ�cpp
*****************************************/
#include "GA.h"
void Adjacent_Cross(vector<string>& group,int num)
{
	// ѡ���ٽ������������н���
	// ���ԸĽ�Ϊ���ѡ��
	int point = 0;
	int choice1, choice2;
	while (point < group_size) {
		double pick = ((double)rand()) / RAND_MAX;  // 0��1�������
		if (pick > p_cross)
			continue;  //�ж��Ƿ񽻲�
		else {
			choice1 = point;
			choice2 = point + 1;
			int position = rand() % num;//���λ�㽻��
			swap(group[choice1][position], group[choice2][position]);//����
			//�����ԵĽ��淽����ǿ�ҽ���Ľ�
		}
		point += 2;
	}
}