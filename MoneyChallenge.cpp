#define _WIN32_WINNT 0x0500
#include<iostream>
#include<string>
#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<ctime>
using namespace std;
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width,

height, TRUE);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
void clrscr()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle

(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void DrawRace1(char race[100][100]);
void DrawRace2(char race[100][100]);
void DrawPlayer(char race[100][100], int&,int&);
void DrawMoney(char race[100][100], int& ,int&);
void DrawBomb(char race[100][100], int&, int&);
void PrintRace(char race[100][100]);
void MovePlayer(char race[100][100], int&, int&);
void Handle(char race[100][100],int&,int&, int& );
int main(){
    resizeConsole(800, 400);
    char race[100][100];
    int l=0,k=0;
    int score=0; //diem so
    int x=8,y=28; //Toa do nguoi choi
    int x1=1,y1=1;//Toa do tien
    int x2=10, y2=-5;//Toa do shit1
    int x3=1, y3=3; // toa do shit2
    while(true){
        k++;
        l++;
        //Tao hieu ung chuyen dong cho duong dua
        if(k%2)
            DrawRace1(race);
        else
            DrawRace2(race);
        DrawPlayer(race,y,x);
        if(y2>0)
            DrawBomb(race,y2,x2);
        DrawMoney(race,y1,x1);
        Handle(race,y,x,score);
        PrintRace(race);
        MovePlayer(race,y,x);
        //Cho tien chuyen dong di xuong
        y1++;
        if(y1==30){
            y1=1;
            srand(time(0));
            x1=1+rand()%13;
        }
        //Cho bom chuyen dong di xuong
        y2++;
        if(y2==30){
            y2=1;
            x2=1+rand()%13;
        }
        clrscr();
        //Tang toc do tro choi
        if(l<230)
            Sleep(50);
        else
            Sleep(20);
        if(k>30)
            k=0;
        if(race[y-1][x]==(char)15||race[y][x]==(char)15){
            break;
        }
    }
    cout<<"Your Score: "<<score<<endl;
    cout<<"You Lost"<<endl;
    system("pause");
    return 0;

}

void DrawRace1(char race[100][100]){
    for(int i=0;i<30;i++){
        for(int j=0;j<15;j++){
            if((j==0||j==14)&&i%2==0)
                race[i][j]='|';
            else if((j==0||j==14)&&i%2!=0)
                race[i][j]='.';
            else
                race[i][j]=' ';
        }
    }
}
void DrawRace2(char race[100][100]){
    for(int i=0;i<30;i++){
        for(int j=0;j<15;j++){
            if((j==0||j==14)&&i%2==0)
                race[i][j]='.';
            else if((j==0||j==14)&&i%2!=0)
                race[i][j]='|';
            else
                race[i][j]=' ';
        }
    }
}
void DrawPlayer(char race[100][100], int& y, int& x){
    race[y][x]=(char)30; //ve than
    race[y-1][x]=(char)2; // ve dau
}
void DrawMoney(char race[100][100], int& y1,int& x1){
    race[y1][x1]= '$';
}
void DrawBomb(char race[100][100], int& y2,int& x2){
    race[y2][x2]= (char)15;
}
void PrintRace(char race[100][100]){
    //In duong dua
   for(int i=0;i<30;i++){
        cout<<"\t";
        for(int j=0;j<15;j++){
                //in duong
            if((j==0||j==14)&&i%2==0){
                TextColor(9);
                cout<<race[i][j];
                TextColor(7);
            }

            else if((j==0||j==14)&&i%2!=0){
                TextColor(9);
                cout<<race[i][j];
                TextColor(7);
            }
            //in player
            else if(race[i][j]==(char)30||race[i][j]==(char)2){
                TextColor(12);
                cout<<race[i][j];
                TextColor(7);
            }
            //in tien
            else if(race[i][j]=='$'){
                TextColor(36);
                cout<<race[i][j];
                TextColor(7);
            }
            //in bom
            else if(race[i][j]==(char)15){
                TextColor(14);
                cout<<race[i][j];
                TextColor(7);
            }
            else
                cout<<race[i][j];
        }
        cout<<"\n";
    }


}
void MovePlayer(char race[100][100], int&y, int&x){
    if(kbhit()){
        char c=getch();
        if(c=='j'||c=='J') x--; //Di chuyen sang trai
        if(c=='l'||c=='L') x++; //Di chuyen sang phai
    }
    //khong cho player chay ra ngoai duong dua
    if(x<=0)
        x=1;
    if(x>=14)
        x=13;
}
void Handle(char race[100][100],int& y, int& x, int& score){
    //xu ly diem
    if(race[y-1][x]=='$')
        score++;
}
