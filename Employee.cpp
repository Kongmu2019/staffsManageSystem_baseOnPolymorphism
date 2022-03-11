#include "Employee.h"

#include <iostream>


Employee::Employee() { }
Employee::Employee(int id, string name, int dept) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dept;
}

//显示个人信息
void Employee::showInfo() {
	cout << "职工编号：" << m_Id
		<< "\t职工姓名：" << m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}

//获取岗位名称
string Employee::getDeptName() {
	return string("普通员工");
}
