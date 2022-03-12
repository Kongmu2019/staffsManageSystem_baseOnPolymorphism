
#include <iostream>
#include "WorkerManager.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
using namespace std;

WorkerManager::WorkerManager() {
	//初始化程序时的异常情况处理
	//1.第一种情况：文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (ifs.fail()) {
		//cout << "文件不存在！" << endl;	//用于测试
		//初始化属性值
		//初始化记录人数
		this->m_EmpNum = 0;

		//初始化指针数组
		this->m_EmpArray = NULL;

		//初始化文件是否为空的属性
		this->m_FileIsEmpty = true;

		return;
	}

	//2.第二种情况：文件存在，但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空！" << endl;		//用于测试
		//初始化记录人数
		this->m_EmpNum = 0;

		//初始化指针数组
		this->m_EmpArray = NULL;

		//初始化文件是否为空的属性
		this->m_FileIsEmpty = true;

		return;
	}

	//3.第三种情况：文件存在，并且记录着数据
	int num = this->getEmp_Num();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟一块新的内存空间
	this->m_EmpArray = new Worker*[m_EmpNum];

	//将文件中的数据存入数组中
	this->Init_Emp();

	//输出读取到数组中的职工信息
	/*for (int i = 0; i < m_EmpNum; i++) {
		cout << "职工编号：" << m_EmpArray[i]->m_Id
			<< "\t姓名：" << m_EmpArray[i]->m_Name
			<< "\t部门编号：" << m_EmpArray[i]->m_DeptId << endl;
	}*/

}

WorkerManager::~WorkerManager() {
	/*------------下面的代码是错误示范-------------
	if (this->m_EmpArray != NULL) {		//释放掉在堆区开辟的指针数组
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
	-----------↓--下面的代码才是正确的释放操作--↓----*/

	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}

//显示菜单实现
void WorkerManager::showMenu() {
	cout << "************************************" << endl;
	cout << "*******欢迎使用职工管理系统！*******" << endl;
	cout << "**********0.退出管理程序************" << endl;
	cout << "**********1.增加职工信息************" << endl;
	cout << "**********2.显示职工信息************" << endl;
	cout << "**********3.删除离职员工************" << endl;
	cout << "**********4.修改职工信息************" << endl;
	cout << "**********5.查找职工信息************" << endl;
	cout << "**********6.按照编号排序************" << endl;
	cout << "**********7.清空所有文档************" << endl;
	cout << "************************************" << endl;
	cout << endl;
}


//退出系统实现
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工实现
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;		//保存用户的输入数量
	cin >> addNum;
	if (addNum > 0) {
		//addNum输入合法才添加
		//计算新添加空间的大小
		int newSize = m_EmpNum + addNum;	//新空间人数=原来记录数+新添加人数

		//开辟新空间
		Worker** newSpace = new Worker*[newSize];

		//将原来空间的数据拷贝到新空间下
		for (int i = 0; i < this->m_EmpNum; i++) {
			newSpace[i] = this->m_EmpArray[i];
		}

		//批量添加职工数据
		for (int i = 0; i < addNum; i++) {
			int id;		//职工编号
			string name;	//职工姓名
			int deptSelect;		//部门选择
			cout << "请输入第" << i + 1 << "个职工的编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个职工的姓名：" << endl;
			cin >> name;
			cout << "请选择该职工的职位：" << endl;
			cout << "1---普通员工" << endl
				<< "2---经理" << endl
				<< "3---总裁" << endl;
			cin >> deptSelect;

			Worker *worker = NULL;
			switch (deptSelect)
			{
			case 1:
				worker = new Employee(id, name, deptSelect);
				break;
			case 2:
				worker = new Manager(id, name, deptSelect);
				break;
			case 3:
				worker = new Boss(id, name, deptSelect);
				break;
			default:
				break;
			}

			//将创建好的员工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//让原有空间指向新空间
		this->m_EmpArray = newSpace;

		//更新职工人数
		this->m_EmpNum = newSize;

		//每次添加成功以后，要更新职工不为空标志
		this->m_FileIsEmpty = false;

		//提示用户添加职工成功
		cout << "新增加" << addNum << "个职工成功！" << endl;

		//最后将数据写入文件中用来持久化
		this->save();

	}
	//按任意键清屏并返回上一级菜单
	system("pause");
	system("cls");

}

//保存数据到文件
void WorkerManager::save() {
	//1.创建文件流对象,并用构造函数打开文件
	ofstream ofs(FILENAME,ios::out);

	//2.将每个人的数据写入文件中
	for (int i = 0; i < m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << " " << endl;
	}

	//3.关闭文件
	ofs.close();
}
//统计文件中保存的人数
int WorkerManager::getEmp_Num()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dept;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		num++;
	}

	

	ifs.close();		//文件流别忘了关

	return num;

}

