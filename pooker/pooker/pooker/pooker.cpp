#include "stdafx.h"
#include"pooker.h"
#include"graphics.h"
#include <string>
#include<ctime>
#include<random>
#include <mmsystem.h> //导入声音头文件库   
#pragma comment(lib,"winmm.lib")//导入声音的链接库  
using namespace std;
IMAGE  pooker[55];
IMAGE  caidan[8];
Person A, B;//A为电脑玩家，B为人工玩家
int postion_x=200,postion_y=200;

/*********初始化游戏画布大小************/
void init_window()
{  	initgraph(1000, 600);
   setbkcolor(GREEN);
	cleardevice();

	//mciSendString("open E:\\VC++TEST\\pooker\\pooker\\Debug\\linglongqi.mp3", NULL, 0, 0);  // 播放声音 E盘符后面的根据个人实际自己修改
	//mciSendString("play E:\\VC++TEST\\pooker\\pooker\\Debug\\linglongqi.mp3  repeat", NULL, 0, 0);

	mciSendString("open linglongqi.mp3", NULL, 0, 0);  // 播放声音 资源加载型播放声音。前面两行也能加载
	mciSendString("play linglongqi.mp3  repeat", NULL, 0, 0);


	loadimage(&caidan[0], (LPCTSTR)"chupai.bmp", 0, 0); //菜单数组0存储“出牌”
	loadimage(&caidan[1], (LPCTSTR)"jiesuan.bmp", 0, 0); //菜单数组1存储“结算”
	loadimage(&caidan[2], (LPCTSTR)"dizhu.bmp", 0, 0);  //菜单数组2存储“地主”
	loadimage(&caidan[3], (LPCTSTR)"nongmin.bmp", 0, 0); //菜单数组3存储“农民”
	loadimage(&caidan[4], (LPCTSTR)"nongminwin.bmp", 0, 0); //菜单数组4存储“农民胜利”
	loadimage(&caidan[5], (LPCTSTR)"dizhuwin.bmp", 0, 0); //菜单数组5存储“地主胜利”
	loadimage(&caidan[6], (LPCTSTR)"jixu.bmp", 0, 0); //菜单数组6存储“继续游戏”
	loadimage(&caidan[7], (LPCTSTR)"jinbi.bmp", 0, 0); //菜单数组7存储“金币”

	

	A.money = 1000;                //Person  A存放地主数据
	A.scor = 0;
	A.postion_x = 200;
	A.postion_y = 30;
	A.number = 0;

	B.money = 1000;                //Person  B存放农民数据
	B.scor = 0;
	B.number = 0;
	B.postion_x = 200;
	B.postion_y = 240;

	putimage(650, 470, &caidan[0]); //出牌的坐标范围 650<=x<=650+78;470<=y<=470+30
	putimage(650, 520, &caidan[1]); //结算的坐标范围 650<=x<=650+78;520<=y<=520+30 
	putimage(750, 470, &caidan[6]); //继续的坐标范围 750<=x<=750+78;470<=y<=470+30 
	putimage(50, 50, &caidan[2]);  //地主的位置

	putimage(10, 220, &caidan[7]);  //地主的金币位置
	chenge_money_dizhu();
	outtextxy(100, 230, A.money_change);//输出地主金币

	putimage(500, 440, &caidan[3]);//农民的位置
	putimage(10, 500, &caidan[7]);  //农民的金币位置
	Sleep(500);                   //这一句为了调试BUG
	
	chenge_money_nongmin();
	outtextxy(100, 510, B.money_change);//输出农民金币

}

/**********初始化扑克牌*********************/
void init_pooker()
{
	char inputNum[15];
	for (int i = 0; i <52; i++)
	{
		int j1 = i / 13, j2 = i % 13;
		if (j1 == 0)
		{
			sprintf_s(inputNum, 15, "fangpian%d.bmp", j2+1);
			loadimage(&pooker[i], (LPCTSTR)inputNum, 0, 0);

		}
		else if(j1==1)
		{
			sprintf_s(inputNum, 15, "heitao%d.bmp", j2+1);
			loadimage(&pooker[i], (LPCTSTR)inputNum, 0, 0);
		}
		else if(j1==2)
		{ 
			sprintf_s(inputNum, 15, "hongtao%d.bmp", j2+1);
			loadimage(&pooker[i], (LPCTSTR)inputNum, 0, 0);
		}
		else if(j1==3)
		{
			sprintf_s(inputNum, 15, "meihua%d.bmp", j2+1);
			loadimage(&pooker[i], (LPCTSTR)inputNum, 0, 0);
		
		}
		
		loadimage(&pooker[52], (LPCTSTR)"dawang.bmp", 0, 0);//数组最后两张存放大小王
		loadimage(&pooker[53], (LPCTSTR)"xiaowang.bmp", 0, 0);
		loadimage(&pooker[54], (LPCTSTR)"beimian.bmp", 0, 0);//数组最后一个存放扑克背面。

	}




}

