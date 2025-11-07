
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"

FOptionalArrayOfInFlightMessage::FOptionalArrayOfInFlightMessage()
{
	Val = TArray<UInFlightMessage*>();
	IsSet = false;
}

FOptionalArrayOfInFlightMessage::FOptionalArrayOfInFlightMessage(TArray<UInFlightMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfInFlightMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfInFlightMessage::Set(const void* Data)
{
	Val = *((TArray<UInFlightMessage*>*)Data);
	IsSet = true;
}