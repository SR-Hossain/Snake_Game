#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
int len = 1, lenx[400], leny[400], f[3];
int main()
{
    char area[21][21];
    map<char, int> dir;
    dir['w'] = dir['s'] = 1;
    dir['a'] = dir['d'] = 15;

    memset(area, ' ', sizeof(area));
    for(int i=0; i<21; i++)area[i][0] = area[i][20] = area[0][i] = area[20][i] = '\xFE';

    bool on = 1;
    lenx[0] = leny[0] = 10;
    area[10][10] = 'O';
        f[0] = rand()%18 + 1;
        f[1] = rand()%18 + 1;
        area[f[0]][f[1]] = '#';
    for(int i=0; i<21; i++, cout<<'\n')for(int j=0; j<21; cout<<area[i][j++]<<' ');
    char follow = getch(), key;

    while(on){
        system("cls");
        memset(area, ' ', sizeof(area));
        for(int i=0; i<21; i++)area[i][0] = area[i][20] = area[0][i] = area[20][i] = '\xFE';
        area[f[0]][f[1]] = '#';
        leny[len+1] = leny[0], lenx[len+1] = lenx[0];
        if(_kbhit()){
            key = _getche();
            if(abs(dir[key] - dir[follow]) > 4)follow = key;
        }
             if(follow == 'w')leny[len+1]--;
        else if(follow == 's')leny[len+1]++;
        else if(follow == 'a')lenx[len+1]--;
        else if(follow == 'd')lenx[len+1]++;
        for(int i=len; i>0; i--)lenx[i] = lenx[i-1], leny[i] = leny[i-1];
        lenx[0] = lenx[len+1], leny[0] = leny[len+1];
        len++;
        if(leny[0] - f[0] or lenx[0] - f[1])len--;
        else{
            f[3] += 10; lenx[399] = 1;
            while(lenx[399])
            {
                f[0] = rand()%18 + 1, f[1] = rand()%18 + 1;
                for(int i=0; i<=len; i++)
                {
                    if(i==len)lenx[399]=0;
                    else if(f[0]==leny[0] and f[1]==lenx[0])break;
                }
            }
        }
        for(int i=0; i<len; i++)area[leny[i]][lenx[i]] = 'o';
        area[leny[0]][lenx[0]] = 'O';
        if(lenx[0]==0 or lenx[0]==20 or leny[0]==0 or leny[0]==20)on = 0, area[leny[0]][lenx[0]]='*';
        for(int i=1; i<len; i++)if(lenx[0] == lenx[i] and leny[0] == leny[i]){on = 0, area[leny[0]][lenx[0]]='*';break;}
        for(int i=0; i<21; i++, cout<<'\n')for(int j=0; j<21; cout<<area[i][j++]<<' ');
        cout<<"\nTotal Point : "<<f[3]<<'\n';
        Sleep(30);
    }
    cout<<"Game Over!!!\n"; 
}
