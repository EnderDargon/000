#ifndef  ARMOR_DETECTOR__NUMBER_IDENTIFIER_HPP_
#define  ARMOR_DETECTOR__NUMBER_IDENTIFIER_HPP_

//OpenCV
#include<opencv2/opencv.hpp>

//STL
#include<vector>

//
#include "armor_Panel.hpp"

class NumberIdentifier
{
public:
	NumberIdentifier(cv::Mat& ori_frame);

	void extractNumbers(ArmorPanel& armor, cv::Mat& identify_frame, cv::Mat& ProcessFrame_roi);

	void Identify(ArmorPanel& armor, std::vector<cv::Mat> Template, cv::Mat& ProcessFrame_roi);

	cv::Mat identify_frame;
	cv::Mat ProcessFrame_roi;
	std::vector<cv::Mat> Template;
};

#endif // ! ARMOR_DETECTOR__NUMBER_IDENTIFIER_HPP_
