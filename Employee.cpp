#include "Employee.h"

#include <iostream>


Employee::Employee() { }
Employee::Employee(int id, string name, int dept) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dept;
}

//��ʾ������Ϣ
void Employee::showInfo() {
	cout << "ְ����ţ�" << m_Id
		<< "\tְ��������" << m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

//��ȡ��λ����
string Employee::getDeptName() {
	return string("��ͨԱ��");
}
