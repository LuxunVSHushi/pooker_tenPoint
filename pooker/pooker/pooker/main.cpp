/// loadpng.cpp: 定义控制台应用程序的入口点。
/*

开始必须把项目属性设置成长编码。否则无法读取扑克地址，无法输出

*/

#include "stdafx.h"
#include<iostream>
#include <windows.h>
//#include"graphics.h"
#include <string>
#include"pooker.h"
//#include<system>
using namespace std;

int main()
{
	
	init_window();
	init_pooker();
	output_pooker_dizhu();
	while (1)
	{
		
	
		output_game(mouse_val());

		//choose_pooker();
		//output_pooker(0, 0, 55);
	}
	getchar();
	closegraph();
	return 0;
}

