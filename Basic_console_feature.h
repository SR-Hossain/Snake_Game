#include<bits/stdc++.h>
using namespace std;
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <Windows.h>
    
#elif defined(__linux__)
    #include <sys/ioctl.h>
#endif // Windows/Linux

void get_terminal_size(int& height, int& width) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif // Windows/Linux
}

void cursor(int row, int col){
#if defined(_WIN32)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col, row});
#elif defined(__linux__)
    printf("\033[%d;%dH", row, col);
#endif
}


// void mcursor(int row, int col){
//     int winrow=0, wincol=0;
//     get_terminal_size(winrow, wincol);
// #if defined(_WIN32)
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){wid+wincol/2-10, row+winrow/2-10})
// #elif defined(__linux__)
//     printf("\033[%d;%dH", row+winrow/2-10, col+wincol/2-20);
// #endif
// }

void clscreen(){
#if defined(_WIN32)
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
#elif defined(__linux__)
    std::cout << "\x1B[2J\x1B[H";
#endif
}


#if defined(_WIN32)
    void usleep(__int64 usec) 
    { 
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
    }
#endif