#include<bits/stdc++.h>
#include<conio.h>
#include <sys/ioctl.h>
#include <unistd.h>
using  namespace std;
#define ppr cout<<(char)219
struct winsize w;
#define jjj ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


// int pageno;

int bs = 23, totalboard[500][500], point, fruitposx, fruitposy, h=1,stageunlocked[4], stagenumber=1;
// char border = 219, c, ch;
int highscore = 0, stagepoint[6]={100,50,250,200,200,150} ;
char border = 219;

// board
int bdc = 42;


//home
vector<string> homepagecontent = {"Start New Game", "Help", "Exit"};
int homepagecontentpos, homeorcont;


//continue_game
vector<string> continuecontent = {"Continue", "Start New Game", "Help", "Exit"};
int continuecontentpos;



// level
int levelh;


// Stage ***
vector<string> stagestr = {"Normal", "Campaign", "Tunnel", "Apartment", "Maze"};
int stageh;
int targetpoint[6] = {50, 60, 50, 50, 50};


// help
vector<string> helpstr = { 
"HELP", 
"________________", 
" ",
"\'w\' -> Navigate DOWN", 
"\'s' -> Navigate UP", 
"\'a\' -> Navigate LEFT",
"\'d\' -> Navigate RIGHT",
"\'x\' -> Back to main menu", " ",
"The snake is hunting for the", "food which looks like '#' and", "each time it eats the food, it", "becomes larger and a new food",
"grows somewhere else.", "But if the snake hit the wall", "or its body, then it dies."
};



// exit the game
bool etg;


// game
bool gameover;
char cs, ch;



// Snake
int snakeposx[1000], snakeposy[1000], snakelen = 9;
bool f;



vector<int> prevconsize;


vector<int> consolemid();
void gotoXY(int,int);
void gotoXY(int,int,string);
void gotoXY(int,int,char);
void drawconsole();
void homepage(bool);
void level(bool);
void stage(bool);
void help(bool);
void game(bool);
void continue_game(bool);

void stage_normal();
void stage_campaign();
void stage_tunnel();
void stage_apartment();
void stage_maze();
void brdr(int);
void Draw_border(int);


void snake(int);
void fruit(int);
void move_snake(int, int);
void fruit_eaten(int, int);
void game(bool);
char retch();



void Control(int);





vector<int> consolemid(){
    jjj
    return {w.ws_row, w.ws_col};
}


char retch(){
    gotoXY(bs+1, 20);
    return getch();
}

void gotoXY(int row, int col){
    int coll = col + prevconsize[1]/2 - 21; 
    int roww = row + prevconsize[0]/2 - 10;
    printf("\033[%d;%dH",roww,coll);

}


void gotoXY(int row, int col, string str){
    vector<int> changepos = prevconsize = consolemid();
    int coll = col + changepos[1]/2 - 21; 
    int roww = row + changepos[0]/2 - 10;
    printf("\033[%d;%dH",roww,coll);
	cout<<str;
}
void gotoXY(int row, int col, char str){
    vector<int> changepos = prevconsize = consolemid();
    int coll = col + changepos[1]/2 - 21; 
    int roww = row + changepos[0]/2 - 10;
    printf("\033[%d;%dH",roww,coll);
	cout<<str;
}




