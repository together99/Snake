#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include<time.h>

#define Key_Up 'w' // 向上方向键 　　
#define Key_Down 's' // 向下方向键
#define Key_Right 'd' // 向右方向键
#define Key_Left 'a'  // 向左方向键
#define Key_Space ' ' //暂停键 

#define R 1           //向右的状态量 
#define L 2           //向左的状态量 
#define U 3           //向上的状态量 
#define D 4           //向下的状态量 



typedef struct node //蛇节点的结构体 
{
    int x;
    int y;
    struct node*next;
}snake;

snake *head; //蛇的头指针 
int score=0;  //游戏分数 
int endgamestatus=0;  //结束游戏的状态 
int food_x,food_y; //食物坐标 
int status=R;//蛇状态变量 
int key=Key_Right; //用户输入的方向 



void Pos(int x,int y);//光标定位函数 
void Crat_Map();//生成地图 
void Crosswall();//判断蛇是否撞到墙壁 
int  Bit_Self();//判断蛇头是否与蛇身有接触 
void Creat_Food();//生成食物
void Snake_Moving();//蛇身移动 
void gamecircle();// 游戏循环 
void endgame();//退出游戏函数 
void pause();//游戏暂停 

/* -------------------------------------------*/ 

void Pos(int x,int y) //光标定位 
{
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}


void Creat_Map() //产生边界 
{
	int i,j;
	for(i=0;i<27;i++)
	{
		Pos(0,i);  printf("#");
		Pos(54,i);  printf("#");
		
	}
	for(i=0;i<55;i++)
	{
		Pos(i,0);printf("#");
		Pos(i,26);printf("#");
	}
}


void Init_Snake() //初始化蛇 
{
	int i;
	snake *p,*q;
	head=(snake *)malloc(sizeof(snake));
	head->x=28;
	head->y=5;
	head->next=NULL;
	
	p=head;
	for(i=1;i<4;i++)
	{
		q=(snake *)malloc(sizeof(snake));
		q->x=28-i;
		q->y=5;
		p->next=q;
		p=p->next;
		
	}
	
	p->next=NULL;
	p=head;
	while(p)
	{
		Pos(p->x,p->y);
		printf("#");
		p=p->next;
	}
		 
} 

int  Bit_Self() //判断是否咬到自己 
{
	snake *p;
	int isbit=0;
    p=head->next;
    while(p)
    {
        if(p->x==head->x&&p->y==head->y)
        {
        	isbit=1;
        	break;
        }	
        p=p->next;
    }
    if(isbit==1)
    {
    	endgamestatus=2;
        endgame();
    }
}


void Crosswall() //判断是否撞墙 
{
    if(head->x==0||head->y==0||head->x==54||head->y==26)
    {
    	endgamestatus=1;
    	endgame();
    }
}


void Creat_Food()//产生食物 
{
    srand(time(NULL));
    food_x=rand()%48+2;
    food_y=rand()%21+2;
    Pos(food_x,food_y);
    printf("#");
}



