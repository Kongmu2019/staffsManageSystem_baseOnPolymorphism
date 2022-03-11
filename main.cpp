#include <iostream>
#include "WorkerManager.h"
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"

using namespace std;

int main() {
	//测试代码，不同的对象指针调用同一个接口showInfo()的时候，会显示不同的内容，多态的体现
	//Worker *worker = NULL;
	//worker = new Employee(1,"张三",1);	//张三的编号为1，员工的编号是1
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2, "李四", 2);	//李四的编号为2，经理的编号是2
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "王五", 3);	//王五的编号为3，总裁的编号是3
	//worker->showInfo();
	//delete worker;
	WorkerManager wm;

	int choice = 0;
	while(true){
		//展示菜单
		wm.showMenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice) {
		case 0:		//退出系统
			wm.exitSystem();
			break;
		case 1:		//添加职工
			wm.Add_Emp();
			break;
		case 2:		//显示职工
			wm.show_Emp();
			break;
		case 3:		//删除职工
			wm.Del_Emp();
			break;
		case 4:		//修改职工
			wm.Mod_Emp();
			break;
		case 5:		//查找职工
			wm.Find_Emp();
			break;
		case 6:		//排序职工
			break;
		case 7:		//清空文件
			break;
		default:
			system("cls");
			break;
		}
	}

	return 0;
}