void Control(int pos){
    if(pos == 0){   // homepage
    homeorcont = 0;
        homepagecontentpos=homepagecontentpos<0?2:homepagecontentpos;
        homepagecontentpos=homepagecontentpos>2?0:homepagecontentpos;
        homepage(1);
        char c = retch();
        if(c == 'w')homepagecontentpos--, homepagecontentpos=homepagecontentpos<0?2:homepagecontentpos;
        else if(c == 's')homepagecontentpos++, homepagecontentpos=homepagecontentpos>2?0:homepagecontentpos;
        else if(c == 'j'){
            homepage(0);
            if(homepagecontentpos == 0){
                homepagecontentpos = 3;
            }
            Control(homepagecontentpos);
            return;
        }
        else{
            Control(pos);
            return;
        }
        homepage(0);
        Control(0);
    }
    if(pos == 1){   // Help
        help(1);
        for(char c = retch(); c-'j'; c=getch());
        help(0);
        Control(homeorcont);
    }
    if(pos == 2){   // Exit
        etg = 1;
        return;
    }
    if(pos == 3){   // Level
        level(1);
        char c = retch();
        if(c == 'd')levelh++;
        else if(c == 'a')levelh--;

        if(levelh == -1)levelh = 0;
        else if(levelh == 3)levelh = 2;

        if(c == 'j'){
            level(0);
            Control(4);
            return;
        }

        level(0);
        Control(3);
    }
    if(pos == 4){   // Stages
        if(stageh==5)stageh=0;
        stage(1);
        char c = retch();
        if(c == 'd' or c == 's')stageh++;
        else if(c == 'a' or c == 'w')stageh--;

        if(stageh == -1)stageh=4;
        else if(stageh == 5)stageh=0;

        if(c == 'j'){
            stage(0);
            brdr(0);
            game(0);
            if(stageh == 0)stage_normal();
            else if(stageh == 1)stage_campaign();
            else if(stageh == 2)stage_tunnel();
            else if(stageh == 3)stage_apartment();
            else if(stageh == 4)stage_maze();
            game(1);
            return;
        }
        stage(0);
        Control(4);
    }
    if(pos == 5){   // continue
        homeorcont = 5;
        if(continuecontentpos == -1)continuecontentpos=3;
        if(continuecontentpos == 4)continuecontentpos=0;
        continue_game(1);
        char c = retch();
        if(c == 'w')continuecontentpos--;
        else if(c == 's')continuecontentpos++;
        
        if(continuecontentpos == -1)continuecontentpos=3;
        if(continuecontentpos == 4)continuecontentpos=0;

        if(c == 'j'){
            continue_game(0); // Continue
            if(continuecontentpos == 0){
                return;
            }
            else if(continuecontentpos == 1){ // New Game -> Level
                game(0);
                Control(3);
            }
            else if(continuecontentpos == 2){ // Level
                Control(1);
            }
            else if(continuecontentpos == 3){ // Exit
                continue_game(0);
                Control(2);
            }
            return;
        }
        else{
            Control(pos);
            return;
        }
        continue_game(0);
        Control(5);
    }

}


void stage_normal(){
    for(int i=0; i<bs; i++)gotoXY(i, 0, "|"), totalboard[i][0]=3;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs, "|"),totalboard[i][2*bs]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(0,i, "_"),totalboard[0][i]=3;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i, "\'"),totalboard[bs-1][i]=3;    
}

void stage_campaign(){
    for(int i=0; i<=2*bs; i++)gotoXY(0,i, border), totalboard[0][i]=1;
    for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i, border),totalboard[bs-1][i]=1;
    for(int i=0; i<bs; i++)gotoXY(i, 0, border),totalboard[i][0]=1;
    for(int i=0; i<bs; i++)gotoXY(i, 2*bs, border),totalboard[i][2*bs]=1;
}

void stage_tunnel(){    // ********************************************** 
    stage_normal();

    string solid(10, border);
    gotoXY(0,0,solid); gotoXY(bs-1,0,solid); gotoXY(0, 2*bs-9, solid); gotoXY(bs-1, 2*bs-9, solid);
    for(int i=0; i<10; i++)totalboard[0][i] = totalboard[bs-1][i] = totalboard[0][2*bs-9+i] = totalboard[bs-1][2*bs-9+i] = 1;

    for(int i=11; i<=bs+bs-11; i++)gotoXY(6, i), cout<<(char)border, totalboard[6][i] = 1;
    for(int i=11; i<=bs+bs-11; i++)gotoXY(bs-6, i), cout<<(char)border, totalboard[bs-6][i] = 1;
}

