#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define M 40                 //M is define for border height
#define N 20                 //N is define for width of border
int i,j,Field[N][M],x,y,Gy,Head,Tail,Game,Frogs,a,b,var,dir,score,HighScore,Speed;  /* Global variables where i and j for loop */
FILE *f;                      // File f pointer create for file which store high score in file
void snakeInitilization()     // Snake initialization function for initialize every variables
{
    f=fopen("highscore.txt","r");
    fscanf(f,"%d",&HighScore);
    fclose(f);
   for(i=0; i<N;i++)
   {
       for(j=0; j<M; j++)
       {
           Field[i][j]=0;  //Field is body of snake
       }
   }
   x=N/2;y=M/2; Head = 5; Tail = 1; Gy = y; Game = 0; Frogs = 0; dir = 'd';score = 0; Speed = 99; /* Head is mouth of snake tail is back of snake Frogs is food of snake  */

   for(i=0; i<Head; i++)
   {
       Gy++;
       Field[x][Gy-Head] = i+1;
   }
}
void print()   //Print function create to print box in screen snake and score on the desktop
{
    for(i=0; i<=M+1; i++)
    {
        if(i==0)
        {
            printf("%c",201);
        }
        else if(i==M+1)
        {
           printf("%c",187);
        }
        else
        {
            printf("%c",205);
        }
    }
    printf("\tCurrent Score:%d High Score: %d",score,HighScore);
    printf("\n");

    for(i=0; i<N;i++)
    {
        printf("%c",186);
        for(j=0;j<M;j++)
        {
            if(Field[i][j]==0) printf(" ");
            if(Field[i][j]>0 && Field[i][j]!=Head) printf("%c",176);
            if(Field[i][j]==Head) printf("%c",178);
            if(Field[i][j]==-1) printf("%c",178);
            if(j==M-1) printf("%c\n",186);
        }
    }
    for(i=0; i<=M+1; i++)
    {
        if(i==0)
        {
            printf("%c",200);
        }
        else if(i==M+1)
        {
           printf("%c",188);
        }
        else
        {
            printf("%c",205);
        }
    }
}
void ResetScreenPosition()   //This function define the co-dinate for snake
{
     HANDLE hOut;
     COORD Position;
     hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     Position.X = 0;
     Position.Y = 0;
     SetConsoleCursorPosition(hOut,Position);
}
void Random()  //This function create random food for snake
{
    srand(time(0));
   a = 1 + rand() % 18;
   b = 1 + rand() % 38;
   if(Frogs == 0 && Field[a][b]==0)
   {
       Field[a][b]=-1;
       Frogs = 1;
       if(Speed>10 && score!=0) Speed = Speed - 6;
   }
}
int getch_noblock()  //This function take input from keyboard like up down left and right
{
    if(_kbhit())
        return _getch();
    else
        return -1;
}
void movement()
{
   var = getch_noblock();
   var = tolower(var);
   if(((var=='d' || var =='a') || (var =='w' || var=='s')) && (abs(dir-var)>5)) dir = var;
   if(dir == 'd')
   {
       y++;
       if(Field[x][y]!=0 && Field[x][y] !=-1) GameOver();
       if(Field[x][y]==-1)
       {
           Frogs = 0;
           score +=5;
           Tail -= 2;
       }
       if(y==M-1) y =0;
       Head++;
       Field[x][y] = Head;
   }
   if(dir == 'a')
   {
       y--;
       if(Field[x][y]!=0 && Field[x][y] !=-1) GameOver();
       if(Field[x][y]==-1)
       {
           Frogs = 0;
           score +=5;
           Tail -= 2;
       }
       if(y==0) y=M-1;
       Head++;
       Field[x][y] = Head;
   }
   if(dir == 'w')
   {
       x--;
       if(Field[x][y]!=0 && Field[x][y] !=-1) GameOver();
       if(Field[x][y]==-1)
       {
           Frogs = 0;
           score +=5;
           Tail -= 2;
       }
       if(x==-1) x= N-1;
       Head++;
       Field[x][y] = Head;
   }
   if(dir == 's')
   {
       x++;
       if(Field[x][y]!=0 && Field[x][y] !=-1) GameOver();
       if(Field[x][y]==-1)
       {
           Frogs = 0;
           score +=5;
           Tail -= 2;
       }
       if(x==N-1) x = 0;
       Head++;
       Field[x][y] = Head;
   }
}
void TailRemove()  // This function decrease array of snake means the tail of snake when snake will move
{
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            if(Field[i][j]==Tail)
            {
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}
void GameOver()      // After game this function print option for user restart game or exit and current score and high score
{
    print("\a");
    Sleep(1500);
    system("Cls");
    if(score>HighScore)
    {
        printf("\t New High Score:%d  !!!\n\n",score);
        system("pause");
        f=fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }
    system("Cls");
    printf("\n\n    GAME OVER !!!!");
    printf("        Score : %d\n\n",score);
    printf("        Press Enter to play again Or Esc to Exit...\n");

    while(1)
    {
        var= getch_noblock();
        if(var == 13)
        {
            Game =0;
            snakeInitilization();
            break;
        }
        else if(var == 27)
        {
            Game =1;
            break;
        }
    }
    system("Cls");
}
int main()   //Main function
{
    snakeInitilization();
    while(Game == 0)
    {
       print();
       ResetScreenPosition();
       Random();
       movement();
       TailRemove();
       Sleep(Speed);    // It increase the speed of snake
    }
    return 0;
}
