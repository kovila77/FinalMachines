#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include "MyReader.h"
//#include <fstream>

using namespace std;

const wchar_t* FILE_NAME = _T("data_no_error.bin");


int main()
{
	setlocale(LC_ALL, "Russian");

	HANDLE hFile = CreateFileW(
		FILE_NAME,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "fileMappingCreate - CreateFile failed, fname = " << std::endl;
		return 1;
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		std::cerr << "fileMappingCreate - GetFileSize failed " << std::endl;
		CloseHandle(hFile);
		return 1;
	}
	uint8_t* buff = new uint8_t[dwFileSize + 1];
	ZeroMemory(buff, dwFileSize + 1);
	if (!ReadFile(hFile, buff, dwFileSize, NULL, NULL))
	{
		std::cout << "ReadFile error" << std::endl;
		delete[]buff;
		CloseHandle(hFile);
		return 1;
	}

	ofstream os("result.txt");
	MyReader mr(&os);

	for (int i = 0; i < dwFileSize + 1; i++)
	{
		mr.Read(buff[i]);
	}

	cout << "All: " << to_string(mr.GetCountOfPackages()) << endl;
	cout << "Good: " << to_string(mr.GetCountOfPackages() - mr.GetCountOfBadPackages()) << endl;
	cout << "Bad: " << to_string(mr.GetCountOfBadPackages()) << endl;

	os.close();
	CloseHandle(hFile);
	delete[]buff;

	return 0;
}

