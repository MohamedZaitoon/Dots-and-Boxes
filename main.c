#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define MAX 100

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void loading()
{

    int i,p=0;
    gotoxy(20,10);
    printf("loading..");

    for(i=0; i<=20; i++,p+=5)
    {
        gotoxy(20+i,11);
        delay(100);
        printf("%c",219);
        gotoxy(44,11);
        printf("%d %%",p);

    }
       system("clr");
}
typedef struct
{
    char name[25];
    int score;
    int moves;
    int color;
    clock_t t;

} player;
typedef struct{
                int arr[200][4];
                player pr1,pr2;
                int vs;
                int count;
                int size;
                int diffec;
                clock_t t;
            }saved;

 /* prototype for all functions   mostly in order */

void menu();
void disply_UI();
/* *************** start ************* */
void mode();
void read_info(player *p);
void diffeculity(int * diffec);
void get_size(int * size);
/* *************** game ************* */
void game(player *p1,player *p2,int number_of_player,int diffec,int ifload,saved file );
void draw(char rows[MAX][MAX][5],char cols[MAX][MAX], char squer[MAX][MAX],int color_squer[][MAX],int color_rows[][MAX], int color_cols[][MAX], int size,int count, clock_t start_game );
void print_score_turn_moves(int * point1,int * point2,int turn,int *cp,player * p1,player * p2);
void turns(int * point1,int * point2,int turn,int *cp,player * p1,player * p2);
void get_input(char input_game[]);
/* ********** in case input line >>> 2 >> AI  ************/
// for beginner
void Ai(char input_game[],int size,int store[][4],int count);
// for expert

int best(char rows[][MAX][5],char cols[][MAX],int size ,int path[4],int ai ,int j);
void MinimumLose(char rows[][MAX][5],char cols[][MAX],int size,int path[4]);
void copies(char rows[][MAX][5],char cols[][MAX],int size,char A[][MAX][5],char B[][MAX]);
// -------------
int check_line(int row1,int col1,int row2,int col2,int store[][4],int size,int count );
int check_box(char squer[][MAX],char rows[][MAX][5],char cols[][MAX],int size, int cp, int color_squer[][MAX]);
void fill_store(int store[][4],int redo_arr[][4],int count );// for storing lines that are inputed
void fill_unarr(int store[][4],int redo_arr[][4],int size);//>>>>>>>it will be used in redo operation
//  after end game
void determine_winner(player *p1,player *p2,player *pwin);
void rank(player pwin,int size);
void select_file_rank(int size, char v[]);
void print_rank(int size);
/* ************** other paths of input ****** */
void undo(int store[][4], int *count,char rows[][MAX][5],char cols[][MAX],int color_rows[MAX][MAX],int color_cols[MAX][MAX], int color_squer[MAX][MAX],char squer[][MAX],int size,player *p1,player *p2,int point1,int point2,int *turn);
void redo(char rows[MAX][MAX][5],char cols[MAX][MAX], char squer[MAX][MAX],int color_squer[][MAX],int color_rows[][MAX], int color_cols[][MAX], int redo_arr[][4],player *p1,player *p2,int size,int *count,int * turn,int cp,int point1,int point2);
void saving(saved * file ,int store[][4],player *p1,player *p2);
// or back to menu
//function is  used in undo & save
int  del_box(char squer[][MAX],char rows[][MAX][5],char cols[][MAX],int size,int cp,int color_squer[][MAX]);
void select_file(char v[]);
/* ********* load function ************/
void load(char s[]);
/* ************ functions help in other function ******* */
int comp(char x[],char y[]);
int mini(int x,int y);
void swap(int *x,int *y);
//**********************************************************************************************************************************************************************************************************************************************************

