#pragma once
#ifndef _POOKER_H
#define _POOKER_H
#include "stdafx.h"
#include <string>
#include"graphics.h"
#include <mmsystem.h> //��������ͷ�ļ���   
#pragma comment(lib,"winmm.lib")//�������������ӿ�  
using namespace std;
//pooker[55]�洢54���˿˼�һ���˿˱���ͼ������ͼ�̶�����pooker[54]
//IMAGE pookerPlay[55];
class Person {

public:
	
	int  money;    //�洢��ҽ�Ǯ
	double scor;    //�洢��ҷ���
	IMAGE person_pooker[10]; //�洢��ĵõ����˿�
	int postion_x;  //��ҷ���λ�ú�����
	int postion_y;  //��ҷ���������
	int number;      //��Ҵ洢���˿�����
	char scor_change[10];
	char money_change[10];
};
void init_window();
void init_pooker();
void chenge_money_nongmin(); //ת��ũ���ҳ��ַ����
void chenge_money_dizhu(); // ת��������ҳ��ַ�
void clean_money_dizhu();   //��ʾ�������ǰ���Ȱ���ʾ�������һ��
void clean_money_nongmin(); //��ʾũ����ǰ���Ȱ���ʾ�������һ��

void output_pooker_dizhu(); //����������˿�
double pooker_val();  //�����˿���ֵ
int  mouse_val();     //����������Ǹ�ͼ��ָ��
void output_game( int x);//������Ϸ

void output_nongmin_val();
#endif // !_POOKER_H

