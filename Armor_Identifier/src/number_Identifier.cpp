
//OpenCV
#include<opencv2/opencv.hpp>

//STL
#include<vector>

//
#include "/Armor_Identifier/include/armor_Identifier.hpp"


#define _prama_MinScore 0.6

NumberIdentifier::NumberIdentifier(cv::Mat& ori_frame)
{
	ori_frame.copyTo(identify_frame);
	this->identify_frame = identify_frame;
	//-------------------------����ģ��--------------------------//
	std::vector<cv::Mat> Template;
	Template.push_back(cv::imread("../docs/Template/1.jpg"));
	Template.push_back(cv::imread("../docs/Template/2.jpg"));
	Template.push_back(cv::imread("../docs/Template/3.jpg"));
	Template.push_back(cv::imread("../docs/Template/4.jpg"));
	Template.push_back(cv::imread("../docs/Template/5.jpg"));
	Template.push_back(cv::imread("../docs/Template/6.jpg"));
	Template.push_back(cv::imread("../docs/Template/7.jpg"));
	Template.push_back(cv::imread("../docs/Template/8.jpg"));
	for (int i = 0; i < Template.size(); i++)
	{
		cvtColor(Template[i], Template[i], cv::COLOR_BGR2GRAY);      //ת�Ҷ�ͼ
		threshold(Template[i], Template[i], 80, 255, cv::THRESH_BINARY);          //��ֵ��
	}
	//-----------------------------------------------------------//
	this->Template = Template;
}

void NumberIdentifier::extractNumbers(ArmorPanel& armor,cv::Mat& identify_frame,cv::Mat& ProcessFrame_roi)
{
	cv::RotatedRect Panel(armor.Armor_Center, cv::Size2f(armor.Armor_Width / 2, armor.Armor_height), 0);
	cv::Point2f panel_points[4];
	std::vector<cv::Mat> matchResult;
	Panel.points(panel_points);
	if (panel_points[1].y >= 0.)             //��֤ͼƬ��Ϣ��ȷ
	{
		cv::Rect rect(panel_points[1], cv::Size2f(armor.Armor_Width / 2, armor.Armor_height));
		if (rect.area() >= 720.)                   //���Թ�С���
		{
			if (rect.y + rect.height < identify_frame.rows)     
			{
				ProcessFrame_roi = identify_frame(rect);
				cvtColor(ProcessFrame_roi, ProcessFrame_roi, cv::COLOR_BGR2GRAY);    
				threshold(ProcessFrame_roi, ProcessFrame_roi, 80, 255, cv::THRESH_BINARY);    //ʹģ����ROI��ཱུ����С
			}
		}
	}	
}
void NumberIdentifier::Identify(ArmorPanel& armor, std::vector<cv::Mat> Template, cv::Mat& ProcessFrame_roi)
{
	std::vector<double> Score_arr;
	for (int k = 0; k < Template.size(); k++)
	{
		double count = 0.;
		//��ģ�����ŵ���ROI�ߴ�һ��
		cv::resize(Template[k], Template[k], cv::Size(ProcessFrame_roi.cols, ProcessFrame_roi.rows), 0, 0, cv::INTER_CUBIC);   
		for (int i = 0; i < ProcessFrame_roi.rows; i++)    //����ÿһ�����ؽ��бȶ�
		{
			uchar* data1 = ProcessFrame_roi.ptr<uchar>(i);              //ָ��ͼ��ÿһ�е����ص�
			uchar* data2 = Template[k].ptr<uchar>(i);
			for (int j = 0; j < ProcessFrame_roi.cols; j++)
			{
				if (data1[j] == data2[j])
				{
					count++;
				}
			}
		}
		double Score = count / (ProcessFrame_roi.cols * ProcessFrame_roi.rows);     //��ͬ����/������Ϊ�÷�
		if (Score <= _prama_MinScore)     //�÷�̫С�Ĳ�Ҫ������Ϊ-1,���ȫΪ-1��ʾû��ʶ������
		{
			Score_arr.push_back(-1.);
		}
		else
		{
			Score_arr.push_back(Score);
		}
	}
	ProcessFrame_roi.release();
	float max_position = max_element(Score_arr.begin(), Score_arr.end()) - Score_arr.begin() + 1;      //���ֵ�±꼴Ϊ����
	if (*max_element(Score_arr.begin(), Score_arr.end()) > 0)
	{
		armor.number = max_position;
	}
}

