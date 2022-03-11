#include <iostream>
#include "Boss.h"

using namespace std;


Boss::Boss(){ }

Boss::Boss(int id, string name, int dept)
{
	m_Id = id;
	m_Name = name;
	m_DeptId = dept;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：管理公司的所有事务" << endl;
}

string Boss::getDeptName()
{
	return string("总裁");
}
