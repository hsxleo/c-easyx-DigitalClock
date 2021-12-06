#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")//��Ƶ

#define PI   3.1415926
double h, m, s;
double  x_h, x_m, x_s, y_h, y_m, y_s;
int count = 0;    //�������û���tab���Ĵ���
int count2 = 0;   //���ӽ����û���tab���Ĵ���
int flag = 0;     //�ж��û���û���������ӵ�����

void drawclock();  //���ӱ��ָ��
void drawframe();  //���߿�
void keyborad();   //���̿���
void drawAlarm();  //�������ӽ���
void keyborad2();  //���ӽ���ļ��̿���
void keyborad3();  //�������ʱ��ļ��̿���

int digithour(double h);			//��double�͵�Сʱ������int��  
int digitmin(double m);				//��double�͵ķ���������int��  
int digitsec(double s);				//��double�͵���������int��
void digitclock(int x, int y, int clock);  //��ָ��λ����ʾ����ʱ�� 

struct ti
{
	int ti_min;
	int ti_hour;
	int ti_sec;
};
struct ti t[1];            //�������������ʱ��
struct ti a = { 0,0,0 };   //����û���ʱ��ĸı���
struct ti b = { 0,0,0 };   //����û�������ʱ��ĸı���
struct ti c = { 0,0,0 };   //����û����õ�����


void main()
{
	initgraph(640, 480);
	keyborad();
}

//���߿�
void drawframe()
{
	int i, j;
	double x, y;
	line(82, 430, 558, 430);
	line(70, 62, 70, 418);
	line(82, 50, 558, 50);
	line(570, 62, 570, 418);
	line(70, 62, 570, 62);
	line(310, 48, 310, 35);
	outtextxy(290, 18, "CLOCK");
	arc(70, 50, 94, 74, 89, 179);
	arc(550, 50, 570, 74, 0, 90);
	setcolor(0xC0C0C0);
	rectangle(270, 15, 350, 35);
	setcolor(0x800080);
	rectangle(270, 350, 350, 370);
	setcolor(0xFCFCFC);
	for (i = 290; i <= 335; i += 39)
	{
		for (j = 317; j <= 324; j += 7)
		{
			circle(i, j, 1);
		}
	}
	for (i = 0, m = 0.0, h = 0.0; i <= 11; i++, h++)
	{
		x = 100 * sin((h * 60 + m) / 360 * PI) + 310;
		y = 200 - 100 * cos((h * 60 + m) / 360 * PI);
		circle(x, y, 1);
	}//ʱ��Բ��
	for (i = 0, m = 0.0; i <= 59; m++, i++)
	{
		x = 100 * sin(m / 30 * PI) + 310;
		y = 200 - 100 * cos(m / 30 * PI);
		circle(x, y, 1);
	}
	//����Բ��
	setlinestyle(PS_DASHDOT);
	line(70, 418, 82, 430);
	setlinestyle(PS_DASHDOT);
	line(570, 418, 558, 430);
	setcolor(0xFCFCFC);
	outtextxy(120, 340, "Tab :Cursor move");
	outtextxy(120, 370, "Up  :Time + +");
	outtextxy(370, 340, "Down:Time - -");
	outtextxy(370, 370, "Esc :Quit system!");
	outtextxy(292, 352, "HELP");
	settextstyle(15, 0, _T("����"));
	outtextxy(100, 170, _T("every day"));
	outtextxy(100, 200, _T("is the best"));
	outtextxy(450, 170, _T("ÿһ�춼��"));
	outtextxy(450, 200, _T("��õ����ӡ�"));
	for (i = 0; i < 12; i++)
	{
		x = 310 + (int)(105 * sin(30 * i * 2 * PI / 360));
		y = 200 - (int)(105 * cos(30 * i * 2 * PI / 360));
		switch (i)
		{
		case 0:outtextxy(x - 5, y - 5, "12"); break;
		case 1:outtextxy(x - 5, y - 5, "1"); break;
		case 2:outtextxy(x - 5, y - 5, "2"); break;
		case 3:outtextxy(x - 5, y - 5, "3"); break;
		case 4:outtextxy(x - 5, y - 5, "4"); break;
		case 5:outtextxy(x - 5, y - 5, "5"); break;
		case 6:outtextxy(x - 5, y - 5, "6"); break;
		case 7:outtextxy(x - 5, y - 5, "7"); break;
		case 8:outtextxy(x - 5, y - 5, "8"); break;
		case 9:outtextxy(x - 5, y - 5, "9"); break;
		case 10:outtextxy(x - 5, y - 5, "10"); break;
		case 11:outtextxy(x - 5, y - 5, "11"); break;
		}
	}
	int a, b, a1, b1, n = 0;
	for (n = 0; n < 60; n++)
	{
		a = 310 + (int)(95 * sin(n * 2 * PI / 60));
		b = 200 - (int)(95 * cos(n * 2 * PI / 60));
		a1 = 310 + (int)(85 * sin(n * 2 * PI / 60));
		b1 = 200 - (int)(85 * cos(n * 2 * PI / 60));
		if (n % 5 == 0)
			setlinestyle(PS_DASHDOT);
		else
			setlinestyle(PS_DASHDOT);
		line(a1, b1, a, b);
	}
}


