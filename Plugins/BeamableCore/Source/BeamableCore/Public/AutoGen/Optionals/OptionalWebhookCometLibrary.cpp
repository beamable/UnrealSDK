

#include "OptionalWebhookCometLibrary.h"

FOptionalWebhookComet UOptionalWebhookCometLibrary::MakeOptionalWebhookComet(UWebhookComet* Value)
{
	FOptionalWebhookComet Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalWebhookComet UOptionalWebhookCometLibrary::Conv_OptionalWebhookCometFromValue(UWebhookComet* Value)
{
	FOptionalWebhookComet Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