int main()
{
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
   loading();


    fflush(stdin);
    menu();




    return 0;

}
void menu()
{

    system("cls");
    disply_UI();
    char input[25]= {};
    printf("\t\t\t\tchoose ");
    fflush(stdin);
    gets(input);
    if (comp(input,"START")||comp(input,"start")||comp(input,"1"))
    {

        mode();
        system("cls");
        disply_UI();
        menu();
    }
    else if (comp(input,"LOAD GAME")||comp(input,"load game")||comp(input,"2"))
    {
        b:
        system("cls");
        char s;
        gotoxy(30,5);
        printf("1. save 1");
        gotoxy(30,7);
        printf("2. save 2");
        gotoxy(30,9);
        printf("3. save 3");
        gotoxy(30,11);
        printf("0. retunrn menu");
        gotoxy(30,13);
        char s1[]="save1.bin";
        char s2[]="save2.bin";
        char s3[]="save3.bin";
        s=getche();
        switch(s)
        {
        case '1': load(s1);goto b;
        case '2': load(s2);goto b;
        case '3': load(s3);goto b;
        case '0': menu();
        default: printf("\n!!error!!");goto b;
        }



    }
    else if (comp(input,"TOP 10 PLAYER")||comp(input,"top 10 player")||comp(input,"3"))
    {
        system("cls");
        char s;
        gotoxy(30,5);
        printf("2. 2 X 2");
        gotoxy(30,7);
        printf("3. 3 X 3");
        gotoxy(30,9);
        printf("4. 4 X 4");
        gotoxy(30,11);
        printf("5. 5 X 5");
        gotoxy(30,13);
        printf("6. 6 X 6");
        gotoxy(30,15);
        printf("7. 7 X 7");
        gotoxy(30,17);
        printf("8. 8 X 8");
        gotoxy(30,19);
        printf("0. retunrn menu");
        gotoxy(30,21);
        s=getche();
        print_rank(s-48);
    }
    else if (comp(input,"EXIT")||comp(input,"exit")||comp(input,"4"))
    {
        char h[]=" made by mohamed \" El kazafy & zaitoon\" ^_^ ";
        int i ;
        printf("\n\n\n\t\t\t");
        for(i=0;h[i]!='\0';i++)
        {
            delay(100);
            printf("%c",h[i]);
        }
        delay(800);
        exit(1);
    }
    else
    {
        printf("\t\t\t\t\"!! INVALID INPUT !! \"\t");
        delay(500);
        menu();

    }

}
void disply_UI()
{
    int i,j;
    for (i=0; i<11; i++)
    {
        printf("\t\t\t\t");
        for(j=0; j<34; j++)
        {
            if (i==0)//top
            {
                if (j!=0&&j!=33)
                    printf("%c",205);
                else if (j==0)
                    printf("%c",201);
                else
                    printf("%c",187);
            }
            else if (i==10)
            {
                if (j!=0&&j!=33)
                    printf("%c",205);
                else if (j==0)
                    printf("%c",200);
                else
                    printf("%c",188);
            }
            else
            {
                if(i%2!=0)
                {
                    if (j!=0&&j!=33)
                        printf("%c",32);
                    else
                        printf("%c",186);
                }
                else if(i==2)
                {
                    printf("%c           1.START              %c",186,186);
                    break;
                }
                else if (i==4)
                {
                    printf("%c           2.LOAD GAME          %c",186,186);
                    break;
                }
                else if (i==6)
                {
                    printf("%c           3.TOP 10 PLAYER      %c",186,186);
                    break;
                }
                else if (i==8)
                {
                    printf("%c           4.EXIT               %c",186,186);
                    break;
                }

            }

        }
        printf("\n");
    }
}
                                    /* *************** start ************* */
void mode()
{
    char c[3];int number_of_player,diffec=0;
    player p1,p2;
    saved q;
    x:
    system("cls");
    gotoxy(30,5);
    printf("1. Two player \n");
    gotoxy(30,7);
    printf("2. One player \n");
    gotoxy(30,9);
    printf("0. Back  \n");
    fflush(stdin);
    gotoxy(30,11);
    scanf("%s",c);
        if (comp(c,"1"))
        {   number_of_player=1;
            read_info(&p1);
            read_info(&p2);
            game(&p1,&p2,number_of_player,diffec,0,q);

        }
        else if (comp(c,"2"))
        {
            system("cls");
            number_of_player=2;
            read_info(&p1);
            diffeculity(&diffec);
            player p2= {"Computer",0,0,12};
            game(&p1,&p2,number_of_player,diffec,0,q);
        }
        else if (comp(c,"0"))menu;
        else goto x;


}
void read_info(player *p)
{
    system("cls");
    gotoxy(20,5);
    printf("Player Name : ");
    fflush(stdin);
    scanf("%24s",(*p).name);
    printf("\n");

}
void diffeculity(int * diffec)
{
    char c[3];
    x:
    system("cls");
    gotoxy(30,5);
    printf("1. Beginner \n");
    gotoxy(30,7);
    printf("2. Expert \n");
    gotoxy(30,10);
    printf("0.Back \n");
    gotoxy(30,12);
    fflush(stdin);
    scanf("%s",c);
    if (comp(c,"1"))
        {
            *diffec=1;
        }
    else if (comp(c,"2"))
        {
        *diffec=2;
        }
     else if (comp(c,"0"))mode();
        else goto x;
}
void get_size(int * size)
{
     char q[3];
    a:
    gotoxy(20,5);
    printf("Enter size in rang [ 2 : 8 ] :  ");
    fflush(stdin);
    scanf("%2s",q);
    if(strlen(q)==1)
    {
        *size = q[0]-48;
        while(!(*size>1&&*size<9))
        {

            system("cls");
            gotoxy(20,5);
            printf(" Enter size in rang [ 2 : 8 ] : ");
            fflush(stdin);
            scanf("%2s",q);
            if(strlen(q)==1)
                *size = q[0]-48;
            else
            {
                gotoxy(20,8);
                printf("Error !! ");
                delay(500);
                system("cls");
                goto a;
            }
        }
    }
    else
    {
        printf("Error !! ");
        delay(500);
        system("cls");
        goto a;
    }
}
                                    /* *************** game ************* */
