
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMailBasicMessage.h"

FOptionalMailBasicMessage::FOptionalMailBasicMessage()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMailBasicMessage::FOptionalMailBasicMessage(UMailBasicMessage* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMailBasicMessage::GetAddr() const { return &Val; }

void FOptionalMailBasicMessage::Set(const void* Data)
{
	Val = *((UMailBasicMessage**)Data);
	IsSet = true;
}