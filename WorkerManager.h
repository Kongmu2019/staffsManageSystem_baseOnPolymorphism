#pragma once
#include "Worker.h"
#include <fstream>
#define FILENAME "empFile.txt"
/*-----------------
管理类负责：
1.与用户沟通的菜单界面
2.对职工进行增删改查的操作
3.与文件的读写交互

------------------*/
class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//析构函数
	~WorkerManager();

	//显示菜单
	void showMenu();

	//退出系统
	void exitSystem();
	
	//添加员工
	void Add_Emp();

	//保存数据到文件
	void save();

	//统计文件中保存的人数
	int getEmp_Num();

	//初始化职工
	void Init_Emp();

	//显示职工
	void show_Emp();

	//记录职工人数
	int m_EmpNum;

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//按职工编号进行排序
	void Sort_Emp();

	//清空文件
	void Clean_File();

	//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
	int IsExist(int id);

	//职工数组指针
	Worker** m_EmpArray;

	//判断文件是否存在的属性
	bool m_FileIsEmpty;
};

