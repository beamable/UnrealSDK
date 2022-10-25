

#include "AutoGen/Optionals/OptionalGatewayLimitsLibrary.h"

FOptionalGatewayLimits UOptionalGatewayLimitsLibrary::MakeOptional(UGatewayLimits* Value)
{
	FOptionalGatewayLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalGatewayLimits UOptionalGatewayLimitsLibrary::Conv_OptionalFromValue(UGatewayLimits* Value)
{
	FOptionalGatewayLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalGatewayLimitsLibrary::HasValue(const FOptionalGatewayLimits& Optional, UGatewayLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UGatewayLimits* UOptionalGatewayLimitsLibrary::GetOptionalValue(const FOptionalGatewayLimits& Optional, UGatewayLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