void stage_apartment(){
    stage_normal();
    string s; s+=border;
    for(int i=0; i<=2*bs; i++)gotoXY(6, i, s), totalboard[6][i]=1;
    for(int i=1; i<=6; i++)gotoXY(i, 16, s), totalboard[i][16]=1;
    for(int i=1; i<=6; i++)gotoXY(i, 17, s), totalboard[i][17]=1;
    for(int i=0; i<=2*bs; i++)
    if(i<13 or i>19) gotoXY(bs-6, i, s), totalboard[bs-6][i]=1;
    
}

void stage_maze(){
    stage_apartment();
    for(int i=bs-6; i<bs; i++)gotoXY(i, 20, (char)219), totalboard[i][20]=1;
    for(int i=bs-6; i<bs; i++)gotoXY(i, 21, (char)219), totalboard[i][21]=1;
    for(int i=14; i<30; i++)gotoXY(bs-1, i, (char)219), totalboard[bs-1][i]=1, totalboard[0][i]=1;
    for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs-1, (char)219), totalboard[i][2*bs-1]=1;
    for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs, (char)219), totalboard[i][2*bs]=1, totalboard[i][0]=1;
    
}



void snake(int key){
    if(key == 1){
        for(int i=0, j=0; i<snakelen-1; i++, j+=2){
            if(i&1)gotoXY(snakeposx[i], snakeposy[i], "o");
            else gotoXY(snakeposx[i], snakeposy[i], (char)248);
        }
        gotoXY(snakeposx[snakelen-1], snakeposy[snakelen -1], "O");
    }
    else if(key == 0){
        for(int i=0; i<snakelen; i++){
            gotoXY(snakeposx[i], snakeposy[i]);cout<<" ";
        }
    }
    else{
        snakelen = 9;
        for(int i=0, j=0; i<snakelen; i++, j+=2){
            snakeposx[i] = 10;
            snakeposy[i] = 16+j;
            totalboard[10][16+j] = 1;
        }
        totalboard[10][34] = 0;
    }
}

void fruit(int key){
    if(key == 1){
        totalboard[fruitposx][fruitposy] = 2;
        gotoXY(fruitposx, fruitposy, "#");
    }
    else if(key == 0){
        gotoXY(fruitposx, fruitposy); cout<<" ";
    }
    else{
            if(gameover){
            totalboard[fruitposx][fruitposy] = 0;
            gotoXY(fruitposx, fruitposy),cout<<' ';
            return;}
            totalboard[fruitposx][fruitposy] = 0;
        fruitposy = rand()%(bs-1); fruitposy = 2*fruitposy+2;
        fruitposx = rand()%(bs-2); fruitposx++;
        int x = fruitposx;
        int y = fruitposy;
        if(totalboard[x][y])fruit(3);
        else totalboard[x][y] = 2;
    }
}


void move_snake(int x, int y){
    snakeposx[snakelen] = x; snakeposy[snakelen] = y;

    totalboard[snakeposx[0]][snakeposy[0]] = 0;
    totalboard[x][y] = 1;


    gotoXY(snakeposx[0], snakeposy[0]); cout<<" ";
    gotoXY(x, y, 'O');
    gotoXY(snakeposx[snakelen-1], snakeposy[snakelen-1], (snakelen-1+f)&1?(char)248:'o');

    for(int i=0; i<snakelen; i++)snakeposx[i]=snakeposx[i+1], snakeposy[i]=snakeposy[i+1];

    f=!f;
}

void fruit_eaten(int x, int y){
    point += 10;

    snakeposx[snakelen] = x;
    snakeposy[snakelen] = y;

    gotoXY(x, y);totalboard[x][y]=1; cout<<"O";
    gotoXY(snakeposx[snakelen-1], snakeposy[snakelen-1], (snakelen-1+f)&1?(char)248:'o'); 

    snakelen++;
    fruit(3);

    if(point == targetpoint[stageh])gameover=1;
}

