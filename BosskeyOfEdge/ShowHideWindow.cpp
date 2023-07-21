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
            }
            MuteOn(processName);
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
                }
            }
            MuteOn(processName);
        }
            break;
        case 1:
        {
            // 读取窗口状态
            windowsvector = DeserializeWindowInfoArray(fileName);

            for (const WindowInfo& window : windowsvector)
            {
                if (window.title.compare(L"画中画") == 1)
                {
                    if (!window.isHide)
                    {
                        ShowWindow(window.hWnd, SW_SHOW);
                    }
                }
                else
                {
                    if (window.isMaximized)
                    {
                        ShowWindow(window.hWnd, SW_MAXIMIZE);
                    }
                    else
                    {
                        ShowWindow(window.hWnd, SW_SHOW);
                    }
                }
            }
            MuteOff(processName);
        }
            break;
        default:
            break;
        }
    }
    else 
    {
        MessageBox(NULL, L"你还没有打开任何窗口哦!!!", L"提示", MB_ICONINFORMATION | MB_OK);
    }
    
}