//初始化职工，把文件中的数据读取到职工数组中
void WorkerManager::Init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dept;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		Worker *worker = NULL;
		
		if (dept == 1) {	//普通员工部门号是1
			worker = new Employee(id, name, dept);	
		}
		else if (dept == 2) {	//经理部门号是2
			worker = new Manager(id, name, dept);
		}
		else if (dept == 3) {	//总裁部门号是3
			worker = new Boss(id, name, dept);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}

	//关闭文件流
	ifs.close();
}

//显示职工信息
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp() {
	//按照职工编号来删除
	int id = 0;
	cout << "请输入要删除职工的编号：" << endl;
	cin >> id;
	int index = this->IsExist(id);
	if (index == -1) {
		cout << "删除失败，未找到该员工！" << endl;
	}
	else {		//说明要删除的职工存在，并且要删除index位置上的职工
		for (int i = index; i < m_EmpNum - 1; i++) {
			//数据前移
			m_EmpArray[i] = m_EmpArray[i + 1];

		}
		//更新数组中记录人员个数
		this->m_EmpNum--;
		//数据同步更新到文件中
		this->save();
		cout << "删除职工成功！" << endl;

	}

	//按任意键清屏
	system("pause");
	system("cls");

}

//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			//查找到该编号的员工
			delete this->m_EmpArray[ret];		//删除员工前先释放掉那部分的空间

			int newId = 0;
			string newName="";
			int newDept=0;

			cout << "查到：" <<id<< "号员工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通员工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> newDept;

			Worker *worker = NULL;

			switch (newDept)
			{
			case 1:
				worker = new Employee(newId, newName, newDept);
				break;
			case 2:
				worker = new Manager(newId, newName, newDept);
				break;
			case 3:
				worker = new Boss(newId, newName, newDept);
				break;
			default:
				break;
			}

			//更新数据到数组中
			m_EmpArray[ret] = worker;

			//保存数据到文件中
			this->save();

			cout << "修改成功！" << endl;


		}
		else {
			cout << "修改失败，查无此人！" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空！" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1----通过编号查找" << endl;
		cout << "2----通过姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			cout << "请输入要查找的职工编号：" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "查找成功，职工编号为"
					<< this->m_EmpArray[ret]->m_Id
					<< "号的职工信息如下：" << endl;

				m_EmpArray[ret]->showInfo();	//查找成功，就调用显示职工的接口
			}
			else {
				cout << "查无此人。" << endl;
			}
		}
		else if (select == 2) {
			cout << "请输入要查找的职工姓名：" << endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					m_EmpArray[i]->showInfo();		//查找到了此人，若有重名，会逐行显示
					flag = true;
				}
			}
			if (flag == false) {
				cout << "查无此人。" << endl;
			}
		}
		else {
			cout << "输入的选项有误，请重新选择1或2" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

//按职工编号进行排序
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请输入排序方式：" << endl;
		cout << "1、按照升序排序" << endl;
		cout << "2、按照降序排序" << endl;
		int select = 0;
		cin >> select;
		//简单选择排序算法
		for (int i = 0; i < m_EmpNum; i++) {
			int min_or_max = i;	//每次循环假设第一个下标的Id是最小或最大的
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {//升序
					if (m_EmpArray[j]->m_Id < m_EmpArray[min_or_max]->m_Id) {
						min_or_max = j;
					}
				}
				else if (select == 2) {//降序
					if (m_EmpArray[j]->m_Id > m_EmpArray[min_or_max]->m_Id) {
						min_or_max = j;
					}
				}
				else {
					cout << "选项选择错误，请选择1或2。" << endl;
				}
			}
			
			//用于交换的代码
			//这里判断一开始认定的那个最大值和最小值i是不是计算出来的最大值或最小值min，若不是就交换
			Worker* temp = NULL;
			if (min_or_max != i) {
				temp = m_EmpArray[min_or_max];
				m_EmpArray[min_or_max] = m_EmpArray[i];
				m_EmpArray[i] = temp;
			}
			
		}

		//保存排序后的结果到文件中
		this->save();

		//提示用户排序成功
		cout << "排序成功，排序结果为：" << endl;
		this->show_Emp();

		
	}
}

//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;		//找到职工
			break;
		}
	}
	return index;
}

//清空文件
void WorkerManager::Clean_File() {
	cout << "确认要清空所有职工信息吗？" << endl;
	cout << "1----确定" << endl;
	cout << "2----取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);		//若文件存在，删除文件并创建一个新的空文件
		ofs.close();
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];		//释放掉堆区的每一个指针元素
				this->m_EmpArray[i] = NULL;
			}
			//释放数组中的指针元素完毕后，再释放堆区的指针数组
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;		//让释放空间后的指针置空，防止野指针
			this->m_EmpNum = 0;				//职工人数置为0
			this->m_FileIsEmpty = true;		//置文件空标志为真
		}

		cout << "清空完毕！" << endl;
	}
	system("pause");
	system("cls");
}
