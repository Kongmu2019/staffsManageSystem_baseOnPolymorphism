#pragma once
#include <iostream>
#include "Worker.h"

using std::cout;
using std::endl;
using std::string;

//经理类
class Manager:public Worker
{
public:
	Manager();
	//有参构造函数
	Manager(int id, string name, int dept);
	//显示个人信息
	void showInfo();

	//获取岗位名称
	string getDeptName();
};

