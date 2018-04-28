#include "init_arr.h"
array<char[14], 10> fillJump(string path, string ext)
{
	array< char[14], 10> arr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 10; i++)
		strcpy(arr[i], (path + to_string(i + 1) + ext).c_str());
	return arr;
}

array< char[14], 15> fillWalk(string path, string ext)
{
	array< char[14], 15> arr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 15; i++)
		strcpy(arr[i], (path + to_string(i + 1) + ext).c_str());

	return arr;
}

