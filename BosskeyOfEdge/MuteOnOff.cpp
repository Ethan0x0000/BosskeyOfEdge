#include "BossKey.h"


void MuteOn(wstring processName)
{
    LPCWSTR executableName = L"nircmd.exe";// ִ�ж���

    wstring operateName = L"muteappvolume";// ����
    wstring stateName = L"1";// ��������
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();

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
    shellExecuteInfo.lpParameters = Parameters;
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
        MessageBox(NULL, L"�޷�ִ�������У�����nircmd.exe��·����", L"����", MB_ICONERROR | MB_OK);
    }
}

// ȡ������
void MuteOff(wstring processName)
{
    LPCWSTR executableName = L"nircmd.exe";// ִ�ж���

    wstring operateName = L"muteappvolume";// ����
    wstring stateName = L"0";// ��������
    wstring parameters = operateName + L" " + processName + L" " + stateName;
    LPCWSTR Parameters = parameters.c_str();

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
    shellExecuteInfo.lpParameters = Parameters;
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
        MessageBox(NULL, L"�޷�ִ�������У�����nircmd.exe��·����", L"����", MB_ICONERROR | MB_OK);
    }
}