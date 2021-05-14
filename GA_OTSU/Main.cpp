/****************************************
Main.cpp
Author: gzy
Date: 2021/4/25
Description:
�����������������㣬����GAͷ�ļ�
ͨ�����ֲ�ͬ�ķ�ʽ���Ŵ��㷨����ͳOTSU�������ͼ��ָ��һ����ֵ
*****************************************/
#include "GA.h"
#include <time.h>
void myOtsu_mul(Mat& src, int num) {
	PrefixSum src_sum(src);
	/*
	const char t[5] = { 45,88,128,167,210 };//�������ֵ
	string tmp(t);
	cout << "�������ֵ" << src_sum.CalculateVariance(tmp, num);
	*/
	//for (int j = 1; j <= num; ++j)
	for (int j = num; j <= num; ++j)
	{
		//���㿪��ʱ�䣬�Ա������㷨Ч��
		double start = (double)getTickCount();  //��ʼʱ��
		Mat dst;
		dst = Mat::zeros(src.size(), CV_8UC1);
		string maxth(j, 0);
		double deltaMax = 0;
		GASolve(src_sum, j, maxth, deltaMax);

		double end = (double)getTickCount();  //����ʱ��
		cout << "My GA_Otsu_mul end algorithm >> " << (end - start) / getTickFrequency()
			<< "��" << endl;  //���ʱ��
		cout << "��󷽲�" << deltaMax << endl;
		cout << "��ֵ��" << endl;
		for (int i = 0; i < j; i++) cout << (maxth[i] < 0 ? 256 + maxth[i] : maxth[i]) << endl;//�����ֵ
		GetNewPic(src, dst, j, maxth);//��ȡ�������ͼ��
		imshow("my_dst_GA" + to_string(j), dst);
		moveWindow("my_dst_GA" + to_string(j), 600, 100 + 100 * (j > 6 ? 6 : j));


		//����Ϊ��ͳ�㷨��
		/*
		string tmpth(j + 1, 0);//�������飬�����ʱֵ
		double start2 = (double)getTickCount();  //��ʼʱ��
		dst = Mat::zeros(src.size(), CV_8UC1);
		string th(j + 1, 0);
		deltaMax = 0;
		Solve(src_sum, j, tmpth, j, th, deltaMax);//��⣬���մ𰸷���th[]��

		double end2 = (double)getTickCount();  //����ʱ��
		cout << "My Otsu_mul end algorithm >> " << (end2 - start2) / getTickFrequency()
			<< "��" << endl;  //���ʱ��
		cout << "��ֵ��" << endl;
		for (int i = 0; i < j; i++) cout << (th[i] < 0 ? 256 + th[i] : th[i]) << endl;//�����ֵ
		GetNewPic(src, dst, j, th);//��ȡ�������ͼ��
		imshow("my_dst_otsu" + to_string(j), dst);
		moveWindow("my_dst_otsu" + to_string(j), 700, 350);
		*/
	}
	cout << "������Ƶ�ͼƬ���棬����������˳���" << endl;
	if (waitKey(0)) destroyAllWindows();

}

int main() {
	int num; bool cinagain;
	cout << "��������ֵ����" << endl;
	do {
		cinagain = false;
		cin >> num;
		if (cin.fail() ||
			(cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != EOF) ||
			num >= GrayScale - 1 || num <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "�����������������" << endl;
			cout << "��������ֵ����" << endl;
			cinagain = true;
		}
	} while (cinagain);
	Mat src = imread("../4.jpg", IMREAD_GRAYSCALE); //���ڴ˴��޸�·��

	myOtsu_mul(src, num);

	return 0;
}