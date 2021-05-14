/****************************************
PrefixSum.h
Author: gzy
Date: 2021/4/23
Description:
�����˷������ģ���ͷ�ļ���������ǰ׺�ͼ�����
������PrefixSum�࣬�����˷ָ�ͼ���ȡ����GetNewPic()
������˵����
void getHistogram(Mat&);//���ڻ�ȡֱ��ͼ(ÿ���Ҷ�ֵ��ռ���ظ���)

void CalculatePrefixSum(Mat&);//��ʼ��������ǰ׺������
srcΪ��ǰͼ������ص�������opencv�ĵ�����numΪ��ֵ����

double CalculateVariance(const string& tmp, int num);//����һ������Ĵ����tmp[]�е���ֵ�������Ӧ�ķ���
numΪ��ֵ������th[]Ϊ��ŵ�ǰ���Ž�����飬tmp[]Ϊ��ŵ�ǰһ����ֵ������
ͨ������CalculateVariance���ص�ǰ������ֵ��Ӧ�ķ��ȡ���ֵ�Ը���th[]����

void GetNewPic(Mat& src, Mat& dst, int num, const string& th);//�õ��ָ���ͼ��
srcΪ��ǰͼ������ص����dstΪ����󣬾�GetNewPic�������º����ڻ�ȡ�ָ���ͼ��

*****************************************/
#pragma once
#define GrayScale 256           //��ͨ��ͼ���ܻҶ�256��
#include<algorithm>
#include<iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

class PrefixSum {
	//����Ϊͼ���ǰ׺�����飬�����Ż����㸴�Ӷ�
	int pixCount[GrayScale];       //ÿ���Ҷ�ֵ��ռ���ظ���
	double pixPro[GrayScale];      //ÿ���Ҷ�ֵ��ռ�����ر���
	double SumpixPro[GrayScale];   // �����ĺ�
	double WpixPro[GrayScale];     //���� * Ȩ��
	double SumWpixPro[GrayScale];  //���� * Ȩ�� �� ��
public:
	PrefixSum(Mat& source)
	{
		memset(pixCount, 0, sizeof(int) * GrayScale);
		memset(pixPro, 0, sizeof(double) * GrayScale);
		memset(SumpixPro, 0, sizeof(double) * GrayScale);
		memset(WpixPro, 0, sizeof(double) * GrayScale);
		memset(SumWpixPro, 0, sizeof(double) * GrayScale);
		getHistogram(source);
		CalculatePrefixSum(source);
	}
	void getHistogram(Mat&);
	void CalculatePrefixSum(Mat&);
	double CalculateVariance(const string& tmp, int num);
};
void GetNewPic(Mat& src, Mat& dst, int num, const string& th);
