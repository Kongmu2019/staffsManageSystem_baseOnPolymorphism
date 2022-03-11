#pragma once
#include "Worker.h"
#include <fstream>
#define FILENAME "empFile.txt"
/*-----------------
�����ฺ��
1.���û���ͨ�Ĳ˵�����
2.��ְ��������ɾ�Ĳ�Ĳ���
3.���ļ��Ķ�д����

------------------*/
class WorkerManager
{
public:
	//���캯��
	WorkerManager();

	//��������
	~WorkerManager();

	//��ʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();
	
	//���Ա��
	void Add_Emp();

	//�������ݵ��ļ�
	void save();

	//ͳ���ļ��б��������
	int getEmp_Num();

	//��ʼ��ְ��
	void Init_Emp();

	//��ʾְ��
	void show_Emp();

	//��¼ְ������
	int m_EmpNum;

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(int id);

	//ְ������ָ��
	Worker** m_EmpArray;

	//�ж��ļ��Ƿ���ڵ�����
	bool m_FileIsEmpty;
};