void game(player *p1,player *p2,int number_of_player,int diffec,int ifload,saved file )
{
    //******************************************************************************//
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    /* ---------------------------------------------------------------------------------------*/
    p1->score=p2->score=p1->moves=p2->moves=0;
    p2->color=12;
    p1->color=9;
    /* --------------------------------------------------------------------------------------*/
    fflush(stdin);
    char c[5]= {196,196,196,196},c1=179,input_game[6],c2[]="-",c3[]="+";
    system("cls");
    int row1,col1,row2,col2,minim,size,x,y,count=0,point1=0,point2=0,point,turn=0;
    int s,cp,ai,random;
    clock_t start_game;
    /* --------------------------------------------------------------------------------------*/
    if(ifload==1)size=file.size;
    else get_size(&size);
    //*********************************** array decleration********************************************//
    char rows[MAX][MAX][5];
    char cols[MAX][MAX];
    char squer[MAX][MAX];
    int store [size*(size+1)*2][4];
    int color_rows[MAX][MAX],color_cols[MAX][MAX],color_squer[MAX][MAX];
    int redo_arr[size*(size+1)*2][4];
    int path[MAX][4];
    //*************************************** bensafer el arrays***********************************************//

    for(x=0; x<size+1; x++)
    {
        for(y=0; y<size+1; y++)
        {
            fflush(stdin);
            strcpy(rows[x][y],"    ");
            cols[x][y]=' ';
            squer[x][y]=' ';
            color_rows[x][y]=15;
            color_cols[x][y]=15;
            color_squer[x][y]=15;

        }
    }


    for(x=0; x<size*(size+1)*2; x++)
    {
        for(y=0; y<4; y++)
        {
            fflush(stdin);
            store[x][y]=0;
            if(ifload==1)
               {
                redo_arr[x][y]=file.arr[x][y];
               }
            else
                {redo_arr[x][y]=0;}

        }
    }
    start_game=clock();
    if (ifload==1)
    {
        for(count=0;count<file.count;)
        {
        turns(&point1,&point2,turn,&cp,&(*p1),&(*p2));
        redo(rows,cols,squer,color_squer,color_rows,color_cols,redo_arr,&(*p1),&(*p2),size, &count, & turn,cp, point1, point2);
        }
        //fill_rearr(store,redo_arr,size);
        fill_store(store,redo_arr,count );
        start_game=clock()-file.t;
    }
    //************************************************ game ********************************************************///
    for(count; count<=size*(size+1)*2; count++)
    {
        x=count;//>>>>>>>>>> for redo
        d:
        y=0;//>>>>>>>>>>>>>>>> for undo & redo
        fflush(stdin);

        draw(rows,cols, squer,color_squer,color_rows,color_cols,size, count,start_game );

        print_score_turn_moves(&point1,&point2,turn,&cp,&(*p1),&(*p2));


        if(count==size*(size+1)*2)break;

        turns(&point1,&point2,turn,&cp,&(*p1),&(*p2));

        if(number_of_player==2&&turn%2!=0)
        {   if(diffec==1)
             {Ai(input_game,size,store,count );}
            else if (diffec==2)
            {
                ai=1;
             best(rows,cols,size ,path,ai,0);
             input_game[0]=path[0][0]+48;input_game[2]=path[0][1]+48;input_game[1]=path[0][2]+48;input_game[3]=path[0][3]+48;
             input_game[4]='\0';
             }
        }

       else
        {

            get_input(input_game);
        }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>> undo & redo & put intputs in row1,col1,.....  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-
        if(comp(input_game,c2))
        {
            if (count<1)
            {

                printf("\n\n\t\tError");
                delay(500);
                goto d;
            }
            else
            {   if(number_of_player==1){
                undo(store, &count,rows,cols,color_rows, color_cols,  color_squer,squer,size,&(*p1),&(*p2), point1, point2,&turn);
                goto d;}
                else
                {again:
                 undo(store, &count,rows,cols,color_rows, color_cols,  color_squer,squer,size,&(*p1),&(*p2), point1, point2,&turn);
                y++;
                turns(&point1,&point2,turn,&cp,&(*p1),&(*p2));
                if(y<number_of_player&&turn%2!=0) goto again;
                if(turn%2!=0)goto again;
                goto d;
                }
            }
        }
        /* ************* redo************/
        else if (comp(input_game,c3))
        {
            if(count<x&&x>0)
            {
                if(number_of_player==1){
                redo(rows,cols,squer,color_squer,color_rows,color_cols,redo_arr,&(*p1),&(*p2),size, &count, & turn,cp, point1, point2);
                turns(&point1,&point2,turn,&cp,&(*p1),&(*p2));
                fill_store(store,redo_arr,count );
                goto d;
                }
                else
                {
                    re:

                    redo(rows,cols,squer,color_squer,color_rows,color_cols,redo_arr,&(*p1),&(*p2),size, &count, & turn,cp, point1, point2);
                    y++;
                    turns(&point1,&point2,turn,&cp,&(*p1),&(*p2));
                    if(y<number_of_player&&turn%2!=0) goto re;
                    if(turn%2!=0)goto re;
                    fill_store(store,redo_arr,count );
                    goto d;
                }
            }
            else {printf("\n\n\t\tError");
                delay(500);
                goto d;};
        }
        /* ************* save *******************/
        else if (comp(input_game,"*"))
        {   saved file;char v[15];
            file.size=size;            file.count=count;        file.diffec=diffec;    file.t=clock()-start_game;
            file.vs =number_of_player;
            saving(&file,store,&(*p1),&(*p2));
            select_file(v);
            FILE *save;
            save=fopen(v,"wb");
            fflush(save);
            fwrite(&file,sizeof(file),1,save);
            fclose(save);
            printf("\n\n\t\t\tsaved");
            delay(500);
            goto d;
        }
        //********* put points to draw line************
       else if (comp(input_game,"/")){menu();}
        else
        {
            if(strlen(input_game)!=4)goto f;
            else
            {
                fflush(stdin);
                row1=input_game[0]-48;
                col1=input_game[1]-48;
                row2=input_game[2]-48;
                col2=input_game[3]-48;
            }

        }
 /* ------------------------------------------------ put line in the cell------------------------------------------*/
        if(check_line(row1,col1,row2,col2,store,size,count))goto f;
        else
        {
            if(row1>0&&row1<size+2&&row2>0&&row2<size+2&&col1>0&&col1<size+2&&col2>0&&col2<size+2&&(abs(row1-row2)!=0||abs(col1-col2)!=0))
            {
                if (abs(row1-row2)==1||abs(col1-col2)==1)
                {
                    if(row1==row2)
                    {
                        minim=mini(col1,col2);
                        fflush(stdin);
                        strcpy(rows[row1-1][minim-1],c);
                        color_rows[row1-1][minim-1]=cp;
                    }
                    else if (col1==col2)
                    {
                        minim=mini(row1,row2);
                        fflush(stdin);
                        cols [minim-1][col1-1]=c1;
                        color_cols [minim-1][col1-1]=cp;
                    }
                    else
                        goto f;
                }
                else
                    goto f;

            }
            else
            {
                f:
                printf("\n\n\t\tError , try again \n");
                delay(500);
                goto d;
            }
        }
        store[count][0]=row1;
        store[count][1]=col1;
        store[count][2]=row2;
        store[count][3]=col2;
        fill_rearr(store,redo_arr,size);
        point =check_box(squer,rows,cols,size,cp,color_squer);//cp------> color of player
        if (point !=0)
        {
            p1->score+=point1*point;
            p2->score+=point2*point;
            turn--;
        }
        turn++;
        p1->moves+=point1;
        p2->moves+=point2;

    }
    player pwin={"none",0,0,15,0};
    determine_winner( &(*p1), &(*p2) , &(pwin) );
    pwin.t=clock()-start_game;
    printf("\n\n\t\t\t\t  \n\n\n\t\t\t\t\t To continue Press any key");
    getche();
    rank(pwin,size);
}

