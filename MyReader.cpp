#include "MyReader.h"
#include <ostream>
#define NEXT  << " " <<
using namespace std;

MyReader::MyReader(uint8_t* buff, int length)
{
	this->buff = buff;
	this->buffLength = length;
}

void MyReader::ReadPart()
{

}

int MyReader::GetBuffLength()
{
	return buffLength;
}

int MyReader::GetPosition()
{
	return position;
}

bool MyReader::IsMessageReady()
{
	return isMessageReady;
}

void MyReader::WriteMessage(ostream& ostr)
{
	ostr << Ax
		NEXT Ay
		NEXT Az
		NEXT Wx
		NEXT Wy
		NEXT Wz
		NEXT Tax
		NEXT Tay
		NEXT Taz
		NEXT Twx
		NEXT Twy
		NEXT Twz
		NEXT S
		NEXT Timestamp
		NEXT Status
		NEXT Number << endl;
	isMessageReady = false;
}
