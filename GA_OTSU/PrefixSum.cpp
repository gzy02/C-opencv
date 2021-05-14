/****************************************
CalculateVariance.cpp
Author: gzy
Date: 2021/4/21
Description:
计算前缀和数组+计算方差
*****************************************/
#include "PrefixSum.h"

/****************************************
用于获取直方图(每个灰度值所占像素个数)
src为当前图像的像素点矩阵。
pixCount即为pixCount[]
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
初始化前缀和数组
src为当前图像的像素点矩阵（详见opencv文档），num为阈值个数
*****************************************/
void PrefixSum::CalculatePrefixSum(Mat& src) {
	int pixSum = src.cols * src.rows;  //图像总像素点
	for (int i = 0; i < GrayScale; i++) {
		pixPro[i] = pixCount[i] * 1.0 / pixSum;  //计算每个灰度级的像素数目占整幅图像的比例
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
对于一组给定的存放在tmp[]中的阈值，计算对应的方差
num为阈值个数，th[]为存放当前最优解的数组，tmp[]为存放当前一组阈值的数组
通过函数CalculateVariance返回当前该组阈值对应的方差，取最大值以更新th[]数组
由于反复动态申请、销毁实在太慢，下面我将它改为静态
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
	exit(-1);//正规军写法，但反复动态申请、销毁实在太慢，下面改为静态(放在了全局,见上）
	*/

	//sort(tmp, tmp + num, greater<char>());//先排序
	for (int i = 0; i < num; ++i)tmp[i] = tmpth[i] < 0 ? 256 + tmpth[i] : tmpth[i];
	for (int i = 1; i < num; ++i)//插入排序进行降序排序
	{
		int tep = tmp[i];
		for (int j = 0; j < i; ++j)
		{
			if (tmp[j] == tep)return -2;//有阈值重复则返回-2，非法值
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
		deltaTmp += (w[m] * pow((u[m] - uu), 2));  //类间方差公式
	}
	/*for (int j = 0; j <= num; ++j)
		for (int k = j + 1; k <= num; ++k)
				deltaTmp += w[j] * w[k] * pow((u[j] - u[k]),2);//O(n^2)写法，慢！
		delete[] u;
		delete[] utmp;
		delete[] w;
		delete[] tmp;
	*/
	return deltaTmp;
}

/****************************************
用于得到分割后的图像
src为当前图像的像素点矩阵。
dst为零矩阵，经GetNewPic函数更新后用于获取分割后的图像
*****************************************/
void GetNewPic(Mat& src, Mat& dst, int num, const string& th)
{
	int* tmp = new int[num];
	for (int i = 0; i < num; ++i)tmp[i] = th[i] < 0 ? 256 + th[i] : th[i];
	for (int i = 1; i < num; ++i)//插入排序进行降序排序
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
	LUT(src, lut, dst);  //更新二值化的图像。无需遍历整张图片，利用opencv的函数进行操作
	delete[] tmp;
}
