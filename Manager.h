#pragma once
#include <iostream>
#include "Worker.h"

using std::cout;
using std::endl;
using std::string;

//������
class Manager:public Worker
{
public:
	Manager();
	//�вι��캯��
	Manager(int id, string name, int dept);
	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName();
};

