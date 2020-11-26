#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void drawShip(int x,int y);
void gotoxy(int, int);
void eraseShip(int, int);
void setcursor(bool visible);
void setColorBg(int, int);
void drawBullet(int, int);
void eraseBullet(int, int);
void drawStar(int, int);
void eraseStar(int, int);
void score(int);
char cursor(int, int);
int main()
{
	setcursor(0);
	int x = 38, y = 20, s = 0;
	int sx, sy;
	char ch = ' ', direction = 'r', shoot = 'f',shootLimit = 0,beepLimit=0;
	int starStatus = 0;
	int shootStatus[5] = { 0,0,0,0,0 };
	int shootX[5] = { 0,0,0,0,0 };
	int shootY[5] = { 0,0,0,0,0 };
	srand(time(NULL));
	drawShip(x, y);
	for (; starStatus < 20; starStatus++) {
		sx = rand() % 60 + 10;
		sy = rand() % 5 + 1;
		if (cursor(sx, sy) == '*') { continue; }
		setColorBg(7, 0);
		drawStar(sx, sy);
	}
	do {
		if (_kbhit()) {
			ch = _getch();
			//direction variables
			if (ch == 'a') { direction = 'l'; }
			if (ch == 'd') { direction = 'r'; }
			if (ch == 'w') {
				if (y > 15)
				{
					eraseShip(x, y);
					drawShip(x, --y);
				}
				else {
					drawShip(x, y);
				}
			}
			if (ch == 's') {
				if (y < 24) {
					eraseShip(x, y);
					drawShip(x, ++y);
				}
				else
				{
					drawShip(x, y);
				}
			}
			//bullet control
			if (ch == ' ') {
				if (shootLimit < 5)
				{
					for (int i = 0; i < 5; i++)
					{
						if (shootStatus[i] == 0) 
						{
							shootLimit++;
							shootStatus[i] = 1;
							//Coord of bullet
							shootX[i] = x;
							shootY[i] = y - 2;
							break;
						}
 					}
					shoot = 't';					
				}
				if (beepLimit < 5)
				{
					Beep(1500, 20);
					beepLimit++;
				}
				
			}
			fflush(stdin);
		}
		// Direction control
		if (direction == 'l')
		{
			if (x > 0)
			{
				eraseShip(x,y); drawShip(--x, y);
			}
			else
			{
				drawShip(x, y);
			}	
		}
		if (direction == 'r')
		{
			if (x < 70)
			{
				eraseShip(x, y); drawShip(++x, y);
			}
			else
			{
				drawShip(x, y);
			}
		}
		
		// Bullet shoot
		if (shoot == 't') 
		{		
			for (int i = 0; i < 5; i++)
			{
				if (shootStatus[i] == 1) {
					eraseBullet(shootX[i] + 3, shootY[i] + 1);
					if (shootY[i] <= -1) {
						shootLimit--;
						beepLimit--;
						if (shootLimit < 0) {
							shootLimit = 0;
						}
						eraseBullet(shootX[i] + 3, shootY[i] + 1);
						if (beepLimit < 0)
						{
							beepLimit = 0;
						}
						shootStatus[i] = 0;
					}
					else
					{
						if (cursor(shootX[i] + 3, shootY[i]) == '*')
						{
							Beep(200, 100);
							shootLimit--;
							if (shootLimit < 0) {
								shootLimit = 0;
								beepLimit--;
							}
							eraseBullet(shootX[i] + 3, shootY[i] );
							shootY[i] = shootY[i] - 1;
							s++;
							beepLimit--;
							shootStatus[i] = 0;
							drawStar(rand() % 60 + 10, rand() % 5 + 1);
						}
						else {
							drawBullet(shootX[i] + 3, shootY[i]);
							shootY[i] = shootY[i] - 1;
						}
					}
				}
			}
		}
		Sleep(35);
		score(s);
	} while (ch != 'x');
		return 0;
}
void gotoxy(int x, int y)
{
	COORD c = {x,y};
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void drawShip(int x, int y)
{
	setColorBg(7, 5);
	gotoxy(x, y);
	printf(" <-0-> ");
}
void eraseShip(int x,int y)
{
	gotoxy(x, y);
	setColorBg(2, 0);
	printf("       ");	
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setColorBg(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void drawBullet(int x, int y)
{
	setColorBg(0, 6);
	gotoxy(x, y);
	printf("^");
}
void eraseBullet(int x, int y)
{
	gotoxy(x, y);
	setColorBg(2, 0);
	printf(" ");
}
void drawStar(int x, int y)
{
	setColorBg(7, 0);
	gotoxy(x, y); printf("*");
}
void eraseStar(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void score(int x)
{
	gotoxy(81, 0);
	setColorBg(9, 0);
	printf("Score : %d", x);
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