double pooker_val(int x)  //传过来的是从扑克数组pooker[55]中第几张牌
{
	double val;
	
	int  j2 = (x % 13)+1; //扑克1-10的分值为1-10.J Q K 大小王为0.5分
	if (x == 52 || x == 53)
	{
		return val = 0.5;
	}
	else if (j2 >= 1 && j2 <= 10)
	{
		return val = j2;

	}
	else if (j2 >= 11 && j2 <= 13)
	{
		return val = 0.5;
	}
	else return 0;
}
/**************先给地主发牌*************************/
void output_pooker_dizhu()
{
	A.number=0;
	int index1 ;
	
	while (A.scor <= 8)
	{
		srand(time(NULL) + rand());
		index1 = rand() % 54;
		A.scor += pooker_val(index1);
		putimage(A.postion_x, A.postion_y, &pooker[54]);
		A.postion_x += 40;
		A.person_pooker[A.number] = pooker[index1];
		A.number++;
		Sleep(500);//模拟思考的过程
	}
    string scor1; //地主分数转换成字符串
	scor1 = to_string(A.scor);
	int len = scor1.length();
	for (int i = 0; i <= len; i++)
		A.scor_change[i] = scor1[i];
	A.scor_change[len + 1] = '\0';
  
	chenge_money_dizhu();


}

/***************计算鼠标指令*****************************/
int  mouse_val()
{
	MOUSEMSG input = { 0,0,0,0,0,0,0,0,0 };
	int index1,val;
	input = GetMouseMsg();
	//鼠标点击出牌，数值返回1； 结算的坐标范围 650<=x<=650+78;520<=y<=520+30 
	if (input.x >= 650 && input.x <= 728 && input.y >= 470 && input.y <= 500 && input.mkLButton)
	{
		Sleep(100); //防止鼠标连击
		if (input.x >= 650 && input.x <= 728 && input.y >= 470 && input.y <= 500 && input.mkLButton)
		{
			FlushMouseMsgBuffer();
			return  val = 1;
		}
	}
	else if (input.x >= 650 && input.x <= 728 && input.y >= 520&& input.y <= 550 && input.mkLButton)
	{
		Sleep(100);
		if (input.x >= 650 && input.x <= 728 && input.y >= 520 && input.y <= 550 && input.mkLButton)
		{
			FlushMouseMsgBuffer();
			return  val = 2;
		}
	}
	else if (input.x >= 750 && input.x <= 830 && input.y >= 470 && input.y <= 500 && input.mkLButton)
	{
		Sleep(100);
		if (input.x >= 750 && input.x <= 830 && input.y >= 470 && input.y <= 500 && input.mkLButton)
		{
			FlushMouseMsgBuffer();
			return  val = 3;
		}
	}
	else {
		FlushMouseMsgBuffer();
		return val = 0;

	}

}