//���ӱ��ָ��
void drawclock()
{
	SYSTEMTIME xx;  // ����������浱ǰʱ�� 
	GetLocalTime(&xx);
	t[0].ti_hour = xx.wHour;
	t[0].ti_min = xx.wMinute;
	t[0].ti_sec = xx.wSecond;

	//���õ�ǰϵͳʱ��   
	h = t[0].ti_hour + a.ti_hour;
	m = t[0].ti_min + a.ti_min;
	s = t[0].ti_sec + a.ti_sec;

	//����ʱ��
	x_h = 50 * sin((h * 60 + m) / 360 * PI) + 310;/*ʱ���x����*/
	y_h = 200 - 50 * cos((h * 60 + m) / 360 * PI);/*ʱ���y����*/
	setcolor(RED);
	line(310, 200, x_h, y_h);

	//���Ʒ���
	x_m = 80 * sin(m / 30 * PI) + 310;/*�����x����*/
	y_m = 200 - 80 * cos(m / 30 * PI);/*�����y����*/
	setcolor(BLUE);
	line(310, 200, x_m, y_m);

	//��������
	x_s = 98 * sin(s / 30 * PI) + 310;/*�����x����ֵ*/
	y_s = 200 - 98 * cos(s / 30 * PI);/*�����y����ֵ*/
	setcolor(WHITE);
	line(310, 200, x_s, y_s);

	//����ʱ��
	if (count == 1)
	{
		setcolor(RED);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		setcolor(WHITE);
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
	}
	else if (count == 2)
	{
		setcolor(RED);
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
	}
	else if (count == 3)
	{
		setcolor(RED);
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
	}
	else
	{
		setcolor(WHITE);
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
	}
}


//���̿���
void keyborad()
{
	drawframe();
	while (TRUE)
	{
		clearcliprgn();  //��������
		BeginBatchDraw();
		drawframe();   //���߿�
		if (flag == 1)
		{
			keyborad3();
		}
		drawclock();   //���ӱ��ָ��
		FlushBatchDraw();

		if (_kbhit())
		{
			char userkey;
			userkey = _getch();
			if (userkey == 9)       //�û�����tab��ʱ
			{
				count++;
				if (count > 4)
				{
					count = count % 4;
				}
			}
			else if (count == 1 && userkey == 72) //�ϵ�Сʱ
			{
				a.ti_hour++;
			}
			else if (count == 1 && userkey == 80) //�µ�Сʱ
			{
				a.ti_hour--;
			}
			else if (count == 2 && userkey == 72) //�ϵ�����
			{
				a.ti_min++;
			}
			else if (count == 2 && userkey == 80) //�µ�����
			{
				a.ti_min--;
			}
			else if (count == 3 && userkey == 72) //�ϵ�����
			{
				a.ti_sec++;
			}
			else if (count == 3 && userkey == 80) //�µ�����
			{
				a.ti_sec--;
			}
			else if (userkey == 32)
			{
				initgraph(640, 480);
				keyborad2();
			}
			else if (userkey == 27)   //�û�����esc��ʱ
			{
				exit(0);
			}
		}
	}
}


