#include "BossKey.h"

//���ػ�����ʾ����
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
                bool isHua = false;
                if (window.title.length() == 4)
                {
                    wstring title = L"���л�";
                    size_t len1 = window.title.length();
                    size_t len2 = title.length();
                    // ���ѭ������1�����п��ܵ��Ӵ�
                    for (size_t i = 0; i < len1; ++i) 
                    {
                        // �ڲ�ѭ������2�����п��ܵ��Ӵ�
                        for (size_t j = 0; j < len2; ++j)
                        {
                            size_t len = 0;
                            // ����i��ʼ��1�Ӵ��Ƿ����j��ʼ��2�Ӵ���ͬ
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
        MessageBox(NULL, L"�㻹û�д��κδ���Ŷ!!!", L"��ʾ", MB_ICONINFORMATION | MB_OK);
    }
    
}