void draw(char rows[MAX][MAX][5],char cols[MAX][MAX], char squer[MAX][MAX],int color_squer[][MAX],int color_rows[][MAX], int color_cols[][MAX], int size,int count, clock_t start_game )
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    int i,j,s,h;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf(" UNDO ( - )  REDO ( + ) SAVE ( * ) MENU ( / )");
    printf("\t\t Remainning moves : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("%d",size*(size+1)*2-count);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\t\t\t\ttime %d : %d \n\n",(clock()-start_game)/CLOCKS_PER_SEC/60,(clock()-start_game)/CLOCKS_PER_SEC%60);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);

    for(i=0; i<size+2; i++)
    {
        printf("\n\t\t");
        for(j=0; j<size+2; j++) // >>>>> for rows
        {
            if (i==0)
            {
                if(j!=0)
                    printf("%d    ",j);
                else printf("     ");
            }
            else if (j==0)
            {
                if(i!=0)
                    printf("%d    ",i);
                else
                    printf("      ");
            }
            else
            {
                if (j>0&&j<size+1)
                {
                    printf("%c",254);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_rows[i-1][j-1]);
                    printf("%s",rows[i-1][j-1]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
                }
                else
                {
                    printf("%c",254);
                }

            }

        }
        if(i<size+1&&i>0)// >>>>>>> for columns
        {
            for (h=0; h<2; h++)
            {
                printf("\n\t\t     ");
                for(s=0; s<size+1; s++)
                {
                    if(s<size)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_cols[i-1][s]);
                        printf("%c",cols[i-1][s]);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_squer[i-1][s]);
                        printf("%c%c%c%c",squer[i-1][s],squer[i-1][s],squer[i-1][s],squer[i-1][s]);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);

                    }
                    else
                    {

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_cols[i-1][s]);
                        printf("%c",cols[i-1][s]);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
                    }
                }


            }
        }
        if(i==0&&j==0)printf("\n\n\n");
    }
}
void print_score_turn_moves(int * point1,int * point2,int turn,int *cp,player * p1,player * p2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p1->color);
    printf("\n\n\n\n\t  %s ",(*p1).name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p2->color);
    printf("\t\tVS\t\t %s",p2->name);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\n\nscore : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p1->color);
    printf("\t%d",(*p1).score);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p2->color);
    printf("\t\t\t\t\t%d",(*p2).score);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\n\nmove  : ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),p1->color);
    printf("\t%d",(*p1).moves);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p2->color);
    printf("\t\t\t\t\t%d",(*p2).moves);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);



    if ((turn)%2==0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("\n\nTurn  : ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p1->color);
        printf("\t^^");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        printf("\n\nTurn  : ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p2->color);
        printf("\t\t\t\t\t\t^^");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    }
    printf("\n\nEnter two point in same line : ");

}
void turns(int * point1,int * point2,int turn,int *cp,player * p1,player * p2)
{
    if ((turn)%2==0)
    {
        *point1=1;
        *point2=0;
        *cp=(*p1).color;
    }
    else
    {
        * point2=1;
        * point1=0;
        *cp=(*p2).color;

    }

}

void get_input(char input_game[])
{
    fflush(stdin);
    printf("\t\t");
    scanf("%5s",input_game);
}
                    /* ********** in case input line >>> 2 >> AI  ************/
// ****** beginner
void Ai(char input_game[],int size,int store[][4],int count)
{   int i,j,k,l;
    int row1,col1,row2,col2;

    for(i=0;i<=size;i++)
    {
        input_game[0]=i+49;
         for(j=0;j<=size;j++)
            {
                input_game[1]=j+49;
                 for(k=0;k<=size;k++)
                {
                    input_game[2]=k+49;
                     for(l=0;l<=size;l++)
                        {
                            input_game[3]=l+49;
                             fflush(stdin);
                            row1=input_game[0]-48;
                            col1=input_game[1]-48;
                            row2=input_game[2]-48;
                            col2=input_game[3]-48;
                            if(check_line(row1,col1,row2,col2,store,size,count)){}
                            else
                            {
                                if(row1>0&&row1<size+2&&row2>0&&row2<size+2&&col1>0&&col1<size+2&&col2>0&&col2<size+2&&(abs(row1-row2)!=0||abs(col1-col2)!=0))
                                {
                                    if (abs(row1-row2)==1||abs(col1-col2)==1)
                                    {
                                        if(row1==row2)
                                        {
                                        goto f;}
                                    else if(col1==col2)
                                    {
                                        goto f;
                                    }
                                }

                            }

                }

            }

        }
    }
    }
    f:
    input_game[5]='\0';

}

/* *************************************************************  expert **************************************/
int best(char rows[][MAX][5],char cols[][MAX],int size ,int path[4],int ai ,int j)
{
     char c1=179;
     int x,y,out,i;
     char c[5]= {196,196,196,196};
     do
     {
         out=0;
         x=0;
         while (out==0&&x<=size)
         {
             y=0;
             while (out==0&&y<=size)
             {
                 if (!(strcmp(rows[x][y],c))&&!(strcmp(rows[x+1][y],c))&&cols[x][y]==c1&&cols[x][y+1]!=c1)
                 {
                     j++;
                     path[0]=x+1;
                     path[1]=x+2;
                     path[2]=y+2;
                     path[3]=y+2;
                     out=1;
                     if(ai==0)
                        cols[x][y+1]=c1;

                 }
                 else if (!(strcmp(rows[x][y],c))&&!(strcmp(rows[x+1][y],c))&&cols[x][y]!=c1&&cols[x][y+1]==c1)
                 {
                     j++;
                     path[0]=x+1;
                     path[1]=x+2;
                     path[2]=y+1;
                     path[3]=y+1;
                     out=1;
                     if (ai==0)
                        cols[x][y]=c1;


                 }
                else  if (!(strcmp(rows[x][y],c))&&(strcmp(rows[x+1][y],c))&&cols[x][y]==c1&&cols[x][y+1]==c1)
                 {
                     j++;
                     path[0]=x+2;
                     path[1]=x+2;
                     path[2]=y+1;
                     path[3]=y+2;
                     out=1;
                     if(ai==0)
                        strcpy(rows[x+1][y],c);

                 }
                 else if ((strcmp(rows[x][y],c))&&!(strcmp(rows[x+1][y],c))&&cols[x][y]==c1&&cols[x][y+1]==c1)
                 {
                     j++;
                     path[0]=x+1;
                     path[1]=x+1;
                     path[2]=y+1;
                     path[3]=y+2;
                     out=1;
                     if(ai==0)
                        strcpy(rows[x][y],c);

                 }


             y++;
             }
          x++;
         }

     }while (out==1&&ai==0);
     if (out==0&&ai==1){
           MinimumLose(rows,cols,size,path);
         }
return j;
}
void MinimumLose(char rows[][MAX][5],char cols[][MAX],int size,int path[4])
{
    char rows1[MAX][MAX][5],cols1[MAX][MAX],c[5]= {196,196,196,196},c1=179;
    char usedrows[MAX][MAX][5],usedcols[MAX][MAX];
    int x=0,y=0,z=0,i,t=0,j=0,s,ss=size*size,path2[4],path3[MAX][4],random;
    copies(rows,cols,size,usedrows,usedcols);
    for (x=0;x<size+1;x++)
    {
        for (y=0;y<size;y++)
        {
           copies(rows,cols,size,rows1,cols1);
           if(strcmp(usedrows[x][y],c))
           {
               strcpy(rows1[x][y],c);
               path2[0]=x+1;path2[1]=x+1;path2[2]=y+1;path2[3]=y+2;
               s=best(rows1,cols1,size,path2,0,0);
               strcpy(usedrows[x][y],c);
               if (s<ss)
                {
                    j=0;
                   path3[j][0]=x+1;path3[j][1]=x+1;path3[j][2]=y+1;path3[j][3]=y+2;
                   ss=s;
               }
               else if (s==ss)
               {
                   j+=1;
                   path3[j][0]=x+1;path3[j][1]=x+1;path3[j][2]=y+1;path3[j][3]=y+2;
                   ss=s;
               }

           }
           copies(rows,cols,size,rows1,cols1);
           if(usedcols[y][x]!=c1)
           {
               cols1[y][x]=c1;
               path2[0]=y+1;path2[1]=y+2;path2[2]=x+1;path2[3]=x+1;
               s=best(rows1,cols1,size,path2,0,0);
               usedcols[y][x]=c1;
               if (s<ss)
                {
                    j=0;
                   path3[j][0]=y+1;path3[j][1]=y+2;path3[j][2]=x+1;path3[j][3]=x+1;
                   ss=s;
               }
               else if (s==ss)
               {
                   j+=1;
                  path3[j][0]=y+1;path3[j][1]=y+2;path3[j][2]=x+1;path3[j][3]=x+1;
               }
           }
        }

    }

    random=rand()%(j+1);
    for (i=0;i<4;i++){
        path[i]=path3[random][i];
    }
}
void copies(char rows[][MAX][5],char cols[][MAX],int size,char A[][MAX][5],char B[][MAX])
{
    int i=0,j;
    char c[5]= {196,196,196,196},c1=179;
    for (i=0;i<=size;i++)
    {
        for (j=0;j<size;j++)
        {
            strcpy(A[i][j],rows[i][j]);
            B[j][i]=cols[j][i];
        }
    }
}


int check_box(char squer[][MAX],char rows[][MAX][5],char cols[][MAX],int size,int cp,int color_squer[][MAX])
{
    char c1=179,c2=219;
    int x,y,s=0;
    char c[5]= {196,196,196,196};
    for (x=0; x<size; x++)
    {
        for(y=0; y<size; y++ )
        {
            if( (comp(rows[x][y],c))&&(comp(rows[x+1][y],c))&&cols[x][y]==c1&&cols[x][y+1]==c1)
            {

                if (squer[x][y]!=c2)
                {
                    squer[x][y]=219;
                    color_squer[x][y]=cp;
                    s++;
                }

            }
        }
    }
    return s;
}
int check_line(int row1,int col1,int row2,int col2,int store[][4],int size,int count )
{
    int i,f=0;

    for (i=0; i<count; i++)
    {
        if(store[i][0]==row1&&store[i][1]==col1&&store[i][2]==row2&&store[i][3]==col2)f=1;
        else if(store[i][0]==row2&&store[i][1]==col2&&store[i][2]==row1&&store[i][3]==col1)f=1;
    }
    return f;
}

void fill_rearr(int store[][4],int redo_arr[][4],int size)
{
    int i;
    for(i=0; i<size*(size+1)*2; i++)
    {

        redo_arr[i][0]=store[i][0];
        redo_arr[i][1]=store[i][1];
        redo_arr[i][2]=store[i][2];
        redo_arr[i][3]=store[i][3];
    }
}
void fill_store(int store[][4],int redo_arr[][4],int count )
{
    int i;
    for(i=0; i<=count; i++)
        {
        store[i][0]=redo_arr[i][0];
        store[i][1]=redo_arr[i][1];
        store[i][2]=redo_arr[i][2];
        store[i][3]=redo_arr[i][3];
        }
}
                            //  after end game

void determine_winner(player *p1,player *p2,player *pwin)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if ((*p1).score>(*p2).score)
    {
        *pwin=*p1;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(*p1).color);
        printf("\n\n\n\t\t\t\t%s Winner \n",(*p1).name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
    }

    else if ((*p2).score>(*p1).score)
    {
        *pwin=*p2;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (*p2).color);
        printf("\n\n\n\t\t\t\t%s Winner \n",(*p2).name);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);

    }
}

