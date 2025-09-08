
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventsBasicInFlightMessage.h"

FOptionalArrayOfEventsBasicInFlightMessage::FOptionalArrayOfEventsBasicInFlightMessage()
{
	Val = TArray<UEventsBasicInFlightMessage*>();
	IsSet = false;
}

FOptionalArrayOfEventsBasicInFlightMessage::FOptionalArrayOfEventsBasicInFlightMessage(TArray<UEventsBasicInFlightMessage*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventsBasicInFlightMessage::GetAddr() const { return &Val; }

void FOptionalArrayOfEventsBasicInFlightMessage::Set(const void* Data)
{
	Val = *((TArray<UEventsBasicInFlightMessage*>*)Data);
	IsSet = true;
}