#include "Manager.h"

Manager::Manager() { }
//�вι��캯��
Manager::Manager(int id, string name, int dept) {
	m_Id = id;
	m_Name = name;
	m_DeptId = dept;
}
//��ʾ������Ϣ
void Manager::showInfo() {
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񣬲��·������Ա��" << endl;
}

//��ȡ��λ����
string Manager::getDeptName() {
	return string("����");
}
