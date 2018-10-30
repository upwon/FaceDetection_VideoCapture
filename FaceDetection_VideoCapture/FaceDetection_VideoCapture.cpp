// FaceDetection_VideoCapture.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image, image_gray;       //定义两个Mat变量，用于存储每一帧的图像
	VideoCapture capture(0);      //从摄像头读入视频


	while (1)                     //循序显示每一帧
	{
		capture >> image;          //读取当前帧
		

		cvtColor(image, image_gray, CV_RGB2GRAY);   //转灰度图
		equalizeHist(image_gray,image_gray);             //直方图均衡化，增强对比度方便处理

		CascadeClassifier eye_Classifier;               //载入分类器
		CascadeClassifier face_cascade;					//载入分类器

														//加载分类训练器，OpenCV官方文档的xml文档，可以直接调用
														//我的xml的路径D:\OpenCV\opencv\build\etc\haarcascades  

		if (!eye_Classifier.load("./haarcascade_eye.xml"))    //把xml文档复制到了当前项目的路径下
		{
			cout << "导入haarcascade_eye.xml时出错 !" << endl;
			return 0;

		}

		if (!face_cascade.load("./haarcascade_frontalface_alt.xml"))    //把xml文档复制到了当前项目的路径下
		{
			cout << "导入haarcascade_frontalface_alt.xml时出错 !" << endl;
			return 0;

		}


		//vector 是个类模板 需要提供明确的模板实参  vector<Rect>则是个确定的类 模板的实例化

		vector<Rect> eyeRect;
		vector<Rect> faceRect;


		//检测眼睛的位置
		eye_Classifier.detectMultiScale(image_gray, eyeRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		for (size_t eyeIdx = 0; eyeIdx < eyeRect.size(); eyeIdx++)
		{

			rectangle(image, eyeRect[eyeIdx], Scalar(0, 0, 255));    //用矩形画出检测到的眼睛的位置

		}
		/*
		CV_WRAP virtual void detectMultiScale(
		const Mat& image,
		CV_OUT vector<Rect>& objects,
		double scaleFactor=1.1,
		int minNeighbors=3, int flags=0,
		Size minSize=Size(),
		Size maxSize=Size()
		);


		各参数含义：
		const Mat& image: 需要被检测的图像（灰度图）
		vector<Rect>& objects: 保存被检测出的人脸位置坐标序列
		double scaleFactor: 每次图片缩放的比例
		int minNeighbors: 每一个人脸至少要检测到多少次才算是真的人脸
		int flags： 决定是缩放分类器来检测，还是缩放图像
		Size(): 表示人脸的最大最小尺寸

		*/

		//检测关于脸部的位置

		face_cascade.detectMultiScale(image_gray, faceRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	//	cout << "face position is:" << endl << face_cascade << endl << endl;

		for (size_t i = 0; i < faceRect.size(); i++)
		{
			rectangle(image, faceRect[i], Scalar(0, 0, 255));           //用矩形画出检测到脸部的位置
		}

		imshow("人脸识别", image);         //显示当前帧
	//	waitKey(1);
		char c = waitKey(30);             //延时30ms,即每秒播放33帧图像
		if (c == 27)
			break;

	}


    return 0;
}

