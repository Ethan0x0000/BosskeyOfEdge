#include "BossKey.h"



//��ں���
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    
    wstring processName = L"msedge.exe";// ָ��������
    wstring targetClassName = L"Chrome_WidgetWin_1";// ָ����������

    ShowHideWindow(processName, targetClassName);

    return 0;
}
