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
        if (IsWindowVisible(hWnd) && GetWindowLong(hWnd, GWL_STYLE) & WS_VISIBLE)
        {
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
            ShowWindow(hWnd, SW_SHOW);

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
