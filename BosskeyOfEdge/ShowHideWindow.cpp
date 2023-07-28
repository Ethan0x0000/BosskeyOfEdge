#include "BossKey.h"

//���ػ�����ʾ����
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
            // �Ƚ��д��ھ���
            MuteOn(processName);

            // ���洰��״̬
            SerializeWindowInfoArray(windowsvector, fileName);

            for (const WindowInfo& window : windowsvector)
            {
                ShowWindow(window.hWnd, SW_HIDE);
            }
        }
            break;
        case 0:
        {
            // �Ƚ��д��ھ���
            MuteOn(processName);

            // �ȶ�ȡ֮ǰ�Ĵ���״̬
            vector<WindowInfo> windowsvectorTemp = DeserializeWindowInfoArray(fileName);

            if (windowsvectorTemp.size() != 0)
            {
                //���������������кϲ�
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

            // ���洰��״̬
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
            // ��ȡ����״̬
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
        MessageBox(NULL, L"�㻹û�д��κδ���Ŷ!!!", L"��ʾ", MB_ICONINFORMATION | MB_OK);
    }
    
}
