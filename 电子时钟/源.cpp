#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#pragma comment(lib,"winmm.lib")//音频

#define PI   3.1415926
double h, m, s;
double  x_h, x_m, x_s, y_h, y_m, y_s;
int count = 0;    //主界面用户按tab键的次数
int count2 = 0;   //闹钟界面用户按tab键的次数
int flag = 0;     //判断用户有没有设置闹钟的旗帜

void drawclock();  //画钟表的指针
void drawframe();  //画边框
void keyborad();   //键盘控制
void drawAlarm();  //绘制闹钟界面
void keyborad2();  //闹钟界面的键盘控制
void keyborad3();  //闹钟响的时候的键盘控制

int digithour(double h);			//将double型的小时数换成int型  
int digitmin(double m);				//将double型的分钟数换成int型  
int digitsec(double s);				//将double型的秒数换成int型
void digitclock(int x, int y, int clock);  //在指定位置显示数字时钟 

struct ti
{
	int ti_min;
	int ti_hour;
	int ti_sec;
};
struct ti t[1];            //存放现在正常的时间
struct ti a = { 0,0,0 };   //存放用户对时间的改变量
struct ti b = { 0,0,0 };   //存放用户对闹钟时间的改变量
struct ti c = { 0,0,0 };   //存放用户设置的闹钟


void main()
{
	initgraph(640, 480);
	keyborad();
}

//画边框
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
	}//时钟圆点
	for (i = 0, m = 0.0; i <= 59; m++, i++)
	{
		x = 100 * sin(m / 30 * PI) + 310;
		y = 200 - 100 * cos(m / 30 * PI);
		circle(x, y, 1);
	}
	//分针圆点
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
	settextstyle(15, 0, _T("宋体"));
	outtextxy(100, 170, _T("every day"));
	outtextxy(100, 200, _T("is the best"));
	outtextxy(450, 170, _T("每一天都是"));
	outtextxy(450, 200, _T("最好的日子。"));
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


//画钟表的指针
void drawclock()
{
	SYSTEMTIME xx;  // 定义变量保存当前时间 
	GetLocalTime(&xx);
	t[0].ti_hour = xx.wHour;
	t[0].ti_min = xx.wMinute;
	t[0].ti_sec = xx.wSecond;

	//设置当前系统时间   
	h = t[0].ti_hour + a.ti_hour;
	m = t[0].ti_min + a.ti_min;
	s = t[0].ti_sec + a.ti_sec;

	//绘制时针
	x_h = 50 * sin((h * 60 + m) / 360 * PI) + 310;/*时针的x坐标*/
	y_h = 200 - 50 * cos((h * 60 + m) / 360 * PI);/*时针的y坐标*/
	setcolor(RED);
	line(310, 200, x_h, y_h);

	//绘制分针
	x_m = 80 * sin(m / 30 * PI) + 310;/*分针的x坐标*/
	y_m = 200 - 80 * cos(m / 30 * PI);/*分针的y坐标*/
	setcolor(BLUE);
	line(310, 200, x_m, y_m);

	//绘制秒针
	x_s = 98 * sin(s / 30 * PI) + 310;/*秒针的x坐标值*/
	y_s = 200 - 98 * cos(s / 30 * PI);/*秒针的y坐标值*/
	setcolor(WHITE);
	line(310, 200, x_s, y_s);

	//电子时钟
	if (count == 1)
	{
		setcolor(RED);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		setcolor(WHITE);
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
	}
	else if (count == 2)
	{
		setcolor(RED);
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
	}
	else if (count == 3)
	{
		setcolor(RED);
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
	}
	else
	{
		setcolor(WHITE);
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
	}
}


//键盘控制
void keyborad()
{
	drawframe();
	while (TRUE)
	{
		clearcliprgn();  //清屏函数
		BeginBatchDraw();
		drawframe();   //画边框
		if (flag == 1)
		{
			keyborad3();
		}
		drawclock();   //画钟表的指针
		FlushBatchDraw();

		if (_kbhit())
		{
			char userkey;
			userkey = _getch();
			if (userkey == 9)       //用户按下tab键时
			{
				count++;
				if (count > 4)
				{
					count = count % 4;
				}
			}
			else if (count == 1 && userkey == 72) //上调小时
			{
				a.ti_hour++;
			}
			else if (count == 1 && userkey == 80) //下调小时
			{
				a.ti_hour--;
			}
			else if (count == 2 && userkey == 72) //上调分钟
			{
				a.ti_min++;
			}
			else if (count == 2 && userkey == 80) //下调分钟
			{
				a.ti_min--;
			}
			else if (count == 3 && userkey == 72) //上调秒数
			{
				a.ti_sec++;
			}
			else if (count == 3 && userkey == 80) //下调秒数
			{
				a.ti_sec--;
			}
			else if (userkey == 32)
			{
				initgraph(640, 480);
				keyborad2();
			}
			else if (userkey == 27)   //用户按下esc键时
			{
				exit(0);
			}
		}
	}
}


