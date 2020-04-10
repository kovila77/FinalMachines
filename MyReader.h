#pragma once
#include <cstdint>
#include <ostream>

enum MyReaderState
{
	ReadingByte,
	ReadedSyncByte,
	ReadingLen,
	ReadingId,
	ReadingData,
	ReadingCrcAndCheckingMessage,
	WritingMessage,
};

class MyReader
{
public:
	MyReader(uint8_t*, int);

	void ReadPart();

	int GetBuffLength();
	int GetPosition();
	bool IsMessageReady();
	void WriteMessage(ostream& ostr);

private:
	uint8_t* buff;
	int buffLength;
	int position{ 0 };
	bool isMessageReady{ false };
	int32_t Ax;
	int32_t Ay;
	int32_t Az;
	int32_t Wx;
	int32_t Wy;
	int32_t Wz;
	int16_t Tax;
	int16_t Tay;
	int16_t Taz;
	int16_t Twx;
	int16_t Twy;
	int16_t Twz;
	int16_t S;
	int16_t Timestamp;
	int8_t Status;
	int8_t Number;
};