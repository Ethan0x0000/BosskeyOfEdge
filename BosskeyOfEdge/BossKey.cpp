#include "BossKey.h"



//入口函数
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    
    wstring processName = L"msedge.exe";// 指定进程名
    wstring targetClassName = L"Chrome_WidgetWin_1";// 指定窗口类名

    ShowHideWindow(processName, targetClassName);

    return 0;
}
