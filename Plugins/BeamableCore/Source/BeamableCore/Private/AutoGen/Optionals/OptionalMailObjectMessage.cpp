
#include "AutoGen/Optionals/OptionalMailObjectMessage.h"

FOptionalMailObjectMessage::FOptionalMailObjectMessage()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMailObjectMessage::FOptionalMailObjectMessage(UMailObjectMessage* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMailObjectMessage::GetAddr() const { return &Val; }

void FOptionalMailObjectMessage::Set(const void* Data)
{
	Val = *((UMailObjectMessage**)Data);
	IsSet = true;
}