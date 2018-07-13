#include<iostream>
#include"NewGraphics.h"
#include<winuser.h>
#include<windows.h>
#include<conio.h>
#define MAPWIDTH 25
#define MAPLENGTH 25
#define MAXLENGTH 20
#define SPEED_LOW 1000
#define SPEED_MEDIUM 500
#define SPEED_HIGH 100
using namespace std;

struct Snake
{
    int x[MAXLENGTH-1];
    int y[MAXLENGTH-1];
    int length;
}snake;
struct ToaDo
{
    int x;
    int y;
}food,duoi;
struct dichuyen
{
    int x;
    int y;
}step;
void khoitao();
void movesnake(dichuyen dc);
void drawfood();
void drawsnake();
bool checkKey(int key);
void loop();
void drawmap();
void drawgame();
bool GameOver;
void khoitao()
{
    GameOver=false;
    //khoi tao vi tri ban dau cua ran
    snake.length=3;
    snake.x[0]=10;
    snake.x[1]=9;
    snake.x[2]=8;
    snake.y[0]=10;
    snake.y[1]=10;
    snake.y[2]=10;
    //huong di chuyen ban dau sang phai
    step.x=1;
    step.y=0;
    //khoi tao food
    food.x=15;
    food.y=15;
}
void movesnake(dichuyen dc)
{
    duoi.x=snake.x[snake.length-1];
    duoi.y=snake.y[snake.length-1];
    for (int i=snake.length-1;i>=0;i--)
    {
        if (i==0)
        {
            snake.x[0]+=dc.x;
            snake.y[0]+=dc.y;
        }
        else
        {
            snake.x[i]=snake.x[i-1];
            snake.y[i]=snake.y[i-1];
        }


    }
    //xu li khi ran qua tuong
    if (snake.x[0] >= MAPWIDTH) snake.x[0] = 1;
	if (snake.x[0] < 1) snake.x[0] = MAPWIDTH - 1;
	if (snake.y[0] >= MAPLENGTH) snake.y[0] = 1;
	if (snake.y[0] < 1) snake.y[0] = MAPLENGTH - 1;

	//xu li an food
	if (snake.x[0] == food.x && snake.y[0] == food.y) {
		snake.length++;
		snake.x[snake.length-1]=duoi.x;
		snake.y[snake.length-1]=duoi.y;

        food.x = 1+rand() % (MAPWIDTH-1);
		food.y = 1+rand() % (MAPLENGTH-1);
	}
}
void drawfood()
{
    gotoxy(food.x,food.y);
    cout<<"o";
}
void drawsnake()
{
    for (int i = 0; i < snake.length; i++) {
		gotoxy(snake.x[i], snake.y[i]);
		cout<<"x";
	}
}
bool checkKey(int key)
{
    return GetAsyncKeyState(key);
}
void loop()
{

    if (checkKey(VK_LEFT)) {
    if (step.x != 1) {
        step.x = -1; step.y = 0;
    }
    }
	else if (checkKey(VK_RIGHT)) {
    if (step.x != -1) {
        step.x = 1; step.y = 0;
    }
	}
	else if (checkKey(VK_UP)) {
    if (step.y != 1) {
        step.y = -1; step.x = 0;
    }
	}
	else if (checkKey(VK_DOWN)) {
    if (step.y != -1) {
        step.y = 1; step.x = 0;
    }
	}

	if (checkKey(VK_ESCAPE)) {
		GameOver = true;
	}
	movesnake(step);
	 //check can phai duoi
    for (int i=0;i<snake.length;i++)
    if (i != 0 && (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])) GameOver = true;
    //xoa duoi
    gotoxy(duoi.x,duoi.y);
    cout<<" ";
}
void drawmap()
{
      for (int i=0;i<=MAPLENGTH;i++)
      {
          if (i==0)
          {
              for (int j=0;j<=MAPWIDTH;j++)
                cout<<"#";
              cout<<endl;
          }
          else if (i==MAPLENGTH)
            for (int j=0;j<=MAPWIDTH;j++) cout<<"#";
          else
          {
              cout<<"#";
              for (int j=0;j<=MAPLENGTH-2;j++) cout<<" ";
              cout<<"#"<<endl;
          }
      }
}
void drawgame()
{
    drawfood();
    drawsnake();
    gotoxy(30,15);
    cout<<"SCORE:"<<snake.length-3;
}
int main()
{
    cls(hCon);
    drawmap();
    khoitao();
    ShowCur(false);//an con tro
    while(!GameOver)
    {
        loop();
        drawgame();
        Sleep(SPEED_HIGH);
    }
    cls(hCon);
    cout<<"GAME OVER!";
    Sleep(5000);
    return 0;

}
