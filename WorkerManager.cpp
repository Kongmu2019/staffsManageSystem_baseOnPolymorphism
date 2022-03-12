
#include <iostream>
#include "WorkerManager.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
using namespace std;

WorkerManager::WorkerManager() {
	//��ʼ������ʱ���쳣�������
	//1.��һ��������ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (ifs.fail()) {
		//cout << "�ļ������ڣ�" << endl;	//���ڲ���
		//��ʼ������ֵ
		//��ʼ����¼����
		this->m_EmpNum = 0;

		//��ʼ��ָ������
		this->m_EmpArray = NULL;

		//��ʼ���ļ��Ƿ�Ϊ�յ�����
		this->m_FileIsEmpty = true;

		return;
	}

	//2.�ڶ���������ļ����ڣ�������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;		//���ڲ���
		//��ʼ����¼����
		this->m_EmpNum = 0;

		//��ʼ��ָ������
		this->m_EmpArray = NULL;

		//��ʼ���ļ��Ƿ�Ϊ�յ�����
		this->m_FileIsEmpty = true;

		return;
	}

	//3.������������ļ����ڣ����Ҽ�¼������
	int num = this->getEmp_Num();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//����һ���µ��ڴ�ռ�
	this->m_EmpArray = new Worker*[m_EmpNum];

	//���ļ��е����ݴ���������
	this->Init_Emp();

	//�����ȡ�������е�ְ����Ϣ
	/*for (int i = 0; i < m_EmpNum; i++) {
		cout << "ְ����ţ�" << m_EmpArray[i]->m_Id
			<< "\t������" << m_EmpArray[i]->m_Name
			<< "\t���ű�ţ�" << m_EmpArray[i]->m_DeptId << endl;
	}*/

}

WorkerManager::~WorkerManager() {
	/*------------����Ĵ����Ǵ���ʾ��-------------
	if (this->m_EmpArray != NULL) {		//�ͷŵ��ڶ������ٵ�ָ������
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
	-----------��--����Ĵ��������ȷ���ͷŲ���--��----*/

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

//��ʾ�˵�ʵ��
void WorkerManager::showMenu() {
	cout << "************************************" << endl;
	cout << "*******��ӭʹ��ְ������ϵͳ��*******" << endl;
	cout << "**********0.�˳��������************" << endl;
	cout << "**********1.����ְ����Ϣ************" << endl;
	cout << "**********2.��ʾְ����Ϣ************" << endl;
	cout << "**********3.ɾ����ְԱ��************" << endl;
	cout << "**********4.�޸�ְ����Ϣ************" << endl;
	cout << "**********5.����ְ����Ϣ************" << endl;
	cout << "**********6.���ձ������************" << endl;
	cout << "**********7.��������ĵ�************" << endl;
	cout << "************************************" << endl;
	cout << endl;
}


//�˳�ϵͳʵ��
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//���ְ��ʵ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ����������" << endl;
	int addNum = 0;		//�����û�����������
	cin >> addNum;
	if (addNum > 0) {
		//addNum����Ϸ������
		//��������ӿռ�Ĵ�С
		int newSize = m_EmpNum + addNum;	//�¿ռ�����=ԭ����¼��+���������

		//�����¿ռ�
		Worker** newSpace = new Worker*[newSize];

		//��ԭ���ռ�����ݿ������¿ռ���
		for (int i = 0; i < this->m_EmpNum; i++) {
			newSpace[i] = this->m_EmpArray[i];
		}

		//�������ְ������
		for (int i = 0; i < addNum; i++) {
			int id;		//ְ�����
			string name;	//ְ������
			int deptSelect;		//����ѡ��
			cout << "�������" << i + 1 << "��ְ���ı�ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��ְ����������" << endl;
			cin >> name;
			cout << "��ѡ���ְ����ְλ��" << endl;
			cout << "1---��ͨԱ��" << endl
				<< "2---����" << endl
				<< "3---�ܲ�" << endl;
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

			//�������õ�Ա��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//��ԭ�пռ�ָ���¿ռ�
		this->m_EmpArray = newSpace;

		//����ְ������
		this->m_EmpNum = newSize;

		//ÿ����ӳɹ��Ժ�Ҫ����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ�û����ְ���ɹ�
		cout << "������" << addNum << "��ְ���ɹ���" << endl;

		//�������д���ļ��������־û�
		this->save();

	}
	//�������������������һ���˵�
	system("pause");
	system("cls");

}

//�������ݵ��ļ�
void WorkerManager::save() {
	//1.�����ļ�������,���ù��캯�����ļ�
	ofstream ofs(FILENAME,ios::out);

	//2.��ÿ���˵�����д���ļ���
	for (int i = 0; i < m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << " " << endl;
	}

	//3.�ر��ļ�
	ofs.close();
}
//ͳ���ļ��б��������
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

	

	ifs.close();		//�ļ��������˹�

	return num;

}

