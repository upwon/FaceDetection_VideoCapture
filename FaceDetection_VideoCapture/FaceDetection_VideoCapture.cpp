// FaceDetection_VideoCapture.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image, image_gray;       //��������Mat���������ڴ洢ÿһ֡��ͼ��
	VideoCapture capture(0);      //������ͷ������Ƶ


	while (1)                     //ѭ����ʾÿһ֡
	{
		capture >> image;          //��ȡ��ǰ֡
		

		cvtColor(image, image_gray, CV_RGB2GRAY);   //ת�Ҷ�ͼ
		equalizeHist(image_gray,image_gray);             //ֱ��ͼ���⻯����ǿ�Աȶȷ��㴦��

		CascadeClassifier eye_Classifier;               //���������
		CascadeClassifier face_cascade;					//���������

														//���ط���ѵ������OpenCV�ٷ��ĵ���xml�ĵ�������ֱ�ӵ���
														//�ҵ�xml��·��D:\OpenCV\opencv\build\etc\haarcascades  

		if (!eye_Classifier.load("./haarcascade_eye.xml"))    //��xml�ĵ����Ƶ��˵�ǰ��Ŀ��·����
		{
			cout << "����haarcascade_eye.xmlʱ���� !" << endl;
			return 0;

		}

		if (!face_cascade.load("./haarcascade_frontalface_alt.xml"))    //��xml�ĵ����Ƶ��˵�ǰ��Ŀ��·����
		{
			cout << "����haarcascade_frontalface_alt.xmlʱ���� !" << endl;
			return 0;

		}


		//vector �Ǹ���ģ�� ��Ҫ�ṩ��ȷ��ģ��ʵ��  vector<Rect>���Ǹ�ȷ������ ģ���ʵ����

		vector<Rect> eyeRect;
		vector<Rect> faceRect;


		//����۾���λ��
		eye_Classifier.detectMultiScale(image_gray, eyeRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		for (size_t eyeIdx = 0; eyeIdx < eyeRect.size(); eyeIdx++)
		{

			rectangle(image, eyeRect[eyeIdx], Scalar(0, 0, 255));    //�þ��λ�����⵽���۾���λ��

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


		���������壺
		const Mat& image: ��Ҫ������ͼ�񣨻Ҷ�ͼ��
		vector<Rect>& objects: ���汻����������λ����������
		double scaleFactor: ÿ��ͼƬ���ŵı���
		int minNeighbors: ÿһ����������Ҫ��⵽���ٴβ������������
		int flags�� ���������ŷ���������⣬��������ͼ��
		Size(): ��ʾ�����������С�ߴ�

		*/

		//������������λ��

		face_cascade.detectMultiScale(image_gray, faceRect, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	//	cout << "face position is:" << endl << face_cascade << endl << endl;

		for (size_t i = 0; i < faceRect.size(); i++)
		{
			rectangle(image, faceRect[i], Scalar(0, 0, 255));           //�þ��λ�����⵽������λ��
		}

		imshow("����ʶ��", image);         //��ʾ��ǰ֡
	//	waitKey(1);
		char c = waitKey(30);             //��ʱ30ms,��ÿ�벥��33֡ͼ��
		if (c == 27)
			break;

	}


    return 0;
}

