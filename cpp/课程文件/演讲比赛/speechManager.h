#pragma once 
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>


//演讲管理类
class SpeechManager
{
public:

	//构造函数
	SpeechManager();

	//显示菜单栏
	void show_Menu();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化属性
	void initSpeech();

	//初始化创建12名选手
	void createSpeaker();

	//开始比赛-比赛控制流程
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛分数
	void showScore();

	//保存分数
	void saveRecord();

	//保存记录
	void loadRecord();

	//查看记录功能
	void showRecord();

	//清空记录
	void clearRecord();


	//文件为空的表示
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>>m_Record;

	//比赛选手
	//比赛选手 容器 12人
	vector<int>v1;

	//第一轮晋级容器 6人
	vector<int>v2;

	//胜利前3名容器 3人
	vector<int>vVictory;

	//存放编号以及对应的具体选手容器
	map<int, Speaker>m_Speaker;

	//��ű������� 
	int m_Index;

};