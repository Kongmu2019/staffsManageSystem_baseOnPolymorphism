#pragma once
#include "Worker.h"
class Boss :public Worker
{
public:
	Boss();
	//有参构造函数
	Boss(int id, string name, int dept);
	//显示个人信息
	void showInfo();

	//获取岗位名称
	string getDeptName();
};

