#pragma once
#include <ostream>
#include <cstdint>

using namespace std;

enum MyReaderState
{
	ReadingSyncByte,
	ReadingSecondSyncByte,
	ReadingLen,
	ReadingId,
	ReadingAx,
	ReadingAy,
	ReadingAz,
	ReadingWx,
	ReadingWy,
	ReadingWz,
	ReadingTax,
	ReadingTay,
	ReadingTaz,
	ReadingTwx,
	ReadingTwy,
	ReadingTwz,
	ReadingS,
	ReadingTimestamp,
	ReadingStatus,
	ReadingNumber,
	ReadingFirstCrc,
	ReadingSecondCrc,
	//End
};

class MyReader
{
public:
	int GetStatus();
	void Read(uint8_t bt);

private:
	int counter{ 0 };
	void WriteMessage(ostream& ostr);
	MyReaderState status{ ReadingSyncByte };
	uint8_t messageLength;
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
	int16_t CRC;
	bool ReadInt32(int32_t& i, uint8_t& bt);
	bool ReadInt16(int16_t& i, uint8_t& bt);
};