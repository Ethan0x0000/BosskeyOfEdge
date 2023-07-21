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