#include "BossKey.h"


void MuteOn(wstring processName)
{
    LPCWSTR executableName = L"nircmd.exe";// 执行对象

    wstring operateName = L"muteappvolume";// 操作
    wstring stateName = L"1";// 操作类型
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();

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
    shellExecuteInfo.lpParameters = Parameters;
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
        MessageBox(NULL, L"无法执行命令行，请检查nircmd.exe的路径。", L"错误", MB_ICONERROR | MB_OK);
    }
}

// 取消静音
void MuteOff(wstring processName)
{
    LPCWSTR executableName = L"nircmd.exe";// 执行对象

    wstring operateName = L"muteappvolume";// 操作
    wstring stateName = L"0";// 操作类型
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();

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
    shellExecuteInfo.lpParameters = Parameters;
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
        MessageBox(NULL, L"无法执行命令行，请检查nircmd.exe的路径。", L"错误", MB_ICONERROR | MB_OK);
    }
}