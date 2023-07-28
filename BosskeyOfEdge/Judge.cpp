#include "BossKey.h"

int IsAllHide(vector<WindowInfo> windowsvector)
{
	int i = 0, sum = 0;
	for (const WindowInfo& window : windowsvector)
	{
		if (window.isHide)
		{
			sum++;
		}
		i++;
	}
	if (sum == 0)
	{
		return -1;
	}
	else if (sum == i)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

bool IsHua(wstring title)
{
    if (title.length() == 4)
    {
        wstring Target = L"画中画";
        size_t len1 = title.length();
        size_t len2 = Target.length();
        // 外层循环遍历1的所有可能的子串
        for (size_t i = 0; i < len1; ++i)
        {
            // 内层循环遍历2的所有可能的子串
            for (size_t j = 0; j < len2; ++j)
            {
                size_t len = 0;
                // 检查从i开始的1子串是否与从j开始的2子串相同
                while (i + len < len1 && j + len < len2 && title[i + len] == Target[j + len])
                {
                    ++len;
                }

                if (len == 3)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}