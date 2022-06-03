#include "speechManager.h"
//构造函数实现
SpeechManager::SpeechManager()
{
	//调用初始化比赛
	this->initSpeech();
	//调用初始化speaker
	this->createSpeaker();

	this->loadRecord();
}

//实现菜单栏显示
void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//初始化属性
void SpeechManager::initSpeech()
{
	//容器保证为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//初始化记录容器
	/*
	问题：在初始化时，没有初始化记录容器
	解决：在initSpeech中添加初始化记录容器
	*/
	this->m_Record.clear();
}

//初始化12名选手
void SpeechManager::createSpeaker()
{
	//12名选手
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "player";
		name += nameSeed[i];

		//演讲者
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//12名选手编号
		this->v1.push_back(i + 10001);

		//选手编号以及对应选手存放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮比赛

	//1.抽签
	this->speechDraw();

	//2.比赛(调用比赛函数)
	this->speechContest();

	//3.显示晋级结果(在实现完showScore()后在startSpeech中调用)
	this->showScore();

	//第二轮比赛
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	speechContest();
	//3.显示最终结果
	this->showScore();
	//4.保存分数
	this->saveRecord();

	/*
	重置比赛:
	以下3个函数
	功能:为了解决比赛完毕后，查不到本届比赛的记录，没有实时更新
	解决方式：比赛完毕后，所有数据重置
	*/
	//初始化属性
	this->initSpeech();

	//创建选手
	this->createSpeaker();

	//获取往届记录
	this->loadRecord();



	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "--------------------------" << endl;
	cout << "抽签后演讲顺序如下" << endl;

	if (this->m_Index == 1)
	{
		//第一轮比赛选手的随机排列
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛选手的随机排列
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "--------------------------" << endl;
	system("pause"); 
	cout << endl;
}

//开始比赛
void SpeechManager::speechContest()
{
	cout << "----------- 第" << this->m_Index << " 轮正式比赛开始" << endl;

	//临时容器，保存key分数，value选手编号，并从大到小排列
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //记录人员数，6个为1组

	vector<int>v_Src;//比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有的参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front(); //去掉最高分
		d.pop_back(); //去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f); //获取总分
		double avg = sum / (double)d.size();  //获取平均分

		//每个人平均分
		//cout << "编号 " << *it << " 选手 " << this->m_Speaker[*it].m_Name << " 获取平均分为" << avg << endl;

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6个人为一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));

		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号" << it->second << "姓名" << this->m_Speaker[it->second].m_Name << " 成绩"
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			} 

			//取前3名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear(); //清空成绩组容器
			cout << endl;

		}
	}

	cout << "------------------ 第" << this->m_Index << "轮比赛完毕--------------" << endl;
	system("pause");

}

//显示比赛分数
void SpeechManager::showScore()
{
	cout << "------------------ 第" << this->m_Index << "轮晋级选手信息如下-------------------" <<  endl;

	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号" << *it << " 姓名 " << this->m_Speaker[*it].m_Name << " 得分" <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存分数
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //用输出的方式打开文件--写文件
	
	//将每个人数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();
	cout << "记录已经保存" << endl;

	//有记录了，文件不为空
	/*
	主要是为了解决若记录为空或者不存在，比赛完后依然提示记录为空
	解决方式：saveRecord中更新文件为空的标志
	*/ 
	this->fileIsEmpty = false;
}

//保存记录的成员函数
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in); //输入流对象，读取文件
	
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//往输入流中读取文件
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch); //读取的单个字符放回去

	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55,

		vector<string>v;

		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);//从0开始查找
			if (pos == -1)
			{
				//找不到break返回
				break;
			}
			//找到了进行分割:参数1 起始位置 参数2 截取长度
			string temp = data.substr(start, pos - start);

			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{
	//	cout << it->first << "�ھ���ţ� " << it->second[0] << " ������ " << it->second[1] << endl;
	//}
}

//显示往届得分
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "得分文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届 "
				<< "冠军编号" << this->m_Record[i][0] << " 得分" << this->m_Record[i][1] << " "
				<< "亚军编号" << this->m_Record[i][2] << " 得分 " << this->m_Record[i][3] << " "
				<< "季军编号" << this->m_Record[i][4] << " 得分 " << this->m_Record[i][5] << endl;
		}
	}


	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		//打开模式:ios::trunc:如果文件已经存在，则删除文件
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager()
{

}