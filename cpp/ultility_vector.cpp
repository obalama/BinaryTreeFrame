#include "../include/ultility_vector.h"
vector<int> getVectorFormStdin(int len)
{
	vector<int>result(len,0);
	for(int i=0;i<len;++i)
	{
		cin>>result[i];
	}

	return result;
}

