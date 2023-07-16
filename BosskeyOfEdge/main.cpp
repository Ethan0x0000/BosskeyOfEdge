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

//隐藏或者显示窗口
void ShowOrHideWindow(HWND hWnd)
{


    wstring targetClassName = L"Chrome_WidgetWin_1";  // 目标窗口类名,这里为Edge的主界面类名，增强判定

    // 获取窗口类名
    wchar_t className[256];
    GetClassNameW(hWnd, className, 256);

    // 检查窗口类名是否与目标类名匹配
    wstring currentClassName = className;
    if (currentClassName == targetClassName)
    {
        if (IsWindowVisible(hWnd) && GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)
        {
            // 隐藏窗口
            ShowWindow(hWnd, SW_HIDE);

            // 窗口静音
            LPCWSTR executableName = L"nircmd.exe";
            LPCWSTR parameters = L"muteappvolume msedge.exe 1";// 1表示静音，0表示取消静音

            WCHAR executablePath[MAX_PATH];
            WCHAR programPath[MAX_PATH];

            // 获取当前程序的目录路径
            GetModuleFileName(NULL, programPath, MAX_PATH);
            PathRemoveFileSpec(programPath);

            // 设置当前目录为程序的目录路径
            SetCurrentDirectory(programPath);

            // 使用相对路径获取可执行文件的位置
            wcscpy_s(executablePath, MAX_PATH, executableName);

            SHELLEXECUTEINFO shellExecuteInfo = { 0 };
            shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellExecuteInfo.lpVerb = L"open";
            shellExecuteInfo.lpFile = executablePath;
            shellExecuteInfo.lpParameters = parameters;
            shellExecuteInfo.nShow = SW_HIDE;  // 隐藏窗口

            if (ShellExecuteEx(&shellExecuteInfo))
            {
                // 等待命令行进程执行完毕
                WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
                CloseHandle(shellExecuteInfo.hProcess);
            }
            else
            {
                // 执行命令行失败
                MessageBox(NULL, L"无法执行命令行", L"错误", MB_ICONERROR | MB_OK);
            }
        }
        else
        {
            // 显示窗口
            ShowWindow(hWnd, SW_SHOW);

            // 窗口取消静音
            LPCWSTR executableName = L"nircmd.exe";
            LPCWSTR parameters = L"muteappvolume msedge.exe 0";

            WCHAR executablePath[MAX_PATH];
            WCHAR programPath[MAX_PATH];

            // 获取当前程序的目录路径
            GetModuleFileName(NULL, programPath, MAX_PATH);
            PathRemoveFileSpec(programPath);

            // 设置当前目录为程序的目录路径
            SetCurrentDirectory(programPath);

            // 使用相对路径获取可执行文件的位置
            wcscpy_s(executablePath, MAX_PATH, executableName);

            SHELLEXECUTEINFO shellExecuteInfo = { 0 };
            shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellExecuteInfo.lpVerb = L"open";
            shellExecuteInfo.lpFile = executablePath;
            shellExecuteInfo.lpParameters = parameters;
            shellExecuteInfo.nShow = SW_HIDE;  // 隐藏窗口

            if (ShellExecuteEx(&shellExecuteInfo))
            {
                // 等待命令行进程执行完毕
                WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
                CloseHandle(shellExecuteInfo.hProcess);
            }
            else
            {
                // 执行命令行失败
                MessageBox(NULL, L"无法执行命令行", L"错误", MB_ICONERROR | MB_OK);
            }
        }
    }
}


//入口函数
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 指定进程名
    wstring processName = L"msedge.exe";

    // 获取进程ID
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
        // 获取窗口句柄
        HWND hWnd = FindWindowExW(NULL, NULL, NULL, NULL);
        unordered_set<HWND> processedWindows; // 存储已处理的窗口句柄
        while (hWnd != NULL)
        {
            DWORD windowProcessId;
            GetWindowThreadProcessId(hWnd, &windowProcessId);

            if (windowProcessId == processId)
            {
                // 判断窗口是否已处理过
                if (processedWindows.find(hWnd) == processedWindows.end())
                {
                    ShowOrHideWindow(hWnd);  // 处理窗口
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
