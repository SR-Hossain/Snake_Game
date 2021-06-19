#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
int wincol, winrow;
int exit_the_game=0;
#define sp(r, c, k) totalboard[r][c]=k
#define br 23
#define bc 45
int create_new=1, erase=0, draw=2, f, reset_row, reset_col, reset = 7;
int totalboard[br][bc];
    int fruits=3, snakes=4, eagles = 5;

void nothing(){
    return;
}
void new_console_size();
void print(int, int, string);
void print(int, int, char);
void erasef(int, int, string);
void erasef(int, int);
void draw_afresh();


char retch(){
    print(br+1, bc/2, "");
    char kkkk = getch();
    print(br+1, bc/2, "  ");
    return kkkk;
}


void game(int);
    bool tw;
    ///////////////////// mode /////////////////
    bool survival = 1;
    long long highscore;
    int level;
    FILE* storepoint;


        
void snake(int);
    long long snaketail, snakehead, snakelen;
    map<long long, int> snakerow, snakecol;
void fruit(int);
    int fruitrow, fruitcol, point = 5;

void eagle(int);
    map<long long, int> eaglerow, eaglecol;
    int eaglecount = 1;
void board();
    int stageh=1, normal=1, campaign=2, tunnel=3, apartment=4;
bool key_press();
    char cs='d', ch='d';
    void fruit_eaten(int, int);
    void move_snake(int, int);
    void eagle_eaten(int, int);

void lives_and_points(int);
        vector<long long> lives={20, 20, 20, 20, 20, 20};
        vector<long long> points(6);
void printarr(vector<string>);
    vector<string> homestr={"Continue", "New Game", "High Score", "Help", "Exit"};
    vector<string> helpstr = { 
"HELP", 
"________________", 
" ",
"Navigation",
"w",
"a s d",
" ",
"The snake is hunting frog", "but being hunted by eagle", "each time it eats the frog or the", "eagle, it becomes larger and more frog",
"or eagle arise somewhere else.", "If it hit the wall or its body", "or its lives end, then it dies."
};
    vector<string> levelstr = {"Fast", "Slow", "Sloth"};
    int pointpos;

void control();
    




void move_snake(int row, int col){
    print(snakerow[snaketail], snakecol[snaketail], "erase");
    print(snakerow[snakehead], snakecol[snakehead], (snakelen-1+f)&1?"ờ":"ợ"); f=!f;

    snaketail++;
    snakehead++; 

    snakerow[snakehead] = row;
    snakecol[snakehead] = col;
    print(row, col, "O");
    print(br+1, bc/2, "  ");
}
void fruit_eaten(int row, int col){
    snakelen++;
    lives[stageh]+=5;
    lives[0]+=5;
    points[stageh]++;
    print(snakerow[snakehead], snakecol[snakehead], (snakelen-1+f)&1?"ờ":"ợ"); 
    snakehead++;
    snakerow[snakehead] = row;
    snakecol[snakehead] = col;
    print(row, col, "O");

    fruit(create_new);
    fruit(draw);
 
    print(br+1, bc/2, "  ");

}


void eagle_eaten(int row, int col){
    reset_row = row, reset_col = col;
    eagle(reset);

    eagle(create_new);
    snakelen++;
    lives[stageh]+=10;
    lives[0]+=20;
    // print(snakerow[snakehead], snakecol[snakehead], (snakelen-1+f)&1?"ờ":"ợ"); 
    snakehead++;
    snakerow[snakehead] = row;
    snakecol[snakehead] = col-!(col&1);
    snake(draw);
    fruit(draw);
    print(row, col-!(col&1), "O");


}





bool key_press(){
    int row=snakerow[snakehead], col = snakecol[snakehead];

    eagle(draw);
    fruit(draw);
    if(_kbhit()) cs = retch();


    if(!(cs=='a' or cs=='s' or cs=='d' or cs=='w' or cs=='j'))cs = ch;
    else if(cs+ch==234 or cs+ch==197)cs=ch;
    else if(cs == 'j'){
        system("clear");
        control();
        if(exit_the_game == 1)return 0;
        draw_afresh();
        retch();
        cs = ch;
    }
    ch = cs;


    if(cs=='w')row--;
    else if(cs=='s')row++;
    else if(cs=='a')col-=2;
    else if(cs=='d')col+=2;


    if(totalboard[row][col] == campaign) return 0;
    else if(totalboard[row][col] == snakes) return 0;
    else if(totalboard[row][col] == fruits)fruit_eaten(row, col);
    else if(totalboard[row][col] == eagles)eagle_eaten(row, col);


    
    else{ 
        if(totalboard[row][col] == normal){
            if(col <= 0)col = bc-2;
            else if(row == 0)row = br-2;
            else if(row == br-1)row = 1;
            else if(col >= bc-1)col = 1;
        }
        if(totalboard[row][col] == campaign)return 0;
        else if(totalboard[row][col] == snakes)return 0;
        else if(totalboard[row][col] == fruits)fruit_eaten(row, col);
        else if(totalboard[row][col] == eagles)eagle_eaten(row, col);
        else {
            move_snake(row, col);
        }
    }

    if(points[stageh] == point){lives_and_points(draw);return 0;}
    if(survival){
        
        if(lives[0] <= 0){
            return 0;
        }
    }
    // eagle(draw);
    return 1;
}


