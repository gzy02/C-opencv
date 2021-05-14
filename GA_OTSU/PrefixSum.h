/****************************************
PrefixSum.h
Author: gzy
Date: 2021/4/23
Description:
定义了方差计算模块的头文件，用于求前缀和及方差
定义了PrefixSum类，声明了分割图像获取函数GetNewPic()
各函数说明：
void getHistogram(Mat&);//用于获取直方图(每个灰度值所占像素个数)

void CalculatePrefixSum(Mat&);//初始化，计算前缀和数组
src为当前图像的像素点矩阵（详见opencv文档），num为阈值个数

double CalculateVariance(const string& tmp, int num);//对于一组给定的存放在tmp[]中的阈值，计算对应的方差
num为阈值个数，th[]为存放当前最优解的数组，tmp[]为存放当前一组阈值的数组
通过函数CalculateVariance返回当前该组阈值对应的方差，取最大值以更新th[]数组

void GetNewPic(Mat& src, Mat& dst, int num, const string& th);//得到分割后的图像
src为当前图像的像素点矩阵。dst为零矩阵，经GetNewPic函数更新后用于获取分割后的图像

*****************************************/
#pragma once
#define GrayScale 256           //单通道图像总灰度256级
#include<algorithm>
#include<iostream>
using namespace std;

#include <opencv2\opencv.hpp>
using namespace cv;

class PrefixSum {
	//以下为图像的前缀和数组，用于优化计算复杂度
	int pixCount[GrayScale];       //每个灰度值所占像素个数
	double pixPro[GrayScale];      //每个灰度值所占总像素比例
	double SumpixPro[GrayScale];   // 比例的和
	double WpixPro[GrayScale];     //比例 * 权重
	double SumWpixPro[GrayScale];  //比例 * 权重 的 和
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
