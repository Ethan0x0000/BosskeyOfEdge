#include "BossKey.h"


vector<WindowInfo> GetvectorByName(const wstring& processName, const wstring& className)
{
    vector<WindowInfo> windowsvector;
    HWND hWnd = NULL;

    do {
        hWnd = FindWindowEx(NULL, hWnd, className.c_str(), NULL);
        if (hWnd != NULL) 
        {
            DWORD processId = 0;
            GetWindowThreadProcessId(hWnd, &processId);
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

            if (hProcess != NULL) 
            {
                WCHAR szProcessName[MAX_PATH] = { 0 };
                if (GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH)) 
                {
                    wstring foundProcessName = szProcessName;
                    size_t foundPos = foundProcessName.find_last_of(L"\\");
                    if (foundPos != wstring::npos)
                    {
                        foundProcessName = foundProcessName.substr(foundPos + 1);
                    }

                    if (foundProcessName == processName) 
                    {
                        // 在此处理找到后的操作
                        int titleLength = GetWindowTextLength(hWnd);
                        if (titleLength > 0) {
                            wstring title;
                            title.resize(titleLength + 1);
                            GetWindowText(hWnd, &title[0], titleLength + 1);
                            bool isHide = !IsWindowVisible(hWnd);
                            bool isMaximized = IsZoomed(hWnd);
                            windowsvector.push_back({ hWnd, title, isHide, isMaximized});
                        }
                    }
                }

                CloseHandle(hProcess);
            }
        }
    } while (hWnd != NULL);

    return windowsvector;
}