void rank(player pwin,int size)
{   int i;

    player p[10],temp;
    char file_num[15];
    select_file_rank(size,file_num);
    FILE *ranks;
    ranks=fopen(file_num,"rb");
    if(ranks==NULL)
      {
           for(i=0;i<10;i++)
            {
                strcpy(p[i].name,"none");
                p[i].score=0;
                p[i].color=15;
                p[i].t=0;
            }

        fclose(ranks);
        ranks=fopen(file_num,"wb");
        fwrite(&p,sizeof(p),1,ranks);
        fclose(ranks);
        }
        fclose(ranks);
        ranks=fopen(file_num,"rb");
        fread(&p,sizeof(p),1,ranks);
        for(i=0;i<10;i++)
        {
            if(comp(pwin.name,p[i].name)){
                if(pwin.score>p[i].score)
                {
                    p[i]=pwin;
                    strcpy(pwin.name,"none");pwin.score=0;pwin.color=15;
                }
                else { strcpy(pwin.name,"none");pwin.score=0;pwin.color=15;}
            }
             if(pwin.score>p[i].score)
            {
                temp=pwin;
                pwin=p[i];
                p[i]=temp;
            }
        }
        for(i=0;i<10;i++)
        {

        }
        fclose(ranks);
        ranks=fopen(file_num,"wb");
        fwrite(&p,sizeof(p),1,ranks);
        fclose(ranks);
        print_rank( size);
        return;

}
void select_file_rank(int size, char v[])
{

                char z =size+48;
                char s2[]="rank2.bin";
                char s3[]="rank3.bin";
                char s4[]="rank4.bin";
                char s5[]="rank5.bin";
                char s6[]="rank6.bin";
                char s7[]="rank7.bin";
                char s8[]="rank8.bin";
                switch(z)
                {
                case '2': strcpy(v,s2);break;
                case '3': strcpy(v,s3);break;
                case '4': strcpy(v,s4);break;
                case '5': strcpy(v,s5);break;
                case '6': strcpy(v,s6);break;
                case '7': strcpy(v,s7);break;
                case '8': strcpy(v,s8);break;
                case '0': menu();
                default: {printf("\n\t\t\t\t!!error!!");delay(500);menu();}
                }
}
void print_rank(int size)
{
    //************************************************
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    //************************************************
    int i;
    char file_num[15];
    player p[10];
    FILE *ranks;
    select_file_rank(size,file_num);//<<<<<<<<<<<<<<<<<<<<<<<<< file
    ranks=fopen(file_num,"rb");
    if(ranks==NULL)
      {
           for(i=0;i<10;i++)
            {
                strcpy(p[i].name,"none");
                p[i].score=0;
                p[i].color=15;
                p[i].t=0;
            }

        fclose(ranks);
        ranks=fopen(file_num,"wb");
        fwrite(&p,sizeof(p),1,ranks);
        fclose(ranks);
        }
        fclose(ranks);
        ranks=fopen(file_num,"rb");
        fread(&p,10*sizeof(player),1,ranks);
        fclose(ranks);
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("\t\t\t\t\tTOP 10");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
        printf("\n\n\t\tNAME\t\t\tSCORE\t\t\tTIME ");
        for(i=0;i<10;i++)
        {
           SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p[i].color);
           gotoxy(16,4+i*2);
            printf("%s",p[i].name);
            gotoxy(40,4+i*2);printf("%d",p[i].score);
            gotoxy(64,4+i*2);
            printf("%d : %d ",(p[i].t)/CLOCKS_PER_SEC/60,(p[i].t)/CLOCKS_PER_SEC%60);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
        }
    printf("\n\n\n\n\n\t\t\t\t\t To Return Menu Press any key");
    getche();
    menu();
}
                            /* ************** other paths of input ****** */
