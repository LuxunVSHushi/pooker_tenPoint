#include "stdafx.h"
#include"pooker.h"
#include"graphics.h"
#include <string>
#include<ctime>
#include<random>
#include <mmsystem.h> //��������ͷ�ļ���   
#pragma comment(lib,"winmm.lib")//�������������ӿ�  
using namespace std;
IMAGE  pooker[55];
IMAGE  caidan[8];
Person A, B;//AΪ������ң�BΪ�˹����
int postion_x=200,postion_y=200;

/*********��ʼ����Ϸ������С************/
void init_window()
{  	initgraph(1000, 600);
   setbkcolor(GREEN);
	cleardevice();

	//mciSendString("open E:\\VC++TEST\\pooker\\pooker\\Debug\\linglongqi.mp3", NULL, 0, 0);  // �������� E�̷�����ĸ��ݸ���ʵ���Լ��޸�
	//mciSendString("play E:\\VC++TEST\\pooker\\pooker\\Debug\\linglongqi.mp3  repeat", NULL, 0, 0);

	mciSendString("open linglongqi.mp3", NULL, 0, 0);  // �������� ��Դ�����Ͳ���������ǰ������Ҳ�ܼ���
	mciSendString("play linglongqi.mp3  repeat", NULL, 0, 0);


	loadimage(&caidan[0], (LPCTSTR)"chupai.bmp", 0, 0); //�˵�����0�洢�����ơ�
	loadimage(&caidan[1], (LPCTSTR)"jiesuan.bmp", 0, 0); //�˵�����1�洢�����㡱
	loadimage(&caidan[2], (LPCTSTR)"dizhu.bmp", 0, 0);  //�˵�����2�洢��������
	loadimage(&caidan[3], (LPCTSTR)"nongmin.bmp", 0, 0); //�˵�����3�洢��ũ��
	loadimage(&caidan[4], (LPCTSTR)"nongminwin.bmp", 0, 0); //�˵�����4�洢��ũ��ʤ����
	loadimage(&caidan[5], (LPCTSTR)"dizhuwin.bmp", 0, 0); //�˵�����5�洢������ʤ����
	loadimage(&caidan[6], (LPCTSTR)"jixu.bmp", 0, 0); //�˵�����6�洢��������Ϸ��
	loadimage(&caidan[7], (LPCTSTR)"jinbi.bmp", 0, 0); //�˵�����7�洢����ҡ�

	

	A.money = 1000;                //Person  A��ŵ�������
	A.scor = 0;
	A.postion_x = 200;
	A.postion_y = 30;
	A.number = 0;

	B.money = 1000;                //Person  B���ũ������
	B.scor = 0;
	B.number = 0;
	B.postion_x = 200;
	B.postion_y = 240;

	putimage(650, 470, &caidan[0]); //���Ƶ����귶Χ 650<=x<=650+78;470<=y<=470+30
	putimage(650, 520, &caidan[1]); //��������귶Χ 650<=x<=650+78;520<=y<=520+30 
	putimage(750, 470, &caidan[6]); //���������귶Χ 750<=x<=750+78;470<=y<=470+30 
	putimage(50, 50, &caidan[2]);  //������λ��

	putimage(10, 220, &caidan[7]);  //�����Ľ��λ��
	chenge_money_dizhu();
	outtextxy(100, 230, A.money_change);//����������

	putimage(500, 440, &caidan[3]);//ũ���λ��
	putimage(10, 500, &caidan[7]);  //ũ��Ľ��λ��
	Sleep(500);                   //��һ��Ϊ�˵���BUG
	
	chenge_money_nongmin();
	outtextxy(100, 510, B.money_change);//���ũ����

}

/**********��ʼ���˿���*********************/
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
		
		loadimage(&pooker[52], (LPCTSTR)"dawang.bmp", 0, 0);//����������Ŵ�Ŵ�С��
		loadimage(&pooker[53], (LPCTSTR)"xiaowang.bmp", 0, 0);
		loadimage(&pooker[54], (LPCTSTR)"beimian.bmp", 0, 0);//�������һ������˿˱��档

	}




}

double pooker_val(int x)  //���������Ǵ��˿�����pooker[55]�еڼ�����
{
	double val;
	
	int  j2 = (x % 13)+1; //�˿�1-10�ķ�ֵΪ1-10.J Q K ��С��Ϊ0.5��
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
/**************�ȸ���������*************************/
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
		Sleep(500);//ģ��˼���Ĺ���
	}
    string scor1; //��������ת�����ַ���
	scor1 = to_string(A.scor);
	int len = scor1.length();
	for (int i = 0; i <= len; i++)
		A.scor_change[i] = scor1[i];
	A.scor_change[len + 1] = '\0';
  
	chenge_money_dizhu();


}

