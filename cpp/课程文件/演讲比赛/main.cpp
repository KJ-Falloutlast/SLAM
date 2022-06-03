#include <iostream>
using namespace std;
#include "speechManager.h"
#include<string>
#include <ctime>
int main()
{
	//添加随机数种子
	srand((unsigned int)time(NULL));
	//演讲比赛主管
	SpeechManager sm;

	//测试，可以在创建完管理对象后使用下面的代码测试12名选手的初始状态
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ� " << it->first << " ������ " << it->second.m_Name << " ������ " << it->second.m_Score[0] << endl;
	//}

	int choice = 0; //储存用户的选项

	while (true)
	{
		sm.show_Menu();

		cout << "请输入您的选择" << endl;
		cin >> choice;//接受用户的选择

		switch (choice)
		{
		case 1: // 开始比赛(调用开始比赛的接口)
			sm.startSpeech();
			break;
		case 2: //查看记录
			sm.showRecord();
			break;
		case 3:  //清空记录
			sm.clearRecord();
			break;
		case 0:  //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	
	return 0;
}