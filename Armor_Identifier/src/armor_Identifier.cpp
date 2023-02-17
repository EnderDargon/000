
//OpenCV


//STL
#include<iostream>
#include<string>
#include<iomanip>


#include "/Armor_Identifier/include/armor_Identifier.hpp"

ArmorIdentifier::ArmorIdentifier(cv::VideoCapture& vc)
{
	vc.set(cv::CAP_PROP_EXPOSURE, -8);  //降低曝光度使后续识别更便利
	this->vc = vc;
}

void ArmorIdentifier::run_test(cv::VideoCapture& vc)
{
	cv::Mat ori_frame;  //初始帧
	cv::String str;
	std::stringstream ss;
	double tick = 0, fps = 0;
	while (1)
	{
		tick = (double)cv::getTickCount();
		if (cv::waitKey(1) == 27)
		{
			break;
		}
		if (vc.isOpened())
		{
			//--------------------------------------------------------------------------------//
			int number = -1;
			vc.read(ori_frame);
			Detector armor_detector(ori_frame);
			armor_detector.find_Lightbar(armor_detector.preprocess_frame, armor_detector.Lightbar_Arr);
			armor_detector.draw_Armor_Panel(armor_detector.Lightbar_Arr, ori_frame, armor_detector.armorpanel);
			NumberIdentifier numberidfier(ori_frame);
			numberidfier.extractNumbers(armor_detector.armorpanel, numberidfier.identify_frame, numberidfier.ProcessFrame_roi);
			if (numberidfier.ProcessFrame_roi.cols > 0. && numberidfier.ProcessFrame_roi.rows > 0.)
			{
				numberidfier.Identify(armor_detector.armorpanel, numberidfier.Template, numberidfier.ProcessFrame_roi);
				armor_detector.armorpanel.is_Identify_number(armor_detector.armorpanel, ori_frame);
				number = armor_detector.armorpanel.number;
			}
			//-------------------------------------------------------------------------------//
			tick = (((double)cv::getTickCount() - tick) / (double)cv::getTickFrequency());
			fps = 1.0 / tick;
			ss << std::fixed << std::setprecision(2) << fps;    //计算FPS
			ss >> str;
			ss.clear();
			cv::String fpstring("FPS: ");
			fpstring += str;
			ss << number;   //计算识别结果string
			ss >> str;
			ss.clear();
			cv::String identstring("result: ");
			identstring += str;
			cv::putText(                                             //显示FPS
				ori_frame,      
				fpstring,   
				cv::Point(5, 20),
				cv::FONT_HERSHEY_COMPLEX,
				0.5,
				cv::Scalar(0, 255, 0)
			);
			cv::putText(
				ori_frame,
				identstring,
				cv::Point(7, 50),
				cv::FONT_HERSHEY_COMPLEX,
				0.5,
				cv::Scalar(0, 255, 0)
			);
			cv::imshow("0", ori_frame);
		}
	}
}