//画闹钟界面
void drawAlarm()
{
	//设置当前系统时间   
	c.ti_hour = t[0].ti_hour + b.ti_hour;
	c.ti_min = t[0].ti_min + b.ti_min;
	c.ti_sec = t[0].ti_sec + b.ti_sec;
	h = c.ti_hour;
	m = c.ti_min;
	s = c.ti_sec;
	//电子时钟
	if (count2 == 1)
	{
		setcolor(RED);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		setcolor(WHITE);
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
	}
	else if (count2 == 2)
	{
		setcolor(RED);
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
	}
	else if (count2 == 3)
	{
		setcolor(RED);
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
		setcolor(WHITE);
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
	}
	else
	{
		setcolor(WHITE);
		digitclock(356, 314, digitsec(s)); /*显示秒针值*/
		digitclock(260, 314, digithour(h));/*显示小时值*/
		digitclock(308, 314, digitmin(m)); /*显示分钟值*/
	}
	outtextxy(280, 100, "闹钟设置");
	int i, j;
	for (i = 290; i <= 335; i += 39)
	{
		for (j = 317; j <= 324; j += 7)
		{
			circle(i, j, 1);
		}
	}
}


//闹钟界面的键盘控制
void keyborad2()
{
	drawAlarm();
	while (TRUE)
	{
		clearcliprgn();  //清屏函数
		BeginBatchDraw();
		drawAlarm();     //绘制闹钟界面		
		FlushBatchDraw();
		if (_kbhit())
		{
			char userkey;
			userkey = _getch();
			if (userkey == 9)       //用户按下tab键时
			{
				flag = 1;
				count2++;
				if (count2 > 4)
				{
					count2 = count2 % 4;
				}
			}
			else if (count2 == 1 && userkey == 72) //上调小时
			{
				b.ti_hour++;
			}
			else if (count2 == 1 && userkey == 80) //下调小时
			{
				b.ti_hour--;
			}
			else if (count2 == 2 && userkey == 72) //上调分钟
			{
				b.ti_min++;
			}
			else if (count2 == 2 && userkey == 80) //下调分钟
			{
				b.ti_min--;
			}
			else if (count2 == 3 && userkey == 72) //上调秒数
			{
				b.ti_sec++;
			}
			else if (count2 == 3 && userkey == 80) //下调秒数
			{
				b.ti_sec--;
			}
			else if (userkey == 27)   //用户按下esc键时  返回主界面
			{
				keyborad();
			}
		}
	}
}



//闹钟的键盘控制
void keyborad3()
{
	SYSTEMTIME xx;  // 定义变量保存当前时间 
	GetLocalTime(&xx);
	t[0].ti_hour = xx.wHour;
	t[0].ti_min = xx.wMinute;
	t[0].ti_sec = xx.wSecond;

	if (t[0].ti_hour == c.ti_hour && t[0].ti_min == c.ti_min && t[0].ti_sec == c.ti_sec)
	{
		//清空旧闹钟内容
		flag = 0;
		b.ti_hour = 0;
		b.ti_min = 0;
		b.ti_sec = 0;
		mciSendString("open 闹钟2.wav alias alarm", nullptr, 0, nullptr);
		mciSendString("play alarm", nullptr, 0, nullptr);
		clearcliprgn();  //清屏函数
		BeginBatchDraw();
		drawAlarm();     //绘制闹钟界面		
		FlushBatchDraw();
		_getch();
		mciSendString("close alarm", nullptr, 0, nullptr);

	}
}

//在指定位置显示数字时钟   
void digitclock(int x, int y, int clock)
{
	char buffer1[3] = "";
	if (clock == 60)
		clock = 0;
	sprintf_s(buffer1, "%d", clock);  //文件方式    
	outtextxy(x, y, buffer1);         //文字输出 
}


//将double型的小时数换成int型  
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


//将double型的分钟数换成int型  
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


//将double型的秒数换成int型  
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
