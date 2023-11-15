
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMessage.h"

FOptionalArrayOfMessage::FOptionalArrayOfMessage()
{
	Val = TArray<UMessage*>();
	IsSet = false;
}

FOptionalArrayOfMessage::FOptionalArrayOfMessage(TArray<UMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfMessage::Set(const void* Data)
{
	Val = *((TArray<UMessage*>*)Data);
	IsSet = true;
}