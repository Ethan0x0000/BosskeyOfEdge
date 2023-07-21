#include "BossKey.h"

// 获取用户文件夹地址
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

// 将数组序列化至二进制文件
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
        MessageBox(NULL, L"创建配置文件失败", L"错误", MB_ICONERROR | MB_OK);
        return;
    }

    // 序列化数组大小
    size_t vectorSize = windowInfoArray.size();
    file.write(reinterpret_cast<const char*>(&vectorSize), sizeof(size_t));

    // 序列化数组节点
    for (const auto& windowInfo : windowInfoArray) {
        // 序列化窗口句柄（HWND）
        intptr_t hWndValue = reinterpret_cast<intptr_t>(windowInfo.hWnd);
        file.write(reinterpret_cast<const char*>(&hWndValue), sizeof(intptr_t));

        // 序列化窗口标题长度 (wstring)
        streamsize titleLength = windowInfo.title.length();
        file.write(reinterpret_cast<const char*>(&titleLength), sizeof(streamsize));

        // 序列化窗口标题 (wstring)
        file.write(reinterpret_cast<const char*>(windowInfo.title.c_str()), titleLength * sizeof(wchar_t));

        // 序列化窗口隐藏状态（bool）
        file.write(reinterpret_cast<const char*>(&windowInfo.isHide), sizeof(bool));

        // 序列化窗口最大化状态（bool）
        file.write(reinterpret_cast<const char*>(&windowInfo.isMaximized), sizeof(bool));
    }

    file.close();
}

// 从二进制文件中读取数组
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
        MessageBox(NULL, L"读取配置文件失败", L"错误", MB_ICONERROR | MB_OK);
        return windowInfoArray;
    }

    // 反序列化数组大小
    size_t vectorSize;
    file.read(reinterpret_cast<char*>(&vectorSize), sizeof(size_t));
    windowInfoArray.resize(vectorSize);

    // 反序列化数组节点
    for (auto& windowInfo : windowInfoArray) 
    {
        // 反序列化窗口句柄（HWND）
        intptr_t hWndValue;
        file.read(reinterpret_cast<char*>(&hWndValue), sizeof(intptr_t));
        windowInfo.hWnd = reinterpret_cast<HWND>(hWndValue);

        // 反序列化窗口标题长度 (wstring)
        streamsize titleLength;
        file.read(reinterpret_cast<char*>(&titleLength), sizeof(streamsize));

        // 反序列化窗口标题 (wstring)
        wstring title;
        title.resize(titleLength);
        file.read(reinterpret_cast<char*>(&title[0]), titleLength * sizeof(wchar_t));
        windowInfo.title = title;

        // 反序列化窗口隐藏状态（bool）
        file.read(reinterpret_cast<char*>(&windowInfo.isHide), sizeof(bool));

        // 反序列化窗口最大化状态（bool）
        file.read(reinterpret_cast<char*>(&windowInfo.isMaximized), sizeof(bool));
    }

    file.close();

    return windowInfoArray;
}