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
        wstring Target = L"���л�";
        size_t len1 = title.length();
        size_t len2 = Target.length();
        // ���ѭ������1�����п��ܵ��Ӵ�
        for (size_t i = 0; i < len1; ++i)
        {
            // �ڲ�ѭ������2�����п��ܵ��Ӵ�
            for (size_t j = 0; j < len2; ++j)
            {
                size_t len = 0;
                // ����i��ʼ��1�Ӵ��Ƿ����j��ʼ��2�Ӵ���ͬ
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