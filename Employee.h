#pragma once
#include "Worker.h"

class Employee:public Worker
{
public:
	Employee();
	Employee(int id, string name, int dept);
	//显示个人信息
	void showInfo();
	//获取岗位名称
	string getDeptName();
};