void Snake_Moving()  //蛇的移动 
{
    snake *newhead,*p;
    newhead=(snake*)malloc(sizeof(snake));
    
    if(status==R)//向右走 
    {
        if((head->x)+1==food_x && head->y==food_y)//判断是否吃到食物 
        {
            score=score+10;
            newhead->x=head->x+1;
            newhead->y=head->y;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                Pos(p->x,p->y);
                printf("#");
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
        	newhead->x=head->x+1;
        	newhead->y=head->y;
        	newhead->next=head;
        	head=newhead;
        	p=head;
        	while(p->next->next)
        	{
            	Pos(p->x,p->y);
            	printf("#");
            	p=p->next;
        	}
        	Pos(p->x,p->y);
            printf("#");
        	Pos(p->next->x,p->next->y);
        	printf(" ");
        	free(p->next);
        	p->next=NULL;
        }
    }
    
    if(status==L)  //向左走 
    {
        if((head->x)-1==food_x && head->y==food_y)
        {
            score=score+10;
            newhead->x=head->x-1;
            newhead->y=head->y;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                Pos(p->x,p->y);
                printf("#");
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
        	newhead->x=head->x-1;
        	newhead->y=head->y;
        	newhead->next=head;
        	head=newhead;
        	p=head;
        	while(p->next->next)
        	{
            	Pos(p->x,p->y);
            	printf("#");
            	p=p->next;
        	}
        	Pos(p->x,p->y);
            printf("#");
        	Pos(p->next->x,p->next->y);
        	printf(" ");
        	free(p->next);
        	p->next=NULL;
        }
    }
    
    
    if(status==U)  //向上走 
    {
        if((head->x)==food_x && (head->y)+1==food_y)
        {
            score=score+10;
            newhead->x=head->x;
            newhead->y=head->y-1;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                Pos(p->x,p->y);
                printf("#");
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
        	newhead->x=head->x;
        	newhead->y=head->y-1;
        	newhead->next=head;
        	head=newhead;
        	p=head;
        	while(p->next->next)
        	{
            	Pos(p->x,p->y);
            	printf("#");
            	p=p->next;
        	}
        	Pos(p->next->x,p->next->y);
        	printf(" ");
        	free(p->next);
        	p->next=NULL;
        }
    }
     
    
    if(status==D)  //向下走 
    {
        if((head->x)==food_x && (head->y)+1==food_y)
        {
            score=score+10;
            newhead->x=head->x;
            newhead->y=head->y+1;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                Pos(p->x,p->y);
                printf("#");
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
        	newhead->x=head->x;
        	newhead->y=head->y+1;
        	newhead->next=head;
        	head=newhead;
        	p=head;
        	while(p->next->next)
        	{
            	Pos(p->x,p->y);
            	printf("#");
            	p=p->next;
        	}
        	Pos(p->next->x,p->next->y);
        	printf(" ");
        	free(p->next);
        	p->next=NULL;
        }
    }
    
    
    Crosswall();   //判断是否撞墙 
    Bit_Self();    //判断是否咬到自己 
     
}



void pause()  //暂停 
{   
    while(1)
    {
        if(key=getch()==' ')
        break;
     } 
}

void endgame()
{
    system("cls");  //清屏 
    Pos(27,13);
    if(endgamestatus==1)
    printf("您撞到墙了");
    if(endgamestatus==2)
    printf("您咬到了自己");
    Pos(27,14);
    printf("您的得分为%d",score);
    exit(0);
}


void welcome()
{
	Pos(27,8);
	printf("##  代码作者：together  ##");
    Pos(27,13);
    printf("欢迎来到贪吃蛇游戏");
    system("pause");
    system("cls");
    Pos(50,9);
    printf("欢迎大家对源代码进行修改");
    Pos(50,11);
    printf("开发出更多好玩的玩法");
    Pos(50,12);
    system("pause");
    system("cls");
}

void gamecircle()
{
    Pos(57,4);
    printf("操作说明");
    Pos(57,5);
    printf("w a s d分别对应上 左 下 右 ");
    Pos(57,6);
    printf("按空格键暂停");   
    while(1)
    {   
        Pos(57,7);
    	printf("游戏分数:%d",score);
        if(kbhit())
        	key=getch();
    
        switch(key)
            {
                case Key_Right:
                    if(status!=L)   //向左移动的时候无法向右移动 
                        status=R;
                    break;
                case Key_Left:
                    if(status!=R)  //与上同理 
                        status=L;
                    break;
                case Key_Up:
                    if(status!=D)
                        status=U;
                    break;
                case Key_Down:
                    if(status!=U)
                        status=D;
                    break;
                case Key_Space:
                    pause();
                    break;
                default:
                break;
            }
        Sleep(400);
        Snake_Moving();
    }
}


int main()
{
	welcome();
    Creat_Map();
    Creat_Food();
    Init_Snake();
    gamecircle();
}
