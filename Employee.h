#pragma once
#include "Worker.h"

class Employee:public Worker
{
public:
	Employee();
	Employee(int id, string name, int dept);
	//��ʾ������Ϣ
	void showInfo();
	//��ȡ��λ����
	string getDeptName();
};

