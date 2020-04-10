#include "MyReader.h"
#include <string>
#include <iomanip>
using namespace std;

//bool MyReader::ReadInt16(int16_t& i, uint8_t& bt)
//{
//	counter++;
//	i = i << 8 + bt;
//	if (counter > 1)
//	{
//		counter = 0;
//		return true;
//	}
//	return false;
//}

void MyReader::Read(uint8_t bt)
{
	switch (status)
	{
	case ReadingSyncByte:
		if (bt == 0xAA) status = ReadingSecondSyncByte;
		break;
	case ReadingSecondSyncByte:
		status = (bt == 0xAA) ? ReadingLen : ReadingSyncByte;
		break;
	case ReadingLen:
		messageLength = bt;
		status = ReadingId;
		break;
	case ReadingId:
		status = (bt == 0x87) ? ReadingInt32 : ReadingSyncByte;
		//counter = 0;
		//buff[counter] = bt;
		//counter++;
		break;
	case ReadingInt32:
		buff[counter] = bt;
		counter++;
		if (sizeof(int32_t) * COUNT_INT32 <= counter)
		{
			status = ReadingInt16;
			prevCounter = counter;
		}
		break;
	case ReadingInt16:
		buff[counter] = bt;
		counter++;
		if (prevCounter + sizeof(int16_t) * COUNT_INT16 <= counter)
		{
			status = ReadingUInt8;
			prevCounter = counter;
		}
		break;
	case ReadingUInt8:
		buff[counter] = bt;
		counter++;
		if (prevCounter + sizeof(uint8_t) * COUNT_UINT8 <= counter)
		{
			status = ReadingFirstCrc;
			counter = 0;
		}
		break;
	case ReadingFirstCrc:
		CRC = bt;
		status = ReadingSecondCrc;
		break;
	case ReadingSecondCrc:
		CRC = CRC << 8 + bt;
		WriteMessage();
		status = ReadingSyncByte;
		break;
	default:
		return;
		break;
	}
}

MyReader::MyReader(ostream* ostr)
{
	this->ostr = ostr;
	*ostr << setw(WIDTH) << "Ax";
	*ostr << setw(WIDTH) << "Ay";
	*ostr << setw(WIDTH) << "Az";
	*ostr << setw(WIDTH) << "Wx";
	*ostr << setw(WIDTH) << "Wy";
	*ostr << setw(WIDTH) << "Wz";
	*ostr << setw(WIDTH) << "Tax";
	*ostr << setw(WIDTH) << "Tay";
	*ostr << setw(WIDTH) << "Taz";
	*ostr << setw(WIDTH) << "Twx";
	*ostr << setw(WIDTH) << "Twy";
	*ostr << setw(WIDTH) << "Twz";
	*ostr << setw(WIDTH) << "S";
	*ostr << setw(WIDTH) << "Timestamp";
	*ostr << setw(WIDTH) << "Status";
	*ostr << setw(WIDTH) << "Number";
	*ostr << endl;
	buff = new uint8_t[sizeof(int32_t) * COUNT_INT32 + sizeof(int16_t) * COUNT_INT16 + sizeof(uint8_t) * COUNT_UINT8];
}

MyReaderState MyReader::GetStatus()
{
	return status;
}

void MyReader::WriteMessage()
{
	int32_t* p1 = (int32_t*)buff;
	for (int i = 0; i < COUNT_INT32; i++, p1++)
	{
		*ostr << setw(WIDTH) << to_string(*p1) << " ";
	}
	int16_t* p2 = (int16_t*)p1;
	for (int i = 0; i < COUNT_INT16; i++, p2++)
	{
		*ostr << setw(WIDTH) << to_string(*p2) << " ";
	}
	uint8_t* p3 = (uint8_t*)p2;
	for (int i = 0; i < COUNT_UINT8; i++, p3++)
	{
		*ostr << setw(WIDTH) << to_string(*p3) << " ";
	}
	*ostr << endl;
}
