/****************************************
Main.cpp
Author: gzy
Date: 2021/4/25
Description:
定义了整个程序的入点，引入GA头文件
通过两种不同的方式（遗传算法、传统OTSU法）求得图像分割的一组阈值
*****************************************/
#include "GA.h"
#include <time.h>
void myOtsu_mul(Mat& src, int num) {
	PrefixSum src_sum(src);
	/*
	const char t[5] = { 45,88,128,167,210 };//理论最大值
	string tmp(t);
	cout << "理论最大值" << src_sum.CalculateVariance(tmp, num);
	*/
	//for (int j = 1; j <= num; ++j)
	for (int j = num; j <= num; ++j)
	{
		//计算开销时间，对比两个算法效率
		double start = (double)getTickCount();  //开始时间
		Mat dst;
		dst = Mat::zeros(src.size(), CV_8UC1);
		string maxth(j, 0);
		double deltaMax = 0;
		GASolve(src_sum, j, maxth, deltaMax);

		double end = (double)getTickCount();  //结束时间
		cout << "My GA_Otsu_mul end algorithm >> " << (end - start) / getTickFrequency()
			<< "秒" << endl;  //输出时间
		cout << "最大方差" << deltaMax << endl;
		cout << "阈值：" << endl;
		for (int i = 0; i < j; i++) cout << (maxth[i] < 0 ? 256 + maxth[i] : maxth[i]) << endl;//输出阈值
		GetNewPic(src, dst, j, maxth);//获取处理过的图像
		imshow("my_dst_GA" + to_string(j), dst);
		moveWindow("my_dst_GA" + to_string(j), 600, 100 + 100 * (j > 6 ? 6 : j));


		//以下为传统算法：
		/*
		string tmpth(j + 1, 0);//辅助数组，存放临时值
		double start2 = (double)getTickCount();  //开始时间
		dst = Mat::zeros(src.size(), CV_8UC1);
		string th(j + 1, 0);
		deltaMax = 0;
		Solve(src_sum, j, tmpth, j, th, deltaMax);//求解，最终答案放在th[]中

		double end2 = (double)getTickCount();  //结束时间
		cout << "My Otsu_mul end algorithm >> " << (end2 - start2) / getTickFrequency()
			<< "秒" << endl;  //输出时间
		cout << "阈值：" << endl;
		for (int i = 0; i < j; i++) cout << (th[i] < 0 ? 256 + th[i] : th[i]) << endl;//输出阈值
		GetNewPic(src, dst, j, th);//获取处理过的图像
		imshow("my_dst_otsu" + to_string(j), dst);
		moveWindow("my_dst_otsu" + to_string(j), 700, 350);
		*/
	}
	cout << "将光标移到图片界面，按任意键可退出。" << endl;
	if (waitKey(0)) destroyAllWindows();

}

int main() {
	int num; bool cinagain;
	cout << "请输入阈值个数" << endl;
	do {
		cinagain = false;
		cin >> num;
		if (cin.fail() ||
			(cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != EOF) ||
			num >= GrayScale - 1 || num <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "输入错误，请重新输入" << endl;
			cout << "请输入阈值个数" << endl;
			cinagain = true;
		}
	} while (cinagain);
	Mat src = imread("../4.jpg", IMREAD_GRAYSCALE); //请在此处修改路径

	myOtsu_mul(src, num);

	return 0;
}