void game(int key){
    if(exit_the_game == 1)return;

    if (key == 1)
    {
        game(0);
        board();
        snake(draw);
        fruit(draw);
        while (tw = key_press())
        {
            new_console_size();
            lives_and_points(draw);
            usleep(70000+level*10000);
        }
        if(exit_the_game)return;
        getch();
        fruit(erase);
        snake(erase);
        system("clear");
        while(1){
                if(_kbhit())
                    cs = getch();
                    if(cs == 'j')break;
                new_console_size();
                if(points[stageh] == point){
                    if(cs == 'x')break;
                    print(br/2-3, bc/2-10, "Stage complete!!!");
                    if(survival)print(br/2-1, bc/2-12, "Remaining Lives = "),cout<<lives[0];
                    else print(br/2-1, bc/2-12, "Remaining Lives = "),cout<<lives[stageh];
                    print(br/2+1, bc/2-16, "Press x to jump to next stage");
                    print(br/2+3, bc/2-14, "Press j to go to homepage");
                    print(br+2, bc/2, "");
                }
                else{
                    print(br/2-1, bc/2-6, "You FAILED!!!");
                    print(br/2+1, bc/2-13, "Press j to go to homepage");
                    print(br+2, bc/2, "");
                }
                if(cs == 'j');
            }
        if(cs == 'x'){
            stageh++;
            if(survival)lives[0]+=stageh*2;
            if(stageh == apartment+1){
                print(br/2, bc/2-10, "All Stages Complete!!!");
                if(highscore < lives[0]){
                    highscore = lives[0];
                    storepoint = fopen("Snake_Game_Score.txt", "w");
                    fprintf(storepoint, "%d", highscore);
                    fclose(storepoint);
                }
                usleep(200000);
                return;
                }
            else game(1);
            return;
        }
        system("clear");
    }
    if(key == 0){
        lives[0] = 20;
        survival=1;
        system("clear");
        points = {0,0,0,0,0,0};
        // lives = {0,0,0,0,0,0};
        cs = ch = 'd';
        tw = 1;
        new_console_size();
        snakelen = 9; eaglecount = 0;
        snaketail = 0;
        snakehead = 8;
        memset(totalboard, 0, sizeof(totalboard));
        snake(create_new);
        fruit(create_new);
        eagle(create_new);
    }
}


void eagle(int key){
    if(key == reset){
        for(int i=0; i<eaglecount; i++){
            if(eaglerow[i] == reset_row and eaglecol[i] == reset_col){
                eaglerow[i] = rand()%(br-2)+1;
                eaglecol[i] = ( (bc-rand()%4-4)/2 )*2+1;
                if(totalboard[eaglerow[i]][eaglecol[i]]){
                    eagle(reset);
                    return;
                }
                else{
                    sp(eaglerow[i], eaglecol[i], eagles);
                    return;
                }
            }
        }
        return;
    }
    if(key == create_new){
        eaglerow[eaglecount] = rand()%(br-2)+1;
        eaglecol[eaglecount] = ( (int)(bc-rand()%4-4)/2 )*2 + 1;
        if(totalboard[eaglerow[eaglecount]][eaglecol[eaglecount]]){
            eagle(create_new);
            return;
        }
        else{
            sp(eaglerow[eaglecount], eaglecol[eaglecount], eagles);
            eaglecount++;
            return;
        }
    }
    else if(key == draw){
        for(int i=0; i<eaglecount; i++){
            if(totalboard[eaglerow[i]][eaglecol[i]-2] == snakes){lives[stageh]--;lives[0]--;continue;}
            print(eaglerow[i], eaglecol[i], "erase");
            eaglecol[i]-=2;
            if(eaglecol[i] <= 0 or totalboard[eaglerow[i]][eaglecol[i]] == campaign){
                eaglerow[i] = rand()%(br-1)+1;
                eaglecol[i] = bc - 4;
                while(totalboard[eaglerow[i]][eaglecol[i]]){
                    eaglerow[i] = rand()%(br-2)+1;
                    eaglecol[i]-=2;
                    if(eaglecol[i] <= 0)eaglecol[i]=bc-4;
                }
            }
            print(br+1, bc/2, "         ");
            print(eaglerow[i], eaglecol[i], "🦅");    
        }
    }
    if(totalboard[snakerow[snakehead]][snakecol[snakehead]] == eagles)eagle_eaten(snakerow[snakehead], snakecol[snakehead]);
    snake(draw);
    print(br+2, bc/2, "    ");
}