//��ʼ��ְ�������ļ��е����ݶ�ȡ��ְ��������
void WorkerManager::Init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dept;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dept) {
		Worker *worker = NULL;
		
		if (dept == 1) {	//��ͨԱ�����ź���1
			worker = new Employee(id, name, dept);	
		}
		else if (dept == 2) {	//�����ź���2
			worker = new Manager(id, name, dept);
		}
		else if (dept == 3) {	//�ܲò��ź���3
			worker = new Boss(id, name, dept);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}

	//�ر��ļ���
	ifs.close();
}

//��ʾְ����Ϣ
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}

	//�����������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp() {
	//����ְ�������ɾ��
	int id = 0;
	cout << "������Ҫɾ��ְ���ı�ţ�" << endl;
	cin >> id;
	int index = this->IsExist(id);
	if (index == -1) {
		cout << "ɾ��ʧ�ܣ�δ�ҵ���Ա����" << endl;
	}
	else {		//˵��Ҫɾ����ְ�����ڣ�����Ҫɾ��indexλ���ϵ�ְ��
		for (int i = index; i < m_EmpNum - 1; i++) {
			//����ǰ��
			m_EmpArray[i] = m_EmpArray[i + 1];

		}
		//���������м�¼��Ա����
		this->m_EmpNum--;
		//����ͬ�����µ��ļ���
		this->save();
		cout << "ɾ��ְ���ɹ���" << endl;

	}

	//�����������
	system("pause");
	system("cls");

}

//�޸�ְ��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			//���ҵ��ñ�ŵ�Ա��
			delete this->m_EmpArray[ret];		//ɾ��Ա��ǰ���ͷŵ��ǲ��ֵĿռ�

			int newId = 0;
			string newName="";
			int newDept=0;

			cout << "�鵽��" <<id<< "��Ա������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1����ͨԱ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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

			//�������ݵ�������
			m_EmpArray[ret] = worker;

			//�������ݵ��ļ���
			this->save();

			cout << "�޸ĳɹ���" << endl;


		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1----ͨ����Ų���" << endl;
		cout << "2----ͨ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			cout << "������Ҫ���ҵ�ְ����ţ�" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "���ҳɹ���ְ�����Ϊ"
					<< this->m_EmpArray[ret]->m_Id
					<< "�ŵ�ְ����Ϣ���£�" << endl;

				m_EmpArray[ret]->showInfo();	//���ҳɹ����͵�����ʾְ���Ľӿ�
			}
			else {
				cout << "���޴��ˡ�" << endl;
			}
		}
		else if (select == 2) {
			cout << "������Ҫ���ҵ�ְ��������" << endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					m_EmpArray[i]->showInfo();		//���ҵ��˴��ˣ�������������������ʾ
					flag = true;
				}
			}
			if (flag == false) {
				cout << "���޴��ˡ�" << endl;
			}
		}
		else {
			cout << "�����ѡ������������ѡ��1��2" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

//��ְ����Ž�������
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "����������ʽ��" << endl;
		cout << "1��������������" << endl;
		cout << "2�����ս�������" << endl;
		int select = 0;
		cin >> select;
		//��ѡ�������㷨
		for (int i = 0; i < m_EmpNum; i++) {
			int min_or_max = i;	//ÿ��ѭ�������һ���±��Id����С������
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {//����
					if (m_EmpArray[j]->m_Id < m_EmpArray[min_or_max]->m_Id) {
						min_or_max = j;
					}
				}
				else if (select == 2) {//����
					if (m_EmpArray[j]->m_Id > m_EmpArray[min_or_max]->m_Id) {
						min_or_max = j;
					}
				}
				else {
					cout << "ѡ��ѡ�������ѡ��1��2��" << endl;
				}
			}
			
			//���ڽ����Ĵ���
			//�����ж�һ��ʼ�϶����Ǹ����ֵ����Сֵi�ǲ��Ǽ�����������ֵ����Сֵmin�������Ǿͽ���
			Worker* temp = NULL;
			if (min_or_max != i) {
				temp = m_EmpArray[min_or_max];
				m_EmpArray[min_or_max] = m_EmpArray[i];
				m_EmpArray[i] = temp;
			}
			
		}

		//���������Ľ�����ļ���
		this->save();

		//��ʾ�û�����ɹ�
		cout << "����ɹ���������Ϊ��" << endl;
		this->show_Emp();

		
	}
}

//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;		//�ҵ�ְ��
			break;
		}
	}
	return index;
}

//����ļ�
void WorkerManager::Clean_File() {
	cout << "ȷ��Ҫ�������ְ����Ϣ��" << endl;
	cout << "1----ȷ��" << endl;
	cout << "2----ȡ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);		//���ļ����ڣ�ɾ���ļ�������һ���µĿ��ļ�
		ofs.close();
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];		//�ͷŵ�������ÿһ��ָ��Ԫ��
				this->m_EmpArray[i] = NULL;
			}
			//�ͷ������е�ָ��Ԫ����Ϻ����ͷŶ�����ָ������
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;		//���ͷſռ���ָ���ÿգ���ֹҰָ��
			this->m_EmpNum = 0;				//ְ��������Ϊ0
			this->m_FileIsEmpty = true;		//���ļ��ձ�־Ϊ��
		}

		cout << "�����ϣ�" << endl;
	}
	system("pause");
	system("cls");
}
