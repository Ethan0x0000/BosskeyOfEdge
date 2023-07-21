#include "BossKey.h"

//���ػ�����ʾ����
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
            // ���洰��״̬
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
            // ���洰��״̬
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
            // ��ȡ����״̬
            windowsvector = DeserializeWindowInfoArray(fileName);

            for (const WindowInfo& window : windowsvector)
            {
                if (window.title.compare(L"���л�") == 1)
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
        MessageBox(NULL, L"�㻹û�д��κδ���Ŷ!!!", L"��ʾ", MB_ICONINFORMATION | MB_OK);
    }
    
}
