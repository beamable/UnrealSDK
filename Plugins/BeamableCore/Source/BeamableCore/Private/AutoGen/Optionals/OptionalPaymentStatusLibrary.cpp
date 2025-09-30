

#include "AutoGen/Optionals/OptionalPaymentStatusLibrary.h"

FOptionalPaymentStatus UOptionalPaymentStatusLibrary::MakeOptional(EBeamPaymentStatus Value)
{
	FOptionalPaymentStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPaymentStatus UOptionalPaymentStatusLibrary::Conv_OptionalFromValue(EBeamPaymentStatus Value)
{
	FOptionalPaymentStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalPaymentStatusLibrary::HasValue(const FOptionalPaymentStatus& Optional, EBeamPaymentStatus& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamPaymentStatus UOptionalPaymentStatusLibrary::GetOptionalValue(const FOptionalPaymentStatus& Optional, EBeamPaymentStatus DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

