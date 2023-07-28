#include "BossKey.h"

//隐藏或者显示窗口
void ShowHideWindow(wstring processName, wstring className)
{
    vector<WindowInfo> windowsvector = GetvectorByName(processName, className);

    string fileName = wstring_to_string(className + L".bin") ;

    if (!windowsvector.empty()) 
    {
        switch(IsAllHide(windowsvector))
        {
        case -1:
        {
            // 先进行窗口静音
            MuteOn(processName);

            // 保存窗口状态
            SerializeWindowInfoArray(windowsvector, fileName);

            for (const WindowInfo& window : windowsvector)
            {
                ShowWindow(window.hWnd, SW_HIDE);
            }
        }
            break;
        case 0:
        {
            // 先进行窗口静音
            MuteOn(processName);

            // 先读取之前的窗口状态
            vector<WindowInfo> windowsvectorTemp = DeserializeWindowInfoArray(fileName);

            if (windowsvectorTemp.size() != 0)
            {
                //对新增后的数组进行合并
                for (int i = 0; i < windowsvector.size(); i++)
                {
                    int j = 0;
                    for (; j < windowsvectorTemp.size(); j++)
                    {
                        if (windowsvector[i].hWnd == windowsvectorTemp[j].hWnd)
                        {
                            if (IsHua(windowsvector[i].title))
                            {
                                windowsvectorTemp[j] = windowsvector[i];
                            }
                            break;
                        }
                    }
                    if (j == windowsvectorTemp.size())
                    {
                        windowsvectorTemp.push_back(windowsvector[i]);
                    }
                }
            }
            else
            {
                windowsvectorTemp = windowsvector;
            }

            // 保存窗口状态
            SerializeWindowInfoArray(windowsvectorTemp, fileName);

            for (const WindowInfo& window : windowsvectorTemp)
            {
                if (!window.isHide)
                {
                    ShowWindow(window.hWnd, SW_HIDE);
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
                
                if (IsHua(window.title))
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
