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
	ifstream fin(FILE_NAME, ios::in | ios::binary);
	if (fin.fail()) return 1;
	ofstream os("result.txt");
	MyReader mr(&os);


	while (!fin.eof())
	{
		mr.Read((uint8_t)fin.get());
	}

	cout << "All: " << to_string(mr.GetCountOfPackages()) << endl;
	cout << "Good: " << to_string(mr.GetCountOfPackages() - mr.GetCountOfBadPackages()) << endl;
	cout << "Bad: " << to_string(mr.GetCountOfBadPackages()) << endl;

	fin.close();
	os.close();

	return 0;
}

