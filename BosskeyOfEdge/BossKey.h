#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <Mmsystem.h>
#include <fstream>
#include <shellapi.h>
#include <shlwapi.h>
#include <locale>
#include <codecvt>
#include <Psapi.h>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <shlobj.h>
#include <filesystem>

#pragma comment(lib, "Shlwapi.lib")

using namespace std;

struct WindowInfo
{
    HWND hWnd;
    wstring title;
    bool isHide;
    bool isMaximized;
};

string wstring_to_string(const wstring&);

string GetUserDocumentsPath();
void SerializeWindowInfoArray(const vector<WindowInfo>&, string);
vector<WindowInfo> DeserializeWindowInfoArray(string);

vector<WindowInfo> GetvectorByName(const wstring&, const wstring&);

int IsAllHide(vector<WindowInfo>);
bool IsHua(wstring);


void MuteOn(const std::wstring& processName);
void MuteOff(const std::wstring& processName);


void ShowHideWindow(wstring, wstring);
