/// loadpng.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <windows.h>
#include"graphics.h"
#include <string>

//#include<system>
using namespace std;

int main()
{

	MOUSEMSG input = { 0,0,0,0,0,0,0,0,0 };
	IMAGE pic, pic2, a[6], b[4];
	/*loadimage(&pic, "meihua1.bmp");
	a[0] = pic;
	loadimage(&pic, "meihua2.bmp");
	a[1] = pic;
	loadimage(&pic, "meihua3.bmp");
	a[2] = pic;
	loadimage(&pic, "meihua1.bmp");
	a[3] = pic;
	loadimage(&pic, "meihua2.bmp");
	a[4] = pic;
	loadimage(&pic, "meihua3.bmp");
	a[5] = pic;*/
	char inputNum[15];
	for (int i = 0; i < 4; i++)
	{
		//int numColor = (int)pow(2.0, (double)i);
		sprintf_s(inputNum, 15, "meihua%d.bmp", i);
		loadimage(&b[i], (LPCTSTR)inputNum, 0, 0);




	}




	int step = 30, n = 3;
	initgraph(800, 600);



	//string s = "E:\\VC++TEST\\xiangqi\\loadpng\\loadpng\\meihua3.bmp";
	// pic2 = "meihua3.bmp";
	setbkcolor(GREEN);
	cleardevice();
	//putimage(150, 150, &a[0]);
	putimage(0, 150, &b[3]);

	//*p ="meihua3.bmp";
	//outtextxy(200, 200, "nihao");
	//circle(200, 200, 100);
	// sleep(2000);
	// outtext("nihao");
	//for (int i = 0; i <= 6; i++)
	//{
	//	//setorigin(400+step, 400);
	//	putimage(300 + step * i, 0, &a[i]);

	//	Sleep(200);

	//}

	int j = 1;
	while (1)
	{
		int i = 30;

		input = GetMouseMsg();
		if (input.x >= 120 && input.x <= 180 && input.y >= 120 && input.y <= 180 && input.mkLButton)
		{
			putimage(300 + i * j, 400, &b[2]);
			j++;

			FlushMouseMsgBuffer();
		}

	}
	// 从图片文件获取图像(bmp/jpg/gif/emf/wmf)
	//getchar();
	closegraph();
	return 0;
}

