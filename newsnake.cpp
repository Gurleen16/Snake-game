#include<vector>
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
char board[20][80];
static int length=4;
class food
{
    public:
    int x;
    int y;
    char value;
    void create_Food()
		{
			x=rand()%20;
			y=rand()%80;
			value='@';
			if(x==0 || x==19 || y==0 || y==79)
			{
				create_Food();
			}
			else
				insert_Food();
		}
		void insert_Food()
		{
			board[x][y]='@';
		}
};
class snake
{
    public:
    int x;
    int y;
    char value;
    void create_snake(int a,int b,char val)
    {
        x=a;
        y=b;
        value=val;
    }
    void insert_snake(vector<snake> &s)
    {
        int i;
        for(i=0;i<length;i++)
        board[s[i].x][s[i].y]=s[i].value;
    }

};
vector<snake>s;
void modifySnake(vector<snake>&s)
{
	s[length-1].value='#';
	length++;
	snake s1;
	s1.x=s[length-1].x;
	s1.y=s[length-1].y;
	s1.value='T';
	s.push_back(s1);
}

int move_snake(char c)
{

	for(int i=length-2;i>=0;i--)
	{
		s[i+1].x=s[i].x;
		s[i+1].y=s[i].y;
	}
	if(c=='u')
	{
		s[0].x-=1;
	}
	else if(c=='l')
	{
		s[0].y-=1;
	}
	else if(c=='r')
	{
		s[0].y+=1;
	}
	else if(c=='d')
	{
		s[0].x+=1;
	}
    if(board[s[0].x][s[0].y]=='#'|| board[s[0].x][s[0].y]=='T' )
	{
		return -1;
	}
	else
	{
		return 0;
	}

}

void make_board()
{
    int i;
    for(i=0;i<80;i++)
        board[0][i]='*';
    for(i=0;i<80;i++)
        board[19][i]='*';
    for(i=0;i<20;i++)
        board[i][0]='*';
    for(i=0;i<20;i++)
        board[i][79]='*';
}
void makeBoardNull()
{
	for(int i=1;i<19;i++)
	{
		for(int j=1;j<79;j++)
		{
			board[i][j]='\0';
		}
	}
}
void show_board()
{
    int i,j,x;
    for(i=0;i<20;i++)
    {
        for(j=0;j<80;j++)
            {
                cout<<board[i][j];
            }
        cout<<endl;
    }
}
void checkCorners()
{
	if(s[0].x==0)
	{
		s[0].x=18;
	}
	else if(s[0].x==19)
	{
		s[0].x=1;
	}
	else if(s[0].y==79)
	{
		s[0].y=1;
	}
	else if(s[0].y==0)
	{
		s[0].y=78;
	}
}

int main()
{
    int i;
    char ch;
    food f;
    snake d;
    cout<<"Welcome!!!"<<endl<<"Press Y for starting game and N for exit"<<endl;
    cin>>ch;
    if(ch=='Y'||ch=='y')
        system("cls");
    else
    {
        cout<<"Thanks for playing!!!"<<endl;
        return 0;
    }
    makeBoardNull();
    make_board();
    for(i=0;i<4;i++)
	{
		 if(i==0)
		 {
			 d.create_snake(4,4+i,'H');
		 }
		 else if(i==3)
		 {
            d.create_snake(4,4+i,'T');
         }
		 else
		 {
            d.create_snake(4,4+i,'#');
         }
		 s.push_back(d);
	}
    d.insert_snake(s);
    f.create_Food();
    show_board();
    char move;
    cout<<"Press r for right, l for left, u for up and d for down"<<endl;
    cin>>move;
    int k;
    while(!_kbhit())
    {
        system("cls");
        k=move_snake(move);
        if(k==-1)
        {
            cout<<"Game over!!!"<<endl<<"You lose!!!"<<endl;
            break;
        }

        checkCorners();
        make_board();
        makeBoardNull();
		f.insert_Food();
        d.insert_snake(s);
        show_board();
        if(s[0].x==f.x && s[0].y==f.y)
        {
            modifySnake(s);
            f.create_Food();
        }
        move=getch();
        if((int)move==27)
        {
            cout<<"Game over!!!";
            break;
        }
    }

}
