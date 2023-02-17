#ifndef armor_Panel
#define armor_Panel


//OpenCV
#include <opencv2/core.hpp>

class Lightbar
{
public:

	Lightbar(cv::Point2f& Lightbar_Center, float& Lightbar_Height)
	{
		this->Lightbar_Center = Lightbar_Center;
		this->Lightbar_Height = Lightbar_Height;
	}


	cv::Point2f Lightbar_Center;
	float Lightbar_Height;
};

class ArmorPanel
{
public:
	ArmorPanel()
	{

	}
	ArmorPanel(Lightbar& lightbar_1, Lightbar& lightbar_2)
	{
		Armor_Center = (lightbar_1.Lightbar_Center + lightbar_2.Lightbar_Center) / 2;     //计算中点
		//计算装甲板的长
		Armor_Width = sqrtf(powf((lightbar_1.Lightbar_Center.x - lightbar_2.Lightbar_Center.x), 2.) + powf((lightbar_1.Lightbar_Center.y - lightbar_2.Lightbar_Center.y), 2.));
		//计算装甲板的宽
		Armor_height = (lightbar_1.Lightbar_Height + lightbar_2.Lightbar_Height) / 2;
	}
	
	void is_Identify_number(ArmorPanel& armor,cv::Mat& ori_frame)
	{
		if (armor.number > -1)
		{
			cv::circle(ori_frame, armor.Armor_Center, 5, cv::Scalar(0, 255, 0));
		}

	}
	cv::Point2f Armor_Center;
	float Armor_height;
	float Armor_Width;
	int number = -1;        //最后识别到的数字
};


#endif // !armor_Panel