void undo(int store[][4], int *count,char rows[][MAX][5],char cols[][MAX],int color_rows[MAX][MAX],int color_cols[MAX][MAX], int color_squer[MAX][MAX],char squer[][MAX],int size,player *p1,player *p2,int point1,int point2,int *turn)
{
    int minim,point;
    char c[]="    ";
    int cp=15;
    int row1,row2,col2,col1;
            row1=store[*count-1][0];
            col1=store[*count-1][1];
            row2=store[*count-1][2];
            col2=store[*count-1][3];
            if(row1==row2)
            {
                minim=mini(col1,col2);
                strcpy(rows[row1-1][minim-1],c);
                color_rows[row1-1][minim-1]=cp;
            }
            else if (col1==col2)
            {
                minim=mini(row1,row2);
                cols [minim-1][col1-1]=' ';
                color_cols [minim-1][col1-1]=cp;
            }
            point=del_box(squer,rows,cols,size,cp,color_squer);
            store[*count-1][0]=0;
            store[*count-1][1]=0;
            store[*count-1][2]=0;
            store[*count-1][3]=0;
            if (point !=0)
            {
                p1->score+=point1*point;
                p2->score+=point2*point;
                p1->moves-=point1;
                p2->moves-=point2;
                *turn=*turn-1;
            }
            else
            {
                swap(&point1,&point2);
                p1->moves-=point1;
                p2->moves-=point2;
            }
            *turn=*turn+1;
            *count=*count-1;

}
void redo(char rows[MAX][MAX][5],char cols[MAX][MAX], char squer[MAX][MAX],int color_squer[][MAX],int color_rows[][MAX], int color_cols[][MAX], int redo_arr[][4],player *p1,player *p2,int size,int *count,int * turn,int cp,int point1,int point2)
{

    char c[5]= {196,196,196,196},c1=179;
    int minim,row1,row2,col1,col2,point;
                row1=redo_arr[*count][0];
                col1=redo_arr[*count][1];
                row2=redo_arr[*count][2];
                col2=redo_arr[*count][3];

                if(row1==row2)
                    {
                        minim=mini(col1,col2);
                        fflush(stdin);
                        strcpy(rows[row1-1][minim-1],c);
                        color_rows[row1-1][minim-1]=cp;
                    }
                    else if (col1==col2)
                    {
                        minim=mini(row1,row2);
                        fflush(stdin);
                        cols [minim-1][col1-1]=c1;
                        color_cols [minim-1][col1-1]=cp;
                    }
                point =check_box(squer,rows,cols,size,cp,color_squer);
                    if(point!=0){
                    p1->score+=point1*point;
                    p2->score+=point2*point;
                    * turn=*turn-1;}
                * turn=*turn+1;
                p1->moves+=point1;
                p2->moves+=point2;
                *count=*count+1;



}
void saving(saved * file ,int store[][4],player *p1,player *p2)
{
    int i ;
    for(i=0;i<200;i++)
    {
        if(i<(*file).count)
        {
        (*file).arr[i][0]=store[i][0];
        (*file).arr[i][1]=store[i][1];
        (*file).arr[i][2]=store[i][2];
        (*file).arr[i][3]=store[i][3];
        }
        else{
            (*file).arr[i][0]=0;
            (*file).arr[i][1]=0;
            (*file).arr[i][2]=0;
            (*file).arr[i][3]=0;
        }
    }
    (*file).pr1=(*p1);
    (*file).pr2=(*p2);
    return;
}

