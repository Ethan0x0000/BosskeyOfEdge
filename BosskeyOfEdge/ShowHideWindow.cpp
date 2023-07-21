#include "BossKey.h"

//隐藏或者显示窗口
void ShowHideWindow(wstring processName, wstring className)
{
    vector<WindowInfo> windowsvector = GetvectorByName(processName, className);
    string fileName = "windowstate.bin";

    if (!windowsvector.empty()) 
    {
        switch(IsAllHide(windowsvector))
        {
        case -1:
        {
            // 保存窗口状态
            SerializeWindowInfoArray(windowsvector, fileName);

            for (const WindowInfo& window : windowsvector)
            {
                ShowWindow(window.hWnd, SW_HIDE);
                MuteOn(processName);
            }
        }
            break;
        case 0:
        {
            // 保存窗口状态
            SerializeWindowInfoArray(windowsvector, fileName);

            for (const WindowInfo& window : windowsvector)
            {
                if (!window.isHide)
                {
                    ShowWindow(window.hWnd, SW_HIDE);
                    MuteOn(processName);
                }
            }
        }
            break;
        case 1:
        {
            // 读取窗口状态
            windowsvector = DeserializeWindowInfoArray(fileName);

            for (const WindowInfo& window : windowsvector)
            {
                if (window.isMaximized)
                {
                    ShowWindow(window.hWnd, SW_MAXIMIZE);
                }
                else
                {
                    ShowWindow(window.hWnd, SW_SHOW);
                }
                MuteOff(processName);
            }
        }
            break;
        default:
            break;
        }
    }
    else 
    {
        MessageBox(NULL, L"找不到对应窗口", L"错误", MB_ICONERROR | MB_OK);
    }
    
}
