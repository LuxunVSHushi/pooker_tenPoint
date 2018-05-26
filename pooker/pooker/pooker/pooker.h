#pragma once
#ifndef _POOKER_H
#define _POOKER_H
#include "stdafx.h"
#include <string>
#include"graphics.h"
#include <mmsystem.h> //导入声音头文件库   
#pragma comment(lib,"winmm.lib")//导入声音的链接库  
using namespace std;
//pooker[55]存储54张扑克加一张扑克背面图。背面图固定存在pooker[54]
//IMAGE pookerPlay[55];
class Person {

public:
	
	int  money;    //存储玩家金钱
	double scor;    //存储玩家分数
	IMAGE person_pooker[10]; //存储玩的得到的扑克
	int postion_x;  //玩家发牌位置横坐标
	int postion_y;  //玩家发牌纵坐标
	int number;      //玩家存储的扑克数量
	char scor_change[10];
	char money_change[10];
};
void init_window();
void init_pooker();
void chenge_money_nongmin(); //转换农民金币成字符输出
void chenge_money_dizhu(); // 转换地主金币成字符
void clean_money_dizhu();   //显示地主金币前，先把显示区域擦除一遍
void clean_money_nongmin(); //显示农民金币前，先把显示区域擦除一遍

void output_pooker_dizhu(); //输出地主的扑克
double pooker_val();  //计算扑克数值
int  mouse_val();     //计算鼠标点击那个图标指令
void output_game( int x);//处理游戏

void output_nongmin_val();
#endif // !_POOKER_H

