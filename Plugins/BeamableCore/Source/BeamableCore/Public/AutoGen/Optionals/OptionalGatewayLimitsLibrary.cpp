

#include "OptionalGatewayLimitsLibrary.h"

FOptionalGatewayLimits UOptionalGatewayLimitsLibrary::MakeOptionalGatewayLimits(UGatewayLimits* Value)
{
	FOptionalGatewayLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalGatewayLimits UOptionalGatewayLimitsLibrary::Conv_OptionalGatewayLimitsFromValue(UGatewayLimits* Value)
{
	FOptionalGatewayLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

