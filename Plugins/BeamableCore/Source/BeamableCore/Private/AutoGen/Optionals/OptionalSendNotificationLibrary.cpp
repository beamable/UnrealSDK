

#include "AutoGen/Optionals/OptionalSendNotificationLibrary.h"

FOptionalSendNotification UOptionalSendNotificationLibrary::MakeOptional(USendNotification* Value)
{
	FOptionalSendNotification Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSendNotification UOptionalSendNotificationLibrary::Conv_OptionalFromValue(USendNotification* Value)
{
	FOptionalSendNotification Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalSendNotificationLibrary::HasValue(const FOptionalSendNotification& Optional, USendNotification*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USendNotification* UOptionalSendNotificationLibrary::GetOptionalValue(const FOptionalSendNotification& Optional, USendNotification* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