/******************计算游戏********************/
void output_game(int x) //根据鼠标处理的数值，做出相应的动作
{  
	int index1;
	switch (x) {

        case 0:  //点击在空白处
	       break;
		case 1: //点击出牌，随机抽一张牌输出
			
			srand(time(NULL) + rand());
			index1 = rand() % 54;
			B.scor+=pooker_val(index1);
			B.person_pooker[B.number] = pooker[index1];
			putimage(B.postion_x, B.postion_y, &B.person_pooker[B.number]);
			B.postion_x += 40;
			B.number++;
			break;
		case 2:      //结算相关处理程序
			A.postion_x = 200;  //地主的出牌位置回到初始化位置
			A.postion_y = 30;
			
			outtextxy(50, 190, A.scor_change);//输出地主分数
			//outtextxy(100, 230, A.money_change);//输出地主金币
			output_nongmin_val(); //输出农民分数
			

			for (int i = 0; i < A.number; i++) //先把地主底牌亮出来
			{
				
				putimage(A.postion_x, A.postion_y, &A.person_pooker[i]);
				A.postion_x += 40;
				A.person_pooker[i] = 0;
			}
			


			if((B.scor<=10.5)&&(A.scor<=10.5)&&(B.scor>=A.scor)) //双方都没超过10.5，且B>A的分数，B赢了输出一张大王
			{
				putimage(420, 230, &caidan[4]);  //caidan[4]是农民胜利。caidan[5]是地主胜利
				A.money -= 50;
				B.money += 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币

				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
				
				
			}
			else if ((B.scor <= 10.5) && (A.scor > 10.5) )  //A方数值超了，B赢输出一张大王
			{
				putimage(420,230, &caidan[4]);
				A.money -= 50;
				B.money += 50;
				
				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
			}
			else if ((B.scor > 10.5) && (A.scor >10.5) && (B.scor<=A.scor))//双方都超了，谁小谁赢
			{
				putimage(420, 230, &caidan[4]);
				A.money -= 50;
				B.money += 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
			}
			else if ((B.scor <= 10.5) && (A.scor <= 10.5) && (B.scor <= A.scor)) //双方都没超过10.5，且B<A的分数，B输了输出一张小王
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
			}
			else if ((B.scor > 10.5) && (A.scor <= 10.5))  //B方数值超了，A赢输出一张小王
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
			}
			else if ((B.scor > 10.5) && (A.scor >10.5) && (A.scor<= B.scor))//双方都超了，谁小谁赢
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//输出地主金币
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//输出农民金币
			}


			A.scor = 0;  
			A.postion_x = 200;
			A.postion_y = 30;
			A.number = 0;

			
			B.scor = 0;
			B.number = 0;
			B.postion_x = 200;
			B.postion_y = 240;

			
			break;
		case 3:
			
			
			HRGN rgn = CreateRectRgn(190, 30, 900, 440); //设置裁剪区域，然后清除
			
			setcliprgn(rgn);
			clearcliprgn();
			setcliprgn(NULL);  //释放当前裁剪区域

           Sleep(500);
			

			HRGN rgn1 = CreateRectRgn(50, 190, 120, 220); //清除地主头像下方的分数
			setcliprgn(rgn1);
			clearcliprgn();
			setcliprgn(NULL);   //释放当前裁剪区域

			HRGN rgn2= CreateRectRgn(400, 490, 490, 510); //清除农民头像左侧的分数
			setcliprgn(rgn2);
			clearcliprgn();
			setcliprgn(NULL);   //释放当前裁剪区域
			output_pooker_dizhu(); 
			
			//chenge_money(B);

			//outtextxy(100, 500,B.money_change);//输出农民金币
			break;
	}
		




}

/********************计算农民得分**********************/
void output_nongmin_val()
{
	string scor1; //地主分数转换成字符串
	scor1 = to_string(B.scor);
	int len = scor1.length();
	for (int i = 0; i <= len; i++)
		B.scor_change[i] = scor1[i];
	B.scor_change[len + 1] = '\0';

	outtextxy(400, 490, B.scor_change);//输出农民分数





}
/****************处理农民的金币成字符*******************************/
void chenge_money_nongmin()  //处理对象的金币
{
	string scor1; //地主金币转换成字符串
	scor1 = to_string(B.money);
	int len1 = scor1.length();
	for (int i = 0; i <= len1; i++)
		B.money_change[i] = scor1[i];
	B.money_change[len1 + 1] = '\0';

	}

/****************处理地主的金币成字符*******************************/
void chenge_money_dizhu()
{

	string scor1; //地主金币转换成字符串
	scor1 = to_string(A.money);
	int len1 = scor1.length();
	for (int i = 0; i <= len1; i++)
		A.money_change[i] = scor1[i];
	A.money_change[len1 + 1] = '\0';


}

void clean_money_dizhu()  //显示地主金币前，先把显示区域擦除一遍
{
	HRGN rgn1 = CreateRectRgn(95, 250,200, 230); //清除地主头像下方的分数
	setcliprgn(rgn1);
	clearcliprgn();
	setcliprgn(NULL);   //释放当前裁剪区域


}
void clean_money_nongmin() //显示农民金币前，先把显示区域擦除一遍
{

	HRGN rgn1 = CreateRectRgn(95, 530, 200, 500); //清除地主头像下方的分数
	setcliprgn(rgn1);
	clearcliprgn();
	setcliprgn(NULL);   //释放当前裁剪区域



}