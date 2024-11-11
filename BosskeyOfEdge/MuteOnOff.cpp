#include "BossKey.h"
#include <windows.h>
#include <filesystem>
#include <shlwapi.h>
#include <string>


void MuteOn(const std::wstring& processName)
{
    LPCWSTR executableName = L"nircmd.exe";
    std::wstring operateName = L"muteappvolume";
    std::wstring stateName = L"1";
    std::wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();
    WCHAR executablePath[MAX_PATH];
    WCHAR programPath[MAX_PATH];

    GetModuleFileName(NULL, programPath, MAX_PATH);
    PathRemoveFileSpec(programPath);
    SetCurrentDirectory(programPath);
    wcscpy_s(executablePath, MAX_PATH, executableName);

    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI; // ½ûÓÃ´íÎóµ¯´°
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

void MuteOff(const std::wstring& processName)
{
    LPCWSTR executableName = L"nircmd.exe";
    std::wstring operateName = L"muteappvolume";
    std::wstring stateName = L"0";
    std::wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();
    WCHAR executablePath[MAX_PATH];
    WCHAR programPath[MAX_PATH];

    GetModuleFileName(NULL, programPath, MAX_PATH);
    PathRemoveFileSpec(programPath);
    SetCurrentDirectory(programPath);
    wcscpy_s(executablePath, MAX_PATH, executableName);

    SHELLEXECUTEINFO shellExecuteInfo = { 0 };
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI; // ½ûÓÃ´íÎóµ¯´°
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
