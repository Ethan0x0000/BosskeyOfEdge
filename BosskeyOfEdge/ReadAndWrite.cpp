#include "BossKey.h"

// ��ȡ�û��ļ��е�ַ
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

// ���������л����������ļ�
void SerializeWindowInfoArray(const vector<WindowInfo>& windowInfoArray, string filename) 
{
    string folderPath = GetUserDocumentsPath() + "BossKeyFile";
    if (!filesystem::exists(folderPath)) 
    {
        filesystem::create_directory(folderPath);
    }
    string filePath = folderPath + "\\" + filename;

    ofstream file(filePath, ios::binary);
    if (!file) 
    {
        MessageBox(NULL, L"���������ļ�ʧ��", L"����", MB_ICONERROR | MB_OK);
        return;
    }

    // ���л������С
    size_t vectorSize = windowInfoArray.size();
    file.write(reinterpret_cast<const char*>(&vectorSize), sizeof(size_t));

    // ���л�����ڵ�
    for (const auto& windowInfo : windowInfoArray) {
        // ���л����ھ����HWND��
        intptr_t hWndValue = reinterpret_cast<intptr_t>(windowInfo.hWnd);
        file.write(reinterpret_cast<const char*>(&hWndValue), sizeof(intptr_t));

        // ���л����ڱ��ⳤ�� (wstring)
        streamsize titleLength = windowInfo.title.length();
        file.write(reinterpret_cast<const char*>(&titleLength), sizeof(streamsize));

        // ���л����ڱ��� (wstring)
        file.write(reinterpret_cast<const char*>(windowInfo.title.c_str()), titleLength * sizeof(wchar_t));

        // ���л���������״̬��bool��
        file.write(reinterpret_cast<const char*>(&windowInfo.isHide), sizeof(bool));

        // ���л��������״̬��bool��
        file.write(reinterpret_cast<const char*>(&windowInfo.isMaximized), sizeof(bool));
    }

    file.close();
}

// �Ӷ������ļ��ж�ȡ����
vector<WindowInfo> DeserializeWindowInfoArray(string filename) 
{
    string folderPath = GetUserDocumentsPath() + "BossKeyFile";
    if (!filesystem::exists(folderPath))
    {
        filesystem::create_directory(folderPath);
    }
    string filePath = folderPath + "\\" + filename;

    vector<WindowInfo> windowInfoArray;

    ifstream file(filePath, ios::binary);
    if (!file) 
    {
        MessageBox(NULL, L"��ȡ�����ļ�ʧ��", L"����", MB_ICONERROR | MB_OK);
        return windowInfoArray;
    }

    // �����л������С
    size_t vectorSize;
    file.read(reinterpret_cast<char*>(&vectorSize), sizeof(size_t));
    windowInfoArray.resize(vectorSize);

    // �����л�����ڵ�
    for (auto& windowInfo : windowInfoArray) 
    {
        // �����л����ھ����HWND��
        intptr_t hWndValue;
        file.read(reinterpret_cast<char*>(&hWndValue), sizeof(intptr_t));
        windowInfo.hWnd = reinterpret_cast<HWND>(hWndValue);

        // �����л����ڱ��ⳤ�� (wstring)
        streamsize titleLength;
        file.read(reinterpret_cast<char*>(&titleLength), sizeof(streamsize));

        // �����л����ڱ��� (wstring)
        wstring title;
        title.resize(titleLength);
        file.read(reinterpret_cast<char*>(&title[0]), titleLength * sizeof(wchar_t));
        windowInfo.title = title;

        // �����л���������״̬��bool��
        file.read(reinterpret_cast<char*>(&windowInfo.isHide), sizeof(bool));

        // �����л��������״̬��bool��
        file.read(reinterpret_cast<char*>(&windowInfo.isMaximized), sizeof(bool));
    }

    file.close();

    return windowInfoArray;
}