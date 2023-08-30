

#include "AutoGen/Optionals/OptionalArrayOfTicketLibrary.h"

FOptionalArrayOfTicket UOptionalArrayOfTicketLibrary::MakeOptional(TArray<UTicket*> Value)
{
	FOptionalArrayOfTicket Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTicket UOptionalArrayOfTicketLibrary::Conv_OptionalFromValue(TArray<UTicket*> Value)
{
	FOptionalArrayOfTicket Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTicketLibrary::HasValue(const FOptionalArrayOfTicket& Optional, TArray<UTicket*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTicket*> UOptionalArrayOfTicketLibrary::GetOptionalValue(const FOptionalArrayOfTicket& Optional, TArray<UTicket*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

