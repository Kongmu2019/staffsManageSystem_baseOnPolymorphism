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
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ�𣺹���˾����������" << endl;
}

string Boss::getDeptName()
{
	return string("�ܲ�");
}