void snake(int key){
    if(key == create_new){
        for(int i=0, j=snaketail; j<=snakehead; i++, j++){
            snakerow[j]=10, snakecol[j]=11+i+i;
            sp(10, 11+i+i, snakes);
        }
    }
    if(key == draw){
        new_console_size();
        for(int i=snaketail; i<=snakehead; i++)
            print(snakerow[i], snakecol[i], i==snakehead?"O":i&1?"ợ":"ờ");
    }
    if(key == erase){
        for(int i=snaketail; i<=snakehead; i++)
            print(snakerow[i], snakecol[i], ' ');
    }
}



void fruit(int key){
    if(key == create_new){
        int x = fruitrow = rand()%(br-2)+1;
        int y = fruitcol = (rand()%( (bc-3)/2 )*2)+1;

        if(totalboard[x][y] == 0)totalboard[x][y]=fruits;
        else fruit(create_new);
    }
    else if(key == draw){
        print(fruitrow, fruitcol, "🐸");
        print(br+2, bc/2, "      ");
    }
    else if(key == erase){
        if(totalboard[fruitrow][fruitcol]==fruits)print(fruitrow, fruitcol, "erase");
    }
}

void board()
{
    if (stageh == normal)
    {
        for (int i = 0; i < br; i++) print(i, -1, "🟩"), print(i, bc - 1, "🟩");
        for (int i = -1; i < bc; i += 2) print(0, i, "🟩"), print(br - 1, i, "🟩");

        for(int i=0; i<br; i++)sp(i, 0, normal), sp(i, bc-1, normal);
        for(int i=0; i<bc; i++)sp(0, i, normal), sp(br-1, i, normal);
    }
    else if (stageh == campaign)
    {
        for (int i = 0; i < br; i++) print(i, -1, "🧱"), print(i, bc - 1, "🧱"); // |
        for (int i = -1; i < bc; i += 2) print(0, i, "🧱"), print(br - 1, i, "🧱"); // _

        for(int i=0; i<br; i++)sp(i, 0, campaign), sp(i, bc-1, campaign);
        for(int i=0; i<bc; i++)sp(0, i, campaign), sp(br-1, i, campaign);

    }
    else if (stageh == tunnel)
    {
        for(int i=0; i<br; i++)sp(i, 0, normal), sp(i, bc-1, normal);
        for(int i=0; i<bc; i++)sp(0, i, normal), sp(br-1, i, normal);



        for (int i = 11; i <= bc - 11; i += 2) print(7, i, "🧱"), print(br - 8, i, "🧱");



        for(int i=1; i<=4; i++)print(i, -1, "🧱"), print(i, bc-1, "🧱"), print(br-1-i, -1, "🧱"), print(br-1-i, bc-1, "🧱");
        for(int i=-1; i<=8; i+=2)print(0, i, "🧱"), print(br-1, i, "🧱"), print(0, bc-2-i, "🧱"), sp(0, bc-1-i, campaign), print(br-1, bc-2-i, "🧱"), sp(br-1, bc-1-i, campaign);


    }
    else if(stageh == apartment){
        for(int i=0; i<br; i++)sp(i, 0, normal), sp(i, bc-1, normal);
        for(int i=0; i<bc; i++)sp(0, i, normal), sp(br-1, i, normal);

        for (int i = -1; i <= bc; i += 2) print(7, i, "🧱"), i<20?print(br-8, i, "🧱"):nothing() ,i> 32 ? print(br - 8, i-1, "🧱"),sp(br-8, i, campaign) : 1;
        for (int i = 0; i < 8; i++) print(i, 13, "🧱");

        for(int i=1; i<=4; i++)print(i, -1, "🧱"), print(i, bc-1, "🧱"), print(br-1-i, -1, "🧱"), print(br-1-i, bc-1, "🧱");
        for(int i=-1; i<=8; i+=2)print(0, i, "🧱"), print(br-1, i, "🧱"), print(0, bc-2-i, "🧱"), sp(0, bc-1-i, campaign), print(br-1, bc-2-i, "🧱"), sp(br-1, bc-1-i, campaign);

    }
}

