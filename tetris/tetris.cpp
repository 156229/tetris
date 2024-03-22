// tetris.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "tetris_process.h"
#include <iostream>
#include <Windows.h>
using namespace std;
COORD scrn;
HANDLE hOuput;

void gotoxy(int xpos, int ypos)
{
    hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; 
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void display(vector<vector<int>>board)
{
    gotoxy(0,0);
    for (int y = 0; y < 20; y++)
    {
        cout << "｜";
        for (int x = 0; x < 10; x++)
        { 
            if (board[y][x] == 1)
            {
                cout << "⬜";
            }  
            else
            {
                cout << "  ";
            }
        }
        cout << "｜\n";
    }
    cout << "￣￣￣￣￣￣￣￣￣￣￣￣\n";
}

int main()
{
    tetris_process process;
    int count=0;
    while (1)
    {
        count++;
        if (count >= 12)
        {
            count = 0;
            process.fall();
        }
        Sleep(42);  
        process.move();
        display(process.get_board());
        if (process.end)break;
    }
    cout << "\n\n\n\n\n遊戲結束";
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
