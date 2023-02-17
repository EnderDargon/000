
//OpenCV
#include<opencv2/opencv.hpp>

//STL
#include<vector>

#include "/Armor_Identifier/include/armor_Detector.hpp"


#define _param_Mincontour 50.
#define _param_Min_WHratio 2.
#define _param_Max_WHratio 6.
#define _param__Armor_Panel__enlargetimes 1.75

Detector::Detector(cv::Mat& ori_frame)
{
	cv::Mat preprocess_frame;
	ori_frame.copyTo(preprocess_frame);
	preprocess_image(preprocess_frame);
	this->preprocess_frame = preprocess_frame;
}

void Detector::preprocess_image(cv::Mat& preprocess_frame)
{
	std::vector<cv::Mat> channels;
	cv::split(preprocess_frame, channels);     //分离通道
	preprocess_frame = channels.at(2) - channels.at(0);   //用r-b后的图像直接代替灰度图，可使二值化后图像红色区域变为白色，寻找灯条时更容易寻找
	threshold(preprocess_frame, preprocess_frame, 90, 255, cv::THRESH_BINARY);  //二值化
	blur(preprocess_frame, preprocess_frame, cv::Size(3, 3));   
}

void Detector::find_Lightbar(cv::Mat& preprocess_frame, std::vector<Lightbar>& Lightbar_Arr)
{
	std::vector<std::vector<cv::Point>> Contours;
	std::vector<std::vector<cv::Point>> resultContours;
	cv::findContours(preprocess_frame, Contours, 1, 1);          //对前期处理好的图片寻找轮廓
	double mincontour = _param_Mincontour;
	int count = 0;
	for (int i = 0; i < Contours.size(); i++)
	{
		int Contouresize = Contours.size();
		double ContorArea = contourArea(Contours[i]);       //面积太小的不要
		if (ContorArea >= mincontour)
		{
			count = i;
		}
		resultContours.push_back(Contours[count]);
		if (resultContours.size() > 0)
		{
			cv::RotatedRect rect = minAreaRect(resultContours[i]);
			//下面用长宽比继续筛选灯条
			if ((abs(rect.size.width / rect.size.height) >= _param_Min_WHratio && abs(rect.size.width / rect.size.height) <= _param_Max_WHratio) ||
				(abs(rect.size.height / rect.size.width) >= _param_Min_WHratio && abs(rect.size.height / rect.size.width) <= _param_Max_WHratio))   
			{
				if (rect.size.height / rect.size.width < 1.)                    //调整因为坐标系不同而使两个不同灯条外接矩形长宽定义不同的问题
				{
					float temp = rect.size.height;
					rect.size.height = rect.size.width;
					rect.size.width = temp;
				}
				//-----------------------------------------筛选完毕提取灯条---------------------------------------//           
				Lightbar_Arr.push_back(Lightbar(rect.center, rect.size.height));      //找出每个灯条轮廓的中心点,灯条的高作为装甲板的宽
			}
		}
	}
}

void Detector::draw_Armor_Panel(std::vector<Lightbar>& Lightbar_Arr, cv::Mat& ori_frame, ArmorPanel& armor)
{
	if (Lightbar_Arr.size() == 2)
	{
		ArmorPanel Armor(Lightbar_Arr[0], Lightbar_Arr[1]);
		cv::Point2f panel_points[4];
		Armor.Armor_height *= _param__Armor_Panel__enlargetimes;      //对装甲板区域适当扩大
		cv::RotatedRect Panel(Armor.Armor_Center, cv::Size2f(Armor.Armor_Width, Armor.Armor_height), 0);   
		Panel.points(panel_points);
		for (int i = 0; i < 4; i++)
		{
			cv::line(ori_frame, panel_points[i], panel_points[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);    //画出装甲板区域
		}
		armor = Armor;
	}
}
