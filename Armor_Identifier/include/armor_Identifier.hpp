#ifndef ARMOR_IDENTIFIER_HPP
#define ARMOR_IDENTIFIER_HPP

//Opencv
#include<opencv2\videoio.hpp>
#include<opencv2/core/mat.hpp>

//STL


#include "armor_Detector.hpp"
#include "number_Identifier.hpp"

class ArmorIdentifier
{
public:
	ArmorIdentifier(cv::VideoCapture& vc);

	void run_test(cv::VideoCapture& vc);    //¿ªÆô²âÊÔ

	cv::VideoCapture vc;
};
#endif // !ARMOR_IDENTIFIER_HPP
