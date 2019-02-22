#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;
char pos='1';
struct food
{
    int x,y;
    char ch;
};
struct snake
{
    int x,y;
    char ch;
    struct snake *next;
};
void incr(struct snake *s);
void change(struct snake *s,char c);
void genfood(struct food *f);
void crbox(char board[20][80],struct snake *s,struct food *f);
void incr(struct snake *s)
{
    struct snake *temp=(struct snake *)malloc(sizeof(struct snake));
    temp->x=s->x;
    temp->y=s->y;
    temp->ch='#';
    temp->next=s->next;
    s->next=temp;
    change(s,pos);
}
void change(struct snake *s,char c)
{
    int a=0,b=0,p,q,r,t;
    struct snake *temp=s;
    if(pos=='1'&&c=='3')
        c='1';
    else if(pos=='3'&&c=='1')
        c='3';
    else if(pos=='2'&&c=='5')
        c='2';
    else if(pos=='5'&&c=='2')
        c='5';
    else if(c!='1'&&c!='2'&&c!='3'&&c!='5')
        c=pos;
    pos=c;
    if(pos=='1')
        b=-1;
    else if(pos=='2')
        a=1;
    else if(pos=='3')
        b=1;
    else if(pos=='5')
        a=-1;
    r=temp->x;
    t=temp->y;
    while(temp->next!=NULL)
    {
        p=temp->next->x;
        q=temp->next->y;
        temp->next->x=r;
        temp->next->y=t;
        temp=temp->next;
        r=p;
        t=q;
    }
    temp=s;
    temp->x=temp->x+a;
    temp->y=temp->y+b;
    if(temp->x==-1)
        temp->x=19;
    if(temp->x==20)
        temp->x=0;
    if(temp->y==-1)
        temp->y=79;
    if(temp->y==80)
        temp->y=0;
}
void genfood(struct food *f)
{
    srand(time(0));
    f->x=rand()%20;
    f->y=rand()%80;
}
void crbox(char board[20][80],struct snake *s,struct food *f)
{
    struct snake *temp=s;
    board[f->x][f->y]=f->ch;
    char c=pos;
    while(temp!=NULL)
    {
        board[temp->x][temp->y]=temp->ch;
        temp=temp->next;
    }
    for(int i=0;i<20;++i)
    {
        for(int j=0;j<80;++j)
            printf("%c",board[i][j]);
        printf("\n");
    }
    temp=s;
    while(temp!=NULL)
    {
        board[temp->x][temp->y]=' ';
        temp=temp->next;
    }
    board[f->x][f->y]=' ';
    while(1)
    {
        system("cls");
        if(f->x==s->x&&f->y==s->y)
        {
            genfood(f);
            incr(s);
        }
        temp=s;
        if(kbhit())
           c=getch();
        if(c==27)
            break;
        change(temp,c);
        temp=temp->next;
        while(temp!=NULL)
        {
            if(s->x==temp->x&&s->y==temp->y)
            {
                printf("You Failed");
                ofstream fout;
                fout.open("SnakeLinked.txt");
                fout.close();
                exit(0);
            }
            temp=temp->next;
        }
        temp=s;
        board[f->x][f->y]=f->ch;
        while(temp!=NULL)
        {
            board[temp->x][temp->y]=temp->ch;
            temp=temp->next;
        }
        for(int i=0;i<20;++i)
        {
            for(int j=0;j<80;++j)
                printf("%c",board[i][j]);
            printf("\n");
        }
        temp=s;
        while(temp!=NULL)
        {
            board[temp->x][temp->y]=' ';
            temp=temp->next;
        }
        board[f->x][f->y]=' ';
    }
}
int main()
{
    char board[20][80],opt;
    printf("Welcome to Snake game\n");
    printf("Do you want to start a new game or continue from where you left?(y/n) ");
    scanf("%c",&opt);
    for(int i=0;i<20;++i)
    {
        for(int j=0;j<80;++j)
            board[i][j]=' ';
    }
    struct food f;
    f.x=4;
    f.y=4;
    f.ch='F';
    struct snake *s=(struct snake *)malloc(sizeof(struct snake)),*temp=(struct snake *)malloc(sizeof(struct snake)),*temp1=(struct snake *)malloc(sizeof(struct snake));
    temp1->x=14;
    temp1->y=14;
    temp1->ch='H';
    temp1->next=NULL;
    s=temp1;
    temp->x=14;
    temp->y=15;
    temp->ch='#';
    temp->next=NULL;
    temp1->next=temp;
    temp1=temp1->next;
    temp=(struct snake *)malloc(sizeof(struct snake));
    temp->x=14;
    temp->y=16;
    temp->ch='#';
    temp->next=NULL;
    temp1->next=temp;
    temp1=temp1->next;
    temp=(struct snake *)malloc(sizeof(struct snake));
    temp->x=14;
    temp->y=17;
    temp->ch='T';
    temp->next=NULL;
    temp1->next=temp;
    if(opt=='y')
    {
        ifstream fin;
        fin.open("SnakeLinked.txt");
        fin>>pos;
        if(!fin.eof())
        {
            s=(struct snake *)malloc(sizeof(struct snake));
            temp=(struct snake *)malloc(sizeof(struct snake));
            fin>>f.x;
            fin>>f.y;
            fin>>f.ch;
            fin>>temp->x;
            fin>>temp->y;
            fin>>temp->ch;
            temp->next=NULL;
            s=temp;
            while(fin.is_open())
            {
                temp1=(struct snake *)malloc(sizeof(struct snake));
                fin>>temp1->x;
                fin>>temp1->y;
                fin>>temp1->ch;
                temp1->next=NULL;
                temp->next=temp1;
                if(fin.eof())
                    break;
                temp=temp->next;
            }
            temp=s;
            while(temp->next->next!=NULL)
                temp=temp->next;
            temp->next=NULL;
        }
        fin.close();
    }
    crbox(board,s,&f);
    ofstream fout;
    fout.open("SnakeLinked.txt");
    fout<<pos<<" ";
    fout<<f.x<<" ";
    fout<<f.y<<" ";
    fout<<f.ch<<" ";
    while(s->next!=NULL)
    {
        fout<<s->x<<" "<<s->y<<" "<<s->ch<<" ";
        s=s->next;
    }
    fout<<s->x<<" "<<s->y<<" "<<s->ch<<" ";
    fout.close();
    return 0;
}
