#include <iostream>
using namespace std;
#include "speechManager.h"
#include <string>
#include <ctime>

int main()
{
	srand((unsigned int)time(NULL));

	SpeechManager sm;

	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first
	//		<< " 姓名： " << it->second.m_Name
	//		<< " 成绩： " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;

	while (true)
	{
		sm.show_Menu();

		cout << "请输入宁的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}