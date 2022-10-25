

#include "AutoGen/Optionals/OptionalWebhookCometLibrary.h"

FOptionalWebhookComet UOptionalWebhookCometLibrary::MakeOptional(UWebhookComet* Value)
{
	FOptionalWebhookComet Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalWebhookComet UOptionalWebhookCometLibrary::Conv_OptionalFromValue(UWebhookComet* Value)
{
	FOptionalWebhookComet Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalWebhookCometLibrary::HasValue(const FOptionalWebhookComet& Optional, UWebhookComet*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UWebhookComet* UOptionalWebhookCometLibrary::GetOptionalValue(const FOptionalWebhookComet& Optional, UWebhookComet* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

