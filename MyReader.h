#pragma once
#include <iostream>
#include <cstdint>

using namespace std;

enum MyReaderState
{
	ReadingSyncByte,
	ReadingSecondSyncByte,
	ReadingLen,
	ReadingId,
	ReadingInt32,
	ReadingInt16,
	ReadingUInt8,
	ReadingFirstCrc,
	ReadingSecondCrc,
	//End
};

class MyReader
{
public:
	MyReader(ostream* ostr);
	MyReaderState GetStatus();
	void Read(uint8_t bt);

private:
	const int COUNT_INT32 = 6;
	const int COUNT_INT16 = 8;
	const int COUNT_UINT8 = 2;
	const int WIDTH = 7;
	ostream* ostr;
	int counter{ 0 };
	int prevCounter{ 0 };
	int countOfPackages{ 0 };
	int countOfBadPackages{0};
	void WriteMessage();
	MyReaderState status{ ReadingSyncByte };
	uint8_t messageLength;
	int16_t CRC;
	//bool ReadInt16(int16_t& i, uint8_t& bt);
	uint8_t* buff;
};