int main(){
    ifstream danzo("Snake_Game_Score.txt");
    if(danzo.good()==0){
        danzo.close();
        ofstream danzo("Snake_Game_Score.txt");
        danzo<<0;
        danzo.close();
    }
    else {
        string strd;
        getline(danzo, strd);
        const char* sttr = strd.c_str();
        sscanf(sttr, "%d", &highscore);
        danzo.close();
    }

    // game(1); 
    // system("clear");
    new_console_size();
    // printarr(homestr);
    // getch();
    // system("clear");
    // printarr(helpstr);
    control();
}

void printarr(vector<string> vec){
    cs = 'o';int it=0, veclen = vec.size();
    if(!tw){
        it = 1;
        if(pointpos == 0)pointpos = -1;
    }
    if(pointpos == -1)pointpos = vec.size()-1;
    if(pointpos == vec.size())pointpos = tw?0:1;
    int skp = br/veclen;
    int row = 11 - skp*(veclen/2);
    for(; it<veclen; it++){
        print(row, bc/2-vec[it].size()/2, vec[it]);
        if(veclen<8 and it==pointpos) print(row,bc/2-vec[it].size()/2-2,'>');

        row += skp;
    }
    print(br+2, bc/2, "");

    while(1){
        if(_kbhit()){
            cs = getch();
            if(cs == 's' or cs == 'd')pointpos++;
            else if(cs == 'a' or cs == 'w')pointpos--;
            else if(cs == 'j'){system("clear");return;}
            else continue;
            system("clear");
            printarr(vec);
            return;
        }
        int precol=wincol, prerow=winrow;
        wincol=WEXITSTATUS(std::system("exit `tput cols`"));
        winrow = WEXITSTATUS(std::system("exit `tput lines`"));
        if(precol-wincol or prerow-winrow){
            system("clear");
            printarr(vec);
            return;
        }
    }
}

void control(){
    if(exit_the_game == 1)return;
    printarr(homestr);
    if(pointpos == 1){
        stageh = normal;
        tw = 1;
        printarr(levelstr);
        level = pointpos;
        game(1);
        control();
        return;
    }
    else if(pointpos == 2){
        system("clear");
        print(br/2, bc/2, "");
        cout<<highscore;
        print(br+2, bc/2, "");
        getch();
        system("clear");
        control();
        return;
    }
    else if(pointpos == 3){
        printarr(helpstr);
        control();
        return;
    }
    else if(pointpos == 4 or pointpos == 0){exit_the_game=1; system("clear");return;}
}

















void lives_and_points(int key)
{
    if (key == erase) {
        print(-3, bc / 2 - 12, "                               ");
        print(-2, bc / 2 - 6, "                               ");

    }

    
    if (key == draw) {
        lives_and_points(erase);
        print(-3, bc / 2 - 12, " ");
        cout << "Remaining Lives = " << lives[0] * 10;
        print(-2, bc/2-2, "");
        cout<<points[stageh]<<" / "<<point;
    }
}



















void print(int row, int col, string str)
{
    printf("\033[%d;%dH", row+winrow/2-10, col+wincol/2-20);
    if(str!="erase")cout<<str;
    if(col == -1)col=0;
    if(str =="🧱")sp(row, col, campaign);
    else if(str=="erase")sp(row, col, 0), cout<<' ';
    else if(str == "O")sp(row, col, snakes);
    else if(str == "🐸")sp(row, col, fruits);
    else if(str == "🦅")sp(row, col, eagles);
}


void erasef(int row, int col, string str)
{
    printf("\033[%d;%dH", row+winrow/2-10, col+wincol/2-23);
    cout<<str;
}

void print(int row, int col, char str)
{
    printf("\033[%d;%dH%c", row+winrow/2-10, col+wincol/2-20, str);
}


void erasef(int row, int col)
{
    printf("\033[%d;%dH ", row+winrow/2-10, col+wincol/2-23);
}

void new_console_size(){
    int precol=wincol, prerow=winrow;
    wincol=WEXITSTATUS(std::system("exit `tput cols`"));
    winrow = WEXITSTATUS(std::system("exit `tput lines`"));
    if(precol-wincol or prerow-winrow){
        if(tw)draw_afresh();
        else system("clear");
    }

}

void draw_afresh(){
    system("clear");
    snake(draw);
    fruit(draw);
    eagle(draw);
    board();
}

