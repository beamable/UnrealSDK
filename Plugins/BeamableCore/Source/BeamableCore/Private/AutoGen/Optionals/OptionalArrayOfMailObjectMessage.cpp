
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMailObjectMessage.h"

FOptionalArrayOfMailObjectMessage::FOptionalArrayOfMailObjectMessage()
{
	Val = TArray<UMailObjectMessage*>();
	IsSet = false;
}

FOptionalArrayOfMailObjectMessage::FOptionalArrayOfMailObjectMessage(TArray<UMailObjectMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfMailObjectMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfMailObjectMessage::Set(const void* Data)
{
	Val = *((TArray<UMailObjectMessage*>*)Data);
	IsSet = true;
}