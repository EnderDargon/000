#ifndef ARMOR_IDENTIFIER__ARMOR_DETECTOR__DETECTOR_HPP_
#define ARMOR_IDENTIFIER__ARMOR_DETECTOR__DETECTOR_HPP_

//OpenCV
#include<opencv2/opencv.hpp>

//STL
#include<vector>


#include "armor_Panel.hpp"


class Detector
{
public:
	Detector(cv::Mat& ori_frame);

	void preprocess_image(cv::Mat& preprocess_frame);  //对传进来的图像进行预处理

	void find_Lightbar(cv::Mat& preprocess_frame, std::vector<Lightbar>& Lightbar_Arr);  //寻找灯条

	void draw_Armor_Panel(std::vector<Lightbar>& Lightbar_Arr, cv::Mat& ori_frame, ArmorPanel& armor);  //画出装甲板矩形框
	
	ArmorPanel armorpanel;
	cv::Mat preprocess_frame;
	std::vector<Lightbar> Lightbar_Arr;
};
#endif // !ARMOR_IDENTIFIER__ARMOR_DETECTOR__DETECTOR_HPP_