/***************�������ָ��*****************************/
int  mouse_val()
{
	MOUSEMSG input = { 0,0,0,0,0,0,0,0,0 };
	int index1,val;
	input = GetMouseMsg();
	//��������ƣ���ֵ����1�� ��������귶Χ 650<=x<=650+78;520<=y<=520+30 
	if (input.x >= 650 && input.x <= 728 && input.y >= 470 && input.y <= 500 && input.mkLButton)
	{
		Sleep(100); //��ֹ�������
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

/******************������Ϸ********************/
void output_game(int x) //������괦�����ֵ��������Ӧ�Ķ���
{  
	int index1;
	switch (x) {

        case 0:  //����ڿհ״�
	       break;
		case 1: //������ƣ������һ�������
			
			srand(time(NULL) + rand());
			index1 = rand() % 54;
			B.scor+=pooker_val(index1);
			B.person_pooker[B.number] = pooker[index1];
			putimage(B.postion_x, B.postion_y, &B.person_pooker[B.number]);
			B.postion_x += 40;
			B.number++;
			break;
		case 2:      //������ش������
			A.postion_x = 200;  //�����ĳ���λ�ûص���ʼ��λ��
			A.postion_y = 30;
			
			outtextxy(50, 190, A.scor_change);//�����������
			//outtextxy(100, 230, A.money_change);//����������
			output_nongmin_val(); //���ũ�����
			

			for (int i = 0; i < A.number; i++) //�Ȱѵ�������������
			{
				
				putimage(A.postion_x, A.postion_y, &A.person_pooker[i]);
				A.postion_x += 40;
				A.person_pooker[i] = 0;
			}
			


			if((B.scor<=10.5)&&(A.scor<=10.5)&&(B.scor>=A.scor)) //˫����û����10.5����B>A�ķ�����BӮ�����һ�Ŵ���
			{
				putimage(420, 230, &caidan[4]);  //caidan[4]��ũ��ʤ����caidan[5]�ǵ���ʤ��
				A.money -= 50;
				B.money += 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������

				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
				
				
			}
			else if ((B.scor <= 10.5) && (A.scor > 10.5) )  //A����ֵ���ˣ�BӮ���һ�Ŵ���
			{
				putimage(420,230, &caidan[4]);
				A.money -= 50;
				B.money += 50;
				
				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
			}
			else if ((B.scor > 10.5) && (A.scor >10.5) && (B.scor<=A.scor))//˫�������ˣ�˭С˭Ӯ
			{
				putimage(420, 230, &caidan[4]);
				A.money -= 50;
				B.money += 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
			}
			else if ((B.scor <= 10.5) && (A.scor <= 10.5) && (B.scor <= A.scor)) //˫����û����10.5����B<A�ķ�����B�������һ��С��
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
			}
			else if ((B.scor > 10.5) && (A.scor <= 10.5))  //B����ֵ���ˣ�AӮ���һ��С��
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
			}
			else if ((B.scor > 10.5) && (A.scor >10.5) && (A.scor<= B.scor))//˫�������ˣ�˭С˭Ӯ
			{
				putimage(420, 230, &caidan[5]);
				A.money += 50;
				B.money -= 50;

				chenge_money_dizhu();
				clean_money_dizhu();
				outtextxy(100, 230, A.money_change);//����������
				
				chenge_money_nongmin();
				clean_money_nongmin();
				outtextxy(100, 510, B.money_change);//���ũ����
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
			
			
			HRGN rgn = CreateRectRgn(190, 30, 900, 440); //���òü�����Ȼ�����
			
			setcliprgn(rgn);
			clearcliprgn();
			setcliprgn(NULL);  //�ͷŵ�ǰ�ü�����

           Sleep(500);
			

			HRGN rgn1 = CreateRectRgn(50, 190, 120, 220); //�������ͷ���·��ķ���
			setcliprgn(rgn1);
			clearcliprgn();
			setcliprgn(NULL);   //�ͷŵ�ǰ�ü�����

			HRGN rgn2= CreateRectRgn(400, 490, 490, 510); //���ũ��ͷ�����ķ���
			setcliprgn(rgn2);
			clearcliprgn();
			setcliprgn(NULL);   //�ͷŵ�ǰ�ü�����
			output_pooker_dizhu(); 
			
			//chenge_money(B);

			//outtextxy(100, 500,B.money_change);//���ũ����
			break;
	}
		




}

/********************����ũ��÷�**********************/
void output_nongmin_val()
{
	string scor1; //��������ת�����ַ���
	scor1 = to_string(B.scor);
	int len = scor1.length();
	for (int i = 0; i <= len; i++)
		B.scor_change[i] = scor1[i];
	B.scor_change[len + 1] = '\0';

	outtextxy(400, 490, B.scor_change);//���ũ�����





}
/****************����ũ��Ľ�ҳ��ַ�*******************************/
void chenge_money_nongmin()  //�������Ľ��
{
	string scor1; //�������ת�����ַ���
	scor1 = to_string(B.money);
	int len1 = scor1.length();
	for (int i = 0; i <= len1; i++)
		B.money_change[i] = scor1[i];
	B.money_change[len1 + 1] = '\0';

	}

/****************��������Ľ�ҳ��ַ�*******************************/
void chenge_money_dizhu()
{

	string scor1; //�������ת�����ַ���
	scor1 = to_string(A.money);
	int len1 = scor1.length();
	for (int i = 0; i <= len1; i++)
		A.money_change[i] = scor1[i];
	A.money_change[len1 + 1] = '\0';


}

void clean_money_dizhu()  //��ʾ�������ǰ���Ȱ���ʾ�������һ��
{
	HRGN rgn1 = CreateRectRgn(95, 250,200, 230); //�������ͷ���·��ķ���
	setcliprgn(rgn1);
	clearcliprgn();
	setcliprgn(NULL);   //�ͷŵ�ǰ�ü�����


}
void clean_money_nongmin() //��ʾũ����ǰ���Ȱ���ʾ�������һ��
{

	HRGN rgn1 = CreateRectRgn(95, 530, 200, 500); //�������ͷ���·��ķ���
	setcliprgn(rgn1);
	clearcliprgn();
	setcliprgn(NULL);   //�ͷŵ�ǰ�ü�����



}