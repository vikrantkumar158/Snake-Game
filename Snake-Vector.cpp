#include<iostream>
#include<vector>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#include<fstream>
using namespace std;
struct food
{
    int x,y;
    char value;
};
struct snake
{
    int x,y;
    char value;
};
void printbox(char box[][80])
{
    for(int i=0;i<20;++i)
    {
        for(int j=0;j<80;++j)
        {
            cout<<box[i][j];
        }
        cout<<"\n";
    }
}
void genfood(char box[][80],food &f)
{
    srand((unsigned)time(0));
    f.x=rand()%19;
    f.y=rand()%79;
    box[f.x][f.y]=f.value;
}
char so='1';
void change(vector<struct snake> &v,char &ch)
{
    int a=0,b=0;
    if(ch!='1'&&ch!='2'&&ch!='3'&&ch!='5')
        ch=so;
    else if(((ch=='1')&&(so=='3'))||((ch=='3')&&(so=='1')))
    {
        ch=so;
    }
    else if(((ch=='5')&&(so=='2'))||((ch=='2')&&(so=='5')))
    {
        ch=so;
    }
    if(ch=='1')
        b=-1;
    else if(ch=='5')
        a=-1;
    else if(ch=='2')
        a=1;
    else if(ch=='3')
        b=1;
    for(int i=v.size()-1;i>0;--i)
    {
        v[i].x=v[i-1].x;
        v[i].y=v[i-1].y;
    }
    v[0].x+=a;
    v[0].y+=b;
    if(v[0].x==-1)
        v[0].x=19;
    else if(v[0].x==20)
        v[0].x=0;
    if(v[0].y==-1)
        v[0].y=79;
    else if(v[0].y==80)
        v[0].y=0;
    for(int i=v.size()-1;i>3;--i)
    {
        if(v[0].x==v[i].x&&v[0].y==v[i].y)
        {
            cout<<"You Failed";
            ofstream fout;
            fout.open("NewSnake.txt");
            fout.close();
            exit(0);
        }
    }
    so=ch;
}
void start(char box[][80],food &f,vector<struct snake> &v)
{
    char ch='1';
    box[f.x][f.y]=f.value;
    for(int i=0;i<v.size();++i)
    {
        box[v[i].x][v[i].y]=v[i].value;
    }
    printbox(box);
    for(int i=0;i<v.size();++i)
    {
        box[v[i].x][v[i].y]=' ';
    }
    while(1)
    {
        if(kbhit())
            ch=getch();
        if(ch=='e')
            break;
        system("cls");
        change(v,ch);
        if(f.x==v[0].x&&f.y==v[0].y)
        {
            struct snake s;
            s.x=v[0].x;
            s.y=v[0].y;
            s.value='#';
            genfood(box,f);
            v.insert(v.begin()+1,s);
            change(v,ch);
        }
        box[f.x][f.y]=f.value;
        for(int i=0;i<v.size();++i)
        {
            box[v[i].x][v[i].y]=v[i].value;
        }
        printbox(box);
        for(long long nume=0;nume<10000000;++nume);
        for(int i=0;i<v.size();++i)
        {
            box[v[i].x][v[i].y]=' ';
        }
    }
}
int main()
{
    char c;
    cout<<"Welcome to Snake game!!!\n";
    cout<<"Do you want to continue from where you left?(y/n) ";
    cin>>c;
    char box[20][80];
    for(int i=0;i<20;++i)
    {
        for(int j=0;j<80;++j)
        {
            box[i][j]=' ';
        }
    }
    struct food f;
    f.x=0;
    f.y=5;
    f.value='F';
    vector<struct snake> v;
    struct snake s;
    s.x=4;
    s.y=4;
    s.value='H';
    v.push_back(s);
    s.x=4;
    s.y=5;
    s.value='#';
    v.push_back(s);
    s.x=4;
    s.y=6;
    s.value='#';
    v.push_back(s);
    s.x=4;
    s.y=7;
    s.value='T';
    v.push_back(s);
    if(c=='y')
    {
        ifstream fin;
        fin.open("NewSnake.txt");
        fin>>so;
        if(fin.eof())
            so='1';
        else
        {
            v.clear();
            //fin>>so;
            fin>>f.x;
            //cout<<f.x<<" ";
            fin>>f.y;
            //cout<<f.y<<" ";
            //cout<<f.x<<" "<<f.y<<" ";
            while(!fin.eof())
            {
                fin>>s.x;
                //cout<<s.x<<" ";
                fin>>s.y;
                //cout<<s.y<<" ";
                fin>>s.value;
                v.push_back(s);
            }
            v.pop_back();
        }
        fin.close();
    }
    start(box,f,v);
    ofstream fout;
    fout.open("NewSnake.txt");
    fout<<so<<"\n";
    fout<<f.x<<"\n";
    fout<<f.y<<"\n";
    for(int i=0;i<v.size();++i)
    {
        fout<<v[i].x<<"\n";
        fout<<v[i].y<<"\n";
        fout<<v[i].value;
        if(i!=v.size()-1)
            cout<<"\n";
    }
    fout.close();
    return 0;
}