void key_press(){
    int x=snakeposx[snakelen-1], y=snakeposy[snakelen-1];
    if(_kbhit()) 
    cs=retch();

    if(!(cs=='a' or cs=='s' or cs=='d' or cs=='w' or cs=='j'))cs = ch;

    else if(cs+ch==234 or cs+ch==197)cs=ch;

    else if(cs == 'j'){
        snake(0); fruit(0); brdr(0);
        gotoXY(-2, 20);cout<<"                 ";
        continuecontentpos = 0;
        Control(5);
        if(etg)return;
        brdr(3);
        cs=ch;
    }
    else ch = cs;

    if(cs=='w')x--;
    else if(cs=='s')x++;
    else if(cs=='a')y-=2;
    else if(cs=='d')y+=2;


    if(totalboard[x][y] == 1){
        gotoXY(snakeposx[snakelen-1], snakeposy[snakelen-1], 'X');
        gameover = 1;
    }
    else if(totalboard[x][y] == 2)fruit_eaten(x,y);
    else if(totalboard[x][y] == 3){
        if(x == 0)x=bs-2;
        else if(x == bs-1)x=1;
        else if(y == 0)y=2*bs-2;
        else if(y == 2*bs)y=2;

        if(totalboard[x][y] == 2)fruit_eaten(x,y);
        else move_snake(x,y);
    }
    else move_snake(x,y);
    gotoXY(bs+1,20);
}

void game(bool key){
    if(key){
        cs = 'd';
        point = gameover = 0;
        snake(3);
        fruit(3);
        while(gameover == 0){
            gotoXY(-2, 20, " ");
            cout<<point<<"/"<<targetpoint[stageh];
            snake(1);
            fruit(1);
            key_press();
            if(etg)return;
            usleep(130000);
            snake(0);
            fruit(0);
            gotoXY(-2, 20);cout<<"                 ";
            brdr(1);
        }
        brdr(0);
        gotoXY(10, 10, point==targetpoint[stageh]?"You passed!    ":"Game Over!     ");cout<<point<<'/'<<targetpoint[stageh];
        gotoXY(12, 10, "Press j to go to homepage");
        gotoXY(14, 10, "Press x to go to next level");
        gameover = 0;
        point = 0;
        
        for(cs = retch(); cs-'j' and cs-'x'; cs=retch());
        gotoXY(10, 10);cout<<"                              ";
        gotoXY(12, 10);cout<<"                           ";
        gotoXY(14, 10);cout<<"                              ";

        if(cs == 'j')Control(0);
        else stageh++, Control(4);
    }
    else{
        snake(0);
        fruit(0);
        for(int i=0; i<=21; i++)for(int j=0; j<=50; j++)totalboard[i][j]=0;
    }
}

void brdr(int key){
    vector<int> kkkk = consolemid();
    if(key == 0 or kkkk != prevconsize){
        for(int i=0; i<bs; i++)gotoXY(i, 0), cout<<' ';
        for(int i=0; i<bs; i++)gotoXY(i, 2*bs), cout<<' ';
        for(int i=0; i<=2*bs; i++)gotoXY(0,i), cout<<' ';
        for(int i=0; i<=2*bs; i++)gotoXY(bs-1,i), cout<<' ';

        for(int i=0; i<=2*bs; i++)gotoXY(6, i), cout<<' ';
        for(int i=1; i<=6; i++)gotoXY(i, 16), cout<<' ';
        for(int i=1; i<=6; i++)gotoXY(i, 17), cout<<' ';
        for(int i=0; i<=2*bs; i++)gotoXY(bs-6, i), cout<<' ';

        
        for(int i=bs-6; i<bs; i++)gotoXY(i, 20), cout<<' ', totalboard[i][20]=0;
        for(int i=bs-6; i<bs; i++)gotoXY(i, 21), cout<<' ', totalboard[i][21]=0;
        for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs-1), cout<<' ', totalboard[i][2*bs-1]=0;
        for(int i=bs-3; i<bs; i++)gotoXY(i, 2*bs), cout<<' ', totalboard[i][2*bs]=0, totalboard[i][0]=0;


        string solid(10, ' ');
        gotoXY(0,0,solid); gotoXY(bs-1,0), cout<<solid; gotoXY(0, 2*bs-9), cout<<solid; gotoXY(bs-1, 2*bs-9), cout<<solid;
        for(int i=0; i<10; i++)totalboard[0][i] = totalboard[bs-1][i] = totalboard[0][2*bs-9+i] = totalboard[bs-1][2*bs-9+i] = 0;


        if(key == 0){
            for(int i=0; i<bs+1; i++)for(int j=0; j<=50; j++)totalboard[i][j]=0;
            return;
        }

        if(stageh == 0)stage_normal();
        else if(stageh == 1)stage_campaign();
        else if(stageh == 2)stage_tunnel();
        else if(stageh == 3)stage_apartment();
        else if(stageh == 4)stage_maze();
    }
    else if(key == 3){
        if(stageh == 0)stage_normal();
        else if(stageh == 1)stage_campaign();
        else if(stageh == 2)stage_tunnel();
        else if(stageh == 3)stage_apartment();
        else if(stageh == 4)stage_maze();

    }
}





