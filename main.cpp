#include <iostream>
#include "WorkerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

using namespace std;

int main() {
	//���Դ��룬��ͬ�Ķ���ָ�����ͬһ���ӿ�showInfo()��ʱ�򣬻���ʾ��ͬ�����ݣ���̬������
	//Worker *worker = NULL;
	//worker = new Employee(1,"����",1);	//�����ı��Ϊ1��Ա���ı����1
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "����", 2);	//���ĵı��Ϊ2������ı����2
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "����", 3);	//����ı��Ϊ3���ܲõı����3
	//worker->showInfo();
	//delete worker;
	WorkerManager wm;

	int choice = 0;
	while(true){
		//չʾ�˵�
		wm.showMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice) {
		case 0:		//�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1:		//���ְ��
			wm.Add_Emp();
			break;
		case 2:		//��ʾְ��
			wm.show_Emp();
			break;
		case 3:		//ɾ��ְ��
			wm.Del_Emp();
			break;
		case 4:		//�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:		//����ְ��
			wm.Find_Emp();
			break;
		case 6:		//����ְ��
			wm.Sort_Emp();
			break;
		case 7:		//����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	return 0;
}

