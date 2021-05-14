/****************************************
CalculateVariance.cpp
Author: gzy
Date: 2021/4/21
Description:
����ǰ׺������+���㷽��
*****************************************/
#include "PrefixSum.h"

/****************************************
���ڻ�ȡֱ��ͼ(ÿ���Ҷ�ֵ��ռ���ظ���)
srcΪ��ǰͼ������ص����
pixCount��ΪpixCount[]
=*****************************************/
void PrefixSum::getHistogram(Mat& src) {
	Mat hist;
	int channels[1] = { 0 };
	int histSize[1] = { 256 };
	float hranges[2] = { 0, 256.0 };
	const float* ranges[1] = { hranges };
	calcHist(&src, 1, channels, Mat(), hist, 1, histSize, ranges);
	for (int i = 0; i < GrayScale; i++) {
		float binVal = hist.at<float>(i);
		pixCount[i] = int(binVal);
	}
}

/****************************************
��ʼ��ǰ׺������
srcΪ��ǰͼ������ص�������opencv�ĵ�����numΪ��ֵ����
*****************************************/
void PrefixSum::CalculatePrefixSum(Mat& src) {
	int pixSum = src.cols * src.rows;  //ͼ�������ص�
	for (int i = 0; i < GrayScale; i++) {
		pixPro[i] = pixCount[i] * 1.0 / pixSum;  //����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���
		WpixPro[i] = i * pixPro[i];
		if (i == 0) {
			SumWpixPro[i] += WpixPro[i];
			SumpixPro[i] += pixPro[i];
		}
		else {
			SumWpixPro[i] = WpixPro[i] + SumWpixPro[i - 1];
			SumpixPro[i] = pixPro[i] + SumpixPro[i - 1];
		}
	}
}

/****************************************
����һ������Ĵ����tmp[]�е���ֵ�������Ӧ�ķ���
numΪ��ֵ������th[]Ϊ��ŵ�ǰ���Ž�����飬tmp[]Ϊ��ŵ�ǰһ����ֵ������
ͨ������CalculateVariance���ص�ǰ������ֵ��Ӧ�ķ��ȡ���ֵ�Ը���th[]����
���ڷ�����̬���롢����ʵ��̫���������ҽ�����Ϊ��̬
*****************************************/
double PrefixSum::CalculateVariance(const string& tmpth, int num)
{
	double w[GrayScale] = { 0 };
	double u[GrayScale] = { 0 };
	double utmp[GrayScale] = { 0 };
	int tmp[GrayScale] = { 0 };
	/*
	double* w = new(nothrow) double[num + 1];
	double* utmp = new(nothrow) double[num + 1];
	double* u = new(nothrow) double[num + 1];
	int* tmp = new(nothrow) int[num + 1];
	if (!w || !utmp || !u)
	exit(-1);//�����д������������̬���롢����ʵ��̫���������Ϊ��̬(������ȫ��,���ϣ�
	*/

	//sort(tmp, tmp + num, greater<char>());//������
	for (int i = 0; i < num; ++i)tmp[i] = tmpth[i] < 0 ? 256 + tmpth[i] : tmpth[i];
	for (int i = 1; i < num; ++i)//����������н�������
	{
		int tep = tmp[i];
		for (int j = 0; j < i; ++j)
		{
			if (tmp[j] == tep)return -2;//����ֵ�ظ��򷵻�-2���Ƿ�ֵ
			if (tmp[j] < tep)
			{
				for (int k = i; k > j; --k)
				{
					tmp[k] = tmp[k - 1];
				}
				tmp[j] = tep;
				break;
			}
		}
	}


	w[0] = SumpixPro[tmp[num - 1]];
	for (int m = 1; m < num; m++) {
		w[m] = SumpixPro[tmp[num - m - 1]] - SumpixPro[tmp[num - m]];
		if (w[m] == 0) return -1;
	}
	w[num] = 1 - SumpixPro[tmp[0]];
	if (w[num] == 0) return -1;

	utmp[0] = SumWpixPro[tmp[num - 1]];
	for (int m = 1; m < num; m++) {
		utmp[m] = SumWpixPro[tmp[num - m - 1]] - SumWpixPro[tmp[num - m]];
	}
	utmp[num] = SumWpixPro[GrayScale - 1] - SumWpixPro[tmp[0]];

	for (int m = 0; m < num + 1; m++) u[m] = utmp[m] / w[m];
	double deltaTmp = 0;
	double uu = 0;
	for (int m = 0; m < num + 1; m++) uu += w[m] * u[m];
	for (int m = 0; m < num + 1; m++) {
		deltaTmp += (w[m] * pow((u[m] - uu), 2));  //��䷽�ʽ
	}
	/*for (int j = 0; j <= num; ++j)
		for (int k = j + 1; k <= num; ++k)
				deltaTmp += w[j] * w[k] * pow((u[j] - u[k]),2);//O(n^2)д��������
		delete[] u;
		delete[] utmp;
		delete[] w;
		delete[] tmp;
	*/
	return deltaTmp;
}

/****************************************
���ڵõ��ָ���ͼ��
srcΪ��ǰͼ������ص����
dstΪ����󣬾�GetNewPic�������º����ڻ�ȡ�ָ���ͼ��
*****************************************/
void GetNewPic(Mat& src, Mat& dst, int num, const string& th)
{
	int* tmp = new int[num];
	for (int i = 0; i < num; ++i)tmp[i] = th[i] < 0 ? 256 + th[i] : th[i];
	for (int i = 1; i < num; ++i)//����������н�������
	{
		int tep = tmp[i];
		for (int j = 0; j < i; ++j)
		{
			if (tmp[j] < tep)
			{
				for (int k = i; k > j; --k)
				{
					tmp[k] = tmp[k - 1];
				}
				tmp[j] = tep;
				break;
			}
		}
	}

	uchar lutData[GrayScale];
	int j = num - 1;
	int bc = (GrayScale - 1) / num;
	int nowth = 0;
	for (int i = 0; i < GrayScale; i++) {
		if (i <= tmp[j])
			lutData[i] = nowth;
		else {
			nowth += bc;
			lutData[i] = nowth;
			--j;
			if (j < 0) {
				for (int j = i; j < GrayScale; j++) lutData[j] = 255;
				break;
			}
		}
	}
	Mat lut(1, 256, CV_8UC1, lutData);
	LUT(src, lut, dst);  //���¶�ֵ����ͼ�������������ͼƬ������opencv�ĺ������в���
	delete[] tmp;
}
