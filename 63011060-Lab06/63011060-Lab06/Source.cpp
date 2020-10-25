#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(7, 0);
	printf("^");
}
void del(int a, int b)
{
	gotoxy(a, b);
	setcolor(8, 0);
	printf("     ");
}
void delbullet(int a, int b)
{
	gotoxy(a, b);
	setcolor(8, 0);
	printf(" ");
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
void random() {
	int a, b;
	do {
		a = 10 + (rand() % (70 - 10));
		b = 2 + (rand() % (5 - 2));
	} while (cursor(a, b) == '*');
	gotoxy(a, b);
	printf("*");
}
int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int walk = 0; //0 = no walk
	int bullet = 0;
	int i, o;
	int score = 0;
	int star;
	srand(time(NULL));
	for (int star = 0; star < 20; star++) {
		random();
	}
	setcursor(0);
	draw_ship(x, y);
	do {
		gotoxy(65, 0);
		setcolor(3, 0);
		printf("Score : %d", score);
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') walk = 1;
			if (ch == 'd') walk = 2;
			if (ch == 's') walk = 0;
			if (ch == ' ' && bullet != 1)
			{
				bullet = 1;
				i = x + 2;
				o = y - 1;
			}
		}
		if (walk == 1 && x > 0)
		{
			del(x, y);
			draw_ship(--x, y);
		}
		if (walk == 2 && x < 75)
		{
			del(x, y);
			draw_ship(++x, y);
		}
		if (bullet == 1)
		{
			delbullet(i, o);
			if (o == 0)
			{
				bullet = 0;
			}
			if (o > 0) {
				if (cursor(i, o - 1) != '*') {
					draw_bullet(i, --o);
				}
				else {
					gotoxy(i, o - 1);
					printf(" ");
					bullet = 0;
					Beep(700, 200);
					random();
					score++;
				}
			}
		}
		fflush(stdin);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}