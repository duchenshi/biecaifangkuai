#include<graphics.h>
#include<WinUser.h>
#include<conio.h>
#include"CDontTouchWhiteBlock.h"

CDontTouchWhiteBlock game(300, 400);
void Paint();
DWORD WINAPI ThreadProc(LPVOID lParam);

int main()
{
	initgraph(300, 400);


	MOUSEMSG msg;
	msg = GetMouseMsg();
	Paint();
	while (msg.uMsg != WM_LBUTTONDOWN)
	{
		msg = GetMouseMsg();
	}
	game.PointAt(msg.x, msg.y);
	CreateThread(0, 0, ThreadProc, 0, 0, 0);//线程要放在第一次采集鼠标信息之后。不然线程不起作用，不知道为啥。。
	while (game.IsOver() != true)
	{
		game.Move(5);
		Paint();
		Sleep(100);
	}

	_getch();
	closegraph();
	system("pause");
	return 0;
}

void Paint()
{
	IMAGE img(300, 500);
	SetWorkingImage(&img);
	setlinecolor(RGB(0, 0, 0));

	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			switch (game.map[r][c])
			{
			case BlackBlock:
				setfillcolor(RGB(0, 0, 0));
				break;
			case WhiteBlock:
				setfillcolor(RGB(255, 255, 255));
				break;
			case PassBlock:
				setfillcolor(RGB(0, 0, 255));
				break;
			}
			fillrectangle(c * 75, r * 100, c * 75 + 75, r * 100 + 100);
		}
	}
	SetWorkingImage();
	putimage(0, game.GetOffet() - 100, &img);
}

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	while (game.IsOver() != true)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			game.PointAt(msg.x, msg.y);
			//void invalidate();
		}
	}
	return 0;
}