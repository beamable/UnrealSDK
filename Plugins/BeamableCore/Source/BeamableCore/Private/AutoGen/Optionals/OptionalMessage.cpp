
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMessage.h"

FOptionalMessage::FOptionalMessage()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMessage::FOptionalMessage(UMessage* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMessage::GetAddr() const { return &Val; }

void FOptionalMessage::Set(const void* Data)
{
	Val = *((UMessage**)Data);
	IsSet = true;
}