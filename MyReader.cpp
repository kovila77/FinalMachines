#include "MyReader.h"
//#include <ostream>
using namespace std;

bool MyReader::ReadInt32(int32_t& i, uint8_t& bt)
{
	counter++;
	i = i << 8 + bt;
	if (counter > 3)
	{
		counter = 0;
		return true;
	}
	return false;
}

bool MyReader::ReadInt16(int16_t& i, uint8_t& bt)
{
	counter++;
	i = i << 8 + bt;
	if (counter > 1)
	{
		counter = 0;
		return true;
	}
	return false;
}

void MyReader::Read(uint8_t bt)
{
	switch (status)
	{
	case ReadingSyncByte:
		if (bt == 0xAA) status = ReadingSecondSyncByte;
		break;
	case ReadingSecondSyncByte:
		status = (bt == 0xAA) ? ReadingSecondSyncByte : ReadingSyncByte;
		break;
	case ReadingLen:
		messageLength = bt;
		break;
	case ReadingId:
		status = (bt == 0x87) ? ReadingAx : ReadingSyncByte;
		break;
	case ReadingAx:
		if (ReadInt32(Ax, bt)) status = ReadingAy;
		break;
	case ReadingAy:
		if (ReadInt32(Ay, bt)) status = ReadingAz;
		break;
	case ReadingAz:
		if (ReadInt32(Az, bt)) status = ReadingWx;
		break;
	case ReadingWx:
		if (ReadInt32(Wx, bt)) status = ReadingWy;
		break;
	case ReadingWy:
		if (ReadInt32(Wy, bt)) status = ReadingWz;
		break;
	case ReadingWz:
		if (ReadInt32(Wz, bt)) status = ReadingTax;
		break;
	case ReadingTax:
		if (ReadInt16(Tax, bt)) status = ReadingTay;
		break;
	case ReadingTay:
		if (ReadInt16(Tay, bt)) status = ReadingTaz;
		break;
	case ReadingTaz:
		if (ReadInt16(Taz, bt)) status = ReadingTwx;
		break;
	case ReadingTwx:
		if (ReadInt16(Twx, bt)) status = ReadingTwy;
		break;
	case ReadingTwy:
		if (ReadInt16(Twy, bt)) status = ReadingTwz;
		break;
	case ReadingTwz:
		if (ReadInt16(Twz, bt)) status = ReadingS;
		break;
	case ReadingS:
		if (ReadInt16(S, bt)) status = ReadingTimestamp;
		break;
	case ReadingTimestamp:
		if (ReadInt16(Timestamp, bt)) status = ReadingStatus;
		break;
	case ReadingStatus:
		Status = bt;
		status = ReadingNumber;
		break;
	case ReadingNumber:
		Number = bt;
		status = ReadingFirstCrc;
		break;
	case ReadingFirstCrc:

		break;
	case ReadingSecondCrc:

		break;
	default:
		return;
		break;
	}
}


int MyReader::GetStatus()
{
	return status;
}

void MyReader::WriteMessage(ostream& ostr)
{
	ostr << Ax
		<< " " << Ay
		<< " " << Az
		<< " " << Wx
		<< " " << Wy
		<< " " << Wz
		<< " " << Tax
		<< " " << Tay
		<< " " << Taz
		<< " " << Twx
		<< " " << Twy
		<< " " << Twz
		<< " " << S
		<< " " << Timestamp
		<< " " << Status
		<< " " << Number << endl;
}
