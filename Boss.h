#pragma once
#include "Worker.h"
class Boss :public Worker
{
public:
	Boss();
	//�вι��캯��
	Boss(int id, string name, int dept);
	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName();
};