void homepage(bool key){
    if(key){
        int i=1;
        for(auto it: homepagecontent){
            if(homepagecontentpos == i-1)gotoXY(i*5+1, (bdc - it.size() )/2 - 2, ">");
            else gotoXY(i*5+1, (bdc - it.size() )/2 - 2, " ");
            
            gotoXY(i++*5+1, (bdc - it.size() )/2, it);
        }
    }
    else{
        int i=1;
        for(auto it: homepagecontent){
            gotoXY(i++*5+1, (bdc - it.size())/2 - 2), cout<<"                ";
        }
    }
    gotoXY(22,20);
}

void continue_game(bool key){
    if(key){
        int i=1;
        for(auto it: continuecontent){
            if(continuecontentpos == i-1)gotoXY(i*4+1, (bdc - it.size() )/2 - 2, ">");
            else gotoXY(i*4+1, (bdc - it.size() )/2 - 2, " ");
            
            gotoXY(i++*4+1, (bdc - it.size() )/2, it);
        }
    }
    else{
        int i=1;
        for(auto it: continuecontent){
            gotoXY(i++*4+1, (bdc - it.size())/2 - 2), cout<<"                ";
        }
    }
    gotoXY(22,20);
}

void help(bool key){
    int i=1;
    if(key){
        for(auto it: helpstr){
            if(i>2)gotoXY(++i+1, 5, it);
            else gotoXY(++i+1, (bdc - it.size())/2, it );
        }
    }
    else{
        for(auto it: helpstr){
            string s(it.size(), ' ');
            if(i>2)gotoXY(++i+1, 5), cout<<s;
            else gotoXY(++i+1, (bdc - it.size())/2), cout<<s;
        }
    }
}

void level(bool key){
    if(key){
        string dots(16, '.'), updots(16, '\''), str(5*levelh+5, (char)219), strr(5*(2-levelh), ' ');
        str += strr;
        gotoXY(9, 13, dots);
        gotoXY(10,13, "|");
        gotoXY(10, 14, str);
        gotoXY(10, 28, "|");
        gotoXY(11, 13, updots);
    }
    else{
        string dots(17, ' ');
        gotoXY(9, 13); cout<<dots;
        gotoXY(10,13); cout<<dots;
        gotoXY(11, 13); cout<<dots;
    }
}

void stage(bool key){
    if(key){
        int i=1;
        for(auto it: stagestr){
            if(stageh == i-1)gotoXY(i*2+4, i*5, ">");
            gotoXY(i*2+4,i*5+2,it);
            i++;
        }
    }
    else{
        int i=1;
        for(auto it: stagestr){
            string s(it.size()+2, ' ');
            gotoXY(i*2+4,i*5);cout<<s;
            i++;
        }
    }
}

int main(){

    prevconsize = consolemid();

    cs = ch = 'd';
    Control(0);
    // game(1);
}
