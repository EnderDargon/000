#include "/Armor_Identifier/include/armor_Identifier.hpp"

int main()
{
	cv::VideoCapture vc(0);
	ArmorIdentifier AI(vc);
	AI.run_test(AI.vc);
	system("pause");
	return 0;
}