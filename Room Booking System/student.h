#ifndef _STUDENT_
#define _STUDENT_

#include <iostream>
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"
using namespace std;

class Student : public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();
	
	//�鿴����ԤԼ
	void showAllOrder();
	
	//ȡ��ԤԼ
	void cancelOrder();
	
	//ѧ��ѧ��
	int m_Id;

	//��������    
	vector<ComputerRoom> vCom;
};

#endif