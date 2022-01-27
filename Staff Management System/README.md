# Staff Management System

### 职工管理系统

#### **设计思路**：

**1、基于多态实现职工管理系统，职工分为三类：普通员工、经理、老板，需要显示职工编号、职工岗位以及职责。**

**2、主要功能包括：退出系统、添加职工、显示职工、删除职工、修改职工、查找职工、排序职工和清空文件。**

**3、定义管理类。负责内容如下：与用户的沟通菜单界面；对职工增删改查的操作；与文件的读写交互。**

**4、定义职工抽象基类，声明纯虚函数，并在员工类、经理类和老板类中重写纯虚函数。**

#### 实现细节：

##### 1、管理类中记录文件中的人数个数，并且定义员工数组的指针。

```c++
//记录文件中的人数个数
int m_EmpNum;

//员工数组的指针
Worker** m_EmpArray;
```
##### 2、如何将堆区数据写入文件中

###### 	2.1 包含文件流头文件，并定义存储文件

```c++
#include <fstream>
#define FILENAME "empFile.txt"
```

###### 	2.2 保存文件


```c++
void WorkerManager::save()
{
	ofstream ofs;	// 写文件用ofstream
	ofs.open(FILENAME, ios::out);	// ios::out--用输出的方式打开文件，即写文件

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}
```
##### 3、读文件，该操作由管理类构造函数实现。分三种情况：

- 第一次使用，文件未创建

- 文件存在，但是数据被用户清空

- 文件存在，并且保存职工的所有数据

  ###### 3.1 添加新的成员属性m_FileIsEmpty标志文件是否为空

```c++
//标志文件是否为空
bool m_FileIsEmpty;
```
###### 		3.2 文件不存在情况

```c++
ifstream ifs;
ifs.open(FILENAME, ios::in);

//文件不存在情况
if (!ifs.is_open())
{
	//cout << "文件不存在" << endl; //测试输出
	this->m_EmpNum = 0;  //初始化人数
	this->m_FileIsEmpty = true; //初始化文件为空标志
	this->m_EmpArray = NULL; //初始化数组
	ifs.close(); //关闭文件
	return;
}
```
###### 	3.3 文件存在且数据为空

```c++
//文件存在，并且没有记录
char ch;
ifs >> ch;
if (ifs.eof())
{
	cout << "文件为空!" << endl;
	this->m_EmpNum = 0;
	this->m_FileIsEmpty = true;
	this->m_EmpArray = NULL;
	ifs.close();
	return;
}
```
###### 	3.4 文件存在且保存职工数据

在workerManager.h中添加成员函数 ` int get_EmpNum();`

```c++
//统计人数
int get_EmpNum();
```
workerManager.cpp中实现:

```c++
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
        //记录人数
		num++;
	}
	ifs.close();

	return num;
}
```
在workerManager.cpp构造函数中继续追加代码：

```c++
int num =  this->get_EmpNum();
cout << "职工个数为：" << num << endl;  //测试代码
this->m_EmpNum = num;  //更新成员属性 
```
##### 4、根据职工的数据以及职工数据，初始化workerManager中的Worker ** m_EmpArray 指针。

在WorkerManager.h中添加成员函数  `void init_Emp();`

```c++
//初始化员工
void init_Emp();
```
在WorkerManager.cpp中实现：

```c++
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;
		//根据不同的部门Id创建不同对象
		if (dId == 1)  // 1普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //2经理
		{
			worker = new Manager(id, name, dId);
		}
		else //总裁
		{
			worker = new Boss(id, name, dId);
		}
		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
}
```
在workerManager.cpp构造函数中追加代码:

```c++
//根据职工数创建数组
this->m_EmpArray = new Worker *[this->m_EmpNum];
//初始化职工
init_Emp();

//测试代码
for (int i = 0; i < m_EmpNum; i++)
{
	cout << "职工号： " << this->m_EmpArray[i]->m_Id
		<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
}
```
##### 5、删除职工

###### 	5.1 判断职工是否存在

在workerManager.cpp中实现成员函数 `int IsExist(int id);`

```c++
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;

			break;
		}
	}

	return index;
}
```
###### 	5.2 删除职工

在workerManager.cpp中实现成员函数 ` void Del_Emp();`

```c++
//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)  //说明index上位置数据需要删除
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;

			this->save(); //删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	
	system("pause");
	system("cls");
}
```