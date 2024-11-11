#include "BossKey.h"
namespace fs = std::filesystem;

void MuteOn(wstring processName)
{
    if (!fs::exists("nircmd.exe"))
        return;
    LPCWSTR executableName = L"nircmd.exe";
    wstring operateName = L"muteappvolume";
    wstring stateName = L"1";
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();
    WCHAR executablePath[MAX_PATH];
    WCHAR programPath[MAX_PATH];

    GetModuleFileName(NULL, programPath, MAX_PATH);
    PathRemoveFileSpec(programPath);
    SetCurrentDirectory(programPath);
    wcscpy_s(executablePath, MAX_PATH, executableName);

    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shellExecuteInfo.lpVerb = L"open";
    shellExecuteInfo.lpFile = executablePath;
    shellExecuteInfo.lpParameters = Parameters;
    shellExecuteInfo.nShow = SW_HIDE;

    if (ShellExecuteEx(&shellExecuteInfo))
    {
        WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
        CloseHandle(shellExecuteInfo.hProcess);
    }
}

void MuteOff(wstring processName)
{
    if (!fs::exists("nircmd.exe"))
        return;
    LPCWSTR executableName = L"nircmd.exe";
    wstring operateName = L"muteappvolume";
    wstring stateName = L"0";
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();
    WCHAR executablePath[MAX_PATH];
    WCHAR programPath[MAX_PATH];

    GetModuleFileName(NULL, programPath, MAX_PATH);
    PathRemoveFileSpec(programPath);
    SetCurrentDirectory(programPath);
    wcscpy_s(executablePath, MAX_PATH, executableName);

    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shellExecuteInfo.lpVerb = L"open";
    shellExecuteInfo.lpFile = executablePath;
    shellExecuteInfo.lpParameters = Parameters;
    shellExecuteInfo.nShow = SW_HIDE;

    if (ShellExecuteEx(&shellExecuteInfo))
    {
        WaitForSingleObject(shellExecuteInfo.hProcess, INFINITE);
        CloseHandle(shellExecuteInfo.hProcess);
    }
}