void select_file(char v[])
{
                b:
                printf("\n\t\t 1. save1\t2. save2\t 3. save3\n\n\t Select : ");
                char z =getche();
                char s1[]="save1.bin";
                char s2[]="save2.bin";
                char s3[]="save3.bin";
                switch(z)
                {
                case '1': strcpy(v,s1);break;
                case '2': strcpy(v,s2);break;
                case '3': strcpy(v,s3);break;
                default: printf("\n!!error!!");goto b;
                }
}
int  del_box(char squer[][MAX],char rows[][MAX][5],char cols[][MAX],int size,int cp,int color_squer[][MAX])
{
    char c1=179,c2=219,c3=' ';
    int x,y,s=0;
    char c[5]= {196,196,196,196};
    for (x=0; x<size; x++)
    {
        for(y=0; y<size; y++ )
        {
            if (squer[x][y]==c2)
            {
                if( (comp(rows[x][y],c))&&(comp(rows[x+1][y],c))&&cols[x][y]==c1&&cols[x][y+1]==c1)
                    {}
                else
                {
                    squer[x][y]=c3;
                    color_squer[x][y]=cp;
                    s--;
                }

            }
        }
    }
    return s;
}
                            /* ********* load function ************/

                            void load(char s[])
{   saved file;
    FILE *save ;
    save = fopen(s,"r");
    if(save==NULL){gotoxy(30,15);printf("this save is empty");delay(500);return;}
    fread(&file,sizeof(saved),1,save);
    fclose(save);
    player  p1 =file.pr1;
    player  p2 =file.pr2;
    game(&p1,&p2,file.vs,file.diffec,1,file);

}


                            /* ************ functions help in other function ******* */
void swap(int *x,int *y)
{
    *x=*x^*y;
    *y=*x^*y;
    *x=*x^*y;
    return;

}
int comp(char x[],char y[])    /* >>>>>>>> compare string <<<<<<<<<<*/
{       int i,h=1;
        if(strlen(x)!=strlen(y))h=0;
        else{
                for(i=0;x[i]!='\0';i++)
                {
                if(x[i]!=y[i])h=0;
                }
            }
 return h;
 }

 int mini(int x, int y)
{
    if (x<y) return x;
    else return y;
}
