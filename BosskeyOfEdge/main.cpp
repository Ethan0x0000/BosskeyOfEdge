#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <Mmsystem.h>
#include <fstream>
#include <map>
#include <shellapi.h>
#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

string GetUserDocumentsPath()
{
    char* documentsPath;
    string path;

#ifdef _WIN32
    size_t requiredSize;
    getenv_s(&requiredSize, nullptr, 0, "USERPROFILE");
    if (requiredSize > 0)
    {
        documentsPath = new char[requiredSize];
        getenv_s(&requiredSize, documentsPath, requiredSize, "USERPROFILE");
        path = documentsPath;
        path += "\\Documents\\";
        delete[] documentsPath;
    }
#else
    documentsPath = getenv("HOME");
    if (documentsPath != nullptr)
    {
        path = documentsPath;
        path += "/Documents/";
    }
#endif

    return path;
}

// �洢���״̬���û��ĵ�Ŀ¼�е��ļ�
void StoreWindowState(bool isMaximized) {
    std::string filePath = GetUserDocumentsPath() + "window_state.txt";
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << (isMaximized ? "1" : "0") ;
        file.close();
    }
}

// ���û��ĵ�Ŀ¼�е��ļ��ж�ȡ���״̬������״̬
bool ReadWindowState() {
    std::string filePath = GetUserDocumentsPath() + "window_state.txt";
    std::ifstream file(filePath);
    if (file.is_open()) {
        bool isMaximized;
        file >> isMaximized;
        file.close();
        return (isMaximized == 1);
    }
    return false;
}

//���ػ�����ʾ����
void ShowOrHideWindow(HWND hWnd)
{
    wstring targetClassName = L"Chrome_WidgetWin_1";  // Ŀ�괰������,����ΪEdge����������������ǿ�ж�

    // ��ȡ��������
    wchar_t className[256];
    GetClassNameW(hWnd, className, 256);

    // ��鴰�������Ƿ���Ŀ������ƥ��
    wstring currentClassName = className;
    if (currentClassName == targetClassName)
    {
        char title[MAX_PATH];
        if (GetWindowTextA(hWnd, title, MAX_PATH) > 0)
        {
            if (strcmp(title, "���л�") != 0)
            {
                if (IsWindowVisible(hWnd) && GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)
                {
                    StoreWindowState(IsZoomed(hWnd));
                    // ���ش���
                    ShowWindow(hWnd, SW_HIDE);

                    // ���ھ���
                    LPCWSTR executableName = L"nircmd.exe";
                    LPCWSTR parameters = L"muteappvolume msedge.exe 1";// 1��ʾ������0��ʾȡ������

                    WCHAR executablePath[MAX_PATH];
                    WCHAR programPath[MAX_PATH];

                    // ��ȡ��ǰ�����Ŀ¼·��
                    GetModuleFileName(NULL, programPath, MAX_PATH);
                    PathRemoveFileSpec(programPath);

                    // ���õ�ǰĿ¼Ϊ�����Ŀ¼·��
                    SetCurrentDirectory(programPath);

                    // ʹ�����·����ȡ��ִ���ļ���λ��
                    wcscpy_s(executablePath, MAX_PATH, executableName);

                    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
                    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                    shellExecuteInfo.lpVerb = L"open";
                    shellExecuteInfo.lpFile = executablePath;
                    shellExecuteInfo.lpParameters = parameters;
                    shellExecuteInfo.nShow = SW_HIDE;  // ���ش���

                    if (ShellExecuteEx(&shellExecuteInfo))
                    {
                        // �ȴ������н���ִ�����
                        WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
                        CloseHandle(shellExecuteInfo.hProcess);
                    }
                    else
                    {
                        // ִ��������ʧ��
                        MessageBox(NULL, L"�޷�ִ��������", L"����", MB_ICONERROR | MB_OK);
                    }
                }
                else
                {
                    // ��ʾ����
                    if (ReadWindowState())
                    {
                        ShowWindow(hWnd, SW_MAXIMIZE);
                    }
                    else
                    {
                        ShowWindow(hWnd, SW_SHOW);
                    }
                    
                  
                    // ����ȡ������
                    LPCWSTR executableName = L"nircmd.exe";
                    LPCWSTR parameters = L"muteappvolume msedge.exe 0";

                    WCHAR executablePath[MAX_PATH];
                    WCHAR programPath[MAX_PATH];

                    // ��ȡ��ǰ�����Ŀ¼·��
                    GetModuleFileName(NULL, programPath, MAX_PATH);
                    PathRemoveFileSpec(programPath);

                    // ���õ�ǰĿ¼Ϊ�����Ŀ¼·��
                    SetCurrentDirectory(programPath);

                    // ʹ�����·����ȡ��ִ���ļ���λ��
                    wcscpy_s(executablePath, MAX_PATH, executableName);

                    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
                    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                    shellExecuteInfo.lpVerb = L"open";
                    shellExecuteInfo.lpFile = executablePath;
                    shellExecuteInfo.lpParameters = parameters;
                    shellExecuteInfo.nShow = SW_HIDE;  // ���ش���

                    if (ShellExecuteEx(&shellExecuteInfo))
                    {
                        // �ȴ������н���ִ�����
                        WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
                        CloseHandle(shellExecuteInfo.hProcess);
                    }
                    else
                    {
                        // ִ��������ʧ��
                        MessageBox(NULL, L"�޷�ִ��������", L"����", MB_ICONERROR | MB_OK);
                    }
                }
            }
            else
            {
                // ���͹ر���Ϣ
                PostMessage(hWnd, WM_CLOSE, 0, 0);
            }
            
        }
    }
}


//��ں���
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // ָ��������
    wstring processName = L"msedge.exe";

    // ��ȡ����ID
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32W);
    if (Process32FirstW(snapshot, &processEntry))
    {
        do
        {
            wstring currentProcessName = processEntry.szExeFile;
            if (currentProcessName == processName)
            {
                processId = processEntry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapshot, &processEntry));
    }
    CloseHandle(snapshot);

    if (processId != 0)
    {
        // ��ȡ���ھ��
        HWND hWnd = FindWindowExW(NULL, NULL, NULL, NULL);
        unordered_set<HWND> processedWindows; // �洢�Ѵ���Ĵ��ھ��
        while (hWnd != NULL)
        {
            DWORD windowProcessId;
            GetWindowThreadProcessId(hWnd, &windowProcessId);

            if (windowProcessId == processId)
            {
                // �жϴ����Ƿ��Ѵ����
                if (processedWindows.find(hWnd) == processedWindows.end())
                {
                    ShowOrHideWindow(hWnd);  // ������
                    processedWindows.insert(hWnd);
                }
            }

            hWnd = FindWindowExW(NULL, hWnd, NULL, NULL);
        }
    }
    else
    {
       
    }

    return 0;
}