//�����ӽ���
void drawAlarm()
{
	//���õ�ǰϵͳʱ��   
	c.ti_hour = t[0].ti_hour + b.ti_hour;
	c.ti_min = t[0].ti_min + b.ti_min;
	c.ti_sec = t[0].ti_sec + b.ti_sec;
	h = c.ti_hour;
	m = c.ti_min;
	s = c.ti_sec;
	//����ʱ��
	if (count2 == 1)
	{
		setcolor(RED);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		setcolor(WHITE);
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
	}
	else if (count2 == 2)
	{
		setcolor(RED);
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
	}
	else if (count2 == 3)
	{
		setcolor(RED);
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
	}
	else
	{
		setcolor(WHITE);
		digitclock(356, 314, digitsec(s)); /*��ʾ����ֵ*/
		digitclock(260, 314, digithour(h));/*��ʾСʱֵ*/
		digitclock(308, 314, digitmin(m)); /*��ʾ����ֵ*/
	}
	outtextxy(280, 100, "��������");
	int i, j;
	for (i = 290; i <= 335; i += 39)
	{
		for (j = 317; j <= 324; j += 7)
		{
			circle(i, j, 1);
		}
	}
}


//���ӽ���ļ��̿���
void keyborad2()
{
	drawAlarm();
	while (TRUE)
	{
		clearcliprgn();  //��������
		BeginBatchDraw();
		drawAlarm();     //�������ӽ���		
		FlushBatchDraw();
		if (_kbhit())
		{
			char userkey;
			userkey = _getch();
			if (userkey == 9)       //�û�����tab��ʱ
			{
				flag = 1;
				count2++;
				if (count2 > 4)
				{
					count2 = count2 % 4;
				}
			}
			else if (count2 == 1 && userkey == 72) //�ϵ�Сʱ
			{
				b.ti_hour++;
			}
			else if (count2 == 1 && userkey == 80) //�µ�Сʱ
			{
				b.ti_hour--;
			}
			else if (count2 == 2 && userkey == 72) //�ϵ�����
			{
				b.ti_min++;
			}
			else if (count2 == 2 && userkey == 80) //�µ�����
			{
				b.ti_min--;
			}
			else if (count2 == 3 && userkey == 72) //�ϵ�����
			{
				b.ti_sec++;
			}
			else if (count2 == 3 && userkey == 80) //�µ�����
			{
				b.ti_sec--;
			}
			else if (userkey == 27)   //�û�����esc��ʱ  ����������
			{
				keyborad();
			}
		}
	}
}



//���ӵļ��̿���
void keyborad3()
{
	SYSTEMTIME xx;  // ����������浱ǰʱ�� 
	GetLocalTime(&xx);
	t[0].ti_hour = xx.wHour;
	t[0].ti_min = xx.wMinute;
	t[0].ti_sec = xx.wSecond;

	if (t[0].ti_hour == c.ti_hour && t[0].ti_min == c.ti_min && t[0].ti_sec == c.ti_sec)
	{
		//��վ���������
		flag = 0;
		b.ti_hour = 0;
		b.ti_min = 0;
		b.ti_sec = 0;
		mciSendString("open ����2.wav alias alarm", nullptr, 0, nullptr);
		mciSendString("play alarm", nullptr, 0, nullptr);
		clearcliprgn();  //��������
		BeginBatchDraw();
		drawAlarm();     //�������ӽ���		
		FlushBatchDraw();
		_getch();
		mciSendString("close alarm", nullptr, 0, nullptr);

	}
}

//��ָ��λ����ʾ����ʱ��   
void digitclock(int x, int y, int clock)
{
	char buffer1[3] = "";
	if (clock == 60)
		clock = 0;
	sprintf_s(buffer1, "%d", clock);  //�ļ���ʽ    
	outtextxy(x, y, buffer1);         //������� 
}


//��double�͵�Сʱ������int��  
int digithour(double h)
{
	while (h > 24)
	{
		h -= 24;
	}
	while (h < 0)
	{
		h += 24;
	}
	int i;
	for (i = 0; i < 24; i++)
	{
		if (h == i) return i;
	}
}


//��double�͵ķ���������int��  
int digitmin(double m)
{
	while (m > 60)
	{
		m -= 60;
	}
	while (m < 0)
	{
		m += 60;
	}
	int i;
	for (i = 0; i < 60; i++)
	{
		if (m == i) return i;
	}
}


//��double�͵���������int��  
int digitsec(double s)
{
	while (s > 60)
	{
		s -= 60;
	}
	while (s < 0)
	{
		s += 60;
	}
	int i;
	for (i = 0; i < 60; i++)
	{
		if (s == i) return i;
	}
}
