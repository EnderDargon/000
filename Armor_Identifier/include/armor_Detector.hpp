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

	void preprocess_image(cv::Mat& preprocess_frame);  //�Դ�������ͼ�����Ԥ����

	void find_Lightbar(cv::Mat& preprocess_frame, std::vector<Lightbar>& Lightbar_Arr);  //Ѱ�ҵ���

	void draw_Armor_Panel(std::vector<Lightbar>& Lightbar_Arr, cv::Mat& ori_frame, ArmorPanel& armor);  //����װ�װ���ο�
	
	ArmorPanel armorpanel;
	cv::Mat preprocess_frame;
	std::vector<Lightbar> Lightbar_Arr;
};
#endif // !ARMOR_IDENTIFIER__ARMOR_DETECTOR__DETECTOR_HPP_
