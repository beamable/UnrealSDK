

#include "OptionalSendNotificationLibrary.h"

FOptionalSendNotification UOptionalSendNotificationLibrary::MakeOptionalSendNotification(USendNotification* Value)
{
	FOptionalSendNotification Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSendNotification UOptionalSendNotificationLibrary::Conv_OptionalSendNotificationFromValue(USendNotification* Value)
{
	FOptionalSendNotification Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

