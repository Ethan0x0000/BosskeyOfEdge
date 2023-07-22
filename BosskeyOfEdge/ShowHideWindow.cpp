#include "BossKey.h"

//隐藏或者显示窗口
void ShowHideWindow(wstring processName, wstring className)
{
    vector<WindowInfo> windowsvector = GetvectorByName(processName, className);
    string fileName = "WindowState.bin";

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
                bool isHua = false;
                if (window.title.length() == 4)
                {
                    wstring title = L"画中画";
                    size_t len1 = window.title.length();
                    size_t len2 = title.length();
                    // 外层循环遍历1的所有可能的子串
                    for (size_t i = 0; i < len1; ++i) 
                    {
                        // 内层循环遍历2的所有可能的子串
                        for (size_t j = 0; j < len2; ++j)
                        {
                            size_t len = 0;
                            // 检查从i开始的1子串是否与从j开始的2子串相同
                            while (i + len < len1 && j + len < len2 && window.title[i + len] == title[j + len])
                            {
                                ++len;
                            }

                            if (len > 0)
                            {
                               isHua = true;
                            }
                        }
                    }
                }
                if (isHua)
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
